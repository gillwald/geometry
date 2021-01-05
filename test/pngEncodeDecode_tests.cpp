// C++ Standard Library
#include <vector>
#include <iostream>

// C Standard Library
#include <stdio.h>

// UNIX stuff?
#include <sys/stat.h>

// Gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// code to test
#include "util/pngEncodeDecode.hpp"

// Returns a vector that thresholds the image, i.e. pixel values that are greater than the threshold are set to 255, 
// if less than the value set to 0
// std::vector<unsigned char> threshold(int threshVal, std::vector<unsigned char> imageData) 
// {
// 	std::vector<unsigned char> threshVec;
// 	for (const auto& pixel : imageData) {
// 		if (pixel >= threshVal) {
// 			threshVec.push_back(255);
// 		} else {
// 			threshVec.push_back(0);
// 		}
// 	}
// 	return threshVec;
// }

std::ostream& operator<<(std::ostream& os, const std::vector<geometry::Cell>& pixels){
	os << "\n";
	for (const auto& pixel:pixels) {
		os << "(" << pixel.x << "," << pixel.y << ")\n";
	}
	os << "\n";
	return os;
}

// TODO: Make a test that checks if files are properly being written

// TODO: Make a test that checks if an image is properly encoding data 
// (Maybe make it loop through 0-255 twice? Make sure the height and width of the image are correct too?)

// TODO: Make an image that has certain pixels be above a threshold value, then write the image. 
// Read the image with the treshold and see which cells are output and compare them with the correct values

// TODO: 

// TEST(encode_test, file_existence){
// 	// PREPARING by deleting the file


// 	// GIVEN a file name


// 	// WHEN an image is encoded

// }

int main(int argc, char **argv) {
    // testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();

	const char* filename = argc > 1 ? argv[1] : "test_new.png";

	// unsigned width = 8, height = 8;
	// std::vector<unsigned char> image;
	// int bytesPerPix = 1;
	// image.resize(width * height * bytesPerPix); // 1 bytes per pixel
	// int count = 0;
	// for(unsigned y = 0; y < height; y++) {
	// 	for(unsigned x = 0; x < width; x++) {
	// 			count++;
	// 			image[(bytesPerPix * width * y) + (bytesPerPix * x) + 0] = x*y*4 - 1; // most significant
	// 		}
	// }

	// Image testImage(image, height, width);

	// testImage.encode(filename);

	Image testImage(filename);

	std::cout << testImage.threshold_Cell(140);

    return 0;
}