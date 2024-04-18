#pragma once

class Scene;

class C_Enemy
{
public:

	void Init();
	void Update();
	void Draw();

	// セッター
	void SetEnemyTex(KdTexture* a_pTex) { m_pTex = a_pTex; }
	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }
	void SetFlg(UINT active) { m_flg = active; }

	void SetbIsLock(bool ab) { m_bIsLock = ab; }
	bool GetbIsLock() { return m_bIsLock; }
	bool GetFlg() { return m_flg; }

	HitStruct GetObj();

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

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
	
	bool		  m_bIsLock;

};