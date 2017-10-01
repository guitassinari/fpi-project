#include <iostream>
#include <fstream>
#include <QImage>
#include "jpeglib.h"

using namespace std;

class Image {
public:
  Image(const char * filePath); //Constructor
  void write(const char * filePath);
  QImage toQImage();
private:
  JSAMPLE * image;
  int width;
  int height;
  int depth;
  int pixelLineSize();
  int imageSize();
};
