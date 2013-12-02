#ifndef TGA_H
#define TGA_H

#include <vector>
#include <string>

/**
 * @brief Creates a TGA file with the data from the input vector. 
 *
 * Data in the input vector should be row-major (ie rows should be 
 * contiguous in memory). Number of rows = height, number of columns = width.
 *
 * @param filename	output file name *.tga
 * @param in		input vector, should be 2 dimensional, row major 
 * @param height	number of rows
 * @param width		number of columns
 * @param log		Perform log transform on data
 */
void writeTGA(std::string filename, const std::vector<double>& in, int height, 
			int width, bool log = false);
void writeTGA(std::string filename, const std::vector<float>& in, int height, 
			int width, bool log = false);

#endif
