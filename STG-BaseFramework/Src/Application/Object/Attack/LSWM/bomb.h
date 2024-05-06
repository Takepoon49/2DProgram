#pragma once

#include "../../BaseObject.h"

class Bomb : public BaseObject
{
public:
	Bomb() {}
	~Bomb() {}

	void Init(Math::Vector2 _pos, int _flg);
	void Update() override;
	void Draw() override;

private:

	//Scene* m_pOwner = nullptr;

	//KdTexture			m_tex;

	//Math::Rectangle	m_rect;
	//Math::Vector2		m_nowAnim;

	//int				m_frame;
	//int				m_flg;
	//Math::Vector2		m_pos;
	//Math::Vector2		m_move;
	//Math::Vector2		m_moveVec = Math::Vector2::Zero;
	//Math::Vector2		m_scale;
	//Math::Vector2		m_rad;
	//float				m_deg;
	//MathSet			m_mat;
	//Math::Color		m_color;

	//// ‰e
	//struct ShadowSt
	//{
	//	Math::Vector2	pos;
	//	Math::Color		color;
	//	MathSet			mat;
	//}m_shadow;

};