#pragma once

#include "../../BaseObject.h"

class BLaser : public BaseObject
{
public:

	BLaser();
	~BLaser() {};

	void Init();
	void Update();
	void Draw();

private:

	//virtual void Release();

	//ObjType				m_objType = ObjType::Base;

	//Scene* m_pOwner = nullptr;

	//KdTexture			m_tex;

	//Math::Rectangle		m_rect;
	//Math::Vector2		m_nowAnim;

	//int					m_frame;
	//int					m_flg;
	//Math::Vector2		m_pos;
	//Math::Vector2		m_move;
	//Math::Vector2		m_moveVec = Math::Vector2::Zero;
	//Math::Vector2		m_scale;
	//Math::Vector2		m_rad;
	//float				m_deg;
	//MathSet				m_mat;
	//Math::Color			m_color;

	//// ‰e
	//struct ShadowSt
	//{
	//	Math::Vector2	pos;
	//	Math::Color		color;
	//	MathSet			mat;
	//}m_shadow;

};