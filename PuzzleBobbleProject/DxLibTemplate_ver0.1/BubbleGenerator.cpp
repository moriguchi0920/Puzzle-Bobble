#include"BubbleGenerator.h"


std::weak_ptr<Bubble> BubbleGenerator::generate(int _col, Float2 _pos, float _radius)
{
	// ‚Ü‚¸shared_ptr‚Æ‚µ‚Ä¶¬
	std::shared_ptr<Bubble> spBubble = std::make_shared<Bubble>(_col, _pos, _radius);

	// CollisionManager‚Ö“o˜^
	CollisionManager::getInstance()->addObject(&(spBubble->cBubble));
	// RenderableManager‚Ö“o˜^
	RenderableManager::getInstance()->addObject(&(spBubble->rCir));
	// TaskManager‚Ö“o˜^
	TaskManager::getInstance()->addObject(spBubble);

	// weak_ptr‚ğì¬
	std::weak_ptr<Bubble> wpBubble(spBubble);

	// weak_ptr‚ğreturn
	return wpBubble;

}