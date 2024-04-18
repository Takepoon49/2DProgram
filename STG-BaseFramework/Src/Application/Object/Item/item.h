#pragma once

class Scene;

class C_Item
{
public:

	void Init();
	void Update();
	void Draw();

	void Drop(Math::Vector2 a_pos, bool type);

	UINT GetFlg() { return m_flg; }

	void SetFlg(UINT a_alive);

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

	HitStruct GetObj();

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

	Math::Vector2	m_pos;
	Math::Vector2	m_move;
	float			m_rad;
	Math::Color		m_color;

	UINT			m_flg;

	Math::Rectangle m_rect;
	Math::Matrix	m_mat;
};