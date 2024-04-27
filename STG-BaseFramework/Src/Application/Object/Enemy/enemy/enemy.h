#pragma once

#include "../../Attack/Bullet1/bullet1.h"
#include "../../Particle/explosion/explosion.h"

class Scene;

class C_Enemy
{
public:

	void Init();
	void Update(Math::Vector2 ppos);
	void Draw();

	void SetRndPos();

	// 弾関連
	int GetBullet1Size() { return m_bulletList.size(); }
	void SetBullet1Tex(KdTexture* _pTex) { m_pBullet1Tex = _pTex; }

	void DeleteBullet1();
	void CreateBullet1();

	// パーティクル
	void SetParticleTex(KdTexture* _pTex) { m_pParticleTex = _pTex; }
	
	// 爆発
	void CreateExplosion();
	void DeleteExplosion();

	// セッター
	void SetEnemyTex(KdTexture* _pTex) { m_pTex = _pTex; }
	void SetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }
	void SetFlg(UINT active) { m_flg = active; }

	void SetbLock(bool ab) { m_Lock.flg = ab; }
	void SetDeg(float _deg) { m_deg = _deg; }

	bool GetbLock() { return m_Lock.flg; }
	UINT GetFlg() { return m_flg; }
	float GetDeg() { return m_deg; }

	HitStruct GetObj();

	// UI
	void SetUITex(KdTexture* _pTex) { m_pUITex = _pTex; }

	// HP
	int				m_hp;

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;
	KdTexture* m_pUITex;

	// UI
	struct e_Lock
	{
		bool			flg;
		Math::Color		color;
		float			frame;

		MathSet			mat;
		Math::Rectangle rect;

	}m_Lock;

	// 敵機
	Math::Rectangle	m_AlphaRect = { 0, 0, 115, 106 };

	Math::Vector2	m_pos;
	Math::Vector2	m_rad;
	Math::Vector2	m_scale;
	float			m_deg;
	MathSet			m_mat;
	Math::Color		m_color;
	Math::Color		m_dColor;

	UINT			m_flg;
	int				m_frame;

	// 弾
	std::vector<Bullet1*> m_bulletList;
	std::vector<Bullet1*>::iterator m_bulletIt;
	KdTexture* m_pBullet1Tex;

	// パーティクル
	KdTexture* m_pParticleTex;

	// 爆発
	std::vector<Explosion*> m_explsnList;
	std::vector<Explosion*>::iterator m_explsnIt;
};