#include "Gra_solution.h"  //��� easyxͼ�ο��ڸð汾vs�еĴ�������
#include "game.h"

int main(int argc, char* argv[]) {
	Game* snack = new Game();
	while (!snack->m_gameend) {
		snack->UpdateUI();
		snack->InputHandle();
		Sleep(snack->m_snack->m_speed);
	}

	delete snack;
	snack = NULL;
	return 0;
}



