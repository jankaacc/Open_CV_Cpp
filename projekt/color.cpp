#include "color.h"


Color::Color(Scalar _low_border , Scalar _high_border, string _name)
{
	low_border = _low_border;
	high_border = _high_border;
	name = _name;
}

Color::Color()
{
	low_border = 0;
	high_border = 0;
	name = '...';
}

Scalar Color::get_high_b()
{
	return high_border;
}

Scalar Color::get_low_b()
{
	return low_border;
}

string Color::get_name()
{
	return name;
}

Color::~Color()
{
}


////////////////////////////////////////////////



Ccolors::Ccolors()
{	
	Color white = Color(Scalar(28, 0, 168), Scalar(104, 37, 196), "white");
	cout << "elo";
	Color red1 = Color(Scalar(0, 100, 100), Scalar(10, 255, 255),"red");
	Color red2 = Color(Scalar(160, 100, 100), Scalar(179, 255, 255),"red");
	Color yellow1 = Color(Scalar(18, 70, 132), Scalar(25, 255, 255),"yellow");
	Color blue = Color(Scalar(103, 96, 96), Scalar(113, 255, 255),"blue");
	Color green = Color(Scalar(32, 44, 34), Scalar(85, 255, 255),"green");
}


Ccolors::~Ccolors()
{
}