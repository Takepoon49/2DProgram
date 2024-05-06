#pragma once

#include "../../BaseObject.h"

class Scene;

class C_Bullet0	: public BaseObject
{
public:

	C_Bullet0();
	~C_Bullet0() {};

	void Init() override;
	void Update() override;
	void Draw() override;

	void Shot(Math::Vector2 a_pos);		// î≠éÀèàóù

private:

	//KdTexture*			m_pTex;

	Math::Rectangle		m_AlphaRect;
	Math::Rectangle		m_AddRect;

	//UINT				m_flg;
	//Math::Vector2		m_pos;
	//Math::Vector2		m_move;
	Math::Vector2		m_emove;
	//Math::Vector2		m_scale;
	//Math::Vector2		m_rad;
	//float				m_deg;
	//MathSet				m_mat;
	//Math::Color			m_color;

	Math::Vector2		m_speed;

	int					m_frame;
};