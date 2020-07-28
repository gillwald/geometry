// Copyright 2020 Gillwald

// C++ Standard Library
#include <vector>

// Gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Code to test
#include "gillwald/geometry.hpp"

using ::testing::ElementsAre;
using ::testing::ElementsAreArray;

namespace geometry {

/**
* @brief Overloads the << operator to print out the Cells in a vector of cells
* @param os The ostream object
* @param pixels The vector of cells to be printed
* @returns reference to the ostream object
*/	
std::ostream& operator<<(std::ostream& os, const std::vector<Cell>& pixels){
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


/**
* @brief Overloads the == operator to allow equality check between pixel return of the overloaded bresenham function
* @param lhs The "cell" on the left side of the == operator
* @param rhs The cell on the right side of the == operator
* @returns boolean on if the x and y values of the pixels are equal
*/	
bool operator==(const std::vector<int> &lhs,const Cell &rhs) {
	return (lhs[0] == rhs.x) && (lhs[1] == rhs.y);
}


TEST(bresenham_conversion, overloaded_function_check){
	// GIVEN two endpoints
	const Cell start {1, -2};
	const Cell end {6, 8};

	// WHEN the pixels are produced via the two bresenham functions
	const auto pixels_1 = bresenham_conversion(start.x, start.y, end.x, end.y);
	const auto pixels_2 = bresenham_conversion(start, end);

	// THEN the two vectors should be the same size and be equal to each other
	EXPECT_EQ(pixels_1.size(), pixels_2.size());
	EXPECT_THAT(pixels_1, ElementsAreArray(pixels_2));

}

TEST(bresenham_conversion, front_and_back_cells) {
	// GIVEN horizontal line endpoints
	const Cell start {0,0};
	const Cell end {5,0};

	// WHEN the interpolated pixels are produced
	const auto pixels = bresenham_conversion(start, end);

	// THEN the resulting line should have 6 pixels and begin at (0,0) and end at (5,0)
	EXPECT_EQ(pixels.size(), 6);
	EXPECT_EQ(pixels.front(), Cell(0,0));
	EXPECT_EQ(pixels.back(), Cell(5,0));
}


TEST(bresenham_conversion, horz_line_going_right) {
	// GIVEN a horizontal line endpoints that go from left to right
	const Cell start {0,0};
	const Cell end {5,0};	

	// WHEN the interpolated pixels are produced
	const auto pixels = bresenham_conversion(start, end);
		
	// THEN the resulting line has 6 elements, which should be equal to the expected vector
	EXPECT_EQ(pixels.size(),6);
	const std::vector<Cell> expected{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));	
}

TEST(bresenham_conversion, horz_line_going_left) {
	// GIVEN a horizontal line endpoints that goes from right to left
	const Cell start {4,5};
	const Cell end {-1,5};	

	// WHEN the interpolated pixels are produced
	const auto pixels = bresenham_conversion(start, end);
		
	// THEN the resulting line has 6 elements, which should be equal to the expected vector
	EXPECT_EQ(pixels.size(),6);
	const std::vector<Cell> expected{{4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}, {-1, 5}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));	
}

TEST(bresenham_conversion, vert_line_going_up) {
	// GIVEN vertical line endpoints that go from bottom to top
	const Cell start {-2,-3};
	const Cell end {-2,2};	

	// WHEN the interpolated pixels are produced
	const auto pixels = bresenham_conversion(start, end);	

	// THEN the resulting line has 6 elements, which should be equal to the expected vector
	EXPECT_EQ(pixels.size(), 6);
	const std::vector<Cell> expected{{-2, -3}, {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));	
}

TEST(bresenham_conversion, vert_line_going_down) {
	// GIVEN vertical line endpoints that go from top to bottom
	const Cell start {1,2};
	const Cell end {1,-3};	

	// WHEN the pixels are interpolated from the endpoints
	const auto pixels = bresenham_conversion(start, end);	

	// THEN the resulting line has 6 elements, which should equal to the expected vector
	EXPECT_EQ(pixels.size(), 6);
	const std::vector<Cell> expected{{1, 2}, {1, 1}, {1, 0}, {1, -1}, {1, -2}, {1, -3}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));	
}

TEST(bresenham_conversion, point_check) {
	// GIVEN the endpoints of a point
	const Cell start {0,0};
	const Cell end {0,0};

	// WHEN the pixels are interpolated from the endpoints
	const auto pixels = bresenham_conversion(start, end);

	// THEN there should be one pixel produced, which should equal to the expected vector
	EXPECT_THAT(pixels.size(), 1);
	const std::vector<Cell> expected{{0,0}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));	
}

