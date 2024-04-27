#pragma once

#include "../../../utility.h"

class Scene;

class Bullet1
{
public:

	Bullet1() {};
	~Bullet1() {};

	void Init();
	void Shot(Math::Vector2 _pos, float _deg, int _flg);
	void Update();
	void Draw();

	bool GetFlg() { return m_flg; }

	void SetTexture(KdTexture* _pTex) { m_pTex = _pTex; }

	void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

	Math::Rectangle		m_AlphaRect;
	//Math::Rectangle	m_AddRect;

	UINT				m_flg;
	Math::Vector2		m_pos;
	Math::Vector2		m_move;
	Math::Vector2		m_emove;
	Math::Vector2		m_scale;
	Math::Vector2		m_rad;
	float				m_deg;
	MathSet				m_mat;
	Math::Color			m_color;

	Math::Vector2		m_speed;

	int					m_frame;

};