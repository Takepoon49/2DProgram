#pragma once

#include "../../../utility.h"

class Scene;

class HLaser
{
public:

	HLaser() {};
	~HLaser() {};

	void Init();
	void Update(Math::Vector2 _pos);
	void Draw();

	void CalcMove(Math::Vector2 _pos, int _num);

	void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }

	void SetTex(KdTexture* _pTex) { m_pTex = _pTex; }

private:

	void Release();

	Scene* m_pOwner;

	KdTexture* m_pTex;

	static const int MaxNum = 1;
	Math::Vector2		m_pos[MaxNum];		// 座標
	Math::Vector2		m_move[MaxNum];		// 移動量
	Math::Vector2		m_size;				// サイズ
	float				m_deg[MaxNum];		// 角度
	MathSet				m_mat[MaxNum];		// 行列
	Math::Color			m_color[MaxNum];	// 色

	Math::Rectangle		m_rect;

	int					m_flg;
};