TEST(bresenham_conversion, line_going_up_and_right) {
	// GIVEN the endpoints of a line that are going to the up and right
	const Cell start {0,0};
	const Cell end {5,3};

	// WHEN the pixels are interpolated from the endpoints
	const auto pixels = bresenham_conversion(start, end);

	// THEN the resulting line has 6 elements and should equal the expected vector
	EXPECT_EQ(pixels.size(), 6);
	const std::vector<Cell> expected {{0, 0}, {1, 1}, {2, 1}, {3, 2}, {4, 2}, {5, 3}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));	
}

TEST(bresenham_conversion, line_going_down_and_left) {
	// GIVEN the endpoints of a line that is going down and to the left
	const Cell start {5,3};
	const Cell end {0,0};

	// WHEN the pixels are interpolated from the endpoints
	const auto pixels = bresenham_conversion(start, end);

	// THEN the resulting line has 6 elements and should equal the expected vector
	EXPECT_EQ(pixels.size(), 6);
	const std::vector<Cell> expected {{5, 3}, {4, 2}, {3, 2}, {2, 1}, {1, 1}, {0, 0}};
	EXPECT_THAT(pixels, ElementsAreArray(expected));
}

TEST(raytrace, point_check) {
	// GIVEN the endpoints of a point and a max length
	const Cell startPix = {0, 0};
	const Cell endPix = {0, 0};
	const int max_ray_length = 10; // This is an arbitrary number

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(startPix, endPix, max_ray_length);

	// THEN the resulting line should have one element equal to the expected vector
	EXPECT_EQ(pixels.size(), 1);	
	const std::vector<Cell> expected{{0, 0}};	
	EXPECT_THAT(pixels,ElementsAreArray(expected));
}

TEST(raytrace, horz_line_going_right) {
	// GIVEN the endpoints that go from of left to right and a max length
	const Cell start = {0, 0};
	const Cell end = {5, 0};
	const int max_length = 10; // This is an arbitrary number

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);	

	// THEN the resulting line should have 6 elements equal to the expected vector
	const std::vector<Cell> expected{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
	EXPECT_EQ(pixels.size(),(6));	
	EXPECT_THAT(pixels,ElementsAreArray(expected));
}

TEST(raytrace, horz_line_going_left) {
	// GIVEN the endpoints that go from right to left and a max length
	const Cell start = {4, 5};
	const Cell end = {-1, 5};
	const int max_length = 10; // This is an arbitrary number

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);	

	// THEN the resulting line should have 6 elements equal to the expected vector
	const std::vector<Cell> expected{{4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}, {-1, 5}};
	EXPECT_EQ(pixels.size(),(6));	
	EXPECT_THAT(pixels,ElementsAreArray(expected));
}

TEST(raytrace, vert_line_going_up) {
	// GIVEN the endpoints that go from bottom to top and a max length
	const Cell start {-2, -3};
	const Cell end {-2, 2};
	const int max_length = 10; // This is an arbitrary number

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);

	// THEN the resulting line should have 6 elements equal to the expected vector
	const std::vector<Cell> expected{{-2, -3}, {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}};
	EXPECT_EQ(pixels.size(),(6));	
	EXPECT_THAT(pixels,ElementsAreArray(expected));
}

TEST(raytrace, vert_line_going_down) {
	// GIVEN the endpoints that go from top to bottom and a max length
	const Cell start = {1, 2};
	const Cell end = {1,-3};
	const int max_length = 10; // This is an arbitrary number

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);

	// THEN the resulting line should have 6 elements equal to the expected vector
	const std::vector<Cell> expected{{1, 2}, {1, 1}, {1, 0}, {1, -1}, {1, -2}, {1, -3}};
	EXPECT_EQ(pixels.size(),(6));	
	EXPECT_THAT(pixels,ElementsAreArray(expected));
}

TEST(raytrace, max_ray_length_test) {
	// GIVEN the endpoints that produce a horizontal line and a max length of 3
	const Cell start = {0, 0};
	const Cell end = {5, 0};
	const int max_length = 3;

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);

	// THEN the resulting line should have 3 elements equal to the expected vector
	const std::vector<Cell> expected{{0, 0}, {1, 0}, {2, 0}};
	EXPECT_EQ(pixels.size(), 3);	
	EXPECT_THAT(pixels, ElementsAreArray(expected));
}

TEST(raytrace, zero_length) {
	// GIVEN the endpoints and a max length of 0, produce an empty container
	const Cell start = {0, 0};
	const Cell end = {5, 0};
	const int max_length = 0;

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);

	// THEN the resulting line should have 3 elements equal to the expected vector
	EXPECT_EQ(pixels.size(), 0);	
}

TEST(raytrace, negative_length) {
	// GIVEN the endpoints and a max length of 0, produce an empty container
	const Cell start = {0, 0};
	const Cell end = {5, 0};
	const int max_length = -5;

	// WHEN the interpolated pixels are produced
	const auto pixels = raytrace(start, end, max_length);

	// THEN the resulting line should have 3 elements equal to the expected vector
	EXPECT_EQ(pixels.size(), 0);	
}

}  // namespace geometry

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
