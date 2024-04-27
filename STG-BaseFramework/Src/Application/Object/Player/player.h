#pragma once

#include "../BaseObject.h"
#include "../Attack/Bullet/bullet0.h"
#include "../Attack/H-Laser/H-Laser.h"

struct LockOn
{
	Math::Vector2	pos;
	bool			bActive;
};

class Player :public BaseObject
{
public:

	Player() {};
	~Player() { Release(); };

	void Init() override;
	void CheckVec();
	void Update() override;
	void Draw() override;

	// ウェブ
	void DrawWebA();
	void DrawWebB();

	Math::Color GetDebugColor() { return m_DebugColor; }
	
	// シーカー
	void UpdateSeeker();
	void DrawSeeker();

	// 攻撃系
	void UpdateAttack();

	// セッター
	// 切り取り範囲
	void SetNowAnimY(int _animY) { m_nowAnim.y = (int)_animY; }
	// 自機色
	void SetPColor(Math::Color _color) { m_color = _color; }

	//void SetPlayerTex(KdTexture* a_pTex) { m_pTex = a_pTex; }
	void SetBullet0Tex(KdTexture* a_pTex) { m_pBullet0Tex = a_pTex; }
	void SetPDeg(float deg) { m_deg = deg; }

	// ゲッター
	float GetPDeg() { return m_deg; }

	// 弾
	void CreateBullet(Math::Vector2 a_pos);
	void CreateBullet(float _x, float _y);

	int GetBulletNum() { return m_bulletList.size(); }
	int GetBulletFlg(int num) { return m_bulletList[num]->GetFlg(); }

	int GetShootTime() { return m_shootTime; }
	int GetShootFlg() { return m_shootFlg; }

	HitStruct GetBulletObj(int num) { return m_bulletList[num]->GetObj(); }

	//void SetBullet0Tex(KdTexture* a_pTex) { m_pBullet0Tex = a_pTex; }
	void SetBulletFlg(int num, int _flg) { m_bulletList[num]->SetFlg(_flg); }

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }

	HitStruct GetObj();		// 自機当たり判定用
	HitStruct GetSeekObj();	// シーカー当たり判定用

	// ウェブ
	int				m_webMode;	// 0:拡散型 1:集中型

	struct webStruct
	{
		bool			flg;
		Math::Vector2	pos;
		float			size;
		float			sizeXAdd;
		float			degMove;
		float			degAdd;
	};

	HitStruct GetWebBObj();

private:

	Scene* m_pOwner;

	// 拡散型ウェブ (A)
	webStruct m_webA;

	//集中型ウェブ (B)
	webStruct m_webB;

	// キーフラグ
	bool keyFlg[k_end];

	//KdTexture*		m_pTex;

	// 自機
	Math::Rectangle	m_ownAlphaRect;			// 切り取り範囲
	Math::Vector2	m_nowAnim;

	int				m_frame;

	Math::Vector2	m_speed;				// 移動量に入れる値
	float			m_Hrad;					// 弾との当たり判定用半径
	Math::Color		m_DebugColor;			// デバッグ用色

	// シーカー
	//int					m_SImgPosX = 100;
	//int					m_SImgPosY = 106;
	int						m_SImgPosX = 0;
	int						m_SImgPosY = 128 * 2;

	//static const int	m_SImgSizeX = 100;
	//static const int	m_SImgSizeY = 100;
	static const int	m_SImgSizeX = 128;
	static const int	m_SImgSizeY = 128;

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

	int		m_shootFlg;
	int		m_shootTime;

	// 追尾レーザー
	HLaser	m_hLaser;
};