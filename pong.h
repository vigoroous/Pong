#pragma once
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <random>
#include <audiere.h>

using std::vector;
using std::pair;

class Location {
protected:		
	double x; // координата X
	double y; // координата Y
public:   
	Location(int initx, int inity); // конструктор
	~Location(); // деструктор
	double getx();	// получить x координату точки
	double gety();	// получить y координату точки
	virtual void moveto(double, double) = 0;
	virtual void draw(void) = 0;
};

class Point : public Location {
protected:
	float RED, GREEN, BLUE; // RGB
public:
	Point(int InitX = 0.f, int InitY = 0.f, float setRED = 0.0f,
		float setGREEN = 1.0f, float setBLUE = 0.0f); // конструктор класса
	~Point(); // деструктор
	virtual void moveto(double NewX, double NewY); // переместить фигуру
	virtual void draw(void); // показать фигуру ТОЧКА
	void setRGB(float newRED, float newGREEN, float newBLUE); // задать цвет
};

class Square : public Point {
protected:
	int scale;
public:
	Square(float InitX = 0, float InitY = 0, float setRED = 0.f, float setGREEN = 0.f, float setBLUE = 0.f, int Scale = 25);
	~Square(); // деструктор
	void draw(void); // показать фигуру КВАДРАТ
};

class Ball : public Square {
	// в этом классе не будет
	// описан конструктор, но 
	// будет создан автоматически 
	// компилятором; такой конструктор
	// называется стандартным 
	// синтезируемым конструктором
public:
	void bounce(double X, double Y, int direction, double speed_x, double speed_y);
	void moveto(double X, double Y);
};

class Block : public Square {
	
public:
	Block(float InitX = 0, float InitY = 0, float setRED = 0.f, float setGREEN = 0.f, float setBLUE = 0.f, int Scale = 25); // конструктор с одним параметром по умолчанию
	~Block();
	void draw(void); // показать фигуру КВАДРАТ
	
};

class Platform : public Square {
private:
	int size; 
public:
	vector <pair <double, double>> platform; // чтобы можно было менять координаты
	Platform(float InitX, float InitY, float setRED = 0.f, float setGREEN = 1.f,
		float setBLUE = 0.f, int Scale = 25, int InitSize = 4); // конструктор
	~Platform(); // деструктор
	void draw(); 
	int getsize(void);
	double gettalex(int X);
	void moveto(double NewX, double NewY); // переместить фигуру
	bool iscollide(double x, double y, bool orientation);
};
