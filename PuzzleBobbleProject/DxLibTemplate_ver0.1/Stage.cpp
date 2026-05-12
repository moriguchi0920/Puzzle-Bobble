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
				stageBubbles[i][j].reset();
			}
			else
			{
				bool isEven = i % 2 == 0;
				float x = isEven ? STAGE_OFFSET_X + BUBBLE_RADIUS * j * 2 + BUBBLE_RADIUS : STAGE_OFFSET_X + BUBBLE_RADIUS * j * 2 + BUBBLE_RADIUS * 2;
				float y = i * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS;

				Float2 position(x, y);
				stageBubbles[i][j] = BubbleGenerator::getInstance().generate(stageInfoBuffer[i][j], position, BUBBLE_RADIUS, false);
				stageBubbles[i][j].lock()->setState(Bubble::STATE::FIXED);

			}

		}
	}

	for (int i = 0; i < 2; i++)
	{
		Float2 begin(STAGE_OFFSET_X + i * 400, 0);
		Float2 end(STAGE_OFFSET_X + i * 400, 650);
		rWalls[i].set(begin, end);

		CLine* c = new CLine;
		cWalls[i].setShape(c);
		ShapeSetParam param(ShapeSetParam::PT_LINE_BOTH);
		param.param.paramPoint2.point1 = begin;
		param.param.paramPoint2.point2 = end;

		cWalls[i].getShape()->paramUpdate(&param);

		CollisionManager::getInstance()->addObject(&cWalls[i]);
		RenderableManager::getInstance()->addObject(&rWalls[i]);
	}

	CollisionManager::getInstance()->addObject(&cCeiling);
	RenderableManager::getInstance()->addObject(&rCeiling);

	BanishCount = 0;
	
	
	

	
}

void Stage::Update()
{
	
	ballista.updateProc(getExistColor());
	auto s = ballista.shootBubbles.front().lock();
	if (!s) return;

	if (s->getState() == Bubble::STATE::SHOOT
		&& s->hit())
	{
		s->setState(Bubble::STATE::FIXED);
		registerShootBubble(s);
		ballista.shootBubbles.pop();
	}


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

std::vector<int> Stage::getExistColor()
{
	// いったん色保存バッファをクリア
	stageExistColorBuffer.clear();

	// バブル配列の走査
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (i % 2 == 1 && 7 <= j)
			{
				continue;
			}
			if (!stageBubbles[i][j].lock()) continue;

			// std::findでvectorの中身を見て要素が存在しない(登録されていない色)だったら
			if (std::find(stageExistColorBuffer.begin(), stageExistColorBuffer.end(), stageBubbles[i][j].lock()->getColor()) == stageExistColorBuffer.end())
				// バッファに色情報を追加
				stageExistColorBuffer.push_back(stageBubbles[i][j].lock()->getColor());

		}
	}

	// 色情報バッファを返す
	return stageExistColorBuffer;
}

void Stage::registerShootBubble(std::weak_ptr<Bubble> shoot)
{ 
	auto s = shoot.lock();
	if (!s) return;

	float shootPosY = (s->getPos().y);

	int y = std::round(shootPosY / (BUBBLE_RADIUS * 2));

	float shootPosX = (s->getPos().x - STAGE_OFFSET_X - (y % 2 == 0 ? BUBBLE_RADIUS : BUBBLE_RADIUS * 2));

	int x = std::round(shootPosX / (BUBBLE_RADIUS * 2));

	if (COL < y) return;

	if (y % 2 == 0)
	{
		x = fix(x, 0, 8 - 1);
	}
	else
	{
		x = fix(x, 0, 7 - 1);
	}

	
 	if (stageBubbles[y][x].lock())
	{

		int setX = 0;
		int setY = 0;
		float nearDis = 10000.0f;
		for (int i = 0; i < DIRECTION; i++)
		{
			if (y % 2 == 0)
			{
				int offsetX = CheckIdxOffsetEven[i][0];
				int offsetY = CheckIdxOffsetEven[i][1];

				if (x + offsetX < 0 || ROW_EVEN <= x + offsetX) continue;
				if (y + offsetY < 0 || COL <= y + offsetY) continue;

				float dis = GetDistance(shootPosX, shootPosY, BUBBLE_RADIUS * (x + offsetX) * 2 + BUBBLE_RADIUS, (y + offsetY) * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS);




				if (dis < nearDis)
				{
					nearDis = dis;
					setX = offsetX;
					setY = offsetY;
				}
			}
			else
			{
				int offsetX = CheckIdxOffsetOdd[i][0];
				int offsetY = CheckIdxOffsetOdd[i][1];

				if (x + offsetX < 0 || ROW_ODD <= x + offsetX) continue;
				if (y + offsetY < 0 || COL <= y + offsetY) continue;

				float dis = GetDistance(shootPosX, shootPosY, BUBBLE_RADIUS * (x + offsetX) * 2 + BUBBLE_RADIUS * 2, (y + offsetY) * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS);


				if (dis < nearDis)
				{
					nearDis = dis;
					setX = offsetX;
					setY = offsetY;
				}

			}
			
		}
		x += setX;
		y += setY;
	}

		if (y % 2 == 0)
		{


			float posX = STAGE_OFFSET_X + BUBBLE_RADIUS * x * 2 + BUBBLE_RADIUS;
			float posY = y * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS;
			s->setPos(Float2(posX, posY));
		}
		else
		{


			float posX = STAGE_OFFSET_X + BUBBLE_RADIUS * x * 2 + BUBBLE_RADIUS * 2;
			float posY = y * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS;
			s->setPos(Float2(posX, posY));

		}
	
		s->setStage();


		stageBubbles[y][x] = shoot;
		BanishCount = 0;
		CheckBubbleMatch(y, x);
		Banish();
		resetBubbleCheck();
		for (int i = 0; i < stageBubbles[0].size(); i++)
		{
			if (stageBubbles[0][i].lock())
			{
				CheckBubbleFall(0, i);
			}
			
		}
		
		Fall();
		resetBubbleCheck();

}


