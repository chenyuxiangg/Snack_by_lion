#include "snack.h"
#include <ctime>
#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000?1:0)
using namespace std;

typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
}recposition;

void initstart();//初始化界面
void clearscrip();//清空界面
void moveup(Cor& snacor, Cor* cor, int n);//向上运动
void moveleft(Cor& snacor, Cor* cor, int n);//向左运动
void movedown(Cor& snacor, Cor* cor, int n);//向下运动
void moveright(Cor& snacor, Cor* cor, int n);//向右运动
void selectup(recposition& rec);//选择框上移
void selectdown(recposition& rec);//选择框的下移
COLORREF food(Cor& cor, Snack& she);

void main()
{
	initgraph(640, 480);   // 初始化控制台

	//游戏初始界面
	initstart();

	//通过键盘的上下键选择
	recposition cur;//当前矩形框
	cur.left = 275;
	cur.top = 145;
	cur.right = 365;
	cur.bottom = 175;

	while (1)
	{
		//选择框的上移
		if (KEY_DOWN(VK_UP))
		{
			if (cur.top > 145 && cur.bottom > cur.top)
			{
				//将原来的选择框置黑
				setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
				setlinecolor(0);      //设置边框颜色
				rectangle(cur.left, cur.top, cur.right, cur.bottom);
				//上移选择框
				cur.top -= 30;
				cur.bottom -= 30;
				//重绘选择框
				setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
				setlinecolor(BLUE | YELLOW | RED);      //设置边框颜色
				rectangle(cur.left, cur.top, cur.right, cur.bottom);

			}
		}

		//选择框的下移
		if (KEY_DOWN(VK_DOWN))
		{
			if (cur.top < 235 && cur.bottom > cur.top)
			{
				//将原来的选择框置黑
				setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
				setlinecolor(0);      //设置边框颜色
				rectangle(cur.left, cur.top, cur.right, cur.bottom);
				//上移选择框
				cur.top += 30;
				cur.bottom += 30;
				//重绘选择框
				setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
				setlinecolor(BLUE | YELLOW | RED);      //设置边框颜色
				rectangle(cur.left, cur.top, cur.right, cur.bottom);

			}
		}

		//进入选择框
		if (KEY_DOWN(VK_SPACE))
		{
			//如果cur.top == 145,进入游戏
			if (cur.top == 145)
			{
				//初始化小蛇
				clearscrip();
				Snack snack;
				snack.pcorarr[0].n_ox = 310;
				snack.pcorarr[0].n_oy = 230;
				snack.i_len++;
				drawcorcle(snack.pcorarr[0], RGB(200, 100, 100));
				//end

				//使小蛇动起来
				bool fooded = false;
				Cor c;//食物位置坐标
				COLORREF tref;//用于存储食物的颜色
				bool over = false;
				//转折点数组
				Cor turn[MAX_NUM];
				initturn(turn, MAX_NUM);

				while (1)
				{
					//判断撞墙或者咬到自己或者小蛇长度达到最大
					if (snack.i_len >= snack.i_ncapcity || over)
					{
						snack.~Snack();
						clearscrip();
						initstart();
						cur.left = 275;
						cur.top = 145;
						cur.right = 365;
						cur.bottom = 175;
						break;
					}
					//生成食物
					if (!fooded)
					{
						tref = food(c, snack);//这里需要传入snack的引用
						fooded = true;
					}
					//生成食物end

					int x;
					int y;
					bool exe = false;

					//重写移动
					for (int i = 0; i < snack.i_len; i++)
					{
						x = snack.pcorarr[i].n_ox + snack.pcorarr[i].n_r;
						y = snack.pcorarr[i].n_oy + snack.pcorarr[i].n_r;
						if (x <= 628 && y <= 468 && x >= 18 && y >= 18)
						{
							//先将原来的置黑
							drawcorcle(snack.pcorarr[i], 0);
							//按照某一方向一直运动

							if (snack.pcorarr[i].dire == dup && !exe)
							{
								moveup(snack.pcorarr[i], turn, MAX_NUM);
								if (i == snack.i_len - 1)
								{
									for (int j = 0; j < MAX_NUM; j++)
									{
										if (snack.pcorarr[i].n_ox == turn[j].n_ox && (snack.pcorarr[i].n_oy + 2) == turn[j].n_oy)
										{
											turn[j].dire = no;
											turn[j].n_ox = -1;
											turn[j].n_oy = -1;
											break;
										}
									}
								}
								exe = true;
							}

							if (snack.pcorarr[i].dire == dleft && !exe)
							{
								moveleft(snack.pcorarr[i], turn, MAX_NUM);
								if (i == snack.i_len - 1)
								{
									for (int j = 0; j < MAX_NUM; j++)
									{
										if ((snack.pcorarr[i].n_ox + 2) == turn[j].n_ox && snack.pcorarr[i].n_oy == turn[j].n_oy)
										{
											turn[j].dire = no;
											turn[j].n_ox = -1;
											turn[j].n_oy = -1;
											break;
										}
									}
								}
								exe = true;
							}

							if (snack.pcorarr[i].dire == ddown && !exe)
							{
								movedown(snack.pcorarr[i], turn, MAX_NUM);
								if (i == snack.i_len - 1)
								{
									for (int j = 0; j < MAX_NUM; j++)
									{
										if (snack.pcorarr[i].n_ox == turn[j].n_ox && (snack.pcorarr[i].n_oy - 2) == turn[j].n_oy)
										{
											turn[j].dire = no;
											turn[j].n_ox = -1;
											turn[j].n_oy = -1;
											break;
										}
									}
								}
								exe = true;
							}

							if (snack.pcorarr[i].dire == dright && !exe)
							{
								moveright(snack.pcorarr[i], turn, MAX_NUM);
								if (i == snack.i_len - 1)
								{
									for (int j = 0; j < MAX_NUM; j++)
									{
										if ((snack.pcorarr[i].n_ox - 2) == turn[j].n_ox && snack.pcorarr[i].n_oy == turn[j].n_oy)
										{
											turn[j].dire = no;
											turn[j].n_ox = -1;
											turn[j].n_oy = -1;
											break;
										}
									}
								}
								exe = true;
							}

							//判断是否咬到自己
							/*if (i == 0)
							{
								for (int k = 1; k < snack.i_len; k++)
								{
									if (getpixel(snack.pcorarr[0].n_ox, snack.pcorarr[0].n_oy) == RGB(200, 100, 100))
									{
										over = true;
										break;
									}
								}
							}*/
						}

						else
						{
							over = true;
							break;
						}
						exe = false;
					}
					snack.dir = snack.pcorarr[0].dire;
					//重写结束
					Sleep(Speed);//动画效果

					//按键改变小蛇方向
					if (KEY_DOWN(VK_UP) && snack.dir != ddown)
					{
						for (int i = 0; i < MAX_NUM; i++)
						{
							if (turn[i].dire == no)
							{
								turn[i].dire = dup;
								snack.pcorarr[0].dire = dup;
								turn[i].n_ox = snack.pcorarr[0].n_ox;
								turn[i].n_oy = snack.pcorarr[0].n_oy;
								break;
							}
						}
					}

					if (KEY_DOWN(VK_LEFT) && snack.dir != dright)
					{
						for (int i = 0; i < MAX_NUM; i++)
						{
							if (turn[i].dire == no)
							{
								turn[i].dire = dleft;
								snack.pcorarr[0].dire = dleft;
								turn[i].n_ox = snack.pcorarr[0].n_ox;
								turn[i].n_oy = snack.pcorarr[0].n_oy;
								break;
							}
						}
					}

					if (KEY_DOWN(VK_DOWN) && snack.dir != dup)
					{
						for (int i = 0; i < MAX_NUM; i++)
						{
							if (turn[i].dire == no)
							{
								turn[i].dire = ddown;
								snack.pcorarr[0].dire = ddown;
								turn[i].n_ox = snack.pcorarr[0].n_ox;
								turn[i].n_oy = snack.pcorarr[0].n_oy;
								break;
							}
						}
					}

					if (KEY_DOWN(VK_RIGHT) && snack.dir != dleft)
					{
						for (int i = 0; i < MAX_NUM; i++)
						{
							if (turn[i].dire == no)
							{
								turn[i].dire = dright;
								snack.pcorarr[0].dire = dright;
								turn[i].n_ox = snack.pcorarr[0].n_ox;
								turn[i].n_oy = snack.pcorarr[0].n_oy;
								break;
							}
						}
					}

					//按键改变小蛇方向end

					//小蛇长度改变
					int firstx = snack.pcorarr[0].n_ox;
					int firsty = snack.pcorarr[0].n_oy;
					if (snack.dir == dup)
					{
						firsty -= 12;
						if (getpixel(firstx, firsty) == tref)
						{
							snack.i_len++;
							//判断应将变长的部分加到哪
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox < 10)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dleft)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox + 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox > 620)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dup)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy + 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy - 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}
							drawcorcle(c, 0);//把食物位置值黑
							fooded = false;
						}
					}//dup

					if (snack.dir == dleft)
					{
						firstx -= 12;
						if (getpixel(firstx, firsty) == tref)
						{
							snack.i_len++;
							//判断应将变长的部分加到哪
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox < 10)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dleft)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox + 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox > 620)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dup)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy + 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy - 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}
							drawcorcle(c, 0);
							fooded = false;
						}
					}//dleft

					if (snack.dir == ddown)
					{
						firsty += 12;
						if (getpixel(firstx, firsty) == tref)
						{
							snack.i_len++;
							//判断应将变长的部分加到哪
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox < 10)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dleft)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox + 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox > 620)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dup)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy + 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy - 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}
							drawcorcle(c, 0);
							fooded = false;
						}
					}//ddown

					if (snack.dir == dright)
					{
						firstx += 12;
						if (getpixel(firstx, firsty) == tref)
						{
							snack.i_len++;
							//判断应将变长的部分加到哪
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox < 10)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dleft)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox + 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_ox > 620)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else if (snack.pcorarr[snack.i_len - 2].dire == dup)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy + 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}

							else
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy - 12;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//判断是否越出边界线
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}
							drawcorcle(c, 0);
							fooded = false;
						}
					}//dright

					//小蛇长度改变end
				}
				//使小蛇动起来end
			}
			//如果cur.top == 175,设置游戏
			if (cur.top == 175)
			{
				//设置游戏难度，其实就是改变移动速度

				//首先将当前选则框的位置初始化
				cur.left = 275;
				cur.top = 145;
				cur.right = 365;
				cur.bottom = 175;

				//绘制边框及背景
				setlinestyle(PS_SOLID, 10, NULL);  //设置边框像素
				setlinecolor(BLUE | GREEN);      //设置边框颜色
				setfillcolor(0);//设置背景填充颜色
				fillrectangle(0, 0, 640, 480);

				//绘制文字
				settextcolor(RED | BLUE);
				settextstyle(20, 0, _T("黑体"));
				TCHAR c[] = _T("简单");
				outtextxy(280, 150, c);
				TCHAR s[] = _T("一般");
				outtextxy(280, 180, s);
				TCHAR t[] = _T("困难");
				outtextxy(280, 210, t);

				//绘制选择框
				setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
				setlinecolor(BLUE | YELLOW | RED);      //设置边框颜色
				rectangle(275, 145, 365, 175);

				//选择框进入过的标志
				bool selectenter = false;

				//选择模式
				while (!selectenter)
				{
					//选择框上下移动
					if (KEY_DOWN(VK_UP))
					{
						selectup(cur);
					}

					if (KEY_DOWN(VK_DOWN))
					{
						selectdown(cur);
					}

					if(KEY_DOWN(VK_RETURN))
					{
						selectenter = true;
						if (cur.top == 145)
						{
							Speed = 50;
						}

						if (cur.top == 175)
						{
							Speed = 20;
						}

						if(cur.top == 205)
						{
							Speed = 10;
						}
					}

					if(selectenter == true)
					{
						initstart();
						//初始化界面的选择框位置
						cur.left = 275;
						cur.top = 145;
						cur.right = 365;
						cur.bottom = 175;
					}
					Sleep(100);
				}

				//重置进入标志
				selectenter = false;
			}
			//如果cur.top == 205,游戏帮助
			if(cur.top == 205)
			{
				//绘制边框及背景
				setlinestyle(PS_SOLID, 10, NULL);  //设置边框像素
				setlinecolor(BLUE | GREEN);      //设置边框颜色
				setfillcolor(0);//设置背景填充颜色
				fillrectangle(0, 0, 640, 480);

				//绘制文字
				settextcolor(RGB(150,150,150));
				settextstyle(20, 0, _T("宋体"));
				TCHAR c[] = _T("游戏操作说明");
				outtextxy(260, 50, c);
				TCHAR s[] = _T("1.游戏操作十分简单，通过上下左右来选择‘进入游戏’、");
				outtextxy(60, 80, s);
				TCHAR t[] = _T("  ‘游戏设置’、‘游戏帮助’，可通过空格进入选项.");
				outtextxy(60, 120, t);
				TCHAR d[] = _T("2.通过上下左右控制小蛇移动。");
				outtextxy(60, 150, d);

				//任意键继续
				getchar();
				//重绘游戏界面并重置选择框
				initstart();
				cur.left = 275;
				cur.top = 145;
				cur.right = 365;
				cur.bottom = 175;
			}
			//如果cur.top == 235,退出程序
			if(cur.top == 235)
			{
				break;
			}
		}
		Sleep(100);
	}
	getchar();// 按任意键继续
	closegraph();          // 关闭图形界面
}

