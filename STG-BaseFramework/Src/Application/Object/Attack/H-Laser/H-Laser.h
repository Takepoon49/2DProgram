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
	Math::Vector2		m_pos[MaxNum];		// ���W
	Math::Vector2		m_move[MaxNum];		// �ړ���
	Math::Vector2		m_size;				// �T�C�Y
	float				m_deg[MaxNum];		// �p�x
	MathSet				m_mat[MaxNum];		// �s��
	Math::Color			m_color[MaxNum];	// �F

	Math::Rectangle		m_rect;

	int					m_flg;
};