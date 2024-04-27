#pragma once

#include "../../utility.h"

class Scene;

class ParticleBase
{
public:
	ParticleBase() {}
	virtual ~ParticleBase() {}

	virtual void Init(int _type, Math::Vector2 _pos);
	virtual void Update();
	virtual void Draw();

	void SetTexture(KdTexture* _pTex) { m_pTex = _pTex; }
	void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

	int					m_type;

	Math::Vector2		m_nowAnim;
	Math::Rectangle		m_rect;

	int					m_flg;
	int					m_frame;

	Math::Vector2		m_pos;
	Math::Vector2		m_move;
	Math::Vector2		m_scale;
	float				m_deg;
	MathSet				m_mat;
	Math::Color			m_color;
};