#pragma once

#include "../../utility.h"

class EnemyBase
{
public:

	EnemyBase() {}
	virtual ~EnemyBase() {}

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	void SetTexture(std::string _fileName);

	bool GetFlg() { return m_flg; }

protected:

	KdTexture			m_tex;

	Math::Rectangle		m_rect;

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