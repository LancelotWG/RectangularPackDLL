#pragma once
#define MYLIBAPI extern "C" __declspec(dllexport)
typedef struct Rect {
	int index;
	int length;
	int width;
} RECT;
MYLIBAPI void calculate(int number, RECT* rect, int boxLenght, int boxWidth);
