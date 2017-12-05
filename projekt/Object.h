#pragma once
#include "opencv2/opencv.hpp"
//#include "color.h"
#include "Pattern.h"

class Object
{
public:
	Object();
	~Object();
	void setName(string _name);
	void setShape(vector<Point> _shape);
	void setColor1(Color _color1);
	void setColor2(Color _color2);
	void setX(int _x);
	void setY(int _y);
	void setDot_Q(int _dot_quan);
	void set_rect(RotatedRect _rect);
	
	
	vector<Point> getShape();
	int get_dot_quan();
	string get_name();
	RotatedRect get_rect();
	Color get_color(int _nr);

	void show();

private:
	string name;
	vector<Point> shape;
	Color color1;
	Color color2;
	int x, y;
	int dot_quan;
	RotatedRect rect;
};

