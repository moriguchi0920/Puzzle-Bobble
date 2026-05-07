#include "Stage.h"




Stage::Stage(std::vector<int>* stageInfoBuffer) : Task(TaskManager::getInstance()->generateId())
{


	for (int i = 0; i < COL; i++)
	{
			this->stageBubbles[i].resize(i % 2 == 0 ? 8 : 7);
	}



	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (i % 2 == 1 && 7 <= j)
			{
				continue;
			}
			if (stageInfoBuffer[i][j] <= Bubble::COLOR::COL_DEFAULT)
			{
				stageBubbles[i][j] = nullptr;
			}
			else
			{
				bool isEven = i % 2 == 0;
				float x = isEven ? 100 + BUBBLE_RADIUS * i * 2 : 100 + BUBBLE_RADIUS * i * 2 + BUBBLE_RADIUS;
				float y = j * 100 + BUBBLE_RADIUS * 2;

				Float2 position(x, y);
				stageBubbles[i][j] = std::make_shared<Bubble>(stageInfoBuffer[i][j], position, BUBBLE_RADIUS);


			}

		}
	}

	for (int i = 0; i < 2; i++)
	{
		Float2 begin(75 + i * 500, 0);
		Float2 end(75 + i * 500, 650);
		rWalls[i].set(begin, end);

		CollisionManager::getInstance()->addObject(&cWalls[i]);
		RenderableManager::getInstance()->addObject(&rWalls[i]);
	}

	CollisionManager::getInstance()->addObject(&cCeiling);
	RenderableManager::getInstance()->addObject(&rCeiling);

	VanishCount = 0;
	

}

void Stage::Update()
{



}

bool Stage::Destroy()
{
	return false;
}

void Stage::activateProc()
{
}

void Stage::deactivateProc()
{
}

bool Stage::CheckBubbleMatch(int colIdx, int rowIdx)
{
	if (!stageBubbles[colIdx][rowIdx]) return false;
	// チェック済みならreturnして弾く
	if (stageBubbles[colIdx][rowIdx]->getIsChecked()) return false;
	// ここを通っているということは少なくとも最初の一個目か一個目と同色なのでチェック済みに
	stageBubbles[colIdx][rowIdx]->setIsChecked(true);

	// 縦のインデックスで場合分け
	switch (colIdx % 2)
	{
	case 0:
		// インデックスがオーバーならreturnで弾く
		if (colIdx < 0 || COL <= colIdx || rowIdx < 0 || ROW_EVEN <= rowIdx)
			return false;
		break;

	case 1:
		// インデックスがオーバーならreturnで弾く
		if (colIdx < 0 || COL <= colIdx || rowIdx < 0 || ROW_ODD <= rowIdx)
			return false;
		break;
	}

	// 六方向をforで見回る
	for (int i = 0; i < 6; i++)
	{
		// 偶数列かどうか判定用変数
		bool isEven = colIdx % 2 == 0;
		// 偶数の時
		if (isEven)
		{
			// 次回探索するバブルのインデックス
			int nextCol = colIdx + CheckIdxOffsetEven[i][0];
			int nextRow = rowIdx + CheckIdxOffsetEven[i][1];

			// インデックスがオーバーならcontinue
			if (nextCol < 0 ||  nextRow < 0 || COL < nextCol || ROW_ODD < nextRow)
				continue;

			if (stageBubbles[colIdx + CheckIdxOffsetEven[i][0]][rowIdx + CheckIdxOffsetEven[i][1]]) continue;

			// 引数に指定されたバブルの色と今見ているバブルの色が一致していたら
			if (stageBubbles[colIdx][rowIdx]->getColor() == stageBubbles[colIdx + CheckIdxOffsetEven[i][0]][rowIdx + CheckIdxOffsetEven[i][1]]->getColor())
			{
				// 破壊カウントをカウントアップ
				VanishCount++;
				// 再帰
				CheckBubbleMatch(colIdx + CheckIdxOffsetEven[i][0], rowIdx + CheckIdxOffsetEven[i][1]);

			}
		}
		// 奇数の時
		else if (!isEven)
		{
			// 次回探索するバブルのインデックス
			int nextCol = colIdx + CheckIdxOffsetOdd[i][0];
			int nextRow = rowIdx + CheckIdxOffsetOdd[i][1];

			// インデックスがオーバーならcontinue
			if (nextCol < 0 || nextRow < 0 || COL < nextCol || ROW_EVEN < nextRow)
				continue;

			if (stageBubbles[colIdx + CheckIdxOffsetEven[i][0]][rowIdx + CheckIdxOffsetEven[i][1]]) continue;

			// 引数に指定されたバブルの色と今見ているバブルの色が一致していたら
			if (stageBubbles[colIdx][rowIdx]->getColor() == stageBubbles[colIdx + CheckIdxOffsetOdd[i][0]][rowIdx + CheckIdxOffsetOdd[i][1]]->getColor())
			{
				// 破壊カウントをカウントアップ
				VanishCount++;
				// 再帰
				CheckBubbleMatch(colIdx + CheckIdxOffsetOdd[i][0], rowIdx + CheckIdxOffsetOdd[i][1]);

			}
		}

			
	}
	
	// 何も見つからなかったら終了
	return true;
}

void Stage::Vanish()
{



}
