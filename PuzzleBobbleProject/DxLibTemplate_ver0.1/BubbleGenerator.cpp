#include"BubbleGenerator.h"


std::weak_ptr<Bubble> BubbleGenerator::generate(int _col, Float2 _pos, float _radius, bool isShoot)
{
	// ‚Ü‚¸shared_ptr‚Æ‚µ‚Ä¶¬
	std::shared_ptr<Bubble> spBubble = std::make_shared<Bubble>(_col, _pos, _radius, isShoot);

	// CollisionManager‚Ö“o˜^
	CollisionManager::getInstance()->addObject(spBubble->cBubble.get());
	// RenderableManager‚Ö“o˜^
	RenderableManager::getInstance()->addObject(&(spBubble->rBubble));
	// TaskManager‚Ö“o˜^
	TaskManager::getInstance()->addObject(spBubble);

	// weak_ptr‚ğì¬
	std::weak_ptr<Bubble> wpBubble(spBubble);

	// weak_ptr‚ğreturn
	return wpBubble;

}