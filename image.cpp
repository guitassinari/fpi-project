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
    return;
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
  this->histogram = NULL;
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
    return;
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

void Image::rotate(){
    int imageSize = this->imageSize();

    //Changes coordinate sizes
    int newWidth = height;
    int newHeight = width;

    JSAMPLE * rotatedImage = (JSAMPLE*)malloc(imageSize);
    JSAMPLE * rotatedImageIterator = rotatedImage;

    int rotatedImageOffset = 0;
    int currentColumn = 0;
    int currentLine = 0;
    int newColumn = newWidth;
    int newLine = 0;
    for(int i = 0; i < imageSize; i += depth){
        rotatedImageOffset = (newLine*newWidth + newColumn)*depth;
        rotatedImageIterator = &rotatedImage[rotatedImageOffset];
        memcpy(rotatedImageIterator, &image[i], sizeof(JSAMPLE)*depth);

        currentColumn = (i/3) % (width);
        newLine = currentColumn;
        if(i > 0 && (i/3) % (width) == 0){
            currentLine++;
            newColumn--;
        }
    }

    width = newWidth;
    height = newHeight;
    free(image);
    image = rotatedImage;
}

QImage Image::getHistogram(){
    int imageSize = this->imageSize();
    int histogramValues[256];
    for(int i = 0; i < 256; i++){
        histogramValues[i] = 0;
    }

    int maxValue = 0;

    for(int i = 0; i < imageSize; i += depth){
      int greyValue = (int)image[i];
      histogramValues[greyValue] += 1;
      if(histogramValues[greyValue] > maxValue){
          maxValue = histogramValues[greyValue];
      }
    }

    float normalization = 256.0/maxValue;

    for(int i = 0; i < 256; i++){
        histogramValues[i] = (int)floor(histogramValues[i]*normalization);
    }


    int histogramSize = 256*256;
    if(this->histogram == NULL){
        this->histogram = (JSAMPLE *)malloc(sizeof(JSAMPLE) * histogramSize);
    }


    QImage qimage(256, 256, QImage::Format_RGB32);
    qimage.fill(0);

    int currentLine = 0;
    int currentColumn = 0;
    int value = 0;
    for(int i = 0; i < histogramSize; i++){
        currentLine = (int)floor(i/256);
        currentColumn = (int)i%256;
        if(histogramValues[currentColumn] >= (255-currentLine)){
            value = 0;
        } else {
            value = 255;
        }
        this->histogram[i] = value;
        QRgb rgbValue = qRgb(value, value, value);
        qimage.setPixel(currentColumn, currentLine, rgbValue);
    }


    return qimage;
}

void Image::enhanceBrightness(int bias){
    int imageSize = this->imageSize();
    unsigned char unsignedBias = (unsigned char)bias;
    JSAMPLE * iterator = image;
    for(int i = 0;i < imageSize; i++){
        iterator = &image[i];
        int newValue = *iterator + unsignedBias;
        if(newValue > 255){
            newValue = 255;
        }
        if(newValue < 0){
            newValue = 0;
        }
        *iterator = (unsigned char)newValue;
    }
}

void Image::enhanceContrast(double bias){
    int imageSize = this->imageSize();
    JSAMPLE * iterator = image;
    for(int i = 0;i < imageSize; i++){
        iterator = &image[i];
        int newValue = (int)floor((*iterator)*bias);
        if(newValue > 255){
            newValue = 255;
        }
        if(newValue < 0){
            newValue = 0;
        }
        *iterator = (unsigned char)newValue;
    }
}


void Image::convolute(float base[]){
    int imageSize = this->imageSize();
    for(int i = 0; i < imageSize; i+=depth){
        if(i < this->width || i > (height-1)*width*depth || i%(width*depth) == 0 || i%(width*depth) == ((width*depth)-depth)){
        } else {
            int upperPixel = i-width*depth;
            int lowerPixel = i+width*depth;
            for(int j = 0; j < depth; j++){
                float newValue = base[8]*image[upperPixel-depth+j]+base[7]*image[upperPixel+j]+base[6]*image[upperPixel+depth+j];
                newValue += base[5]*image[i-depth+j]+base[4]*image[i+j]+base[3]*image[i+depth+j];
                newValue += base[2]*image[lowerPixel-depth+j]+base[1]*image[lowerPixel+j]+base[0]*image[lowerPixel+depth+j];
                if(newValue > 255){
                    newValue = 255.0;
                } else if(newValue < 0){
                    newValue = 0.0;
                }
                int integerValue = (int)newValue;
                image[i+j] = integerValue;

            }

        }
    }
}
