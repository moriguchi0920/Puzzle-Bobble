#include "Stage.h"




Stage::Stage(std::vector<int*> stageInfoBuffer) : Task(TaskManager::getInstance()->generateId())
{
	for (int i = 0; i < COL; i++)
	{
			this->stageBubbles[i].resize(i % 2 == 0 ? 8 : 7);
	}

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (stageInfoBuffer[i][j] <= Bubble::COLOR::COL_DEFAULT) continue;

			bool isEven = i % 2 == 0;
			float x = isEven ? BUBBLE_RADIUS * i * 2 : BUBBLE_RADIUS * i * 2 + BUBBLE_RADIUS;
			float y = j * BUBBLE_RADIUS * 2;

			Float2 position(x, y);
			stageBubbles[i][j] = new Bubble(stageInfoBuffer[i][j], position, BUBBLE_RADIUS);
		}
	}




}

void Stage::Update()
{
}

bool Stage::Destroy()
{
	return false;
}

bool Stage::CheckBubbleMatch(int colIdx, int rowIdx)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bool isEven;

				if (stageBubbles[colIdx][rowIdx]->getColor() == stageBubbles)
				{

			}
		}
	}



	return false;
}
