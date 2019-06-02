#include "pong.h"

/*-----------------------------------------------------------------------*/
/*                � � � � � � � � � �    � � � � � � �                   */
/*-----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/*                     ������ ������ Location                            */
/*-----------------------------------------------------------------------*/
Location::Location(int InitX, int InitY) { // �����������
	x = InitX;
	y = InitY;
}

Location::~Location(void) {}; // ����������

double Location::getx(void) { // �������� x ���������� �����
	return x;
}

double Location::gety(void) { // �������� y ���������� �����
	return y;
}


/*-----------------------------------------------------------------------*/
/*                     ������ ������ Point                               */
/*-----------------------------------------------------------------------*/

//��� ������������� �������� ����� ���������� ����������� ������
Point::Point(int InitX, int InitY, float setRED,
	float setGREEN, float setBLUE) : Location(InitX, InitY)
{
	RED = setRED;
	GREEN = setGREEN;
	BLUE = setBLUE;
}
Point::~Point(void){}

void Point::draw(void) {
	glColor3f(RED, GREEN, BLUE); // ������ ����
	glRectf(x - 1, y - 1, x + 1, y + 1);
}


void Point::moveto(double NewX, double NewY) { // ����������� �����
	x = NewX; // �������� ���������� �����
	y = NewY;
}

void Point::setRGB(float newRED, float newGREEN, float newBLUE)
{
	RED = newRED;
	GREEN = newGREEN;
	BLUE = newBLUE;
}

/*-----------------------------------------------------------------------*/
/*                        ������ ������ Square                            */
/*-----------------------------------------------------------------------*/
Square::Square(float InitX, float InitY, float setRED, float setGREEN, float setBLUE, int Scale)
	: Point(InitX, InitY, setRED, setGREEN, setBLUE)
{
	scale = Scale;
}

Square::~Square() {} // ��������� ������ ����

void Square::draw() {
	glColor3f(RED, GREEN, BLUE); // ������ ����
	glRectf(x * scale, y * scale, (x + 1) * scale, (y + 1) * scale);
}


/*-----------------------------------------------------------------------*/
/*                     ������ ������ Ball                               */
/*-----------------------------------------------------------------------*/

void Ball::moveto(double NewX, double NewY)
{
	x = NewX; // �������� ���������� 
	y = NewY;
}

void Ball::bounce(double X, double Y, int direction, double speed_x, double speed_y) {
	switch (direction) {
	case 1:
		x += speed_x;
		y -= speed_y;
		break;
	case 2:
		x -= speed_x;
		y -= speed_y;
		break;
	case 3:
		x -= speed_x;
		y += speed_y;
		break;
	case 4:
		x += speed_x;
		y += speed_y;
		break;
	}
}

/*-----------------------------------------------------------------------*/
/*                     ������ ������ Block                               */
/*-----------------------------------------------------------------------*/
Block::Block(float InitX, float InitY, float setRED, float setGREEN, float setBLUE, int Scale) : Square (InitX, InitY, setRED, setGREEN, setBLUE, Scale) {}

Block::~Block() {}

void Block::draw() {
	glColor3f(RED, GREEN, BLUE); // ������ ����
	glRectf(x * scale, y * scale, (x + 1) * scale, (y + 1) * scale);
}


/*-----------------------------------------------------------------------*/
/*                     ������ ������ Platform                               */
/*-----------------------------------------------------------------------*/
Platform::Platform(float InitX, float InitY, float setRED, float setGREEN,
	float setBLUE, int Scale, int InitSize) : Square (InitX, InitY, setRED, setGREEN, setBLUE, Scale) 
{
	size = InitSize;
	pair <double, double> buf;
	buf.first = InitX;
	buf.second = InitY;
	for (int i = 0; i < InitSize; i++) {
		platform.push_back(buf);
		buf.first--;
		
	}
}

Platform::~Platform() {}

void Platform::draw() {
	glColor3f(RED, GREEN, BLUE); // ������ ����
	for (auto now : platform)
		glRectf(now.first * scale, now.second * scale, (now.first + 1.0) * scale, (now.second + 1.0) * scale);
	return;
}


void Platform::moveto(double NewX, double NewY){
	for (int i = 0; i < platform.size(); i++) {
		platform.at(i).first += NewX;
	}
}

int Platform::getsize(void) {
	return size;
}

double Platform::gettalex(int X) {
	return platform.at(X).first;
}

// ������ ������� �� ���������� � ������������ ���� ������ ������
bool Platform::iscollide(double AX, double AY, bool orientation)
{
	if (orientation && AX * scale <= (platform[0].first + 1.0) * scale && AX * scale >= (platform[3].first - 1.0) * scale && platform[0].second + 1.0 >= AY)
		return true;
	else if (!orientation && AX * scale <= (platform[0].first + 1.0) * scale && AX * scale >= (platform[3].first - 1.0) * scale && platform[0].second - 1.0 <= AY)
		return true;
	return false;
}