#pragma once
#include <iostream>
#include "Position.h"

using namespace std;

class PacMap
{
	static constexpr int MAP_X = 28;
	static constexpr int MAP_Y = 31;

	int** TileMap;
	POSITION endPos;
public:
	PacMap(POSITION pos);
	PacMap(const PacMap& _Value);
	~PacMap();

	PacMap& operator=(const PacMap& _Value) 
	{
		if (this != &_Value) {
			for (int i = 0; i < MAP_Y; i++)
			{
				delete[] TileMap[i];
			}
			delete[] TileMap;

			TileMap = new int* [MAP_Y];
			for (int i = 0; i < MAP_Y; i++)
			{
				TileMap[i] = new int[MAP_X];
			}

			for (int i = 0; i < MAP_Y; i++)
			{
				for (int j = 0; j < MAP_X; j++)
				{
					TileMap[i][j] = _Value.TileMap[i][j];
				}
			}
		}
		return *this;
	}
	// �� ���� �ʱ�ȭ
	void InitMap();

	// �� �׸���
	void DrawMap();

	// ������ �� �ִ� �ٴ��ΰ� Ȯ���ϰ� ������
	bool Move(POSITION& pos, int dir);

	int getHeight() { return MAP_Y; }
	int getWidth() { return MAP_X; }
	int** getTileMap() { return TileMap; }

	void setTile(POSITION pos, int num) { TileMap[pos.Y][pos.X] = num; }
	void setEndPos(POSITION pos) { endPos = pos; }
};

