#include "Gra_solution.h"  //解决 easyx图形库在该版本vs中的错误问题
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



