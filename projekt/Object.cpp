#include "Object.h"



Object::Object()
{
	name = "unknown";
}


Object::~Object()
{
}


void Object::setName(string _name)
{
	name = _name;
}
void Object::setShape(vector<Point> _shape)
{
	shape = _shape;
}
void Object::setColor1(Color _color1)
{
	color1 = _color1;
}
void Object::setColor2(Color _color2)
{
	color2 = _color2;
}
void Object::setX(int _x)
{
	x = _x;
}
void Object::setY(int _y)
{
	y = _y;
}
void Object::setDot_Q(int _dot_quan)
{
	dot_quan = _dot_quan;
}

void Object::set_rect(RotatedRect _rect)
{
	rect = _rect;
}

vector<Point> Object::getShape()
{
	return shape;
}

int Object::get_dot_quan()
{
	return dot_quan;
}

string Object::get_name()
{
	return name;
}

RotatedRect Object::get_rect()
{
	return rect;
}

void Object::show()
{
	cout << name << endl;
}

Color Object::get_color(int _nr)
{
	if (_nr == 1)
		return color1;
	if (_nr == 2)
		return color2;
}