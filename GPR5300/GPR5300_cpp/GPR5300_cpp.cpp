// GPR5300_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Board.h"

int main()
{
	SetConsoleTitle(L"N Queens Problem");

	std::cout << "The n queens problem consists of placing n non-attaking queens on an n*n chessboard." << std::endl;
	std::cout << "Please enter the maximum size of the chessboard to be used fo calculation (14 and above are slow)." << std::endl;

	std::cout << "n-max=";
	int maxValue;
	std::cin >> maxValue;

	for (int i = 4; i <= maxValue; i++)
	{
		Board board = Board(i);
		board.CalculateSolutions();
		int fundamental = board.GetFundamentalSolutions();
		int all = board.GetAllSolutions();

		std::cout << "n=" << std::setw(3) << std::setfill(' ') << i
			<< " => fundamental:" << std::setw(12) << std::setfill(' ') << fundamental
			<< ", all:" << std::setw(12) << std::setfill(' ') << all
			<< std::endl;
	}

	system("pause");

	return 0;
}