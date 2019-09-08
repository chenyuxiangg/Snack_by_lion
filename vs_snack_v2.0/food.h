#ifndef FOOD_H
#define FOOD_H

#ifndef CYX_EASYX
#define CYX_EASYX
#include <graphics.h>      // 就是需要引用这个图形库
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
	void UpdateSize();								//赋予食物闪烁的效果 
	
public:
	int m_x;
	int m_y;
	int m_radius;
	bool m_exist;
	COLORREF m_col;
};

#endif
