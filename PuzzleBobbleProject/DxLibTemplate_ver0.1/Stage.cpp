#include "Stage.h"
#include"AnimationRepository.h"



Stage::Stage(std::vector<int>* stageInfoBuffer) :
	Task(TaskManager::getInstance()->generateId()),
	rBackground(0.0f, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_BG)),
	rGround(0.1f, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_GROUND)),
	rBandleFront(0.6f, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_BANDLE_2)),
	rBandleBack(0.2f, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_BANDLE_1))
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
				float y = i * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS * 4;

				Float2 position(x, y);
				stageBubbles[i][j] = BubbleGenerator::getInstance().generate(stageInfoBuffer[i][j], position, BUBBLE_RADIUS, false);
				stageBubbles[i][j].lock()->setState(Bubble::STATE::FIXED);

			}

		}
	}

	for (int i = 0; i < 2; i++)
	{
		Float2 begin(STAGE_OFFSET_X + i * BUBBLE_RADIUS * 2 * 8.0f, 0);
		Float2 end(STAGE_OFFSET_X + i * BUBBLE_RADIUS * 2 * 8.0f, WINDOW_HEIGHT);
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
	
	
	pushCeilingCol = 0;

	deadLineCol = 12;

	isShake = false;

	rBackground.setPos(Float2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	RenderableManager::getInstance()->addObject(&rBackground);

	rGround.setPos(Float2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 8));
	RenderableManager::getInstance()->addObject(&rGround);

	rBandleFront.setPos(Float2(WINDOW_WIDTH / 2 - 84 - 15, BALLISTA_BASE_Y + 28 + 1));

	RenderableManager::getInstance()->addObject(&rBandleFront);

	rBandleBack.setPos(Float2(WINDOW_WIDTH / 2 - 84, BALLISTA_BASE_Y + 28));
	RenderableManager::getInstance()->addObject(&rBandleBack);


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




	if (isShake)
	{
		float offset = 5 <= ballista.shootNum ? 0.2f : 0.1f;

		shakeState = (shakeState++) % 4;
		if (shakeState <= 2)
		{
			Shake(offset);
		}
		else
		{
			SetHome();
		}

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
	// shootは発射されたバブルのweak_ptr
 	auto s = shoot.lock();
	// shootが存在していなかったらreturn
	if (!s) return;

	const float cellHeight = BUBBLE_RADIUS * 2.0f;

	// shootの位置から、きれいに並べるためのxとyのインデックスを計算する
	// インデックス計算のために、天井が押し下げられた分を考慮して位置を補正する
	// 相対座標として天井の位置を0とするため、y座標から天井が押し下げられた分を引く
	float shootPosY = (s->getPos().y - (pushCeilingCol * cellHeight) - BUBBLE_RADIUS * 4 );



	// Bubbleの半径の2倍で割って四捨五入することで、きれいに並べるためのyのインデックスを計算
	int y = std::round(shootPosY / (cellHeight));


	// 列のずれは (行 + pushCeilingCol) の偶奇で決まるのでそれを使って X の基準を決める
	bool screenRowEven = ((y + pushCeilingCol) % 2 == 0);
	float alignmentOffset = screenRowEven ? BUBBLE_RADIUS : BUBBLE_RADIUS * 2.0f;

	// xのインデックスは、偶数列と奇数列でずれているため、yの偶奇で場合分けして計算する
	float shootPosX = (s->getPos().x - STAGE_OFFSET_X - alignmentOffset);

	// Bubbleの半径の2倍で割って四捨五入することで、きれいに並べるためのyのインデックスを計算
	int x = std::round(shootPosX / (cellHeight));

	// インデックスがオーバーしていたら補正
	y = fix(y, 0, COL - 1);

	// インデックスがゲームオーバーラインを越えていたらreturn
	if (deadLineCol <= y) return;

	// xの補正(オーバーしないように)
	if (y % 2 == 0)
	{
		x = fix(x, 0, 8 - 1);
	}
	else
	{
		x = fix(x, 0, 7 - 1);
	}

	// もし、計算したインデックスにすでにバブルが存在していたら、周囲のマスを見ていちばん近いバブルにくっつける	
 	if (stageBubbles[y][x].lock())
	{
		// インデックスの補正用変数
		int setX = 0;
		int setY = 0;
		// 周囲のマスを見ていちばん近いバブルにくっつけるための距離の最小値を保存する変数(初期値は適当に大きく)
		float nearDis = 10000.0f;
		// 周囲のマスを見回るループ
		for (int i = 0; i < DIRECTION; i++)
		{
			// インデックスの補正値
			int offsetX;
			int offsetY;
			// 周囲インデックスは「発見先の行（y + offsetY）」の偶奇で計算が異なるため、
			// ここでは各オフセット配列を使い、あとで境界チェックを行う。
			if (y % 2 == 0)
			{
				offsetX = CheckIdxOffsetEven[i][0];
				offsetY = CheckIdxOffsetEven[i][1];
			}
			else
			{
				offsetX = CheckIdxOffsetOdd[i][0];
				offsetY = CheckIdxOffsetOdd[i][1];
			}

			int nx = x + offsetX;
			int ny = y + offsetY;

			// まず行の範囲チェック
			if (ny < 0 || ny >= COL) continue;

			// 次にその行の列数に応じた列範囲チェック
			int nRowSize = (ny % 2 == 0) ? ROW_EVEN : ROW_ODD;
			if (nx < 0 || nx >= nRowSize) continue;

			float alignmentOffsetByPushCeiling = ((ny + pushCeilingCol) % 2 == 0) ? BUBBLE_RADIUS : BUBBLE_RADIUS * 2.0f;

			// 周囲のマスの中心座標と、発射されたバブルの中心座標の距離を計算
			float dis = GetDistance(shootPosX, shootPosY, cellHeight * (nx)+alignmentOffsetByPushCeiling, (ny + pushCeilingCol) * cellHeight - pushCeilingCol * cellHeight);

			// いちばん近いバブルの距離を保存する変数と比較して、より近かったら、インデックスの補正値を保存する変数に保存
			if (dis < nearDis)
			{
				nearDis = dis;
				setX = offsetX;
				setY = offsetY;
			}

			
		}
		// 周囲のマスを見回るループを抜けたら、インデックスの補正値をインデックスに足す
		x += setX;
		y += setY;
	}

		bool RowEven = ( y % 2 == 0);
		float alignmentOffsetByNewRow = RowEven ? BUBBLE_RADIUS : BUBBLE_RADIUS * 2.0f;

		// インデックスから、きれいに並べるための位置を計算して、発射されたバブルの位置を設定
		float posX = STAGE_OFFSET_X + x * cellHeight + alignmentOffsetByNewRow;
		float posY = (y + pushCeilingCol) * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS * 4;
		s->setPos(Float2(posX, posY));

		
		// ステージに登録する前に、発射されたバブルの状態を固定状態にする
		s->setStage();

		// インデックスに発射されたバブルを登録
		stageBubbles[y][x] = shoot;
		// BanishCountを0に初期化
		BanishCount = 0;
		// バブルが3つ以上つながっているかどうかをチェックする(引数は発射されたバブルのインデックス)
		CheckBubbleMatch(y, x);
		// 3つ以上つながっていたら、バブルを破壊可能状態にする
		Banish();
		// バブルのチェック状態をリセットする
		resetBubbleCheck();
		// 落ちるバブルを見るため、ステージの上一列を走査して、バブル落下判定用の関数を呼び出す
		for (int i = 0; i < stageBubbles[0].size(); i++)
		{
			if (stageBubbles[0][i].lock())
			{
				CheckBubbleFall(0, i);
			}
			
		}
		// 落ちるバブルがあったら落とす
		Fall();
		// バブルのチェック状態をリセットする
		resetBubbleCheck();

		if (4 <= ballista.shootNum)
		{
			isShake = true;
		}
		else
		{
			isShake = false;
		}

		if (ballista.shootNum == 6)
		{
			isShake = false;
			pushCeilingCol++;
			deadLineCol--;
			SetHome();

		}

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
				stageBubbles[i][j].reset();
			}

		}
	}
}

