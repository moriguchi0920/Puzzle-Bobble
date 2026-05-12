#pragma once
#include "taskManager.h"
#include"renderableManager.h"
#include"Bubble.h"
#include"BubbleGenerator.h"
#include<memory>
#include<queue>

// ステージの盤を表現するクラス
// ボールの生成管理も担当するため実質的にマネージャークラス
class Stage final: public Task
{
	// メンバ変数
protected:
	// バブルの二次元配列(8,7,8,7...と続くためstd::vectorのresizeで表現する)
	// 縦は13列
	std::vector<std::weak_ptr<Bubble>> stageBubbles[13];

	std::vector<int> stageExistColorBuffer;
	
	// 発射処理用のクラス
	class Ballista
	{
	public:
		// 発射待機のキュー(現状別にqueueである必要はない)
		std::queue<std::weak_ptr<Bubble>> shootBubbles;

		// 角度
		float rotation;

		// 表示用線
		RenderableLine rLine;

		int state;

	public:
		// コンストラクタ
		Ballista();
		// デストラクタ
		virtual  ~Ballista();

		// 弾を発射状態にする
		void shoot();

		// 待機&角度変更
		void wait();

		// 弾の生成と状態の変化
		void reload(std::vector<int> colorBuffer);

		void updateProc(std::vector<int> colorBuffer);

		std::weak_ptr<Bubble> getShooted();

		enum BALLISTA_STATE
		{
			DEFAULT,
			RELOAD,
			WAIT,
			NUM
		};

	} ballista;


	// バブルを破壊するときのカウント
	// 3以上だった場合canDestroyがtrueのBubbleを一括破壊させる
	int BanishCount;

	// 描画用の壁と当たり判定
	CWall cWalls[2];
	RenderableLine rWalls[2];

	// 描画用の天井と当たり判定
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

	// 現在ステージに存在している色の種類をvectorに保存して返す関数
	std::vector<int> getExistColor();

	void registerShootBubble(std::weak_ptr<Bubble> shoot);

	// バブル破壊判定用の関数
	// 内部で指定したインデックスのバブルの周囲のマスのバブルを確認し、
	// 同じ色のバブルだった場合再帰してほかのバブルを見に行く
	bool CheckBubbleMatch(int colIdx , int rowIdx);

	bool CheckBubbleFall(int colIdx, int rowIdx);


	void resetBubbleCheck();

	// CheckBubbleMatchのあと、isCheckedがtrueのBubbleを破壊可能状態にする
	void Banish();

	void Fall();


};


