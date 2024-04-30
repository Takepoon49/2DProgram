#pragma once

class Scene;

class Map
{
public:

	void Init();
	void Update();
	void Draw();


	void SetImg0(KdTexture* a_pTex) { m_pImgTex[0] = a_pTex; }
	void SetImg1(KdTexture* a_pTex) { m_pImgTex[1] = a_pTex; }
	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	int				m_nowTex;

private:

	Scene* m_pOwner;

	KdTexture*		m_pImgTex[2];

	Math::Vector2	m_BackPos;

	Math::Vector2	m_scale;
	float			m_deg;
	MathSet			m_mat;
	
	Math::Color		m_BackColor;
	Math::Rectangle m_Rect;

};