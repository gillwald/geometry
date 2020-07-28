// Copyright 2020 Gillwald

#pragma once

// C++ Standard Library
#include <vector>

namespace geometry {

  /**
   * @brief Creates a Cell structure that contains X,Y coordinate
   * @param x X coordinate
   * @param y Y coordinate
   */	
	struct Cell {
	  Cell(int x, int y) : x(x),y(y) {};
	  int x; ///< The x coordinate of the cell
	  int y; ///< The y coordinate of the cell
	};

  /**
   * @brief Creates discretized line between two end points
   * @param x0 X coordinate of starting point
   * @param y0 Y coordinate of starting point
   * @param x1 X coordinate of ending point
   * @param y1 Y coordinate of ending point
   * @returns Pixel coordinates representing line
   */	
  [[nodiscard]] std::vector<std::vector<int>> bresenham_conversion(int x0, int y0, int x1, int y1);

  /**
   * @brief Creates discretized line between two end points
   * @param start The starting coordinate of the line
   * @param end The ending coordinate of the line
   * @returns Pixel coordinates representing line
   */	
  [[nodiscard]] std::vector<Cell> bresenham_conversion(const Cell &start, const Cell &end);

  /**
   * @brief Creates discretized line between two end points
   * @param start The starting coordinate of the line
   * @param end The ending coordinate of the line
   * @param max_length The maximum number of elements the returned vector should contain
   * @returns Pixel coordinates representing line
   */	  
  [[nodiscard]] std::vector<Cell> raytrace(const Cell& start, const Cell& end, int max_length);
}  // namespace geometry
