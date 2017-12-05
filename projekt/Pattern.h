#pragma once


#include "opencv2/opencv.hpp"
#include "color.h"
#include <vector>
#include <string>


using namespace std;
using namespace cv;

class Pattern
{
public:
	Pattern(string name);
	~Pattern();
	void show();
	vector<Point> get_contour();
	void set_dot_nr(int _nr);
	int get_dot_q();
	string get_name();
private:
	vector<Point> contour;
	int dot_nr;
	string call;
};

