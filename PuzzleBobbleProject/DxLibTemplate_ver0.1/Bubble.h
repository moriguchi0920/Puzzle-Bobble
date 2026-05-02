#pragma once
#include"renderable.h"
#include"taskManager.h"


// ゲームの中核となるステージに置かれる、またバリスタから発射するバブル
class Bubble : public Task
{
protected:

	// 描画用円
	RenderableCircle Rcir;
	// 破壊判定処理時破壊判定関数を通ったかどうか
	bool isChecked;
	// デバッグ用の色
	DebugColor col;

	// 破壊可能か
	bool canDestroy;



public:
	Bubble();
	Bubble(int _col, Float2 _pos, float _radius);

	void Update() override;
	bool Destroy() override;

	DebugColor& getColor();

	enum COLOR
	{
		COL_DEFAULT,
		COL_RED,
		COL_BLUE,
		COL_YELLOW,
		COL_GREEN,
		COL_ORANGE,
		COL_PURPLE,
	};

};





