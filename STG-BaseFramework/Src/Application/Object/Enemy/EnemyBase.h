#pragma once

#include "../../utility.h"

class EnemyBase
{
public:

	EnemyBase() { Init(); }
	virtual ~EnemyBase() { Release(); }

	virtual void Update();
	virtual void Draw();
	virtual void Init();

	// Ç∞Ç¡ÇΩÅ[
	int GetFlg() { return m_flg; }
	Math::Vector2 GetPos() { return m_pos; }
	Math::Vector2 GetRad() { return m_rad; }

protected:

	virtual void Release();

	KdTexture			m_tex;

	Math::Rectangle		m_rect;

	int					m_hp;
	int					m_flg;
	Math::Vector2		m_pos;
	Math::Vector2		m_move;
	Math::Vector2		m_scale;
	Math::Vector2		m_rad;
	float				m_deg;
	MathSet				m_mat;
	Math::Color			m_color;

	Math::Vector2		m_speed;
};