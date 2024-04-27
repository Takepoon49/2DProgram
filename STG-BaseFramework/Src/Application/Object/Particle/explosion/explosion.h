#pragma once

#include "../ParticleBase.h"

class Scene;

class Explosion : public ParticleBase
{
public:

	Explosion() {};
	~Explosion() override {};

	void Init(int _type, Math::Vector2 _pos) override;
	void Update() override;
	void Draw() override;

private:

	//KdTexture*		m_pTex;

	//int				m_type;

	//Math::Vector2		m_nowAnim;
	//Math::Rectangle	m_rect;

	//int				m_flg;
	//int				m_frame;

	//Math::Vector2		m_pos;
	//Math::Vector2		m_move;
	//Math::Vector2		m_scale;
	//float				m_deg;
	//MathSet			m_mat;
	//Math::Color		m_color;

};