#pragma once
#include"renderableManager.h"
#include"taskManager.h"
#include"collisionManager.h"

// ゲームの中核となるステージに置かれる、またバリスタから発射するバブル
class Bubble : public Task
{
	friend class BubbleGenerator;
protected:

	// 描画用円
	//RenderableCircle rCir;
	RenderableAnimation rBubble;
	// 破壊判定処理時破壊判定関数を通ったかどうか(要するに同色でつながっていればtrueになる)
	bool isChecked;


	// 破壊可能か
	bool canDestroy;

	// 移動用座標
	Float2 position;

	// 移動用方向ベクトル
	Vector2D vec;

	// 当たり判定
	std::unique_ptr<CBubble> cBubble;

	int state;

	int color;

	float gravity;


public:
	// 引数付きコンストラクタ
	Bubble(int _col, Float2 _pos, float _radius, bool isShoot);

	virtual ~Bubble();

	// 更新
	void Update() override;
	// 描画
	bool Destroy() override;

	virtual void activateProc() override;
	virtual void deactivateProc() override;

	// 色取得関数
	int getColor();

	void move(Vector2D _vec, float speed);

	// isCheckedのセッター
	void setIsChecked(bool check);
	// canDestroyのセッター
	void setCanDestroy(bool _canDestroy);

	void setPos(Float2 _pos);

	void setState(int newState);

	int getState();

	void setVector(Vector2D _vec);

	bool hit();

	void setStage();

	void fall();



	Float2 getPos();

	// isCheckedのゲッター
	bool getIsChecked();
	// canDestroyのゲッター
	bool getCanDestroy();

	enum STATE
	{
		RELOAD,
		STAY,
		READY,
		SHOOT,
		FIXED,
		VANISH,
		FALL,
		NUM
	};

	enum COLOR
	{
		COL_DEFAULT,
		COL_RED,
		COL_BLUE,
		COL_YELLOW,
		COL_GREEN,
		COL_ORANGE,
		COL_PURPLE,
		COL_GRAY,
		COL_WHITE,
		COL_NUM
	};

};





