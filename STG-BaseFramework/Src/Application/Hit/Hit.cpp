#include "../Scene/Scene.h"
#include "Hit.h"

bool C_Hit::HitObjBox(HitStruct objA, HitStruct objB)
{
	// A
	float	objALeft = objA.pos.x - objA.rad.x;
	float	objARight = objA.pos.x + objA.rad.x;
	float	objATop = objA.pos.y + objA.rad.y;
	float	objABottom = objA.pos.y - objA.rad.y;

	// B
	float	objBLeft = objB.pos.x - objB.rad.x;
	float	objBRight = objB.pos.x + objB.rad.x;
	float	objBTop = objB.pos.y + objB.rad.y;
	float	objBBottom = objB.pos.y - objB.rad.y;

	// ‹éŒ`”»’è
	if (objARight > objBLeft && objALeft < objBRight &&
		objATop > objBBottom && objABottom < objBTop)
	{
		return true;
	}

	return false;
}

bool C_Hit::HitObjCircle(HitStruct objA, HitStruct objB)
{
	// A
	float	objALeft = objA.pos.x - objA.rad.x;
	float	objARight = objA.pos.x + objA.rad.x;
	float	objATop = objA.pos.y + objA.rad.y;
	float	objABottom = objA.pos.y - objA.rad.y;

	// B
	float	objBLeft = objB.pos.x - objB.rad.x;
	float	objBRight = objB.pos.x + objB.rad.x;
	float	objBTop = objB.pos.y + objB.rad.y;
	float	objBBottom = objB.pos.y - objB.rad.y;

	float a = objB.pos.x - objA.pos.x;
	float b = objB.pos.y - objA.pos.y;
	float c = a * a + b * b;
	float sumRad = objA.rad.x + objB.rad.x;

	if (c <= sumRad * sumRad)
	{
		return true;
	}
	else
	{
		return false;
	}
}
