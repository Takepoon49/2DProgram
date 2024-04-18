#pragma once

class Scene;

class C_Map
{
public:

	void Init();
	void Update();
	void Draw();

	void SetImg0(KdTexture* a_pTex) { m_pImg0Tex = a_pTex; }
	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

private:

	Scene* m_pOwner;

	KdTexture*		m_pImg0Tex;
	Math::Vector2	m_BackPos;
	Math::Matrix	m_BackMatrix;
	Math::Color		m_BackColor;

};