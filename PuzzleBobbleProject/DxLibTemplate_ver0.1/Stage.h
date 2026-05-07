#pragma once
#include "taskManager.h"
#include"renderableManager.h"
#include"Bubble.h"
#include<memory>

// ステージの盤を表現するクラス
// ボールの生成管理も担当するため実質的にマネージャークラス
class Stage final: public Task
{
	// メンバ変数
protected:
	// バブルの二次元配列(8,7,8,7...と続くためstd::vectorのresizeで表現する)
	// 縦は13列
	std::vector<std::shared_ptr<Bubble>> stageBubbles[13];
	

	// バブルを破壊するときのカウント
	// 3以上だった場合canDestroyがtrueのBubbleを一括破壊させる
	int VanishCount;

	CWall cWalls[2];
	RenderableLine rWalls[2];


	CCeiling cCeiling;
	RenderableLine rCeiling;

	

public:
	// デフォルトコンストラクタ(いらない)
	Stage();

	// 引数付きコンストラクタ(後でステージ情報保存用のstd::vector配列を入れるため)
	Stage(std::vector<int>* stageInfoBuffer);

	// 更新
	void Update() override;

	// 破壊判定
	bool Destroy() override;

	virtual void activateProc() override;
	virtual void deactivateProc() override;


	// バブル破壊判定用の関数
	// 内部で指定したインデックスのバブルの周囲のマスのバブルを確認し、
	// 同じ色のバブルだった場合再帰してほかのバブルを見に行く
	bool CheckBubbleMatch(int colIdx , int rowIdx);

	// CheckBubbleMatchのあと、isCheckedがtrueのBubbleを破壊可能状態にする
	void Vanish();


};


