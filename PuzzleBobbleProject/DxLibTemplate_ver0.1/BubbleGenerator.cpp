#include"BubbleGenerator.h"

std::weak_ptr<Bubble> BubbleGenerator::generate(int _col, Float2 _pos, float _radius)
{
	std::shared_ptr<Bubble> spBubble = std::make_shared<Bubble>(_col, _pos, _radius);


	CollisionManager::getInstance()->addObject(&(spBubble->cBubble));
	RenderableManager::getInstance()->addObject(&(spBubble->rCir));
	TaskManager::getInstance()->addObject(spBubble);


	std::weak_ptr<Bubble> wpBubble(spBubble);

	return wpBubble;

}