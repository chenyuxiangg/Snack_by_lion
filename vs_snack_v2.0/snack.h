#ifndef SNACK_H
#define SNACK_H

#ifndef CYX_EASYX
#define CYX_EASYX
#include <graphics.h>      // 就是需要引用这个图形库
#endif

//上下左右
enum direction {no,dup, dleft, ddown, dright };

class Snackpart {
public:
	int x;
	int y;
	direction dir;
	Snackpart* pre;
	Snackpart* next;

public:
	Snackpart(int tx = 100,int ty = 100) {
		x = tx;
		y = ty;
		dir = no;
		pre = NULL;
		next = NULL;
	}
};

//贪吃蛇类
class Snack
{
public:
	Snack(int speed = 1);
	~Snack();
	void Grow();
	void Draw();
	void Move();
	void Destroy(Snackpart* head);

public:
	COLORREF m_col;
	int m_speed;
	int m_radius;
	Snackpart* m_head;
	Snackpart* m_tail;
};
#endif
