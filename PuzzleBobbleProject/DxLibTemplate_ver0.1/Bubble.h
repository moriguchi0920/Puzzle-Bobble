#pragma once
#include"renderableManager.h"
#include"taskManager.h"
#include"collisionManager.h"

// ゲームの中核となるステージに置かれる、またバリスタから発射するバブル
class Bubble : public Task
{
protected:

	// 描画用円
	RenderableCircle rCir;
	// 破壊判定処理時破壊判定関数を通ったかどうか(要するに同色でつながっていればtrueになる)
	bool isChecked;
	// デバッグ用の色
	DebugColor col;

	// 破壊可能か
	bool canDestroy;

	// 移動用座標
	Float2 position;

	// 当たり判定
	CBubble cBubble;


public:
	// 引数付きコンストラクタ
	Bubble(int _col, Float2 _pos, float _radius);

	// 更新
	void Update() override;
	// 描画
	bool Destroy() override;

	virtual void activateProc() override;
	virtual void deactivateProc() override;

	// 色取得関数
	DebugColor& getColor();

	void move(Vector2D vec, float speed);

	// isCheckedのセッター
	void setIsChecked(bool check);
	// canDestroyのセッター
	void setCanDestroy(bool _canDestroy);

	// isCheckedのゲッター
	bool getIsChecked();
	// canDestroyのゲッター
	bool getCanDestroy();

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





