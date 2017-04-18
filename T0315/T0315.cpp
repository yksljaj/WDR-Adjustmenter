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
void testfunc(char *ptr_to_string);

int main(int argc, char* argv[])
{
	//cout << "argc: " << argc << endl;
	if (argc > 1)
	{
		for (int i=1 ; i < argc; i++)
		{
			cout << "argv[" << i << "] = " << argv[i] << endl;
			printf("0x%08X\n", argv[i]);
			testfunc(argv[i]);
		}
	}
	
	//testfunc(&argv[i]);
	system("pause");
	return 0;
}

double gain_func(int& height, int& width,char r_data_out[], char g_data_out[], char b_data_out[], int& region_left, int& region_right, int& region_up, int& region_down,unsigned char r_channel[], unsigned char g_channel[], unsigned char b_channel[])
{
	unsigned int color_table[3][256];
	memset(color_table, 0, 256 * 3 * sizeof(unsigned int));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((j >= region_left) && (j <= region_right)) {
				if ((i >= region_up) && (i <= region_down)) {
					color_table[0][(unsigned char)r_data_out[i*width + j]]++;
					color_table[1][(unsigned char)g_data_out[i*width + j]]++;
					color_table[2][(unsigned char)b_data_out[i*width + j]]++;
				}
			}
		}
	}
	int r_value = 0;
	int threshold = 5;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[0][i] > threshold)
		{
			r_value = i;
			cout << "R_value=" << r_value << endl;
			break;
		}

	}


	int g_value = 0;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[1][i] > threshold)
		{
			g_value = i;
			cout << "G_value=" << g_value << endl;
			break;
		}

	}
	int b_value = 0;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[2][i] > threshold)
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

	double gain = (double)255 / (double)max_value;
	if (max_value == 0)
	{
		gain = 1.0;
	}
	cout << "gain=" << gain << endl;
	//for (int i = 0; i < width * height; i++) {
	//	//condition ? true : false;
	//	// (a>b) ? b : a;
	//	r_channel[i] = (r_channel[i] * gain) > 255 ? 255 : r_channel[i] * gain;
	//	g_channel[i] = (g_channel[i] * gain) > 255 ? 255 : g_channel[i] * gain;
	//	b_channel[i] = (b_channel[i] * gain) > 255 ? 255 : b_channel[i] * gain;
	//}
	return gain;
}

