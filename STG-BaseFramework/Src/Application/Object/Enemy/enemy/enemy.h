#pragma once

#include "../../BaseObject.h"

class HLaser;

class Enemy : public BaseObject
{
public:

	Enemy() {};
	~Enemy() {};

	virtual void Init(int _flg);
	virtual void Update(Math::Vector2 ppos);
	virtual void Draw() override;

	virtual void UpdateMovePattern();

	// �����_���o��
	virtual void SetRndPos();
	void SetLockFlg(int ab) { m_Lock.flg = ab; }

	int GetLockFlg() { return m_Lock.flg; }

	// UI
	void SetUITex(KdTexture* _pTex) { m_pUITex = _pTex; }

protected:

	KdTexture* m_pUITex;

	// �s���p�^�[���p
	int					m_movePtn = EnemyPattern::ep_d1;
	int					m_frame2 = 0;

	// UI
	struct e_Lock
	{
		int				flg;
		Math::Color		color;
		float			frame;

		MathSet			mat;
		Math::Rectangle rect;

	}m_Lock;

	// �G�@
	Math::Rectangle	m_AlphaRect = { 0, 0, 128, 128 };
	Math::Color		m_dColor;
	int				m_nowAnimX;

	int				m_shotTime = 0;
};