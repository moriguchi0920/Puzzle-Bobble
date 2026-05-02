#pragma once

#include"AnimationPlayer.h"
#include"Float2.h"
#include"Line.h"
#include"Rect.h"
#include"Circle.h"

// •`‰æ•¨‚ğ•\Œ»‚·‚éŠî’êƒNƒ‰ƒX
// 0.0 ~ 1.0‚Ì”ÍˆÍ‚Ì•`‰æ‡•Ï”‚ğ•Û‚µA
// ƒˆ‰¼‘zŠÖ”render()‚ğŒp³æ‚ÅƒI[ƒo[ƒ‰ƒCƒh‚³‚¹‚é‚±‚Æ‚Å•`‰æ‚ğˆêŠ‡ŠÇ—‚·‚é
class Renderable
{
public:
	// •`‰æÀ•W•\Œ»—p‚Ì\‘¢‘Ì
	struct Pos
	{
		float x;
		float y;
	};
	union RenderPosition
	{
		Pos leftTop;
		Pos center;
	};

protected :
	// •`‰æ—Dæ‡ˆÊ‚Ì”ÍˆÍ
	// 0.0f
	static const float PRIORITY_MIN;
	// 0.5f
	static const float PRIORITY_MAX;
	// 1.0f
	static const float PRIORITY_DEFAULT;

	// •`‰æ—Dæ‡ˆÊ•Ï”
	float priority;

	// •`‰æÀ•W
	RenderPosition position;

public :
	Renderable(float _priority = 0.0f);
	void setPriority(float newPriority);

	float getPriority();
	virtual void render() = 0;
};

// •`‰æ‚Å‚«‚éü
class RenderableLine : public Renderable
{
protected:
	Line line;
public:
	RenderableLine(float _priority, Float2 _begin, Float2 _end);
	virtual void render() override;

};

// •`‰æ‚Å‚«‚élŠp
class RenderableRect : public Renderable
{
protected:
	Rect rect;
public:
	RenderableRect();
	RenderableRect(float _priority, Float2 _leftTop, Float2 _size);
	virtual void render() override;

};

// •`‰æ‚Å‚«‚é‰~
class RenderableCircle : public Renderable
{
protected:
	Circle circle;
public:
	RenderableCircle();
	RenderableCircle(float _priority, Float2 _pos, float _radius);
	virtual void render() override;

};


// •`‰æ‚Å‚«‚é‰æ‘œ
class RenderableImage : public Renderable
{
protected:
	int imageHandle;
public :
	RenderableImage(float _priority, int _imageHandle);
	virtual void render() override;
};

// •`‰æ‚Å‚«‚éƒAƒjƒ[ƒVƒ‡ƒ“
class RenderableAnimation : public Renderable
{
protected:
	AnimationPlayer AP;
public :
	RenderableAnimation(float _priority, AnimationDataSet* pAdc);
	virtual void render() override;
};
