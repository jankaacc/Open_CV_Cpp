#pragma once
#include <string>
#include "color.h"

using namespace std;

class Brick
{
public:
	Brick();
	~Brick();
private:
	int size;
	string name;
	Color color;
	int min_rect_size;
	int x;
	int y;
};

