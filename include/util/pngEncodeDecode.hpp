#ifndef PNGENCODEDECODE_H
#define PNGENCODEDECODE_H

// C++ standard headers
#include <vector>

// For Cell definition
#include <gillwald/geometry.hpp>

class Image {

public:

	// Constructs an image object that takes in the raw image data, width, and height of the image
	Image(std::vector<unsigned char> image, unsigned width, unsigned height): imageData_(image), width_(width), height_(height) {};

	// Constructs an image object that reads a png file and updates the object fields with the information
	Image(const char* filename){this->decode(filename);};

	// TODO: Casting operator for data to eigin matrix
	// operator Eigen::MatrixXi() const {};

	// Returns a vector of cells that indicate the pixel values that are greater than threshVal
	std::vector<geometry::Cell> threshold_Cell(int threshVal);

	// TODO: make function to write image (I think encode counts right?)
	void encode(const char* filename);

	void decode(const char* filename);

	std::vector<unsigned char> getImageData() {return this->imageData_;};	
	const unsigned& width(){return this->width_;};
	const unsigned& height(){return this->height_;};

private:

	std::vector<unsigned char> imageData_;
	unsigned width_;
	unsigned height_;

};
#endif