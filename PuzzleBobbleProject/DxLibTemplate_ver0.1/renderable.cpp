#include"renderable.h"
#include"DxLib.h"

const float Renderable::PRIORITY_DEFAULT = 0.5f;
const float Renderable::PRIORITY_MIN = 0.0f;
const float Renderable::PRIORITY_MAX = 1.0f;


Renderable::Renderable(float _priority)
{
	setPriority(_priority);
	position.center = { 0.0f, 0.0f };
}


void Renderable::setPriority(float newPriority)
{
	if (newPriority < PRIORITY_MIN)
	{
		newPriority = PRIORITY_MIN;
	}
	if (PRIORITY_MAX < newPriority)
	{
		newPriority = PRIORITY_MAX;
	}
	priority = newPriority;
}

float Renderable::getPriority()
{
	return priority;
}


RenderableImage::RenderableImage(float _priority, int _imageHandle) : Renderable(_priority)
{
	imageHandle = _imageHandle;
}

void RenderableImage::render()
{

}


RenderableAnimation::RenderableAnimation(float _priority, AnimationDataSet* pAdc) : Renderable(_priority), AP(pAdc)
{

}

void RenderableAnimation::render()
{

}

RenderableRect::RenderableRect(float _priority, Float2 _leftTop, Float2 _size) : Renderable(_priority), rect(_leftTop, _size)
{
}

void RenderableRect::render()
{
	DrawBox(rect.begin.x, rect.begin.y, rect.begin.x + rect.size.x, rect.begin.y + rect.size.y, 0x000000, true);
}

RenderableCircle::RenderableCircle()
{
	
}

RenderableCircle::RenderableCircle(float _priority, Float2 _pos, float _radius) : Renderable(_priority), circle(_pos, _radius)
{
}

void RenderableCircle::render()
{
}
