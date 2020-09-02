#pragma once

#include "../defines.h"
#include "../krestiki_noliki.h"

class CGameLogic
{
private:
	bool status_with_player[9][2];
	bool status_without_player[9];
	bool win[3];
public:
	//����� �������� ������� ������ �� ��� ������
	void StatusSet(const int num, const int player)
	{
		status_with_player[num][player] = true;
		status_without_player[num] = true;
		std::cout << __FUNCTION__ << " -> num: " << num << ", player: " << player << std::endl << std::endl;
	}
	//����� ����������� ������ ������� ������ � ������ ������
	bool GetStatus(const int cell)
	{
		return status_without_player[cell];
	}
	//����� ����������� ������ ������� ������ � ������ ������
	bool GetStatusWithPlaya(const int cell, const int player)
	{
		return status_with_player[cell][player];
	}
	//����� �������� ������ � ���������� ������, ���� ������� �������
	int GetWinStatus()
	{
		if (win[0])
			return 1;
		else if (win[1])
			return 2;
		else if (win[2])
			return 3;
		
		return 0;
	}
	//����� ��������������� / ��������� ������� ������
	void Reset()
	{
		for (int i = 0; i < 9; i++)
		{
			status_without_player[i] = false;
			for (int j = 0; j < 2; j++)
			{
				status_with_player[i][j] = false;	
			}
		}
		for (int j = 0; j < 3; j++)
		{
			win[j] = false;
		}
		std::cout << __FUNCTION__ " -> reset" << std::endl << std::endl;
	}
	//�������� �������� �������
	void Run();
};
extern CGameLogic g_pGameLogic;