bool Stage::CheckBubbleMatch(int colIdx, int rowIdx)
{ 
	if (!stageBubbles[colIdx][rowIdx].lock()) return false;
	// チェック済みならreturnして弾く
	if (stageBubbles[colIdx][rowIdx].lock()->getIsChecked()) return false;
	// ここを通っているということは少なくとも最初の一個目か一個目と同色なのでチェック済みに
	stageBubbles[colIdx][rowIdx].lock()->setIsChecked(true);

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
	for (int i = 0; i < DIRECTION; i++)
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
			if (nextCol % 2 == 0)
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_EVEN <= nextRow))
					continue;
			}
			else
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_ODD <= nextRow))
					continue;

			}


			if (!(stageBubbles[nextCol][nextRow].lock())) continue;

			// 引数に指定されたバブルの色と今見ているバブルの色が一致していたら
			if (stageBubbles[colIdx][rowIdx].lock()->getColor() == stageBubbles[nextCol][nextRow].lock()->getColor())
			{
				// 破壊カウントをカウントアップ
				BanishCount++;
				// 再帰
				CheckBubbleMatch(nextCol, nextRow);

			}
		}
		// 奇数の時
		else if (!isEven)
		{
			// 次回探索するバブルのインデックス
			int nextCol = colIdx + CheckIdxOffsetOdd[i][0];
			int nextRow = rowIdx + CheckIdxOffsetOdd[i][1];

			// インデックスがオーバーならcontinue
			if (nextCol % 2 == 0)
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_EVEN <= nextRow))
					continue;
			}
			else
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_ODD <= nextRow))
					continue;

			}

			if (!(stageBubbles[nextCol][nextRow].lock())) continue;

			// 引数に指定されたバブルの色と今見ているバブルの色が一致していたら
			if (stageBubbles[colIdx][rowIdx].lock()->getColor() == stageBubbles[nextCol][nextRow].lock()->getColor())
			{
				// 破壊カウントをカウントアップ
				BanishCount++;
				// 再帰
				CheckBubbleMatch(nextCol, nextRow);

			}
		}

			
	}
	
	// 何も見つからなかったら終了
	return true;
}

bool Stage::CheckBubbleFall(int colIdx, int rowIdx)
{

	// 存在しないならreturnして弾く
	if (!stageBubbles[colIdx][rowIdx].lock()) return false;
	// チェック済みならreturnして弾く
	if (stageBubbles[colIdx][rowIdx].lock()->getIsChecked()) return false;
	// ここを通っているということは少なくとも最初の一個目か一個目と同色なのでチェック済みに
	stageBubbles[colIdx][rowIdx].lock()->setIsChecked(true);

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
	for (int j = 0; j < DIRECTION; j++)
	{
		// 偶数列かどうか判定用変数
		bool isEven = colIdx % 2 == 0;
		// 偶数の時
		if (isEven)
		{
			// 次回探索するバブルのインデックス
			int nextCol = colIdx + CheckIdxOffsetEven[j][0];
			int nextRow = rowIdx + CheckIdxOffsetEven[j][1];

			// インデックスがオーバーならcontinue
			if (nextCol % 2 == 0)
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_EVEN <= nextRow))
					continue;
			}
			else
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_ODD <= nextRow))
					continue;

			}

			// 次見に行くバブルが存在しないならcontinue
			if (!stageBubbles[nextCol][nextRow].lock()) continue;


			// 再帰
			CheckBubbleFall(nextCol, nextRow);


		}
		// 奇数の時
		else if (!isEven)
		{
			// 次回探索するバブルのインデックス
			int nextCol = colIdx + CheckIdxOffsetOdd[j][0];
			int nextRow = rowIdx + CheckIdxOffsetOdd[j][1];

			// インデックスがオーバーならcontinue
			if (nextCol % 2 == 0)
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_EVEN <= nextRow))
					continue;
			}
			else
			{
				if ((nextCol < 0 || nextRow < 0 || COL <= nextCol || ROW_ODD <= nextRow))
					continue;

			}

			// 次見に行くバブルが存在しないならcontinue
			if (!stageBubbles[nextCol][nextRow].lock()) continue;


			// 再帰
			CheckBubbleFall(nextCol, nextRow);

		}

	}
		



	// 何も見つからなかったら終了
	return true;
}

