#ifndef _Image_h
#define _Image_h

#include "image.h"

#endif

#include "jpeglib.h"
#include <cstdlib>
#include <cstring>
#include <QImage>

#define IMAGE_QUALITY 255

using namespace std;

Image::Image(const char * filePath){
  struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

  FILE * image;
  image = fopen(filePath, "rb");
  if(image == NULL){
    fprintf(stderr, "Não foi possível abrir %s\n", filePath);
    exit(1);
  }

  jpeg_stdio_src(&cinfo, image);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  this->width = cinfo.output_width;
  this->height = cinfo.output_height;
  this->depth = cinfo.output_components;

  int rowSize = this->pixelLineSize();

  JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, rowSize, 1);

  this->image = (JSAMPLE *) malloc(this->imageSize());

  while (cinfo.output_scanline < cinfo.output_height) {
    int offset = this->width * this->depth * cinfo.output_scanline;
    jpeg_read_scanlines(&cinfo, buffer, 1);
    memcpy(&this->image[offset], buffer[0], rowSize);
  }

  jpeg_finish_decompress(&cinfo);
}

void Image::write(const char * filePath){

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);

  jpeg_create_compress(&cinfo);

  FILE * destinationFile;
  destinationFile = fopen(filePath, "wb");
  if (destinationFile == NULL) {
    fprintf(stderr, "can't open %s\n", filePath);
    exit(1);
	}

  jpeg_stdio_dest(&cinfo, destinationFile);

  cinfo.image_width = this->width;
  cinfo.image_height = this->height;
  cinfo.input_components = this->depth;
  cinfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, IMAGE_QUALITY, TRUE);
  jpeg_start_compress(&cinfo, TRUE);

  int rowSize = this->pixelLineSize();
  JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, rowSize, 1);

  while (cinfo.next_scanline < cinfo.image_height) {
    memcpy(buffer[0], &this->image[cinfo.next_scanline * rowSize], rowSize);
    jpeg_write_scanlines(&cinfo, buffer, 1);
  }

  jpeg_finish_compress(&cinfo);

  fclose(destinationFile);

  jpeg_destroy_compress(&cinfo);
}

int Image::pixelLineSize(){
  return this->width * this->depth * sizeof(JSAMPLE);
}

int Image::imageSize(){
  return this->pixelLineSize() * this->height;
}

QImage Image::toQImage(){
    QImage image(this->width, this->height, QImage::Format_RGB32);
    image.fill(0);
    for(int i = 0; i < this->height; i++){
        for(int j = 0; j < this->width; j++){
            unsigned char * rgb = &this->image[(i*this->pixelLineSize()) + (j*3)];
            QRgb value = qRgb(rgb[0], rgb[1], rgb[2]);
            image.setPixel(j, i, value);
        }
    }
    return image;
}

