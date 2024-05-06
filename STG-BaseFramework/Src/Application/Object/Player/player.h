#pragma once

#include "../BaseObject.h"
#include "../Attack/Bullet/bullet0.h"

struct LockOn
{
	Math::Vector2	pos;
	bool			bActive;
};

class Player :public BaseObject
{
public:

	Player();
	~Player()override { Release(); };

	void Init() override;
	void CheckVec();
	void Update() override;
	void Draw() override;

	// デバッグ用
	Math::Color GetDebugColor() { return m_DebugColor; }

	// 高速移動
	void UpdateMove();	// X + 方向キーでローリング
	float GetRollingVal() { return m_roll.frame1; }
	float GetRollingValMax() { return m_roll.frameMax; }

	void UpdateMove1();	// 方向キー二度押しでローリング（没）

	// ウェブ
	void DrawWebA();
	void DrawWebB();
	
	// シーカー
	void UpdateSeeker();
	void DrawSeeker();

	// 攻撃系
	void UpdateAttack();

	// ホーミング弾発射
	void CreateHLaser();

	// セッター
	// 切り取り範囲
	void SetNowAnim(Math::Vector2 _animY) { m_nowAnim = _animY; }
	Math::Vector2 GetNowAnim() { return m_nowAnim; }
	void AddNowAnim(int _addX, int _addY);
		
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

	HitStruct GetObj();		// 自機当たり判定用
	HitStruct GetSeekObj();	// シーカー当たり判定用

	HitStruct GetWebBObj();
	float GetWebBsize() { return m_webB.size; }
	float GetWebBdegAdd() { return m_webB.degAdd; }

	int GetRollFlg() { return m_roll.flg; }

	float GetFrame0() { return m_frame; }

private:

	struct webStruct
	{
		bool			flg;
		Math::Vector2	pos;
		float			size;
		float			sizeXAdd;
		float			degMove;
		float			degAdd;
		int				frame;
	};

	// 拡散型ウェブ (A)
	webStruct m_webA;

	//集中型ウェブ (B)
	webStruct m_webB;

	struct charge
	{
		float	frame;
		int		flg;

	}m_charge;

	// 自機
	// 移動速度
	float m_moveSpd = 7.5f;

	Math::Rectangle	m_ownAlphaRect;			// 切り取り範囲

	Math::Vector2	m_speed;				// 移動量に入れる値
	float			m_Hrad;					// 弾との当たり判定用半径
	Math::Color		m_DebugColor;			// デバッグ用色

	// ローリング
	struct Roll
	{
		int		flg;		// ﾌﾗｸﾞ
		Dir		dir;		// 方向
		float	frame1;		// 入力用フレーム
		float	frame2;		// 入力用フレーム
		float	frameMax;		// 入力用フレーム
		float	move;		// 移動量プラス用
		int		cnt;		// キーのカウント用
	}m_roll;

	// シーカー
	int						m_SImgPosX = 0;
	int						m_SImgPosY = 128 * 2;

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
};