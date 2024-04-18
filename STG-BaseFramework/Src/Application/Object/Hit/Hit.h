#pragma once

class Scene;

class C_Hit
{
public:

	bool HitObjBox(HitStruct objA, HitStruct objB);

	bool HitObjCircle(HitStruct objA, HitStruct objB);

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

private:

	Scene* m_pOwner;

};