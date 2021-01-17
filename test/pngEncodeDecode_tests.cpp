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
#include <util/pngEncodeDecode.hpp>

using ::testing::ElementsAreArray;

namespace geometry {

	/**
	* @brief Overloads the << operator to print out the Cells in a vector of cells
	* @param os The ostream object
	* @param pixels The vector of cells to be printed
	* @returns reference to the ostream object
	*/	
	std::ostream& operator<<(std::ostream& os, const std::vector<geometry::Cell>& pixels){
		os << "\n";
		for (const auto& pixel:pixels) {
			os << "(" << pixel.x << "," << pixel.y << ")\n";
		}
		os << "\n";
		return os;
	}

	/**
	* @brief Overloads the == operator to allow equality check between two Cell objects
	* @param lhs The cell on the left side of the == operator
	* @param rhs The cell on the right side of the == operator
	* @returns boolean on if the x and y values of the Cell are equal
	*/	
	bool operator==(const Cell &lhs,const Cell &rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	namespace utility {		

		TEST(encode_test, file_existence){
			// GIVEN a file name
			const char* filename = "test.png";

			// PREPARE by checking if the file exists, and if so deleting the file
		    struct stat buffer;   
		    if (stat ("test.png", &buffer) == 0) {system("rm ./test.png");}

			// WHEN an image is encoded
			std::vector<unsigned char> imageData;
			unsigned width = 2, height = 2;
			imageData.resize(width * height);
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {
					imageData[(y*width) + x] = ((x+y)*64);
				}
			}

			Image testImage(imageData, height, width);

			const auto encFlag = testImage.encode(filename);

			// THEN check to see if the image was properly written
			ASSERT_TRUE(encFlag);

		}

		TEST(encode_decode_test, read_write) {
			// GIVEN a file name and some image data
			const char* filename = "test.png";

			std::vector<unsigned char> imageData;
			unsigned width = 128, height = 4;
			imageData.resize(width * height);
			int count = 0;
			for (unsigned y = 0; y < height; y++) {
				for (unsigned x = 0; x < width; x++) {
					imageData[count] = count % 256;
					count++;
				}
			}

			// PREPARE by checking if the file exists, and if so deleting the file
		    struct stat buffer;   
		    if (stat ("test.png", &buffer) == 0) {system("rm ./test.png");}

			// WHEN an image is succesfully encoded
		    Image encodeImage(imageData, width, height);

			const auto encFlag = encodeImage.encode(filename);

			// THEN check to see if the image was properly written
			ASSERT_TRUE(encFlag);

			// If the image was properly written then decode it
			Image decodeImage(filename);

			// Check to see if the image was properly decoded
			ASSERT_FALSE(decodeImage.getDecodeStatus());

			// Width check
			EXPECT_EQ(decodeImage.width(), 128);

			// Height check
			EXPECT_EQ(decodeImage.height(), 4);

			// Check to see if the decoded data matches the original data
			EXPECT_THAT(imageData, ElementsAreArray(decodeImage.getImageData()));

		}

		TEST(encode_decode_test, threshold_check) {
			// GIVEN a file name and some image data
			const char* filename = "test.png";

			unsigned width = 8, height = 8;
			std::vector<unsigned char> image;
			int bytesPerPix = 1;
			image.resize(width * height * bytesPerPix); // 1 bytes per pixel
			int count = 0;
			for(unsigned y = 0; y < height; y++) {
				for(unsigned x = 0; x < width; x++) {
						count++;
						image[(bytesPerPix * width * y) + (bytesPerPix * x) + 0] = x*y*4 - 1; // most significant
					}
			}

			// PREPARE by checking if the file exists, and if so deleting the file
		    struct stat buffer;   
		    if (stat ("test.png", &buffer) == 0) {system("rm ./test.png");}

			// WHEN an image is succesfully encoded
		    Image encodeImage(image, width, height);

			const auto encFlag = encodeImage.encode(filename);

			// THEN check to see if the image was properly written
			ASSERT_TRUE(encFlag);

			// If the image was properly written then decode it
			Image decodeImage(filename);

			// Check to see if the image was properly decoded
			ASSERT_FALSE(decodeImage.getDecodeStatus());

			// Width check
			EXPECT_EQ(decodeImage.width(), 8);

			// Height check
			EXPECT_EQ(decodeImage.height(), 8);

			// Check the cells returned by the threshold check
			const int threshVal = 139;
			const std::vector<Cell> expected{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {7, 5}, {0, 6}, {6, 6}, {7, 6}, {0, 7}, {5, 7}, {6, 7}, {7, 7}};
			EXPECT_THAT(decodeImage.threshold_Cell(threshVal), ElementsAreArray(expected));	

		}

	};

};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}