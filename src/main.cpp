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

void initstart();//��ʼ������
void clearscrip();//��ս���
void moveup(Cor& snacor, Cor* cor, int n);//�����˶�
void moveleft(Cor& snacor, Cor* cor, int n);//�����˶�
void movedown(Cor& snacor, Cor* cor, int n);//�����˶�
void moveright(Cor& snacor, Cor* cor, int n);//�����˶�
void selectup(recposition& rec);//ѡ�������
void selectdown(recposition& rec);//ѡ��������
COLORREF food(Cor& cor, Snack& she);

void main()
{
	initgraph(640, 480);   // ��ʼ������̨

	//��Ϸ��ʼ����
	initstart();

	//ͨ�����̵����¼�ѡ��
	recposition cur;//��ǰ���ο�
	cur.left = 275;
	cur.top = 145;
	cur.right = 365;
	cur.bottom = 175;

	while (1)
	{
		//ѡ��������
		if (KEY_DOWN(VK_UP))
		{
			if (cur.top > 145 && cur.bottom > cur.top)
			{
				//��ԭ����ѡ����ú�
				setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
				setlinecolor(0);      //���ñ߿���ɫ
				rectangle(cur.left, cur.top, cur.right, cur.bottom);
				//����ѡ���
				cur.top -= 30;
				cur.bottom -= 30;
				//�ػ�ѡ���
				setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
				setlinecolor(BLUE | YELLOW | RED);      //���ñ߿���ɫ
				rectangle(cur.left, cur.top, cur.right, cur.bottom);

			}
		}

		//ѡ��������
		if (KEY_DOWN(VK_DOWN))
		{
			if (cur.top < 235 && cur.bottom > cur.top)
			{
				//��ԭ����ѡ����ú�
				setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
				setlinecolor(0);      //���ñ߿���ɫ
				rectangle(cur.left, cur.top, cur.right, cur.bottom);
				//����ѡ���
				cur.top += 30;
				cur.bottom += 30;
				//�ػ�ѡ���
				setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
				setlinecolor(BLUE | YELLOW | RED);      //���ñ߿���ɫ
				rectangle(cur.left, cur.top, cur.right, cur.bottom);

			}
		}

		//����ѡ���
		if (KEY_DOWN(VK_SPACE))
		{
			//���cur.top == 145,������Ϸ
			if (cur.top == 145)
			{
				//��ʼ��С��
				clearscrip();
				Snack snack;
				snack.pcorarr[0].n_ox = 310;
				snack.pcorarr[0].n_oy = 230;
				snack.i_len++;
				drawcorcle(snack.pcorarr[0], RGB(200, 100, 100));
				//end

				//ʹС�߶�����
				bool fooded = false;
				Cor c;//ʳ��λ������
				COLORREF tref;//���ڴ洢ʳ�����ɫ
				bool over = false;
				//ת�۵�����
				Cor turn[MAX_NUM];
				initturn(turn, MAX_NUM);

				while (1)
				{
					//�ж�ײǽ����ҧ���Լ�����С�߳��ȴﵽ���
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
					//����ʳ��
					if (!fooded)
					{
						tref = food(c, snack);//������Ҫ����snack������
						fooded = true;
					}
					//����ʳ��end

					int x;
					int y;
					bool exe = false;

					//��д�ƶ�
					for (int i = 0; i < snack.i_len; i++)
					{
						x = snack.pcorarr[i].n_ox + snack.pcorarr[i].n_r;
						y = snack.pcorarr[i].n_oy + snack.pcorarr[i].n_r;
						if (x <= 628 && y <= 468 && x >= 18 && y >= 18)
						{
							//�Ƚ�ԭ�����ú�
							drawcorcle(snack.pcorarr[i], 0);
							//����ĳһ����һֱ�˶�

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

							//�ж��Ƿ�ҧ���Լ�
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
					//��д����
					Sleep(Speed);//����Ч��

					//�����ı�С�߷���
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

					//�����ı�С�߷���end

					//С�߳��ȸı�
					int firstx = snack.pcorarr[0].n_ox;
					int firsty = snack.pcorarr[0].n_oy;
					if (snack.dir == dup)
					{
						firsty -= 12;
						if (getpixel(firstx, firsty) == tref)
						{
							snack.i_len++;
							//�ж�Ӧ���䳤�Ĳ��ּӵ���
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}
							drawcorcle(c, 0);//��ʳ��λ��ֵ��
							fooded = false;
						}
					}//dup

					if (snack.dir == dleft)
					{
						firstx -= 12;
						if (getpixel(firstx, firsty) == tref)
						{
							snack.i_len++;
							//�ж�Ӧ���䳤�Ĳ��ּӵ���
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
							//�ж�Ӧ���䳤�Ĳ��ּӵ���
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
							//�ж�Ӧ���䳤�Ĳ��ּӵ���
							if (snack.pcorarr[snack.i_len - 2].dire == dright)
							{
								snack.pcorarr[snack.i_len - 1].n_ox = snack.pcorarr[snack.i_len - 2].n_ox - 12;
								snack.pcorarr[snack.i_len - 1].n_oy = snack.pcorarr[snack.i_len - 2].n_oy;
								snack.pcorarr[snack.i_len - 1].dire = snack.pcorarr[snack.i_len - 2].dire;
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
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
								//�ж��Ƿ�Խ���߽���
								if (snack.pcorarr[snack.i_len - 1].n_oy > 460)
									drawcorcle(snack.pcorarr[snack.i_len - 1], 0);
								else
									drawcorcle(snack.pcorarr[snack.i_len - 1], RGB(200, 100, 100));
							}
							drawcorcle(c, 0);
							fooded = false;
						}
					}//dright

					//С�߳��ȸı�end
				}
				//ʹС�߶�����end
			}
			//���cur.top == 175,������Ϸ
			if (cur.top == 175)
			{
				//������Ϸ�Ѷȣ���ʵ���Ǹı��ƶ��ٶ�

				//���Ƚ���ǰѡ����λ�ó�ʼ��
				cur.left = 275;
				cur.top = 145;
				cur.right = 365;
				cur.bottom = 175;

				//���Ʊ߿򼰱���
				setlinestyle(PS_SOLID, 10, NULL);  //���ñ߿�����
				setlinecolor(BLUE | GREEN);      //���ñ߿���ɫ
				setfillcolor(0);//���ñ��������ɫ
				fillrectangle(0, 0, 640, 480);

				//��������
				settextcolor(RED | BLUE);
				settextstyle(20, 0, _T("����"));
				TCHAR c[] = _T("��");
				outtextxy(280, 150, c);
				TCHAR s[] = _T("һ��");
				outtextxy(280, 180, s);
				TCHAR t[] = _T("����");
				outtextxy(280, 210, t);

				//����ѡ���
				setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
				setlinecolor(BLUE | YELLOW | RED);      //���ñ߿���ɫ
				rectangle(275, 145, 365, 175);

				//ѡ��������ı�־
				bool selectenter = false;

				//ѡ��ģʽ
				while (!selectenter)
				{
					//ѡ��������ƶ�
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
						//��ʼ�������ѡ���λ��
						cur.left = 275;
						cur.top = 145;
						cur.right = 365;
						cur.bottom = 175;
					}
					Sleep(100);
				}

				//���ý����־
				selectenter = false;
			}
			//���cur.top == 205,��Ϸ����
			if(cur.top == 205)
			{
				//���Ʊ߿򼰱���
				setlinestyle(PS_SOLID, 10, NULL);  //���ñ߿�����
				setlinecolor(BLUE | GREEN);      //���ñ߿���ɫ
				setfillcolor(0);//���ñ��������ɫ
				fillrectangle(0, 0, 640, 480);

				//��������
				settextcolor(RGB(150,150,150));
				settextstyle(20, 0, _T("����"));
				TCHAR c[] = _T("��Ϸ����˵��");
				outtextxy(260, 50, c);
				TCHAR s[] = _T("1.��Ϸ����ʮ�ּ򵥣�ͨ������������ѡ�񡮽�����Ϸ����");
				outtextxy(60, 80, s);
				TCHAR t[] = _T("  ����Ϸ���á�������Ϸ����������ͨ���ո����ѡ��.");
				outtextxy(60, 120, t);
				TCHAR d[] = _T("2.ͨ���������ҿ���С���ƶ���");
				outtextxy(60, 150, d);

				//���������
				getchar();
				//�ػ���Ϸ���沢����ѡ���
				initstart();
				cur.left = 275;
				cur.top = 145;
				cur.right = 365;
				cur.bottom = 175;
			}
			//���cur.top == 235,�˳�����
			if(cur.top == 235)
			{
				break;
			}
		}
		Sleep(100);
	}
	getchar();// �����������
	closegraph();          // �ر�ͼ�ν���
}

