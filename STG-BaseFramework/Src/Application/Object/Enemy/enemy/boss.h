#pragma once

#include "../../BaseObject.h"

class Boss : public BaseObject
{
public:

	Boss();
	~Boss() {};

	void Init();
	void Update();
	void Draw();

	//// ゲッター
	//int				GetFlg() { return m_flg; }
	//Math::Vector2	GetPos() { return m_pos; }
	//Math::Vector2	GetMove() { return m_move; }
	//Math::Vector2	GetMoveVec() { return m_moveVec; }
	//Math::Vector2	GetScale() { return m_scale; }
	//Math::Vector2	GetRad() { return m_rad; }
	//float			GetDeg() { return m_deg; }
	//MathSet			GetMathSet() { return m_mat; }
	//Math::Color		GetColor() { return m_color; }

	//// セッター
	//void SetFlg(int _flg) { m_flg = _flg; }
	//void SetPos(Math::Vector2 _pos) { m_pos = _pos; }
	//void SetMove(Math::Vector2 _move) { m_move = _move; }
	//void SetScale(Math::Vector2 _scale) { m_scale = _scale; }
	//void SetRad(Math::Vector2 _rad) { m_rad = _rad; }
	//void SetDeg(float _deg) { m_deg = _deg; }
	//void SetMat(MathSet _mathSet) { m_mat = _mathSet; }
	//void SetColor(Math::Color _color) { m_color = _color; }

	//void SetTexture(std::string _fileName);

	//HitStruct GetObj();

	//int m_hp = 0;
	//void SetHP(int _hp) { m_hp = _hp; }
	//int GetHP() { return m_hp; }

	//void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }

private:

	// 翼共通
	Math::Rectangle m_wingsRect;

	// 左翼


	// 右翼


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

	//// 影
	//struct ShadowSt
	//{
	//	Math::Vector2	pos;
	//	Math::Color		color;
	//	MathSet			mat;
	//}m_shadow;

};