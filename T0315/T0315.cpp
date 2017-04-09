// T0315.cpp: 主要專案檔。

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h> // Needed for time function
#include <ctime> // Needed for time function
#include <stdlib.h> // Needed for the srand and rand functions
#include <stdio.h>
#include <windows.h>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <malloc.h>
#include <string>
#define cimg_use_jpeg
#include "CImg.h"
using namespace cimg_library;

using namespace std;

using namespace System;
void testfunc();

int main(int argc, char* argv[])
{
	//cout << "argc: " << argc << endl;
	//if (argc > 0)
	//{
	//	for (int i = 0 ; i < argc ; i++)
	//	{
	//		cout << "argv[" << i << "] = " << argv[i] << endl;;
	//	}
	//}
	testfunc();
	system("pause");
    return 0;
}

void testfunc()
{
	
	char filename[] = "IMG_7626.jpg";
	//char filename[] = "unnamed.jpg";

	CImg<unsigned char> img(filename);
	CImg<unsigned char> img_orig(filename);

	//CImg<unsigned char> img("unnamed.jpg");

	int width = img.width();
	int height = img.height();
	unsigned char* r_channel = img.data(0, 0, 0, 0);
	unsigned char* g_channel = img.data(0, 0, 0, 1);
	unsigned char* b_channel = img.data(0, 0, 0, 2);
	char* r_data_out = new char[width * height];
	char* g_data_out = new char[width * height];
	char* b_data_out = new char[width * height];
	
	for (int i = 0 ; i < width * height ; i++) {
		r_data_out[i] = r_channel[i];
		g_data_out[i] = g_channel[i];
		b_data_out[i] = b_channel[i];
			/*output<< setw(3) << (r_data_out[i] & 0xFF) << " ";
		if (!((i+1)%width)) {
			output << endl;*/
		}


	/*int count = 0;
	for (int color_level = 0; color_level < 256; color_level++) {

		for (int pixel_scan_at = 0; pixel_scan_at < width * height; pixel_scan_at++) {
			unsigned char current_pixel_r = r_data_out[pixel_scan_at];

			if (current_pixel_r == color_level) {
				count++;
			}

		}
		if (count > 0)
			output << color_level << ":" << count << endl;
		count = 0;
	}*/

	unsigned int color_table[256] = {};


	// zero the array//R
	memset(color_table, 0, 256);
	for (int i = 0 ; i < width*height ; i++) {
		unsigned char current_pix_r = r_data_out[i];
		color_table[current_pix_r]++;
	}
	
	/*ofstream output;
	output.open("data.csv");

	output << "R" << endl;
	output<<"level,count\n";
	for (int color_index = 0; color_index < 256; color_index++) {
		if (color_table[color_index] > 0) {
			output<<color_index<<","<< color_table[color_index]<<endl;
		}
	}*/


	int r_value = 0;
	int threshold = 5;

	for (int i =255; i >=0; i--)
	{
		if (color_table[i] > threshold)
		{
			r_value = i;
			cout <<"R_value="<< r_value << endl;
			break;
		}
		
	}

	//output<< endl;

	// zero the array//G
	memset(color_table, 0, 256 * sizeof(color_table[0]));
	for (int i = 0; i < width*height; i++) {
		unsigned char current_pix_g = g_data_out[i];
		color_table[current_pix_g]++;
	}
	
	int g_value = 0;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[i] > threshold)
		{
			g_value = i;
			cout << "G_value=" << g_value << endl;
			break;
		}

	}

	/*output << "G" << endl;
	output << "level,count\n";
	for (int color_index = 0; color_index < 256; color_index++) {
		if (color_table[color_index] > 0) {
			output << color_index << "," << color_table[color_index] << endl;
		}
	}

	output << endl;*/

	// zero the array//B

	memset(color_table, 0, 256 * sizeof(color_table[0]));
	for (int i = 0; i < width*height; i++) {
		unsigned char current_pix_b = b_data_out[i];
		color_table[current_pix_b]++;
	}
	
	int b_value = 0;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[i] > threshold)
		{
			b_value = i;
			cout << "B_value=" << b_value << endl;
			break;
		}

	}

	//find max_value

	int max_value = 0;
	if (r_value > g_value)
		max_value = r_value;
	else
		max_value = g_value;

	if (b_value > max_value)
		max_value = b_value;

	/*output << "B" << endl;
	output << "level,count\n";
	for (int color_index = 0; color_index < 256; color_index++) {
		if (color_table[color_index] > 0) {
			output << color_index << "," << color_table[color_index] << endl;
		}
	}

	output.close();*/

	
	
	double gain=(double)255/(double)max_value;
	cout << "gain="<<gain << endl;
	for (int i = 0; i < width * height; i++) {
		//condition ? true : false;
		// (a>b) ? b : a;
		r_channel[i] = (r_channel[i]* gain)>255?255: r_channel[i] * gain;
		g_channel[i] = (g_channel[i] * gain)>255 ? 255 : g_channel[i] * gain;
		b_channel[i] = (b_channel[i] * gain)>255 ? 255 : b_channel[i] * gain;
		/*output<< setw(3) << (r_data_out[i] & 0xFF) << " ";
		if (!((i+1)%width)) {
		output << endl;*/
	}


	/*ifstream input;
	input.open("data.csv");
	string value;
	while (!input.eof())
	{
		getline(input, value);
		cout << value << endl;
	}
	input.close();*/


	//r_channel[5 + width * 0] = 0;
	//r_channel[5 + width * 1] = 0;

	CImgDisplay main_disp(img, "New Image");
	CImgDisplay main_disp_orig(img_orig, "Original Image");

	float original_aspect_ratio = ((float)img.width() / (float)img.height());
	int desired_window_height = 720;
	int new_window_width = (int)(original_aspect_ratio * (float)desired_window_height);
	main_disp.resize(new_window_width, desired_window_height, 1);
	main_disp_orig.resize(new_window_width, desired_window_height, 1);

	//main_disp.resize(800, 500);

	while (!main_disp.is_closed() || !main_disp_orig.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y() >= 0) {
			const int y = main_disp.mouse_y();
		}

	}
	img.save("adj.jpg");

}