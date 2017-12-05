#include "Object_recogniser.h"
#include <list>

//using namespace std;

Object_recogniser::Object_recogniser(vector<Mat> _img, vector<Mat> _img_HSV, Mat  _color_recognition)
{
	img = _img;
	img_HSV = _img_HSV;
	color_recognition = _color_recognition;

	Patterns.push_back(Pattern("5.txt"));
	Patterns.push_back(Pattern("2.txt"));
	Patterns.push_back(Pattern("3.txt"));
	Patterns.push_back(Pattern("4.txt"));
	Patterns.push_back(Pattern("1.txt"));

	Patterns[0].set_dot_nr(8);
	Patterns[1].set_dot_nr(8);
	Patterns[2].set_dot_nr(6);
	Patterns[3].set_dot_nr(4);
	Patterns[4].set_dot_nr(4);
	
}


Object_recogniser::~Object_recogniser()
{
}

string print_nr(int j)
{
	switch (j)
	{
	case 0:
	{
			  return "Z";
	}break;
	case 1:
	{
			  return "T";
	}break;
	case 2:
	{
			  return "Tr";
	}break;
	case 3:
	{
			  return "Sq";
	}break;
	case 4:
	{
			  return "Bar";
	}break;
	default:
		break;
	}
}


void Object_recogniser::check_red(int _nr)
{
	licz++;
	inRange(img_HSV[_nr], colors.red1.get_low_b(), colors.red1.get_high_b(), color_recognition);
	current_color1 = colors.red1;
	color_recognition.copyTo(buf_r1);
	inRange(img_HSV[_nr], colors.red2.get_low_b(), colors.red2.get_high_b(), color_recognition);
	color_recognition.copyTo(buf_r2);
	add(buf_r1, buf_r2, color_recognition);
	if (licz % 2 == 1)
	{
		color_recognition.copyTo(buf_1);
	}
	else color_recognition.copyTo(buf_2);
}
void Object_recogniser::check_yellow(int _nr)
{
	licz++;
	inRange(img_HSV[_nr], colors.yellow1.get_low_b(), colors.yellow1.get_high_b(), color_recognition);
	current_color1 = colors.yellow1;

	cout << endl << colors.yellow1.get_low_b();

	if (licz % 2 == 1)
	{
		color_recognition.copyTo(buf_1);
	}
	else color_recognition.copyTo(buf_2);
}
void Object_recogniser::sum_colors()
{
	if (licz >= 2)
	{
		add(buf_1, buf_2, color_recognition);
	}
}

