#pragma once // wtf is this

#include "util/lodepng.h"
// #include <Eigen/Dense>

class Image {

public:

	// Constructs an image object that takes in the raw image data, width, and height of the image
	Image(std::vector<unsigned char> image, unsigned width, unsigned height): imageData_(image), width_(width), height_(height) {};

	// Constructs an image object that reads a png file and updates the object fields with the information
	Image(const char* filename){this->decode(filename);};

	// TODO: Casting operator for data to eigin matrix
	// operator Eigen::MatrixXi() const {};

	// Returns a vector that thresholds the image, i.e. pixel values that are greater than the threshold are set to 255, 
	// if less than the value set to 0
	std::vector<unsigned char> threshold(int threshVal) 
	{
		std::vector<unsigned char> threshVec;
		for (const auto& pixel : this->imageData_) {
			if (pixel >= threshVal) {
				threshVec.push_back(255);
			} else {
				threshVec.push_back(0);
			}
		}
		return threshVec;
	}	

	// Returns a vector of cells that indicate the pixel values that are greater than threshVal
	// I know this isn't right, sorry Griz lol. Should I make like a template function or something?
	std::vector<Cell> threshold_Cell(int threshVal) 
	{
		std::vector<Cell> threshVec;
		int count = 0;
		for (const auto& pixel : this->imageData_) {
			if (pixel >= threshVal) {
				threshVec.push_back({(count % this->width_),(count / this->width_)});
			}
			count++;
		}
		return threshVec;
	}

	// TODO: make function to write image (I think encode counts right?)
	void encode(const char* filename) {
	  //Encode the image
	  // This will encode a grayscale image. Image is expected to be size width*height. 
	  // Each value of image is expected to be from 0-255, and it rolls over
	  unsigned error = lodepng::encode(filename, this->imageData_, this->width_, this->height_, LCT_GREY, 8);

	  //if there's an error, display it
	  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
	}

	void decode(const char* filename) {
	  // decode the image as a grayscale vector of pixels, where each pixel ranges from 0-255
	  unsigned error = lodepng::decode(this->imageData_, this->width_, this->height_, filename, LCT_GREY, 8);

	  //if there's an error, display it
	  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	std::vector<unsigned char> getImageData() {return this->imageData_;};	
	const unsigned& width(){return this->width_;};
	const unsigned& height(){return this->height_;};

private:

	std::vector<unsigned char> imageData_;
	unsigned width_;
	unsigned height_;

};