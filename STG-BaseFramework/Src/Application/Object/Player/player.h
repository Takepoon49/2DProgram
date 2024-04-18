#pragma once
#include "../Attack/Bullet/bullet0.h"

struct LockOn
{
	Math::Vector2	pos;
	bool			bActive;
};

class Scene;

class C_Player
{
public:

	C_Player() {}
	~C_Player() {}

	void Init();
	void CheckVec();
	void Update();
	void Draw();
	
	// シーカー
	void UpdateSeeker();
	void DrawSeeker();

	// セッター
	void SetPlayerTex(KdTexture* a_pTex) { m_pTex = a_pTex; }

	void SetPDeg(float deg) { m_deg = deg; }

	// ゲッター
	float GetPDeg() { return m_deg; }

	// 弾
	void CreateBullet(Math::Vector2 a_pos, bool a_num);
	
	int GetBulletNum() { return m_bulletList.size(); }
	
	bool GetBulletFlg(int num) { return m_bulletList[num]->GetFlg(); }
	
	HitStruct GetBulletObj(int num) { return m_bulletList[num]->GetObj(); }
	
	void SetBullet0Tex(KdTexture* a_pTex) { m_pBullet0Tex = a_pTex; }
	void SetBulletFlg(int num, bool a_bActive) { m_bulletList[num]->SetFlg(a_bActive); }

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	HitStruct GetObj();		// 自機当たり判定用
	HitStruct GetSeekObj();	// シーカー当たり判定用

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

	keynum KeyNum;

	// 自機
	UINT			m_flg;					// 状態管理フラグ

	Math::Rectangle	m_ownAlphaRect;			// 切り取り範囲

	Math::Vector2	m_pos;					// 座標
	Math::Vector2	m_move;					// 移動量
	Math::Vector2	m_speed;				// 移動量に入れる値
	Math::Vector2	m_scale;				// 拡大率
	Math::Vector2	m_rad;					// 端との当たり判定用半径
	float			m_Hrad;					// 弾との当たり判定用半径
	float			m_deg;					// 角度
	MathSet			m_mat;					// 行列
	Math::Color		m_color;				// 色
	Math::Color		m_DebugColor;			// デバッグ用色

	// シーカー
	UINT				m_SImgPosX = 100;
	UINT				m_SImgPosY = 106;
	static const int	m_SImgSizeX = 100;
	static const int	m_SImgSizeY = 100;
	Math::Vector2		m_spos;			// 座標
	Math::Vector2		m_sscale;		// 大きさ
	float				m_sdeg;			// 角度
	MathSet				m_seekerMat;	// 行列
	Math::Color			m_sColor;		// 色
	bool				m_seekerFlg;	// フラグ

	// ロックオン
	std::vector<LockOn*> m_pLockList;
	std::vector<LockOn*>::iterator m_pLockIt;

	// 弾(可変長)
	KdTexture* m_pBullet0Tex;
	std::vector<C_Bullet0*> m_bulletList;
	std::vector<C_Bullet0*>::iterator it;

	float m_bulletTime;


	// ウェブ
	UINT			webMode;	// 0:拡散型 1:集中型

	// 拡散型ウェブ (A)
	bool			Aflg;		// 
	float			Aradius;		// 
	
	// 集中型ウェブ (B)
	bool			Bflg;		// 
	float			Bsize;	// 


	bool GetKeyFlg(int num);
	void SetKeyFlg(int num, bool tf);
};