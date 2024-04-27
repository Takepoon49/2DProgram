#pragma once

#include "../utility.h"

class BaseObject
{
public:

	BaseObject() {}
	virtual	~BaseObject() { Release(); }

	virtual void Update();
	virtual void Draw();
	virtual void Init();

	// ゲッター
	Math::Vector2 GetPos() { return m_pos; }
	Math::Vector2 GetMove() { return m_move; }
	Math::Vector2 GetScale() { return m_scale; }
	Math::Vector2 GetRad() { return m_rad; }
	float GetDeg() { return m_deg; }
	MathSet GetMathSet() { return m_mat; }
	Math::Color GetColor() { return m_color; }

	// セッター
	void SetPos(Math::Vector2 _pos) { m_pos = _pos; }
	void SetMove(Math::Vector2 _move) { m_move = _move; }
	void SetScale(Math::Vector2 _scale) { m_scale = _scale; }
	void SetRad(Math::Vector2 _rad) { m_rad = _rad; }
	void SetDeg(float _deg) { m_deg = _deg; }
	void SetMat(MathSet _mathSet) { m_mat = _mathSet; }
	void SetColor(Math::Color _color) { m_color = _color; }

	void SetTexture(std::string _fileName);

protected:

	virtual void Release();

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

};