#pragma once

#include "Object.h"
#include "opencv2/opencv.hpp"
#include "color.h"
#include "Pattern.h"
#include <fstream>
#include <iterator>
#include <string>

using namespace cv;
using namespace std;

class Object_recogniser
{
public:
	Object_recogniser(vector<Mat> _img, vector<Mat> _img_HSV, Mat _color_recognition);
	~Object_recogniser();
	void recognise();
	void check_red(int _nr);
	void check_yellow(int _nr);
	void check_blue(int _nr);
	void check_green(int _nr);
	void check_white(int _nr);
	void close_img();
	void find_obj(int _nr);
	void curve_dots(int _nr);
	void match(int _nr);
	void sum_colors();
	void helper(int nr,Color col1);
	void helper(int nr, Color col1, Color col2);

private:
	vector<Pattern> Patterns;
	vector<RotatedRect> rects;
	vector<vector<Point>> contours;

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours0;
	vector<Vec4i> hierarchy0;

	int licz = 0;
	int mem = 0;

	Mat buf_1, buf_2, buf_r1, buf_r2;
	vector<Mat> img;
	vector<Mat> img_HSV;
	Mat color_recognition;
		
	Color current_color1;
	Color current_color2;
	Ccolors colors;

	vector<vector<Object>> objects;
	Object buf;
	

};