void initstart()
{
	//���Ʊ߿򼰱���
	setlinestyle(PS_SOLID, 10, NULL);  //���ñ߿�����
	setlinecolor(BLUE | GREEN);      //���ñ߿���ɫ
	setfillcolor(0);//���ñ��������ɫ
	fillrectangle(0, 0, 640, 480);

	//��������
	settextcolor(RED | BLUE);
	settextstyle(20, 0, _T("����"));
	TCHAR c[] = _T("��ʼ��Ϸ");
	outtextxy(280, 150, c);
	TCHAR s[] = _T("��Ϸ����");
	outtextxy(280, 180, s);
	TCHAR t[] = _T("��Ϸ����");
	outtextxy(280, 210, t);
	TCHAR d[] = _T("�˳���Ϸ");
	outtextxy(280, 240, d);

	//����ѡ���
	setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
	setlinecolor(BLUE | YELLOW | RED);      //���ñ߿���ɫ
	rectangle(275, 145, 365, 175);
}

void clearscrip()
{
	//���Ʊ߿򼰱���
	setlinestyle(PS_SOLID, 10, NULL);  //���ñ߿�����
	setlinecolor(BLUE | GREEN);      //���ñ߿���ɫ
	setfillcolor(0);//���ñ��������ɫ
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
		//��ԭ����ѡ����ú�
		setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
		setlinecolor(0);      //���ñ߿���ɫ
		rectangle(rec.left, rec.top, rec.right, rec.bottom);
		//����ѡ���
		rec.top -= 30;
		rec.bottom -= 30;
		//�ػ�ѡ���
		setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
		setlinecolor(BLUE | YELLOW | RED);      //���ñ߿���ɫ
		rectangle(rec.left, rec.top, rec.right, rec.bottom);

	}
}

void selectdown(recposition& rec)
{
	if (rec.top < 205 && rec.bottom > rec.top)
	{
		//��ԭ����ѡ����ú�
		setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
		setlinecolor(0);      //���ñ߿���ɫ
		rectangle(rec.left, rec.top, rec.right, rec.bottom);
		//����ѡ���
		rec.top += 30;
		rec.bottom += 30;
		//�ػ�ѡ���
		setlinestyle(PS_SOLID, 1, NULL);  //���ñ߿�����
		setlinecolor(BLUE | YELLOW | RED);      //���ñ߿���ɫ
		rectangle(rec.left, rec.top, rec.right, rec.bottom);

	}
}
