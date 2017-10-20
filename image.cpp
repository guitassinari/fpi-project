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

Image::Image(){
}

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
    QImage qimage(this->width, this->height, QImage::Format_RGB32);
    qimage.fill(0);
    int imageSize = this->imageSize();
    JSAMPLE * parsedRgb = (JSAMPLE*)malloc(sizeof(JSAMPLE)*3);

    for(int i = 0; i <imageSize; i += depth){
        JSAMPLE * rgb = &image[i];
        if(depth == 1){
            parsedRgb[0] = rgb[0];
            parsedRgb[1] = rgb[0];
            parsedRgb[2] = rgb[0];
        } else {
            parsedRgb[0] = rgb[0];
            parsedRgb[1] = rgb[1];
            parsedRgb[2] = rgb[2];
        }
        QRgb value = qRgb(parsedRgb[0], parsedRgb[1], parsedRgb[2]);
        int line = floor((i/depth)/width);
        int column = floor((i/depth)%width);
        qimage.setPixel(column, line, value);
    }
    free(parsedRgb);
    return qimage;
}

void Image::flipVertically(){
    char * buffer = (char *)malloc(this->pixelLineSize());
    for(int line = 0; line < floor(this->height/2); line++){
        int offset = line*this->pixelLineSize();
        int inverseOffset = (this->height-1-line)*this->pixelLineSize();
        memcpy(buffer, &this->image[offset], this->pixelLineSize());
        memcpy(&this->image[offset], &this->image[inverseOffset], this->pixelLineSize());
        memcpy(&this->image[inverseOffset], buffer, this->pixelLineSize());
    }
    free(buffer);
}

void Image::flipHorizontally(){
    char * buffer = (char *)malloc(this->depth);
    for(int line = 0; line < this->height; line++){
        for(int pixel = 0; pixel < floor(this->width/2); pixel++){
            int lineBeginning = line*this->pixelLineSize();
            int pixelOffset = lineBeginning+(pixel*this->depth);
            int inversePixelOffset = lineBeginning+((this->width-1-pixel)*this->depth);

            memcpy(buffer, &image[pixelOffset], depth);
            memcpy(&image[pixelOffset], &image[inversePixelOffset], depth);
            memcpy(&image[inversePixelOffset], buffer, depth);
        }
    }
}

void Image::toGreyScale(){
    int imageSize = this->imageSize();
    for(int i = 0; i < imageSize; i += depth){
        JSAMPLE * rgb = &image[i];
        unsigned char newValue = (unsigned char)(0.299*(unsigned int)rgb[0] + 0.587*(unsigned int)rgb[1] + 0.114*(unsigned int)rgb[2]);
        for(int j = 0; j < depth; j++){
            rgb[j] = newValue;
        }
    }
}

void Image::quantize(int shadesNumber){
    unsigned int shadeValues[shadesNumber];
    unsigned int initialValue = floor(255/(shadesNumber+1));
    for(int i = 1; i < shadesNumber+1; i++){
        shadeValues[i-1] = initialValue*i;
    }

    this->toGreyScale();

    int imageSize = this->imageSize();
    for(int i = 0; i < imageSize; i += depth){
        JSAMPLE * rgb = &image[i];
        unsigned int sample =  rgb[0];
        unsigned int value = 0;
        if(sample < shadeValues[0]){
            value = shadeValues[0];
        } else if(sample > shadeValues[shadesNumber]){
            value = shadeValues[shadesNumber];
        } else {
            for(int j = 1; j < shadesNumber-1; j++){
                if(sample >= shadeValues[j] && sample <= shadeValues[j+1]){
                    if(shadeValues[j+1]-sample >= initialValue){
                        value = shadeValues[j];
                    } else {
                        value = shadeValues[j+1];
                    }
                }

            }
        }

        for(int j = 0; j < depth; j++){
            rgb[j] = (unsigned char)value;
        }
    }
}

void Image::negative(){
    int imageSize = this->imageSize();
    for(int i = 0; i < imageSize; i += depth){
        JSAMPLE * rgb = &image[i];
        for(int j = 0; j < depth; j++){
            rgb[j] = (unsigned char)(255 - rgb[j]);
        }
    }
}

