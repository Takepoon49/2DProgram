#pragma once

//#include "../../BaseObject.h"
#include "enemy.h"

class Enemy1 : public Enemy
{
public:

	Enemy1();
	~Enemy1() {};

	void Init(int _flg, int _stime) override;
	void Update(Math::Vector2 ppos) override;
	void Draw() override;

	//// ランダム出現
	void SetRndPos() override;
	//void SetLockFlg(int ab) { m_Lock.flg = ab; }

	//int GetLockFlg() { return m_Lock.flg; }

	//// UI
	//void SetUITex(KdTexture* _pTex) { m_pUITex = _pTex; }

private:

	//KdTexture* m_pUITex;

	//// 行動パターン用
	//int					m_movePtn = EnemyPattern::ep_d1;
	//int					m_frame2 = 0;

	//// UI
	//struct e_Lock
	//{
	//	int				flg;
	//	Math::Color		color;
	//	float			frame;

	//	MathSet			mat;
	//	Math::Rectangle rect;

	//}m_Lock;

	//// 敵機
	//Math::Rectangle	m_AlphaRect = { 0, 0, 256, 128 };
	//Math::Color		m_dColor;
	//int				m_nowAnimX;

	//int				m_shotTime = 0;

};