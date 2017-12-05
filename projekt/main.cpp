#include "opencv2/opencv.hpp"
//#include "color.h"
//#include "Pattern.h"
#include "Object_recogniser.h"
#include <fstream>
#include <iterator>
#include <string>

using namespace cv;
using namespace std;

Color adjust_color;
int h_l = 0, s_l = 0, v_l = 0;
int h_h = 0, s_h = 0, v_h = 0;
Scalar l_bord;
Scalar h_bord;

int nr = 0;
Mat img_HSV[18];
Mat color_recognition;
void open(Mat *img);
void Foo(int state, void*)
{

}
void on_trackbar(int,void*)
{
	l_bord = Scalar(h_l, s_l, v_l);
	h_bord = Scalar(h_h, s_h, v_h);
	adjust_color = Color(l_bord, h_bord);
	inRange(img_HSV[nr], adjust_color.get_low_b(), adjust_color.get_high_b(), color_recognition);
	imshow("Display", color_recognition);
}

string print(int i)
{
	switch (i)
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

int main(int, char)
{
	
	vector<Pattern> Patterns;
	Patterns.push_back(Pattern("5.txt"));
	Patterns.push_back(Pattern ("2.txt"));
	Patterns.push_back(Pattern ("3.txt"));
	Patterns.push_back(Pattern ("4.txt"));
	Patterns.push_back(Pattern ("1.txt"));
	
	vector<RotatedRect> rects;
	vector<vector<Point>> contours;
	
	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours0;
	vector<Vec4i> hierarchy0;

	Color current_color ;

	int licz = 0;
	
	Mat buf_1, buf_2,buf_r1,buf_r2;
	Mat img[18];
	char matName[20];
	char a = 'd';
	Ccolors colors;	


	open(img);


	namedWindow("Display1", WINDOW_NORMAL);
	namedWindow("Display", WINDOW_NORMAL);
	
	while (a !='q')
	{
		switch (a)
		{
		case '.':
			nr++;
			break;
		
		case ',':
			nr--;
			break;

		case 'a':
		{
					h_l = current_color.get_low_b()[0];
					s_l = current_color.get_low_b()[1];
					v_l = current_color.get_low_b()[2];

					h_h = current_color.get_high_b()[0];
					s_h = current_color.get_high_b()[1];
					v_h = current_color.get_high_b()[2];

					createTrackbar("H_l", "Display", &h_l, 178, on_trackbar);
					createTrackbar("S_l", "Display", &s_l, 255, on_trackbar);
					createTrackbar("V_l", "Display", &v_l, 255, on_trackbar);

					createTrackbar("H_H", "Display", &h_h, 178, on_trackbar);
					createTrackbar("S_H", "Display", &s_h, 255, on_trackbar);
					createTrackbar("V_H", "Display", &v_h, 255, on_trackbar);

		}break;

		case 'l':
		{
					
					cout << "\nsave range as: ";
					string name;
					cin.ignore();
					getline(cin, name);

					ofstream output_file(name);
					//ostream_iterator<Scalar> output_iterator(output_file, "\n");
					//copy(l_bord, output_iterator);
					cout << l_bord << endl;
					cout << h_bord << endl;
					output_file <<"l_bord : \n" <<l_bord;
					output_file << "\n";
					output_file << "h_bord : \n" << h_bord;
					output_file.close();

		}break;

		case 'w':
		{
			licz++;
			inRange(img_HSV[nr], colors.white.get_low_b(), colors.white.get_high_b(), color_recognition);
			current_color = colors.white;
			if (licz % 2 == 1)
			{
				color_recognition.copyTo(buf_1);
			}
			else color_recognition.copyTo(buf_2);
		}	break;

		case 'r':
		{
			licz++;
			inRange(img_HSV[nr], colors.red1.get_low_b(), colors.red1.get_high_b(), color_recognition);
			current_color = colors.red1;
				color_recognition.copyTo(buf_r1);
				inRange(img_HSV[nr], colors.red2.get_low_b(), colors.red2.get_high_b(), color_recognition);
				color_recognition.copyTo(buf_r2);
				add(buf_r1, buf_r2, color_recognition);
				if (licz % 2 == 1)
				{
				color_recognition.copyTo(buf_1);
				}
				else color_recognition.copyTo(buf_2);
		}
			break;

		case 'y':
		{
			licz++;
			inRange(img_HSV[nr], colors.yellow1.get_low_b(), colors.yellow1.get_high_b(), color_recognition);
			current_color = colors.yellow1;

			cout << endl<<colors.yellow1.get_low_b();

			if (licz % 2 == 1)
			{
				color_recognition.copyTo(buf_1);
			}
			else color_recognition.copyTo(buf_2);
		}
			break;

		case 'b':
		{
			licz++;
			inRange(img_HSV[nr], colors.blue.get_low_b(), colors.blue.get_high_b(), color_recognition);
			current_color = colors.blue;
			if (licz % 2 == 1)
			{
				color_recognition.copyTo(buf_1);
			}
			else color_recognition.copyTo(buf_2);
		}
			break;

		case'g':
		{
			licz++;
			inRange(img_HSV[nr], colors.green.get_low_b(), colors.green.get_high_b(), color_recognition);
			current_color = colors.green;
			if (licz % 2 == 1)
			{
				color_recognition.copyTo(buf_1);
			}
			else color_recognition.copyTo(buf_2);
		}
			break;

		case '=':
		{
					if (licz >= 2)
					{
						add(buf_1, buf_2, color_recognition);						
					}
		}
			break;

		case 'z':
		{
					Mat elem = getStructuringElement(MORPH_RECT, Size(25, 25));
					/*Mat elem1 = getStructuringElement(MORPH_RECT, Size(9, 9));
					erode(color_recognition, color_recognition, elem1);
					dilate(color_recognition, color_recognition, elem1);*/
					
					erode(color_recognition, color_recognition, elem);
					dilate(color_recognition, color_recognition, elem);
					//erode(color_recognition, color_recognition, elem);

					dilate(color_recognition, color_recognition, elem);
					erode(color_recognition, color_recognition, elem);
					//erode(color_recognition, color_recognition, elem);
		}break;
		//case 's':
		//{
		//			createButton("erode", Foo);
		//			//createTrackbar("H_l", "Display", &h_l, 178, on_trackbar);
		//}break;
		case 'x':
		{
					vector<Mat> im, hsv;
					for (int i = 0; i < 18; i++)
					{
						im.push_back(img[i]);
						hsv.push_back(img_HSV[i]);
					}
					Object_recogniser recogniser(im , hsv, color_recognition);
					recogniser.recognise();

		}break;
		case 'f':
		{
					
					
					findContours(color_recognition, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					vector<Point> result;

					cout << endl;
					for (int i = 0; i< contours.size();)
					{
						if (contourArea(contours[i])>30000)
						{
							//approxPolyDP(contours, result, 1, 1);
					
							drawContours(color_recognition, contours, i, 250, 4);
							RotatedRect minRect = minAreaRect(contours[i]);
							Point2f vertices[4];
							minRect.points(vertices);
							for (int i = 0; i < 4; i++)
								line(img[nr], vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0),4);

							
							i++;
						}
						else {
							contours.erase(contours.begin() + i );							
						}
					}

					cout << "contours s: " << contours.size() << endl;

					for (size_t i = 0; i < contours.size(); i++)
					{
						approxPolyDP(contours[i], result, arcLength(Mat(contours[i]),true)*0.035, true);
						cout << endl << result.size() << endl;
						
						
							drawContours(img[nr], contours, i, Scalar(0, 255, 255),6); // fill GREEN
							vector<Point>::iterator vertex;
							for (vertex = result.begin(); vertex != result.end(); ++vertex)
							{
								circle(img[nr], *vertex, 3, Scalar(0, 0, 255), 16);
							}
							
					}




					for (int i = 0; i< contours.size(); i++)
					{
						if (contourArea(contours[i])>30000)
						{
							char a = i + 48;
							string str;
							str.push_back(a);
							//approxPolyDP(Mat(contours[i]), contours0[i], 3, true);
							cout << contourArea(contours[i]) << " " << i << endl;
							RotatedRect minRect = minAreaRect(contours[i]);
							rects.push_back(minRect);
							putText(img[nr], str, minRect.center, 1, 6, Scalar(150, 0, 0),5);
							
						}
					}
					
					
		}break;
		case 'p':
		{
					int a ;
					cout << "which contour you want to check area: ";
					cin >> a;
					
					cout << endl << rects[a].size << endl;
					cout << "area: " << rects[a].size.height * rects[a].size.width << endl;
					Rect bound = rects[a].boundingRect();
					cout << endl << bound.size();

		}break;

		case 'k':
		{
					colors.white = Color(adjust_color.get_low_b(), adjust_color.get_high_b(), "white");
		}break;

		case 'm':
		{
					
					double ans;

					for (int i = 0; i < Patterns.size(); i++)
					{
						for (int j = 0; j < contours.size(); j++)
						{
							cout << print(i) << " z " << j << endl;
							ans = matchShapes(Patterns[i].get_contour(), contours[j], CV_CONTOURS_MATCH_I2, 0);
							cout << ans<<endl;
						}
					}
		}break;

		
		case 'h':
		{
					int i;
					cout << "which contour you would like to save: ";
						cin >> i;
					cout << "\nsave contour as: ";
					string name;
					cin.ignore();
					getline(cin, name);

					ofstream output_file(name);
					ostream_iterator<Point> output_iterator(output_file, "\n");
					copy(contours[i].begin(), contours[i].end(), output_iterator);

					output_file.close();
		}

		default:
			break;
		}

		if (nr > 17)
			nr = 0;
		if (nr < 0)
			nr = 17;

	
	imshow("Display1", img[nr]);
	imshow("Display", color_recognition);

	a = waitKey();
	}
	
	return 0;
}

void open(Mat *img)
{
	Mat buf;
	char matName[20];
	for (int i = 0; i < 9; i++)
	{
		int li = i + 1;
		sprintf(matName, "images/img_00%d.jpg", li);
		img[i] = imread(matName, 1);
		cout << " " << matName;
		if (img[i].empty())
		{
			cout << "ERROR!" << endl;
		}
		cvtColor(img[i], img_HSV[i], COLOR_BGR2HSV);
		
		color_recognition = img[i];
	}
	for (int i = 9; i < 18; i++)
	{
		int li = i + 1;
		sprintf(matName, "images/img_0%d.jpg", li);
		img[i] = imread(matName, 1);
		cout << " " << matName;
		if (img[i].empty())
		{
			cout << "ERROR!" << endl;
		}
		cvtColor(img[i], img_HSV[i], COLOR_BGR2HSV);
		
		color_recognition = img[i];
	}

	//namedWindow("Display1", WINDOW_NORMAL);
	//namedWindow("Display", WINDOW_NORMAL);
}