void Stage::Shake(float shakeOffset)
{
	float rx = getRandomfloatWithDigits(5, 2);
	float ry = getRandomfloatWithDigits(5, 2);
	
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (i % 2 == 1 && 7 <= j)
			{
				continue;
			}

			if (!stageBubbles[i][j].lock()) continue;

			stageBubbles[i][j].lock()->setPos(Float2(stageBubbles[i][j].lock()->getPos().x + rx * shakeOffset, stageBubbles[i][j].lock()->getPos().y + ry * shakeOffset));
		}
	}

	for (int i = 0; i < 2; i++)
	{
		rWalls[i].set(Float2(rWalls[i].line.begin.x + rx * shakeOffset, rWalls[i].line.begin.y + ry * shakeOffset),
			Float2(rWalls[i].line.end.x + rx * shakeOffset, rWalls[i].line.end.y + ry * shakeOffset));
	}

}

void Stage::SetHome()
{
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW_EVEN; j++)
		{
			if (i % 2 == 1 && 7 <= j)
			{
				continue;
			}
			bool isEven = i % 2 == 0;

			float x = isEven ? STAGE_OFFSET_X + BUBBLE_RADIUS* j *2 + BUBBLE_RADIUS : STAGE_OFFSET_X + BUBBLE_RADIUS * j * 2 + BUBBLE_RADIUS * 2;
			float y = (i + pushCeilingCol) * BUBBLE_RADIUS * 2 + BUBBLE_RADIUS * 4;

			if (!stageBubbles[i][j].lock()) continue;

			stageBubbles[i][j].lock()->setPos(Float2(x, y));
		}
	}

	for (int i = 0; i < 2; i++)
	{

		Float2 begin(STAGE_OFFSET_X + i * BUBBLE_RADIUS * 2 * 8.0f, 0);
		Float2 end(STAGE_OFFSET_X + i * BUBBLE_RADIUS * 2 * 8.0f, WINDOW_HEIGHT);
		rWalls[i].set(begin, end);

	}
}

