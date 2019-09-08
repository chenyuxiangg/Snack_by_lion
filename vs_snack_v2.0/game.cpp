#include "game.h"
#include <stdio.h>
#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000?1:0)

Game::Game():m_state(GSMENU),m_gameend(false) {
	initgraph(640, 480);   // ��ʼ������̨
	m_foods = new Food();
	m_snack = new Snack(50);
}

Game::~Game() {
	if(m_foods != NULL) {
		delete m_foods;
		m_foods = NULL;
	}
	if (m_snack != NULL) {
		delete m_snack;
		m_snack = NULL;
	}
	
}

void Game::UpdateUI() {
	switch (m_state) {
		case GSMENU: {
				ShowMenu();
				break;
			}
		case GSSET: {
				ShowSet();
				break;
			}
		case GSHELP: {
				ShowHelp();
				break;
			}
		case GSRUN: {
				ShowStart();
				break;
			}
		case GSRUNING: {
				ShowRunning();
				break;
			}
		case GSOVER: {
				ShowOver();
				break;
			}
		case GSEND: {
				ShowEnd();
				break;
			}
		default:
			break;
	}
}

void Game::InputHandle() {
	switch (m_state) {
		case GSMENU: {
				HandleMenu();
				break;
			}
		case GSSET: {
				HandleSet();
				break;
			}
		case GSHELP: {
				HandleHelp();
				break;
			}
		case GSRUN: {
				HandleStart();
				break;
			}
		case GSRUNING: {
				HandleRunning();
				break;
			}
		case GSOVER: {
				HandleOver();
				break;
			}
		case GSEND: {
				HandleEnd();
				break;
			}
		default:
			break;
	}
}

void Game::ShowMenu() {
	CleanUI();

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

void Game::ShowSet() {

	CleanUI();

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
}

void Game::ShowHelp() {

	CleanUI();

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
}

void Game::ShowStart() {

}

void Game::ShowRunning() {
	CleanUI();
	m_foods->Product();
	m_snack->Draw();
}

void Game::ShowOver() {
	
}

void Game::ShowEnd() {

}

void Game::CleanUI() {
	//���Ʊ߿򼰱���
	setlinestyle(PS_SOLID, 10, NULL);  //���ñ߿�����
	setlinecolor(BLUE | GREEN);      //���ñ߿���ɫ
	setfillcolor(0);//���ñ��������ɫ
	fillrectangle(0, 0, 640, 480);
}

void Game::HandleMenu() {
	//ͨ�����̵����¼�ѡ��
	Rect_cyx cur;//��ǰ���ο�
	cur.left = 275;
	cur.top = 145;
	cur.right = 365;
	cur.bottom = 175;

	while (1) {
		//ѡ��������
		if (KEY_DOWN(VK_UP)) {
			SelectUp(cur);
		}else if (KEY_DOWN(VK_DOWN)) {
			SelectDown(cur, 235);
		}else if (KEY_DOWN(VK_SPACE)) {
			if (cur.top == 145) {
				m_state = GSRUN;
				break;
			}else if (cur.top == 175) {
				m_state = GSSET;
				break;
			}else if (cur.top == 205) {
				m_state = GSHELP;
				break;
			}else if (cur.top == 235) {
				m_state = GSEND;
				break;
			}
		}
		Sleep(100);
	}
}

void Game::HandleSet() {
	//��ʼ�����λ��
	Rect_cyx cur;
	cur.left = 275;
	cur.top = 145;
	cur.right = 365;
	cur.bottom = 175;

	//ѡ��������ı�־
	bool selectenter = false;
	//ѡ��ģʽ
	while (!selectenter) {
		//ѡ��������ƶ�
		if (KEY_DOWN(VK_UP)) {
			SelectUp(cur);
		}else if (KEY_DOWN(VK_DOWN)) {
			SelectDown(cur, 205);
		}else if(KEY_DOWN(VK_RETURN)) {
			selectenter = true;
			if (cur.top == 145) {
				m_snack->m_speed = 50;
			}else if (cur.top == 175) {
				m_snack->m_speed = 20;
			}else if(cur.top == 205) {
				m_snack->m_speed = 10;
			}
		}

		if(selectenter == true) {
			m_state = GSMENU;
		}
		Sleep(100);
	}
}

void Game::HandleHelp() {
	getchar();
	m_state = GSMENU;
}

void Game::HandleStart() {
	m_state = GSRUNING;
}

void Game::HandleRunning() {
	if (KEY_DOWN(VK_UP) && m_snack->m_head->dir != ddown) {
		m_snack->m_head->dir = dup;
	}else if (KEY_DOWN(VK_LEFT) && m_snack->m_head->dir != dright) {
		m_snack->m_head->dir = dleft;
	}else if (KEY_DOWN(VK_DOWN) && m_snack->m_head->dir != dup) {
		m_snack->m_head->dir = ddown;
	}else if (KEY_DOWN(VK_RIGHT) && m_snack->m_head->dir != dleft) {
		m_snack->m_head->dir = dright;
	}
	
	//����С�ߵ��߼�
	m_snack->Move();
	int x = m_snack->m_head->x + 2;
	int y = m_snack->m_head->y;
	if (x <= 628 && y <= 468 && x >= 18 && y >= 18) {
		int foodx = m_foods->m_x;
		int foody = m_foods->m_y;
		
		if (x >= foodx-m_foods->m_radius && y >= foody-m_foods->m_radius \
			&& x <= foodx+m_foods->m_radius && y <= foody + m_foods->m_radius) {
			m_foods->m_exist = false;
			m_snack->Grow();
		}
	}else {
		m_state = GSOVER;
	}
}

void Game::HandleOver() {
	m_state = GSMENU;
	delete m_snack;
	delete m_foods;
	m_foods = NULL;
	m_snack = NULL;

	m_snack = new Snack(50);
	m_foods = new Food();
}

void Game::HandleEnd() {
	m_gameend = true;
}

void Game::SelectUp(Rect_cyx& rec) {
	if (rec.top > 145 && rec.bottom > rec.top) {
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

void Game::SelectDown(Rect_cyx& rec, int top) {
	if (rec.top < top && rec.bottom > rec.top) {
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
