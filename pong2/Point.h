#pragma once

#include <iostream>
#include "utils.h"
using namespace std;

class Point 
{
	int x, y;
	char ch;

public:
	Point(int x1, int y1, char c) : x(x1), y(y1), ch(c) {}

	const char& get_char() {
		return ch;
	}
	void draw() const
	{
		draw(ch);
	}
	void draw(char c) const
	{
		gotoxy(x, y);
		cout << c;
	}
	void erase() {
		setColor(COLOR::BLACK_BACKGROUND);
		draw(' ');
	}
	void move(const int &dir_x,const int &dir_y)
	{
		x += dir_x;
		y += dir_y;
	}
	void set_char(const char &new_char) 
	{
		ch = new_char;
	}
	bool operator!=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}
	const int & get_Y() const
	{
		return y;
	}
	const int & get_X() const
	{
		return x;
	}
	void set_x(const int &new_x) 
	{
		x = new_x;
	}
	void set_y(const int &new_y) 
	{
		y = new_y;
	}

	
};