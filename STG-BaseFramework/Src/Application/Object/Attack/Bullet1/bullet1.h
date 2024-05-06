#pragma once

#include "../../BaseObject.h"

class Scene;

class Bullet1 : public BaseObject
{
public:

	Bullet1() {};
	~Bullet1() {};

	void Init();
	void Shot(Math::Vector2 _pos, float _deg, int _flg);
	void Update();
	void Draw();

private:



	//virtual void Release();

	//Scene* m_pOwner = nullptr;

	float				m_speed = 0.0f;

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