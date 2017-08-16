#include"RectangularPackDLL.h"
#include<iostream>
#include <fstream> 
#include <string>   
#include <streambuf>
#include <string>
#include <cstdio>
#include "pack.h"
using namespace std;

void calculate(int number, RECT* rect, int boxLenght, int boxWidth) {
	//number = 400;
	//boxLenght = 400;
	//boxWidth = 200;
	rect_xywhf *rects = new rect_xywhf[number];
	rect_xywhf **ptr_rects = new rect_xywhf*[number];
	//rect_xywhf rects[RECTS], *ptr_rects[RECTS];

	for (int i = 0; i < number; ++i) {
		rects[i] = rect_xywhf(0, 0, rect[i].length, rect[i].width, rect[i].index);
		//rects[i] = rect_xywhf(0, 0, 7 + rand() % 50, 7 + rand() % 50, i);
		ptr_rects[i] = rects + i;
	}

	vector<bin> bins;

	if (pack(ptr_rects, number, boxLenght, boxWidth, bins)) {
		printf("bins: %d\n", bins.size());
		ofstream location_out;
		location_out.open("location_out.json", std::ios::out);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
																//location_out.open("location_out.json", std::ios::out | std::ios::app);
		if (!location_out.is_open())
			return ;
		location_out << "[" << endl;
		for (int i = 0; i < bins.size(); ++i) {
			location_out << "{" << endl;
			printf("\n\nbin: %dx%d, rects: %d\n", boxLenght, boxWidth, bins[i].rects.size());
			location_out << "\"binName\":\"" << i << "\"," << endl;
			location_out << "\"y\":" << i * (boxWidth + 20) << "," << endl;
			location_out << "\"w\":" << boxLenght << "," << endl;
			location_out << "\"h\":" << boxWidth << "," << endl;
			location_out << "\"contains\":[" << endl;
			for (int r = 0; r < bins[i].rects.size(); ++r) {
				location_out << "{" << endl;
				rect_xywhf* rect = bins[i].rects[r];
				printf("rect %d: x: %d, y: %d, w: %d, h: %d, was flipped: %s\n", rect->index, rect->x, rect->y, rect->w, rect->h, rect->flipped ? "yes" : " no");
				location_out << "\"rect\":\"" << rect->index << "\"," << endl;
				location_out << "\"x\":" << rect->x << "," << endl;
				location_out << "\"y\":" << rect->y << "\," << endl;
				location_out << "\"w\":" << rect->w << "," << endl;
				location_out << "\"h\":" << rect->h << "," << endl;
				location_out << "\"c\":\"rgb(" << rand() % 254 << "," << rand() % 254 << "," << rand() % 254 << ")\"," << endl;
				location_out << "\"flipped\":" << (rect->flipped ? 1 : 0) << endl;
				if (r != bins[i].rects.size() - 1) {
					location_out << "}," << endl;
				}
				else {
					location_out << "}" << endl;
				}
			}
			location_out << "]" << endl;
			if (i != bins.size() - 1) {
				location_out << "}," << endl;
			}
			else {
				location_out << "}" << endl;
			}
		}
		location_out << "]" << endl;
		location_out.close();
	}
	else {
		printf("failed: there's a rectangle with width/height bigger than max_size!\n");
	}

}