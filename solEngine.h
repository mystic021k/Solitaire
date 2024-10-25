#pragma once
#include <QString>

class SolEngine
{
private:
	int SolBoard[7][7];
	QString SolNames[7][7] = { 
		{"A7", "B7", "C7", "D7", "E7", "F7", "G7"},
		{"A6", "B6", "C6", "D6", "E6", "F6", "G6"},
		{"A5", "B5", "C5", "D5", "E5", "F5", "G5"},
		{"A4", "B4", "C4", "D4", "E4", "F4", "G4"},
		{"A3", "B3", "C3", "D3", "E3", "F3", "G3"},
		{"A2", "B2", "C2", "D2", "E2", "F2", "G2"},
		{"A1", "B1", "C1", "D1", "E1", "F1", "G1"}
	};
public:
	void StartNewBoard(int variant);
	bool MovePiece(int sx, int sy, int gx, int gy);
	int CheckLeftPieces();
	int GetBoardNum(int x, int y);
	QString GetSolName(int x, int y);
};

