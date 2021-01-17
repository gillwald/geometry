#include <util/pngEncodeDecode.hpp>
#include <iostream>

// Lodepng file
#include <lodepng/lodepng.h>

namespace geometry {

  namespace utility {

    std::vector<Cell> Image::threshold_Cell(int threshVal) {
    	std::vector<Cell> threshVec;
    	int count = 0;
    	for (const auto& pixel : this->imageData_) {
    		if (pixel >= threshVal) {
    			threshVec.push_back({(count % (int)(this->width_)),(count / (int)(this->width_))});
    		}
    		count++;
    	}
    	return threshVec;
    }

    bool Image::encode(const char* filename) {
      //Encode the image
      // This will encode a grayscale image. Image is expected to be size width*height. 
      // Each value of image is expected to be from 0-255, and it rolls over
      unsigned error = lodepng::encode(filename, this->imageData_, this->width_, this->height_, LCT_GREY, 8);

      //if there's an error, display it
      if (error) {
      	std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
      	return false;
      } else {
      	return true;
      }
    }

    void Image::decode(const char* filename) {
      // decode the image as a grayscale vector of pixels, where each pixel ranges from 0-255x
      unsigned error = lodepng::decode(this->imageData_, this->width_, this->height_, filename, LCT_GREY, 8);

      //if there's an error, display it and return false
      if (error) {
        this->decodeFail_ = true;
      	std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;      	
      }
    }

  };

}