void testfunc(char *ptr_to_string)
{

	char *filename = ptr_to_string;
	//char filename[] = "argv[i]";
	//char filename[] = "unnamed.jpg";

	//cout << "handled file name: " << &filename[0] << endl;

	CImg<unsigned char> img_new(filename);
	CImg<unsigned char> img_display(filename);
	CImg<unsigned char> img_orig(filename);


	//CImg<unsigned char> img("unnamed.jpg");

	int width = img_new.width();
	int height = img_new.height();
	unsigned char* r_new = img_new.data(0, 0, 0, 0);
	unsigned char* g_new = img_new.data(0, 0, 0, 1);
	unsigned char* b_new = img_new.data(0, 0, 0, 2);
	unsigned char* r_display = img_display.data(0, 0, 0, 0);
	unsigned char* g_display = img_display.data(0, 0, 0, 1);
	unsigned char* b_display = img_display.data(0, 0, 0, 2);
	unsigned char* r_ori = img_orig.data(0, 0, 0, 0);
	unsigned char* g_ori = img_orig.data(0, 0, 0, 1);
	unsigned char* b_ori = img_orig.data(0, 0, 0, 2);
	char* r_data_out = new char[width * height];
	char* g_data_out = new char[width * height];
	char* b_data_out = new char[width * height];
	
	for (int i = 0 ; i < width * height ; i++) {
		r_data_out[i] = r_new[i];
		g_data_out[i] = g_new[i];
		b_data_out[i] = b_new[i];
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

	unsigned int color_table[3][256];
	//printf("widaddr: 0x%08X\n", &width);
	//printf("heiaddr: 0x%08X\n", &height);
	//printf("ctbaddr: 0x%08X\n", &color_table[0][0]);
	//printf("rdtaddr: 0x%08X\n", &r_data_out[0]);
	//printf("gdtaddr: 0x%08X\n", &g_data_out[0]);
	//printf("bdtaddr: 0x%08X\n", &b_data_out[0]);



	// zero the array
	memset(color_table, 0, 256*3*sizeof(unsigned int));

	int region_left = 0;
	int region_right = width-1;
	int region_up = 0;
	int region_down = height-1;

	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((j >= region_left) && (j <= region_right)) {
				if ((i >= region_up) && (i <= region_down)) {
					//unsigned char current_idx = r_data_out[i*width + j];
					//color_table[0][current_idx]++;
					//color_table[1][current_idx]++;
					//color_table[2][current_idx]++;
					color_table[0][(unsigned char)r_data_out[i*width + j]]++;
					color_table[1][(unsigned char)g_data_out[i*width + j]]++;
					color_table[2][(unsigned char)b_data_out[i*width + j]]++;
				}
			}
		}
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
		if (color_table[0][i] > threshold)
		{
			r_value = i;
			cout <<"R_value="<< r_value << endl;
			break;
		}
		
	}

	//output<< endl;

	
	int g_value = 0;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[1][i] > threshold)
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

	
	int b_value = 0;

	for (int i = 255; i >= 0; i--)
	{
		if (color_table[2][i] > threshold)
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
		r_new[i] = (r_new[i]* gain)>255?255: r_new[i] * gain;
		g_new[i] = (g_new[i] * gain)>255 ? 255 : g_new[i] * gain;
		b_new[i] = (b_new[i] * gain)>255 ? 255 : b_new[i] * gain;
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

	CImgDisplay main_disp(img_new, "New Image");
	CImgDisplay main_disp_orig(img_orig, "Original Image");

	float original_aspect_ratio = ((float)img_new.width() / (float)img_new.height());
	int desired_window_height = 720;
	int new_window_width = (int)(original_aspect_ratio * (float)desired_window_height);
	main_disp.resize(new_window_width, desired_window_height, 1);
	main_disp_orig.resize(new_window_width, desired_window_height, 1);

	//main_disp.resize(800, 500);
	bool prev_left_button = false;
	int prev_x = 0;
	int prev_y = 0;
	int after_x = 0;
	int after_y = 0;
	int temp = 0;
	while (!main_disp.is_closed() || !main_disp_orig.is_closed()) {
		main_disp_orig.wait();
		bool current_left_button_pressed = ((main_disp_orig.button() & 0x01) > 0) ? true : false;
		//cout << "mouse left: "    << current_left_button_pressed;
		//cout << "\tmouse mid: "   << ((main_disp_orig.button() & 0x04) > 0) ? 1 : 0;
		//cout << "\tmouse right: " << ((main_disp_orig.button() & 0x02) > 0) ? 1 : 0;

		//cout << endl;
		if (prev_left_button == 0 && current_left_button_pressed == 1) {
			cout << "left button just pressed" << endl;
			prev_x = main_disp_orig.mouse_x()*width/ new_window_width;
			prev_y = main_disp_orig.mouse_y()*height/ desired_window_height;
		
		} else if (prev_left_button == 1 && current_left_button_pressed == 0) {
			cout << "left button just released" << endl;
			after_x = main_disp_orig.mouse_x()*width / new_window_width;
			after_y = main_disp_orig.mouse_y()*height / desired_window_height;

			if (prev_x - after_x > 0)
			{
				temp = prev_x;
				prev_x = after_x;
				after_x = temp;

			}
			if (prev_y - after_y >0)
			{
				temp = prev_y;
				prev_y = after_y;
				after_y = temp;

			}
			double z = gain_func(height, width, r_data_out, g_data_out, b_data_out, prev_x, after_x, prev_y, after_y, r_new, g_new, b_new);
			cout << z << endl;
			for (int i = 0; i < width * height; i++) {
				r_new[i] = (r_ori[i] * z) > 255 ? 255 : r_ori[i] * z;
				g_new[i] = (g_ori[i] * z) > 255 ? 255 : g_ori[i] * z;
				b_new[i] = (b_ori[i] * z) > 255 ? 255 : b_ori[i] * z;
			//	/*output<< setw(3) << (r_data_out[i] & 0xFF) << " ";
			//	if (!((i+1)%width)) {
			//	output << endl;*/
			}
			img_new.display(main_disp);
			//img_orig.display(main_disp_orig);
		} else if (current_left_button_pressed == 1) {
			// focus the interest region
			int current_x = main_disp_orig.mouse_x()*width / new_window_width;
			int current_y = main_disp_orig.mouse_y()*height / desired_window_height;

			int left_boundary = min(current_x, prev_x);
			int right_boundary = max(current_x, prev_x);
			int top_boundary = min(current_y, prev_y);
			int bottom_boundary = max(current_y, prev_y);
			int stressed_line_width = 5;
			// draw the stress line in the image
			for (int i = top_boundary - stressed_line_width/2; i <= (bottom_boundary + stressed_line_width / 2) ; i++) {
				for (int j = left_boundary - stressed_line_width / 2; j <= (right_boundary + stressed_line_width / 2) ; j++) {
					// left and right line
					//if (j == left_boundary || j == right_boundary) {
					if (abs(j - left_boundary) < stressed_line_width/2 || abs(j - right_boundary) < stressed_line_width/2) {

						r_display[i*width + j] = 255;
						g_display[i*width + j] = 0;
						b_display[i*width + j] = 0;
					}
					// top and bottom line
					//if (i == top_boundary || i == bottom_boundary) {
					if (abs(i - top_boundary) < stressed_line_width/2 || abs(i - bottom_boundary) < stressed_line_width/2) {

						r_display[i*width + j] = 255;
						g_display[i*width + j] = 0;
						b_display[i*width + j] = 0;
					}
				}
			}
			img_display.display(main_disp_orig);
			img_display.draw_image(img_orig);
		}
		prev_left_button = current_left_button_pressed;


		if (main_disp_orig.button() && (main_disp_orig.mouse_y() >= 0 || main_disp_orig.mouse_x() >= 0)) {
			const int x = main_disp_orig.mouse_x();
			const int y = main_disp_orig.mouse_y();
			//printf("mouse x/y: [%4d] [%4d]\n", x, y);
		}

	}
	img_new.save("adj.jpg");

}