void initstart()
{
	//绘制边框及背景
	setlinestyle(PS_SOLID, 10, NULL);  //设置边框像素
	setlinecolor(BLUE | GREEN);      //设置边框颜色
	setfillcolor(0);//设置背景填充颜色
	fillrectangle(0, 0, 640, 480);

	//绘制文字
	settextcolor(RED | BLUE);
	settextstyle(20, 0, _T("黑体"));
	TCHAR c[] = _T("开始游戏");
	outtextxy(280, 150, c);
	TCHAR s[] = _T("游戏设置");
	outtextxy(280, 180, s);
	TCHAR t[] = _T("游戏帮助");
	outtextxy(280, 210, t);
	TCHAR d[] = _T("退出游戏");
	outtextxy(280, 240, d);

	//绘制选择框
	setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
	setlinecolor(BLUE | YELLOW | RED);      //设置边框颜色
	rectangle(275, 145, 365, 175);
}

void clearscrip()
{
	//绘制边框及背景
	setlinestyle(PS_SOLID, 10, NULL);  //设置边框像素
	setlinecolor(BLUE | GREEN);      //设置边框颜色
	setfillcolor(0);//设置背景填充颜色
	fillrectangle(0, 0, 640, 480);
}

void moveup(Cor& snacor, Cor* cor, int n)
{
	snacor.n_oy -= 2;
	drawcorcle(snacor, RGB(200, 100, 100));
	for (int i = 0; i < n; i++)
	{
		if (snacor.n_ox == cor[i].n_ox && snacor.n_oy == cor[i].n_oy)
		{
			snacor.dire = cor[i].dire;
			break;
		}
	}
}

