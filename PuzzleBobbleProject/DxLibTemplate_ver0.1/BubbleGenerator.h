#pragma once
#include"Bubble.h"

// バブルの生成担当クラス
// メンバ変数は持たず、generate()関数でバブルを生成、
// TaskManagerに管理権を移譲、
// 返り値としてweak_ptrを返す
class BubbleGenerator
{

private :
	

public:
	// インスタンス取得
	static inline BubbleGenerator& getInstance()
	{
		static BubbleGenerator instance;
		return instance;
	}

	// 生成関数
	std::weak_ptr<Bubble> generate(int _col, Float2 _pos, float _radius, bool isShoot);


private:

	inline BubbleGenerator() {};
	BubbleGenerator& operator = (const BubbleGenerator& other) = delete;
	BubbleGenerator(const BubbleGenerator& other) = delete;

};