#include <util/pngEncodeDecode.hpp>
#include <iostream>

// Lodepng file
// #include "./../../third_party/lodepng/lodepng.h"
#include <lodepng/lodepng.h>

// Have two namespaces, geometry and utility i.e. have stuff in geometry namespacea nd put this stuff inside of the utility namespace

std::vector<geometry::Cell> Image::threshold_Cell(int threshVal) {
	std::vector<geometry::Cell> threshVec;
	int count = 0;
	for (const auto& pixel : this->imageData_) {
		if (pixel >= threshVal) {
			threshVec.push_back({(count % (int)(this->width_)),(count / (int)(this->width_))});
		}
		count++;
	}
	return threshVec;
}

// TODO: Return bool if image is written without errors
void Image::encode(const char* filename) {
  //Encode the image
  // This will encode a grayscale image. Image is expected to be size width*height. 
  // Each value of image is expected to be from 0-255, and it rolls over
  unsigned error = lodepng::encode(filename, this->imageData_, this->width_, this->height_, LCT_GREY, 8);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

// TODO: Return bool if decoded wiuthout errors
void Image::decode(const char* filename) {
  // decode the image as a grayscale vector of pixels, where each pixel ranges from 0-255x
  unsigned error = lodepng::decode(this->imageData_, this->width_, this->height_, filename, LCT_GREY, 8);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}