#include <iostream>
#include <fstream>
#include <QImage>
#include "jpeglib.h"

using namespace std;

class Image {
public:
  Image();
  Image(const char * filePath); //Constructor
  void write(const char * filePath);
  QImage toQImage();
  Image * flipVertically();
private:
  JSAMPLE * image;
  int width;
  int height;
  int depth;
  int pixelLineSize();
  int imageSize();
};
