#include "tga.h"

#include <cassert>
#include <fstream>
#include <cmath>

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
			int width, bool log)
{
	assert(in.size() == (size_t)width*height);

	std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

	//Write the header
	o.put(0); //ID 
	o.put(0); //Color Map Type
	o.put(3); //uncompressed grayscale
	
	// color map
	o.put(0); 
	o.put(0);
	o.put(0); 
	o.put(0);
	o.put(0);
	
	//X origin
	o.put(0); 
	o.put(0); 

	//Y origin
	o.put(0); 
	o.put(0); 

	//width
	o.put((width & 0x00FF)); 
	o.put((width & 0xFF00) / 256); 
	
	//height
	o.put((height & 0x00FF));
	o.put((height & 0xFF00) / 256);
	
	//depth
	o.put(8); /* 8 bit bitmap */
	
	//descriptor
	o.put(0);

	//get min and max
	double min = INFINITY; 
	for(uint32_t ii = 0 ; ii < in.size() ; ii++) 
		min = std::min(min, in[ii]);

	double max = -INFINITY;
	if(log) {
		for(uint32_t ii = 0 ; ii < in.size() ; ii++) 
			max = std::max(max, std::log(in[ii]-min+1));
		min = 0;
	} else {
		for(uint32_t ii = 0 ; ii < in.size() ; ii++) 
			max = std::max(max, in[ii]);
	}

	assert(min != max);
	
	//compress range to 0-255
	double range = max-min;

	if(range != 0) {
		//Write the pixel data
		if(log) {
			for(uint32_t ii=0; ii < in.size(); ii++)
				o.put((unsigned char)(255*std::log(in[ii]-min+1)/range));
		} else {
			for(uint32_t ii=0; ii < in.size(); ii++) 
				o.put((unsigned char)(255*(in[ii]-min)/range));
		}
	} else {
		for(uint32_t ii=0; ii < in.size(); ii++) 
			o.put(0);
	}

	//close the file
	o.close();
}

void writeTGA(std::string filename, const std::vector<float>& in, int height, 
			int width, bool log)
{
	assert(in.size() == (size_t)width*height);

	std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

	//Write the header
	o.put(0); //ID 
	o.put(0); //Color Map Type
	o.put(3); //uncompressed grayscale
	
	// color map
	o.put(0); 
	o.put(0);
	o.put(0); 
	o.put(0);
	o.put(0);
	
	//X origin
	o.put(0); 
	o.put(0); 

	//Y origin
	o.put(0); 
	o.put(0); 

	//width
	o.put((width & 0x00FF)); 
	o.put((width & 0xFF00) / 256); 
	
	//height
	o.put((height & 0x00FF));
	o.put((height & 0xFF00) / 256);
	
	//depth
	o.put(8); /* 8 bit bitmap */
	
	//descriptor
	o.put(0);

	//get min and max
	float min = INFINITY; 
	for(uint32_t ii = 0 ; ii < in.size() ; ii++) 
		min = std::min(min, in[ii]);

	float max = -INFINITY;
	if(log) {
		for(uint32_t ii = 0 ; ii < in.size() ; ii++) 
			max = std::max(max, std::log(in[ii]-min+1));
		min = 0;
	} else {
		for(uint32_t ii = 0 ; ii < in.size() ; ii++) 
			max = std::max(max, in[ii]);
	}

	assert(min != max);
	
	//compress range to 0-255
	double range = max-min;

	if(range != 0) {
		//Write the pixel data
		if(log) {
			for(uint32_t ii=0; ii < in.size(); ii++)
				o.put((unsigned char)(255*std::log(in[ii]-min+1)/range));
		} else {
			for(uint32_t ii=0; ii < in.size(); ii++) 
				o.put((unsigned char)(255*(in[ii]-min)/range));
		}
	} else {
		for(uint32_t ii=0; ii < in.size(); ii++) 
			o.put(0);
	}

	//close the file
	o.close();
}