Stage::Ballista::Ballista() : 
	rBallista(0.3f, AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_LAUNCH_PAD)),
	rCrank(0.4f, AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_CRANK)),
	rPipe(0.4f, AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_PIPE)),
	rPlayerLeft(0.5f, AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_PLAYER_LEFT)),
	rPlayerRight(0.5f, AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_PLAYER_RIGHT)),
	rArrow(0.35f, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_ARROW))
{
	RenderableManager::getInstance()->addObject(&rLine);
	rotation = -PI / 2;
	Float2 base(BALLISTA_BASE_X, BALLISTA_BASE_Y);
	Float2 top(base.x, base.y - 50.0f);

	state = Ballista::DEFAULT;
	rLine.set(base, top);
	shootNum = 0;

	rCrank.setBase(Float2(BALLISTA_BASE_X + 48, BALLISTA_BASE_Y + 32));
	rCrank.getAP().update();
	RenderableManager::getInstance()->addObject(&rCrank);
	rBallista.setBase(Float2(BALLISTA_BASE_X - 4, BALLISTA_BASE_Y + 8));
	rBallista.getAP().update();
	RenderableManager::getInstance()->addObject(&rBallista);
	rPipe.getAP().update();
	rPipe.setBase(Float2(BALLISTA_BASE_X + 6, BALLISTA_BASE_Y + 16));
	RenderableManager::getInstance()->addObject(&rPipe);

	rPlayerLeft.setBase(Float2(BALLISTA_BASE_X - 32, BALLISTA_BASE_Y + 28));
	RenderableManager::getInstance()->addObject(&rPlayerLeft);
	rPlayerRight.setBase(Float2(BALLISTA_BASE_X + 56, BALLISTA_BASE_Y + 28));
	RenderableManager::getInstance()->addObject(&rPlayerRight);

	rArrow.setPos(Float2(BALLISTA_BASE_X + 4, BALLISTA_BASE_Y + 4));
	rArrow.setRot(rotation);
	RenderableManager::getInstance()->addObject(&rArrow);
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


	if (CheckHitKey(KEY_INPUT_LEFT) && -3.04 <= rotation)
	{
		rotation -= 0.05;
		rBallista.getAP().changeAnimation(AnimationRepository::A_LAUNCH_PAD);
		rBallista.getAP().update();
		rPlayerRight.getAP().changeAnimation(AnimationRepository::A_PLAYER_RIGHT_CRANK);
		rPlayerRight.getAP().update();
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)  && rotation <= -0.1)
	{
		rPlayerRight.getAP().changeAnimation(AnimationRepository::A_PLAYER_RIGHT_CRANK_REVERSE);
		rPlayerRight.getAP().update();
		rBallista.getAP().changeAnimation(AnimationRepository::A_LAUNCH_PPAD_REVERSE);
		rBallista.getAP().update();
		rotation += 0.05;
	}
	else
	{
		rPlayerRight.getAP().changeAnimation(AnimationRepository::A_PLAYER_RIGHT_IDLE);
		rPlayerRight.getAP().update();

	}

	rLine.set(Float2(BALLISTA_BASE_X, BALLISTA_BASE_Y), Float2(BALLISTA_BASE_X + 50.0f * cosf(rotation), BALLISTA_BASE_Y + 50.0f * sinf(rotation)));
	rArrow.setRot(rotation + 3.14f / 2);
	
}

void Stage::Ballista::reload(std::vector<int> colorBuffer)
{
	Float2 pos(BALLISTA_BASE_X - BUBBLE_RADIUS * 5, BALLISTA_BASE_Y + 36);
	if (colorBuffer.size() <= 0) return;

	int r = GetRand(colorBuffer.size() - 1);


	shootBubbles.push(BubbleGenerator::getInstance().generate(colorBuffer[r], pos, BUBBLE_RADIUS, true));

}

void Stage::Ballista::updateProc(std::vector<int> colorBuffer)
{

	rPlayerLeft.getAP().update();
	rPlayerRight.getAP().update();
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
		if (rPlayerLeft.getAP().getIsStop())
		{
			rPlayerLeft.getAP().changeAnimation(AnimationRepository::A_PLAYER_LEFT_RELOAD);
		}
		if (shootBubbles.front().lock()->getState() == Bubble::STATE::READY)
		{
			reload(colorBuffer);
			state = BALLISTA_STATE::WAIT;
			rPlayerLeft.getAP().changeAnimation(AnimationRepository::A_PLAYER_LEFT_IDLE);
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
			rPlayerLeft.getAP().changeAnimation(AnimationRepository::A_PLAYER_LEFT_SHOOT);
			shootNum = (shootNum++) % 7;
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


