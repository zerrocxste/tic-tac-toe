#include "game_logic.h"

CGameLogic g_pGameLogic;
//основной метод игровой логики, алгоритмы нахождение пересечения игровых линий, все здесь
void CGameLogic::Run()
{
	INIT(std::cout << __FUNCTION__ << " -> running!" << std::endl << std::endl;)

	for (int player = 0; player < 2; player++)
	{
		if (status_with_player[0][player] && status_with_player[1][player] && status_with_player[2][player] // gorizonatl'
			|| status_with_player[3][player] && status_with_player[4][player] && status_with_player[5][player]
			|| status_with_player[6][player] && status_with_player[7][player] && status_with_player[8][player])
		{
			win[player] = true;
			std::cout << __FUNCTION__ << " -> detect type: HORIZONTAL" << std::endl;
		}
		if (status_with_player[0][player] && status_with_player[3][player] && status_with_player[6][player] // vertical'
			|| status_with_player[1][player] && status_with_player[4][player] && status_with_player[7][player]
			|| status_with_player[2][player] && status_with_player[5][player] && status_with_player[8][player])
		{
			win[player] = true;
			std::cout << __FUNCTION__ << " -> detect type: VERTICAL" << std::endl;
		}	
		if (status_with_player[0][player] && status_with_player[4][player] && status_with_player[8][player] // diagonal'
			|| status_with_player[2][player] && status_with_player[4][player] && status_with_player[6][player])
		{
			win[player] = true;
			std::cout << __FUNCTION__ << " -> detect type: DIAGONAL" << std::endl;	
		}
	}

	if (status_without_player[0] && status_without_player[1] && status_without_player[2] // overflow
		&& status_without_player[3] && status_without_player[4] && status_without_player[5]
		&& status_without_player[6] && status_without_player[7] && status_without_player[8]
		&& !win[0] && !win[1])
	{
		win[2] = true;
		std::cout << __FUNCTION__ << " -> detect type: OVERFLOW" << std::endl;
	}
}