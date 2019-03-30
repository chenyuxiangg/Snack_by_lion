#pragma once
#ifndef SNACK_H
#define SNACK_H
#include <Gra_solution.h>  //��� easyxͼ�ο��ڸð汾vs�еĴ�������
#include <graphics.h>      // ������Ҫ�������ͼ�ο�
#include <iostream>
const int MAX_NUM = 100;
int Speed = 50;

//��������
enum direction {no,dup, dleft, ddown, dright };

//̰������СԲȦ����
typedef struct cordinate
{
	int n_ox;
	int n_oy;
	int n_r = 2;
	direction dire = dright;
}Cor;

//��һ��СԲȦ��̰���������һ����
void drawcorcle(Cor cor,COLORREF REF);
void initturn(Cor* cor, int n);

//̰������
class Snack
{
public:
	Snack();
	~Snack();

	Cor* pcorarr;
	int i_len;
	direction dir;
	int i_ncapcity;

};

Snack :: Snack()
{
	i_ncapcity = 500;
	pcorarr = new Cor[i_ncapcity];
	i_len = 0;
	dir = dright;
}

Snack :: ~Snack()
{
	delete[] pcorarr;
	pcorarr = NULL;
}

void drawcorcle(Cor cor,COLORREF REF)
{
	setfillcolor(REF);//RGB(200,100,100)
	setlinecolor(REF);//RGB(200,100,100)
	fillcircle(
		cor.n_ox,
		cor.n_oy,
		cor.n_r
	);
}

void initturn(Cor* cor,const int n)
{
	for (int i = 0;i < n;i++)
	{
		cor[i].n_ox = -1;
		cor[i].n_oy = -1;
		cor[i].dire = no;
	}
}
#endif