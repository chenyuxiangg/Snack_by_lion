#include "food.h"
#include <cmath>
#include <ctime>

Food::Food() :m_exist(false), m_radius(2)
{
	
}

Food::~Food()
{
}

void Food::Product()
{
	if (!m_exist) {
		GetCol();
		GetPos();
		m_exist = true;
	}
	Draw();
}

void Food::Draw()
{
	setfillcolor(m_col);
	setlinecolor(m_col);
	fillcircle(m_x, m_y, m_radius);
	UpdateSize();
} 

void Food::GetPos()
{
	srand(time(0));
	m_x = rand() % 640;
	m_y = rand() % 480;
	while (m_x < 20 || m_x > 620 || m_y < 20 || m_y > 460) {
		m_x = rand() % 640;
		m_y = rand() % 480;
	}
}

void Food::GetCol()
{
	srand(time(0));
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	double diff = sqrt(pow(r - 0, 2) + pow(g - 0, 2) + pow(b - 0, 2));
	while (diff < 30.0) {
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
	}
	m_col = RGB(r, g, b);
}

void Food::UpdateSize()
{
	m_radius = (m_radius == 2 ? 3 : 2);
}

