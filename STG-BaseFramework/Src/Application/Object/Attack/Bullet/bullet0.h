#pragma once

class Scene;

class C_Bullet0
{
public:

	C_Bullet0();
	~C_Bullet0();

	void Init();
	void Update();
	void Draw();

	void Shot(Math::Vector2 a_pos);		// 発射処理

	// ゲッター
	const int GetFlg();					// フラグを返す
	const Math::Vector2 GetPos();		// 座標を返す
	const Math::Vector2 GetRad();		// 半径を返す
	const HitStruct GetObj();			// 当たり判定用の構造体を返す

	// セッター
	void SetFlg(int _flg) { m_flg = _flg; }
	void SetMove(Math::Vector2 _move) { m_move = _move; }

	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:

	KdTexture*			m_pTex;

	Math::Rectangle		m_AlphaRect;
	Math::Rectangle		m_AddRect;

	UINT				m_flg;
	Math::Vector2		m_pos;
	Math::Vector2		m_move;
	Math::Vector2		m_emove;
	Math::Vector2		m_scale;
	Math::Vector2		m_rad;
	float				m_deg;
	MathSet				m_mat;
	Math::Color			m_color;

	Math::Vector2		m_speed;

	int					m_frame;
};