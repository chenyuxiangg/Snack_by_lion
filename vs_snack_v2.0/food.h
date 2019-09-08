#ifndef FOOD_H
#define FOOD_H

#ifndef CYX_EASYX
#define CYX_EASYX
#include <graphics.h>      // ������Ҫ�������ͼ�ο�
#endif

class Food {
public:
	Food();
	~Food();
	void Product();
	void Draw();
	
private:
	void GetPos();
	void GetCol();
	void UpdateSize();								//����ʳ����˸��Ч�� 
	
public:
	int m_x;
	int m_y;
	int m_radius;
	bool m_exist;
	COLORREF m_col;
};

#endif
