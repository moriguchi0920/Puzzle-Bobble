#pragma once
#include"Bubble.h"


class BubbleGenerator
{

private :
	

public:
	static inline BubbleGenerator& getInstance()
	{
		static BubbleGenerator instance;
		return instance;
	}

	std::weak_ptr<Bubble> generate(int _col, Float2 _pos, float _radius);


private:

	inline BubbleGenerator() {};
	BubbleGenerator& operator = (const BubbleGenerator& other) = delete;
	BubbleGenerator(const BubbleGenerator& other) = delete;

};