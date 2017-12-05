#pragma once
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;



class Color
{
public:
	Color(Scalar _low_border, Scalar _high_border, string _name = "...");
	Color::Color();
	~Color();

	Scalar get_low_b();
	Scalar get_high_b();
	string get_name();

private:
	Scalar low_border;
	Scalar high_border;
	string name;
};



class Ccolors 
{
public:
	Ccolors();	
	~Ccolors();

	Color white = Color(Scalar(28, 0, 168), Scalar(104, 37, 196), "white");
	Color red1 = Color(Scalar(0, 100, 100), Scalar(10, 255, 255), "red");
	Color red2 = Color(Scalar(160, 100, 100), Scalar(179, 255, 255), "red");
	Color yellow1 = Color(Scalar(18, 70, 132), Scalar(25, 255, 255), "yellow");
	Color blue = Color(Scalar(103, 96, 96), Scalar(113, 255, 255), "blue");
	Color green = Color(Scalar(32, 44, 34), Scalar(85, 255, 255), "green");
};

