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
  QImage getHistogram();
  void flipVertically();
  void flipHorizontally();
  void toGreyScale();
  void quantize(int shadeNumbers);
  void negative();
  void rotate();
private:
  JSAMPLE * image;
  JSAMPLE * histogram;
  int width;
  int height;
  int depth;
  int pixelLineSize();
  int imageSize();
};
