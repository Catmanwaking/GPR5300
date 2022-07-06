#pragma once
#include <vector>
class Board
{
private:
	int sidelength;
	std::vector<std::vector<int>> possiblePlacements;
	std::vector<int> queens;

	long long fundamentalSolutions;
	long long allSolutions;

	bool PlaceQueen(int y, int lastPos);
	int RemoveQueen(int y);
	void MarkBoard(int x, int y, bool mark);
	bool CompareToPointMirror();
	bool CompareToRotation();

public:
	Board(int sidelength);
	void CalculateSolutions();
	int GetAllSolutions();
	int GetFundamentalSolutions();
};