void moveleft(Cor& snacor, Cor* cor, int n)
{
	snacor.n_ox -= 2;
	drawcorcle(snacor, RGB(200, 100, 100));
	for (int i = 0; i < n; i++)
	{
		if (snacor.n_ox == cor[i].n_ox && snacor.n_oy == cor[i].n_oy)
		{
			snacor.dire = cor[i].dire;
			break;
		}
	}
}

void movedown(Cor& snacor, Cor* cor, int n)
{
	snacor.n_oy += 2;
	drawcorcle(snacor, RGB(200, 100, 100));
	for (int i = 0; i < n; i++)
	{
		if (snacor.n_ox == cor[i].n_ox && snacor.n_oy == cor[i].n_oy)
		{
			snacor.dire = cor[i].dire;
			break;
		}
	}
}

void moveright(Cor& snacor, Cor* cor, int n)
{
	snacor.n_ox += 2;
	drawcorcle(snacor, RGB(200, 100, 100));
	for (int i = 0; i < n; i++)
	{
		if (snacor.n_ox == cor[i].n_ox && snacor.n_oy == cor[i].n_oy)
		{
			snacor.dire = cor[i].dire;
			break;
		}
	}
}

COLORREF food(Cor& cor, Snack& she)
{
	srand(unsigned(time(NULL)));
	int x = rand() % 616 + 20;
	int y = rand() % 456 + 10;
	bool exist = false;

	for (int i = 0; i < she.i_len; i++)
	{
		if (x == she.pcorarr[i].n_ox && y == she.pcorarr[i].n_oy)
			exist = true;
	}
	if (x > 10 && !exist)
	{
		cor.n_ox = x;
		cor.n_oy = y;
	}
	COLORREF ref = RGB(rand() % 200 + 10, rand() % 200 + 10, rand() % 200 + 10);
	drawcorcle(cor, ref);
	return ref;
}

void selectup(recposition& rec)
{
	if (rec.top > 145 && rec.bottom > rec.top)
	{
		//将原来的选择框置黑
		setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
		setlinecolor(0);      //设置边框颜色
		rectangle(rec.left, rec.top, rec.right, rec.bottom);
		//上移选择框
		rec.top -= 30;
		rec.bottom -= 30;
		//重绘选择框
		setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
		setlinecolor(BLUE | YELLOW | RED);      //设置边框颜色
		rectangle(rec.left, rec.top, rec.right, rec.bottom);

	}
}

void selectdown(recposition& rec)
{
	if (rec.top < 205 && rec.bottom > rec.top)
	{
		//将原来的选择框置黑
		setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
		setlinecolor(0);      //设置边框颜色
		rectangle(rec.left, rec.top, rec.right, rec.bottom);
		//上移选择框
		rec.top += 30;
		rec.bottom += 30;
		//重绘选择框
		setlinestyle(PS_SOLID, 1, NULL);  //设置边框像素
		setlinecolor(BLUE | YELLOW | RED);      //设置边框颜色
		rectangle(rec.left, rec.top, rec.right, rec.bottom);

	}
}
