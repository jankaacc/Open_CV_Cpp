#include "Pattern.h"
#include <iostream>
#include <fstream>


using namespace std;

Pattern::Pattern(string name)
{
	call = name;
	call.erase(call.end() - 4,call.end());
	ifstream file(name);
	if (file.is_open())
		cout << "File was correctly opened!" << endl;
	string line;
	char bin = ' ';
	double buf_1, buf_2;
	Point temp;

	while (!file.eof())
	{
		file >> bin;
		file >> buf_1;
		file >> bin;
		file >> noskipws >> bin;
		file >> buf_2;
		file >> bin;
		file >> noskipws >> bin;

		temp = Point(buf_1, buf_2);
		contour.push_back(temp);		
	} 
	contour.pop_back();
	file.close();
}


Pattern::~Pattern()
{

}

void Pattern::show()
{
	cout << contour;
}


vector<Point> Pattern::get_contour()
{
	return contour;
}

void Pattern::set_dot_nr(int _nr)
{
	dot_nr = _nr;
}

int Pattern::get_dot_q()
{
	return dot_nr;
}

string Pattern::get_name()
{
	return call;
}