void Stage::resetBubbleCheck()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (i % 2 == 1 && 7 <= j)
			{
				continue;
			}
			if (!stageBubbles[i][j].lock()) continue;

			stageBubbles[i][j].lock()->setIsChecked(false);
		}
	}
}

void Stage::Banish()
{
	if (3 <= BanishCount)
	{
		for (int i = 0; i < COL; i++)
		{
			for (int j = 0; j < ROW_EVEN; j++)
			{
				if (i % 2 == 1 && 7 <= j)
				{
					continue;
				}

				if (!stageBubbles[i][j].lock()) continue;

				if (stageBubbles[i][j].lock()->getIsChecked() == true)
				{
					stageBubbles[i][j].lock()->deactivate();
					stageBubbles[i][j].reset();
				}


			}
		}

	}
	BanishCount = 0;


}

void Stage::Fall()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (i % 2 == 1 && 7 <= j)
			{
				continue;
			}
			if (!stageBubbles[i][j].lock()) continue;

			if (stageBubbles[i][j].lock()->getIsChecked() == false)
			{
				stageBubbles[i][j].lock()->setState(Bubble::STATE::FALL);
			}

		}
	}
}

Stage::Ballista::Ballista()
{
	RenderableManager::getInstance()->addObject(&rLine);
	rotation = -PI / 2;
	Float2 base(BALLISTA_BASE_X, BALLISTA_BASE_Y);
	Float2 top(base.x, base.y - 50.0f);

	state = Ballista::DEFAULT;
	rLine.set(base, top);
}

Stage::Ballista::~Ballista()
{
}


void Stage::Ballista::shoot()
{
	shootBubbles.front().lock()->setVector(Float2(cosf(rotation), sinf(rotation)));
	shootBubbles.front().lock()->setState(Bubble::SHOOT);
}

void Stage::Ballista::wait()
{
	if (CheckHitKey(KEY_INPUT_LEFT) && -3.14 <= rotation)
	{
		rotation -= 0.05;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)  && rotation <= 3.14)
	{
		rotation += 0.05;
	}
	rLine.set(Float2(BALLISTA_BASE_X, BALLISTA_BASE_Y), Float2(BALLISTA_BASE_X + 50.0f * cosf(rotation), BALLISTA_BASE_Y + 50.0f * sinf(rotation)));
	

}

void Stage::Ballista::reload(std::vector<int> colorBuffer)
{
	Float2 pos(200.0, 500.0);
	if (colorBuffer.size() <= 0) return;

	int r = GetRand(colorBuffer.size() - 1);


	shootBubbles.push(BubbleGenerator::getInstance().generate(colorBuffer[r], pos, BUBBLE_RADIUS, true));

}

void Stage::Ballista::updateProc(std::vector<int> colorBuffer)
{
	if (shootBubbles.size() == 0)
	{
		reload(colorBuffer);
		shootBubbles.front().lock()->setState(Bubble::STATE::RELOAD);
	}
	auto s = shootBubbles.front().lock();
	if (!s) return;



	switch (state)
	{
	case BALLISTA_STATE::DEFAULT:
		if (shootBubbles.front().lock()->getState() == Bubble::STATE::READY)
		{
			reload(colorBuffer);
			state = BALLISTA_STATE::WAIT;
		}
		break;
	case BALLISTA_STATE::RELOAD:
		shootBubbles.back().lock()->setState(Bubble::STATE::RELOAD);
		state = BALLISTA_STATE::DEFAULT;
		break;
	case BALLISTA_STATE::WAIT:
		wait();
		if (pushHitKey(KEY_INPUT_SPACE))
		{
			shoot();

			state = BALLISTA_STATE::RELOAD;
		}
		break;

	}
}

std::weak_ptr<Bubble> Stage::Ballista::getShooted()
{
	auto s = shootBubbles.front().lock();

	return s;
}


