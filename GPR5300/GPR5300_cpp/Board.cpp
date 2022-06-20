#include "Board.h"
#include <stdlib.h>

Board::Board(int sidelength)
{
	this->sidelength = sidelength;

	fundamentalSolutions = 0;
	allSolutions = 0;

	possiblePlacements = (int**)malloc(sidelength * sizeof(int*));
	queens = (int*)malloc(sidelength * sizeof(int));

	for (int i = 0; i < sidelength; i++)
	{
		if (possiblePlacements)
			possiblePlacements[i] = (int*)malloc(sidelength * sizeof(int));
	}
}

Board::~Board()
{
	for (int i = 0; i < sidelength; i++)
		free(possiblePlacements[i]);
	free(possiblePlacements);
	free(queens);
}

void Board::CalculateSolutions()
{
	int currentY = 0;
	int lastPos = 0;

	for (int i = 0; i < sidelength; i++)
	{
		queens[i] = -1;
		for (int j = 0; j < sidelength; j++)
			possiblePlacements[i][j] = 0;
	}

	while (true)
	{
		if (PlaceQueen(currentY, lastPos))
		{
			lastPos = 0;
			currentY++;
			if (currentY == sidelength)
			{
				allSolutions++;
				fundamentalSolutions++;

				if (CompareToPointMirror())
					fundamentalSolutions++;
				if (CompareToRotation())
					fundamentalSolutions += 2;

				currentY--;
				lastPos = RemoveQueen(currentY) + 1;
			}
		}
		else
		{
			currentY--;
			if (currentY == -1)
				break;
			lastPos = RemoveQueen(currentY) + 1;
		}
	}

	fundamentalSolutions >>= 3;
}

int Board::GetAllSolutions()
{
	return allSolutions;
}

int Board::GetFundamentalSolutions()
{
	return fundamentalSolutions;
}

bool Board::PlaceQueen(int y, int lastPos)
{
	for (int i = lastPos; i < sidelength; i++)
	{
		if (possiblePlacements[i][y] == 0)
		{
			queens[y] = i;
			MarkBoard(i, y, true);
			return true;
		}
	}
	return false;
}

int Board::RemoveQueen(int y)
{
	int pos = queens[y];
	MarkBoard(pos, y, false);
	queens[y] = -1;
	return pos;
}

void Board::MarkBoard(int x, int y, bool mark)
{
	int spacesDown = sidelength - y;
	int value = mark ? 1 : -1;
	for (int i = 1; i < spacesDown; i++)
	{
		y++;
		possiblePlacements[x][y] += value;
		if (x - i > -1)
			possiblePlacements[x - i][y] += value;
		if (x + i < sidelength)
			possiblePlacements[x + i][y] += value;
	}
}

bool Board::CompareToPointMirror()
{
	int max = sidelength - 1;
	for (int i = 0; i < sidelength; i++)
	{
		if (max - queens[max - i] != queens[i])
			return false;
	}
	return true;
}

bool Board::CompareToRotation()
{
	int max = sidelength - 1;
	for (int i = 0; i < sidelength; i++)
	{
		if (max - i != queens[queens[i]])
			return false;
	}
	return true;
}