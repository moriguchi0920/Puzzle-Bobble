#pragma once
#include "taskManager.h"
#include"Bubble.h"

class Stage final: public Task
{
protected:
	std::vector<Bubble*> stageBubbles[13];

public:
	Stage();

	Stage(std::vector<int*> stageInfoBuffer);


	void Update() override;

	bool Destroy() override;

	bool CheckBubbleMatch(int colIdx , int rowIdx);




};
