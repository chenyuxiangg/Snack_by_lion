#ifndef GAME_H
#define GAME_H
#include "snack.h"
#include "food.h"

enum Gamestate{
	GSMENU,GSSET,GSHELP,GSRUN,GSRUNING,GSOVER,GSEND
};

typedef struct CYXRECT{
	int left;
	int right;
	int top;
	int bottom;
}Rect_cyx;

class Game{
public:
	Game();
	~Game();
	void UpdateUI();
	void InputHandle();
	
private:
	void ShowMenu();
	void ShowSet();
	void ShowHelp();
	void ShowStart();
	void ShowRunning();
	void ShowOver();
	void ShowEnd();
	void CleanUI();
	
	void HandleMenu();
	void HandleSet();
	void HandleHelp();
	void HandleStart();
	void HandleRunning();
	void HandleOver();
	void HandleEnd(); 
	
	void SelectUp(Rect_cyx& rect);
	void SelectDown(Rect_cyx& rect, int top); 
	
public:
	Food* m_foods;
	Snack* m_snack;
	bool m_gameend;
	Gamestate m_state;
};

#endif
