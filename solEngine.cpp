#include "solEngine.h"

void SolEngine::StartNewBoard(int variant)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (x == 3 && y == 3)
			{
				SolBoard[y][x] = 0;
			}
			else if (y > 1 && y < 5)
			{
				SolBoard[y][x] = 1;
			}
			else if (x > 1 && x < 5)
			{
				SolBoard[y][x] = 1;
			}
			else
			{
				SolBoard[y][x] = -1;
			}
		}
		if (variant != 0)
		{
			SolBoard[1][1] = 1;
			SolBoard[1][5] = 1;
			SolBoard[5][1] = 1;
			SolBoard[5][5] = 1;
		}
	}
}

bool SolEngine::MovePiece(int sx, int sy, int gx, int gy)
{
	if (sx >= 0 && sx < 7 && sy >= 0 && sy < 7 && gx >= 0 && gx < 7 && gy >= 0 && gy < 7)
	{
		if (gy == sy && gx == sx + 2)
		{
			if (SolBoard[sy][sx] == 1 && SolBoard[sy][sx + 1] == 1 && SolBoard[gy][gx] == 0)
			{
				SolBoard[gy][gx] = 1;
				SolBoard[sy][sx + 1] = 0;
				SolBoard[sy][sx] = 0;
				return true;
			}
		}
		if (gy == sy && gx == sx - 2)
		{
			if (SolBoard[sy][sx] == 1 && SolBoard[sy][sx - 1] == 1 && SolBoard[gy][gx] == 0)
			{
				SolBoard[gy][gx] = 1;
				SolBoard[sy][sx - 1] = 0;
				SolBoard[sy][sx] = 0;
				return true;
			}
		}
		if (gy == sy + 2 && gx == sx)
		{
			if (SolBoard[sy][sx] == 1 && SolBoard[sy + 1][sx] == 1 && SolBoard[gy][gx] == 0)
			{
				SolBoard[gy][gx] = 1;
				SolBoard[sy + 1][sx] = 0;
				SolBoard[sy][sx] = 0;
				return true;
			}
		}
		if (gy == sy - 2 && gx == sx)
		{
			if (SolBoard[sy][sx] == 1 && SolBoard[sy - 1][sx] == 1 && SolBoard[gy][gx] == 0)
			{
				SolBoard[gy][gx] = 1;
				SolBoard[sy - 1][sx] = 0;
				SolBoard[sy][sx] = 0;
				return true;
			}
		}
	}
	return false;
}

int SolEngine::CheckLeftPieces()
{
	int count = 0;
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (SolBoard[y][x] == 1)
			{
				count++;
			}
		}
	}
	if (count == 1 && SolBoard[3][3] == 1)
	{
		return -1;
	}
	else
	{
		return count;
	}
}

int SolEngine::GetBoardNum(int x, int y)
{
	return SolBoard[y][x];
}

QString SolEngine::GetSolName(int x, int y)
{
	return SolNames[y][x];
}
