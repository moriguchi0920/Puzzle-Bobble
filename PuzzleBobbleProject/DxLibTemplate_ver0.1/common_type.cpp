#include"common_func.h"



CPoint::CPoint() : point()
{
	
}
CPoint::CPoint(float _x, float _y) : point(_x, _y)
{

}
CPoint::CPoint(const Point& pos) : point(pos)
{

}



void CPoint::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_XY)
	{
		this->point.x = param->param.paramPoint.point.x;
		this->point.y = param->param.paramPoint.point.y;
	}
	else
	{
		return;
	}
}

bool CPoint::checkCollide(CollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		Point* pTarget = dynamic_cast<Point*>(shape);
		if(pContact)return CheckPointHit(this->point, *pTarget, pContact);
		return CheckPointHit(this->point, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		Circle* pTarget = dynamic_cast<Circle*>(shape);
		if(pContact)return CheckPointCircleHit(this->point, *pTarget, pContact);
		return CheckPointCircleHit(this->point, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		Rect* pTarget = dynamic_cast<Rect*>(shape);
		if (pContact)return CheckPointBoxHit(this->point, *pTarget, pContact);
		return CheckPointBoxHit(this->point, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		Line* pTarget = dynamic_cast<Line*>(shape);
		if (pContact)return CheckLinePointHit(*pTarget, this->point, pContact);
		return CheckLinePointHit(*pTarget, this->point);
	}
	return false;
}





CLine::CLine() : line()
{

}
CLine::CLine(const Point& _begin, const Point& _end) : line(_begin, _end)
{

}
CLine::CLine(const Line& _line) : line(_line)
{

}


void CLine::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_LINE_BEGIN)
	{
		this->line.begin = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_LINE_END)
	{
		this->line.end = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_LINE_BOTH)
	{
		this->line.begin = param->param.paramPoint2.point1;
		this->line.end = param->param.paramPoint2.point2;
	}
	else
	{
		return;
	}
}

bool CLine::checkCollide(CollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		Point* pTarget = dynamic_cast<Point*>(shape);
		if(pContact)return CheckLinePointHit(this->line, *pTarget, pContact);
		return CheckLinePointHit(this->line, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		Circle* pTarget = dynamic_cast<Circle*>(shape);
		if(pContact)return CheckLineCircleHit(this->line, *pTarget, pContact);
		return CheckLineCircleHit(this->line, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		Rect* pTarget = dynamic_cast<Rect*>(shape);
		if(pContact)return CheckLineBoxHit(this->line, *pTarget, pContact);
		return CheckLineBoxHit(this->line, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		Line* pTarget = dynamic_cast<Line*>(shape);
		if(pContact)return CheckLineHit(this->line, *pTarget, pContact);
		return CheckLineHit(this->line, *pTarget);
	}
	return false;
}


CCircle::CCircle() : circle()
{
	
}
CCircle::CCircle(const Point& _pos, float _r) : circle(_pos, _r)
{

}
CCircle::CCircle(const Circle& _circle) : circle(_circle)
{

}



void CCircle::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_XY)
	{
		this->circle.pos = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_R)
	{
		this->circle.radius = param->param.paramR.r;
	}
	else if (param->paramType == ShapeSetParam::PT_CIRCLE)
	{
		this->circle.pos = param->param.paramCircle.point;
		this->circle.radius = param->param.paramCircle.r;
	}
	else
	{
		return;
	}
}

bool CCircle::checkCollide(CollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		Point* pTarget = dynamic_cast<Point*>(shape);
		if(pContact) return CheckPointCircleHit(*pTarget, this->circle, pContact);
		return CheckPointCircleHit(*pTarget, this->circle);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		Circle* pTarget = dynamic_cast<Circle*>(shape);
		if(pContact)return CheckCircleHit(this->circle, *pTarget, pContact);
		return CheckCircleHit(this->circle, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		Rect* pTarget = dynamic_cast<Rect*>(shape);
		if(pContact)return CheckCircleBoxHit(this->circle, *pTarget, pContact);
		return CheckCircleBoxHit(this->circle, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		Line* pTarget = dynamic_cast<Line*>(shape);
		if(pContact)return CheckLineCircleHit(*pTarget, this->circle, pContact);
		return CheckLineCircleHit(*pTarget, this->circle);
	}
	return false;
}



CRect::CRect() : rect()
{

}
CRect::CRect(const Point& _begin, const Point& _size) : rect(_begin, _size)
{

}
CRect::CRect(const Rect& _rect) : rect(_rect)
{
}


void CRect::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_XY)
	{
		this->rect.begin = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_WH)
	{
		this->rect.size = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_RECT)
	{
		this->rect.begin = param->param.paramPoint2.point1;
		this->rect.size = param->param.paramPoint2.point2;
	}
	else
	{
		return;
	}
}

bool CRect::checkCollide(CollisionShape* shape, ContactInfo* pContact )
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		Point* pTarget = dynamic_cast<Point*>(shape);
		if(pContact)return CheckPointBoxHit(*pTarget, this->rect, pContact);
		return CheckPointBoxHit(*pTarget, this->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		Circle* pTarget = dynamic_cast<Circle*>(shape);
		if(pContact)return CheckCircleBoxHit(*pTarget, this->rect, pContact);
		return CheckCircleBoxHit(*pTarget, this->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		Rect* pTarget = dynamic_cast<Rect*>(shape);
		if(pContact)return CheckBoxHit(*pTarget, this->rect, pContact);
		return CheckBoxHit(this->rect, *pTarget);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		Line* pTarget = dynamic_cast<Line*>(shape);
		if(pContact)return CheckLineBoxHit(*pTarget, this->rect, pContact);
		return CheckLineBoxHit(*pTarget, this->rect);
	}
	return false;
}




ShapeSetParam::Param::Param()
{
	this->paramR.r = 0.0;
}


ShapeSetParam::ShapeSetParam(ShapeSetParam::ParamType type)
{
	paramType = type;
}


ContactInfo::ContactInfo()
{
	position = { INFO_VAR_DEFAULT, INFO_VAR_DEFAULT };
	crosswise = CROSSWISE::CROSS_DEFAULT;
	hadContact = false;
	side = RECTCOLLIDESIDE::SIDE_DEFAULT;
	lineColVector1 = { INFO_VAR_DEFAULT, INFO_VAR_DEFAULT };
	lineColVector2 = { INFO_VAR_DEFAULT, INFO_VAR_DEFAULT };
}