void Object_recogniser::check_blue(int _nr)
{
	licz++;
	inRange(img_HSV[_nr], colors.blue.get_low_b(), colors.blue.get_high_b(), color_recognition);
	current_color1 = colors.blue;
	//cout << current_color1.get_name();
	if (licz % 2 == 1)
	{
		color_recognition.copyTo(buf_1);
	}
	else color_recognition.copyTo(buf_2);
}
void Object_recogniser::check_green(int _nr)
{
	licz++;
	inRange(img_HSV[_nr], colors.green.get_low_b(), colors.green.get_high_b(), color_recognition);
	current_color1 = colors.green;
	if (licz % 2 == 1)
	{
		color_recognition.copyTo(buf_1);
	}
	else color_recognition.copyTo(buf_2);
}
void Object_recogniser::check_white(int _nr)
{
	licz++;
	inRange(img_HSV[_nr], colors.white.get_low_b(), colors.white.get_high_b(), color_recognition);
	current_color1 = colors.white;
	if (licz % 2 == 1)
	{
		color_recognition.copyTo(buf_1);
	}
	else color_recognition.copyTo(buf_2);
}
void Object_recogniser::close_img()
{
	Mat elem = getStructuringElement(MORPH_RECT, Size(25, 25));
	erode(color_recognition, color_recognition, elem);
	dilate(color_recognition, color_recognition, elem);

	dilate(color_recognition, color_recognition, elem);
	erode(color_recognition, color_recognition, elem);
}
void Object_recogniser::find_obj(int _nr)
{
	///////////////////////////////znalezienie konturów////////////////////////////////
	findContours(color_recognition, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	cout << endl;
	for (int i = 0; i< contours.size();)
	{
		if (contourArea(contours[i])>30000 & contourArea(contours[i])<130000)
		{
			//drawContours(color_recognition, contours, i, 250, 4);
			RotatedRect minRect = minAreaRect(contours[i]);
			//Point2f vertices[4];
			//minRect.points(vertices);
			/*for (int i = 0; i < 4; i++)
				line(img[_nr], vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 4);
*/
			i++;
		}
		else {
			contours.erase(contours.begin() + i);
		}
		
	}cout << "contours s: " << contours.size() << endl;
	////////////////////////////////////////zapisanie znalezionych knturów do obiektu////////////////////////
	vector<Object> temp;
	objects.push_back(temp);

	for (int i = 0; i < contours.size(); i++)
	{
	buf.setShape(contours[i]);
	buf.set_rect(minAreaRect(buf.getShape()));
	buf.setColor1(current_color1);
	buf.setColor2(current_color2);
	objects[_nr].push_back(buf);
	}

	for (int i = 0; i < objects.size(); )
	{
		if (objects[i].empty())
		{
			objects.erase(objects.begin() + i);
		}
		else i++;
	}

}

void Object_recogniser::curve_dots(int _nr)
{
	vector<Point> result;
	for (size_t i = 0; i < objects[_nr].size(); i++)
	{
		approxPolyDP(objects[_nr][i].getShape(), result, arcLength(Mat(objects[_nr][i].getShape()), true)*0.035, true);		
		//cout << endl << result.size() << endl;
		objects[_nr][i].setDot_Q(result.size()); // przypisujê liczbê kropek do obiektu
/////////////////////////////////rysuje kontury/////////////////////////////////////
		//drawContours(img[_nr], contours, (i), Scalar(0, 255, 255), 6); // fill GREEN
		/*vector<Point>::iterator vertex;
		for (vertex = result.begin(); vertex != result.end(); ++vertex)
		{
			circle(img[_nr], *vertex, 3, Scalar(0, 0, 255), 16);
		}
		*/
	}
///////////////////////////////nak³adam cyfry na elementy/////////////////////////////
	//for (int i = 0; i< contours.size(); i++)
	//{
	//	if (contourArea(contours[i])>30000)
	//	{
	//		char a = i + 48;
	//		string str;
	//		str.push_back(a);
	//		//approxPolyDP(Mat(contours[i]), contours0[i], 3, true);
	//		//cout << contourArea(contours[i]) << " " << i << endl;
	//		RotatedRect minRect = minAreaRect(contours[i]);
	//		rects.push_back(minRect);
	//		//putText(img[_nr], str, minRect.center, 1, 6, Scalar(150, 0, 0), 5);

	//	}
	//}

}

void Object_recogniser::match(int _nr)
{
	double ans;

	for (int i = 0; i < Patterns.size(); i++)
	{
		for (int j = 0; j <objects[_nr].size(); j++)
		{
			//cout << print_nr(i) << " z " << j << endl;
			ans = matchShapes(Patterns[i].get_contour(), objects[_nr][j].getShape(), CV_CONTOURS_MATCH_I2, 0);
			//cout << ans << endl;
			if (ans < 0.35)
			{
				if (objects[_nr][j].get_dot_quan() == Patterns[i].get_dot_q())
				{
					objects[_nr][j].setName(Patterns[i].get_name());
					//objects[_nr][j].setColor1(current_color1);
					//objects[_nr][j].setColor2(current_color2);
				}
			}
		}
	}
}

void Object_recogniser::helper(int nr, Color col1)
{
	current_color1 = Color(col1.get_low_b(), col1.get_high_b(), col1.get_name());
	current_color2 = Color(col1.get_low_b(), col1.get_high_b(), col1.get_name());	
	
	cout << current_color1.get_name() << " oraz " << current_color2.get_name() << endl;
	cout << current_color1.get_low_b() << " i " << current_color2.get_low_b() << endl;


	close_img();
	find_obj(nr);
	//curve_dots(nr);
	//match(nr);
}

void Object_recogniser::helper(int nr, Color col1, Color col2)
{
	current_color1 = Color(col1.get_low_b(),col1.get_high_b(),col1.get_name());
	current_color2 = Color(col2.get_low_b(), col2.get_high_b(), col2.get_name());

	cout << current_color1.get_name() << " oraz " << current_color2.get_name() << endl;
	cout << current_color1.get_low_b() << " i " << current_color2.get_low_b() << endl;

	sum_colors();
	close_img();
	find_obj(nr);
	//curve_dots(nr);
	//match(nr);
}

void Object_recogniser::recognise()
{	
	for (int nr = 0; nr < 18; nr++)
	{
		check_red(nr);
		check_yellow(nr);
		helper(nr, colors.red1, colors.yellow1);
		cout << colors.red1.get_name() << endl;

		check_red(nr);
		check_blue(nr);
		helper(nr, colors.red1, colors.blue);

		check_red(nr);
		check_green(nr);
		helper(nr, colors.red1, colors.green);

		check_red(nr);
		check_white(nr);
		helper(nr, colors.red1, colors.white);


		check_blue(nr);
		check_yellow(nr);
		helper(nr, colors.blue, colors.yellow1);

		check_blue(nr);
		check_green(nr);
		helper(nr, colors.blue, colors.green);
		
		check_blue(nr);
		check_white(nr);
		helper(nr, colors.blue, colors.white);

		check_yellow(nr);
		check_green(nr);
		helper(nr, colors.yellow1, colors.green);

		check_yellow(nr);
		check_white(nr);
		helper(nr, colors.yellow1, colors.white);

		check_green(nr);
		check_white(nr);
		helper(nr, colors.white,colors.green);

		check_red(nr);
		helper(nr, colors.red1);
		
		check_yellow(nr);
		helper(nr, colors.yellow1);

		check_white(nr);
		helper(nr, colors.white);

		check_blue(nr);
		helper(nr, colors.blue);

		check_green(nr);
		helper(nr, colors.green);

		

		cout<<endl<<"przed: "<<objects[nr].size()<<endl;
			

		for (vector<Object>::iterator it2 = objects[nr].begin(); it2 != objects[nr].end();)
		{
			bool bErased = false;
			for (vector<Object>::iterator it3 = objects[nr].begin(); it3 != objects[nr].end(); ++it3)
			{
				if (it3->get_rect().center.inside(it2->get_rect().boundingRect()))
				{
					if (it3 != it2)
					{
						if (contourArea(it3->getShape()) > contourArea(it2->getShape()))
						{
							it2 = objects[nr].erase(it2);
							bErased = true;
							break;
						}
					}
				}
			}
			if (!bErased)
				++it2;
		}
		for (vector<Object>::iterator it2 = objects[nr].begin(); it2 != objects[nr].end();)
		{
			bool bErased = false;
			for (vector<Object>::iterator it3 = objects[nr].begin(); it3 != objects[nr].end(); ++it3)
			{
				if (it2->get_rect().center.inside(it3->get_rect().boundingRect()))
				{
					if (it3 != it2)
					{
						if (contourArea(it3->getShape()) > contourArea(it2->getShape()))
						{
							it2 = objects[nr].erase(it2);
							bErased = true;
							break;
						}
					}
				}
			}
			if (!bErased)
				++it2;
		}

		for (vector<Object>::iterator it2 = objects[nr].begin(); it2 != objects[nr].end();)
		{
			bool bErased = false;
			for (vector<Object>::iterator it3 = objects[nr].begin(); it3 != objects[nr].end(); ++it3)
			{
				if (it2->get_rect().center.inside(it3->get_rect().boundingRect()))
				{
					if (it3 != it2)
					{
						if (contourArea(it3->getShape()) == contourArea(it2->getShape()))
						{
							it2 = objects[nr].erase(it2);
							bErased = true;
							break;
						}
					}
				}
			}
			if (!bErased)
				++it2;
		}



		
		cout << endl << "po " << objects[nr].size() << endl;

		curve_dots(nr);
		match(nr);


		/*vector<vector<Point>> drawing;
		for (int i = 0; i < objects[nr].size(); i++)
		{
			drawing.push_back(objects[nr][i].getShape());
		}
		*/

		for (int i = 0; i< objects[nr].size(); i++)
		{	
			Point title = objects[nr][i].get_rect().center;
			
				putText(img[nr], objects[nr][i].get_name(), objects[nr][i].get_rect().center, 1, 6, Scalar(0, 255, 65), 5);
				title.y += 100;
				putText(img[nr], objects[nr][i].get_color(1).get_name(), title, 1, 6, Scalar(0, 255, 65), 5);
				title.y += 50;
				putText(img[nr], objects[nr][i].get_color(2).get_name(), title, 1, 6, Scalar(0, 255, 65), 5);
				Point2f vertices[4];
				objects[nr][i].get_rect().points(vertices);
				for (int i = 0; i < 4; i++)
				line(img[nr], vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 4);
				
				//drawContours(color_recognition, drawing, i, 250, 4);
		}
		
		/*na pocz¹tku sprawdzasz kolory mieszane z czerwonym na koñcu czerwony
		powinno byæteraz ¿e w wektorze jest masa obuektó i nawet niektóre obiekty jedno kolorowe
		majo przypisane dwa kolory, bo wszystkim przypisuje siê cuuren color, ale na koñsu
		ju¿ po wszystkich kolorach sprawdzasz które
		obiekty leza w wenatrz porstokatów i usuwasz te które maj¹ jeden kolor, czyli najlepiej 
		przeprowadziæ sprawdzanie jedno kolorwoeych na koñcu, i jak siê oka¿e ¿e le¿¹ wewn¹trz 
		jakiegoœ dwukoloroewgo to je usun¹æ problem tylko ¿e nawet niektóre jedno kolorowe bêd¹
		mia³y dw kolory przypisane? mo¿n coœ pokombinowaæ z tym który shape ma wiêksz¹ area i usun¹æ t¹ z mniejszym
		*/

		imshow("Display1", img[nr]);
		imshow("Display", color_recognition);
		waitKey();
	}
	cout << "\nsave list of objects as: ";
	string name;
	cin.ignore();
	getline(cin, name);

	ofstream output_file(name);
	//ostream_iterator<Scalar> output_iterator(output_file, "\n");
	//copy(l_bord, output_iterator);
	
	
	
	for (int i = 0; i < 18; i++)
	{
		
		int l[5];
		l[0] = 0;
		l[1] = 0;
		l[2] = 0;
		l[3] = 0;
		l[4] = 0;

		int li[6];
		li[0] = 0;
		li[1] = 0;
		li[2] = 0;
		li[3] = 0;
		li[4] = 0;
		li[5] = 0;

		for (int j = 0; j < objects[i].size(); j++)
		{
			if (objects[i][j].get_name() == "1")
				l[0]++;
			if (objects[i][j].get_name() == "2")
				l[1]++;
			if (objects[i][j].get_name() == "3")
				l[2]++;
			if (objects[i][j].get_name() == "4")
				l[3]++;
			if (objects[i][j].get_name() == "5")
				l[4]++;
		}

		for (int j = 0; j < objects[i].size(); j++)
		{
			if (objects[i][j].get_color(1).get_name() == colors.red1.get_name() && objects[i][j].get_name() != "unknown"&&objects[i][j].get_color(1).get_name() == objects[i][j].get_color(2).get_name())
				li[0]++;
			if (objects[i][j].get_color(1).get_name() == colors.green.get_name() && objects[i][j].get_name() != "unknown"&&objects[i][j].get_color(1).get_name() == objects[i][j].get_color(2).get_name())
				li[1]++;
			if (objects[i][j].get_color(1).get_name() == colors.blue.get_name() && objects[i][j].get_name() != "unknown"&&objects[i][j].get_color(1).get_name() == objects[i][j].get_color(2).get_name())
				li[2]++;
			if (objects[i][j].get_color(1).get_name() == colors.white.get_name() && objects[i][j].get_name() != "unknown"&&objects[i][j].get_color(1).get_name() == objects[i][j].get_color(2).get_name())
				li[3]++;
			if (objects[i][j].get_color(1).get_name() == colors.yellow1.get_name() && objects[i][j].get_name() != "unknown"&&objects[i][j].get_color(1).get_name() == objects[i][j].get_color(2).get_name())
				li[4]++;
			if (objects[i][j].get_color(1).get_name() != objects[i][j].get_color(2).get_name() && objects[i][j].get_name() != "unknown")
				li[5]++;

		}

		for (int n = 0; n < 5; n++)
		{
			char f_name[20];
			sprintf(f_name, "%d_ksztalt_%d", l[n],(n+1));
			output_file << f_name << ", ";
		}
		for (int j = 0; j < objects[i].size(); j++)
		{
			char c_name[20];
			if (j == 0)
			{
				sprintf(c_name, "%d_czerwonych", li[j]);
				output_file << c_name << ", ";
			}if (j == 1)
			{
				sprintf(c_name, "%d_zielonych", li[j]);
				output_file << c_name << ", ";
			}if (j == 2)
			{
				sprintf(c_name, "%d_niebieskich", li[j]);
				output_file << c_name << ", ";
			}if (j == 3)
			{
				sprintf(c_name, "%d_bialych", li[j]);
				output_file << c_name << ", ";
			}if (j == 4)
			{
				sprintf(c_name, "%d_zoltych", li[j]);
				output_file << c_name << ", ";
			}if (j == 5)
			{
				sprintf(c_name, "%d_mieszanych", li[j]);
				output_file << c_name << "\n";
			}


			

		}
	}
	
}

