#pragma once
class Board
{
private:
	int sidelength;
	int** possiblePlacements;
	int* queens;

	long long fundamentalSolutions;
	long long allSolutions;

	bool PlaceQueen(int y, int lastPos);
	int RemoveQueen(int y);
	void MarkBoard(int x, int y, bool mark);
	bool CompareToPointMirror();
	bool CompareToRotation();

public:
	Board(int sidelength);
	~Board();
	void CalculateSolutions();
	int GetAllSolutions();
	int GetFundamentalSolutions();
};
