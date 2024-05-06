#include "H-Laser.h"
#include "../../../Scene/Scene.h"
#include "../../../Object/Enemy/enemy/enemy.h"
#include "../../../Object/Particle/light0/lightH.h"

void HLaser::Init(Math::Vector2 _pos, float _deg)
{
	m_rect = { 28, 14, m_ImgSizeX, m_ImgSizeY };

	m_flg = st_alive;
	m_pos = _pos;
	m_move = { 0.0f, 3.0f };
	m_scale = { 1.2f, 1.3f };
	m_rad = { m_rect.width * m_scale.x / 2.0f, m_rect.height * m_scale.y / 2.0f };
	m_deg = _deg;
	m_mat.Init();

	m_color = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_radian = 0.0f;
	m_speed = 3.0f;
	
	m_frame = 0;

	m_rndTime = rand() % 3 + 3;
}

void HLaser::Update()
{
	m_frame++;
	
	switch (m_flg)
	{
	case st_alive:

		if (m_speed < 15.0f)
		{
			m_speed *= 1.2f;
		}

		//if (m_deg < 270.0f) m_deg -= 4.0f;
		//if (m_deg > 270.0f) m_deg += 4.0f;
		if (m_frame > m_rndTime)
		{
			m_flg = st_stat1;
			m_frame = 0;
			m_speed = 12.0f;
		}

		m_radian = DirectX::XMConvertToRadians(m_deg);
		m_move.x = cos(m_radian) * m_speed;
		m_move.y = sin(m_radian) * m_speed;
		break;

	case st_stat1:
		//CalcMove(m_target->GetPos(), 0);
		m_tgtDeg = CalcTgtDeg(m_target->GetPos());

		// 移動量計算
		if (m_deg > m_tgtDeg) m_deg -= 1.0f;
		if (m_deg < m_tgtDeg) m_deg += 1.0f;

		m_radian = DirectX::XMConvertToRadians(m_deg);
		m_move.x = cos(m_radian) * m_speed;
		m_move.y = sin(m_radian) * m_speed;

		if (m_frame > 7)
		{
			m_flg = st_stat2;
			m_frame = 0;
		}
		break;

	case st_stat2:
		//m_deg = CalcOwnDeg(m_target->GetPos());

		if (m_speed < 14.0f)
		{
			m_speed *= 1.1f;
		}

		if (m_frame < 35 && m_target->GetFlg() == st_alive)
		{
			m_deg = CalcOwnDeg(m_target->GetPos());
		}

		m_radian = DirectX::XMConvertToRadians(m_deg);
		m_move.x = cos(m_radian) * m_speed;
		m_move.y = sin(m_radian) * m_speed;
		break;

	default:
		break;
	}

	// 移動処理
	m_pos += m_move;

	//switch (m_target->GetFlg())
	//{
	//case st_alive:
	//	break;

	//case st_stat1:
	//case st_stat2:
	//	m_target->CalcMove(m_pos, 0);

	//	v = m_target->GetPos() - m_pos;

	//	// 球判定　・・・　ベクトルの長さで判定する
	//	if (v.Length() < 26.0f)
	//	{
	//		m_hp = 0;
	//		m_target->SetFlg(st_dead);
	//	}

	// ターゲットとの当たり判定
	if (m_target->GetFlg() != st_dead)
	if (m_target->GetHP() > 0)
	{
		// 対象座標 - 自分座標 = 対象へのベクトル
		Math::Vector2 v = m_target->GetPos() - m_pos;

		// 円判定
		if (v.Length() < 24.0f)
		{
			m_flg = st_dead;
			m_target->SetHP(0);
			m_pOwner->AddScore(50);
		}
	}

	// 軌跡描画
	if (m_frame % 1 == 0)
	{
		m_pOwner->CreateHLTrail(m_pos, m_deg + 90.0f, m_color);
	}
	// 

	// 画面外判定
	if (m_pos.x > scrRight + 100.0f || m_pos.x < scrLeft - 100.0f) m_flg = st_dead;
	if (m_pos.y > scrTop + 100.0f || m_pos.y < scrBottom - 100.0f) m_flg = st_dead;

	// 行列
	m_mat.s = Math::Matrix::CreateScale(m_scale.x / 1.5f, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg + 90.0f));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
	// 影の行列
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x / 1.5f - 0.3f, m_scale.y - 0.3f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_pos.x + 30.0f, m_pos.y - 25.0f, 0.0f);
	m_shadow.mat.Mix();
}

void HLaser::Draw()
{
	//if (m_flg == 0) return;
	DrawImg(m_mat.m, &m_tex, m_rect, m_color.w);
	DrawImgEX(m_shadow.mat.m, &m_tex, m_rect, m_shadow.color);

	D3D.SetBlendState(BlendMode::Add);

	DrawImgEX(m_mat.m, &m_tex, m_rect, m_color);

	D3D.SetBlendState(BlendMode::Alpha);
}

float HLaser::CalcMove(Math::Vector2 _tpos, int _num)
{


	return m_tgtDeg;
}

float HLaser::CalcOwnDeg(Math::Vector2 _pos)
{
	Math::Vector2 c_pos;
	c_pos.x = _pos.x - m_pos.x;
	c_pos.y = _pos.y - m_pos.y;
	float radian = atan2(c_pos.y, c_pos.x);

	return DirectX::XMConvertToDegrees(radian);
}

float HLaser::CalcTgtDeg(Math::Vector2 _pos)
{
	Math::Vector2 c_pos;
	c_pos.x = _pos.x - m_pos.x;
	c_pos.y = _pos.y - m_pos.y;
	float radian = atan2(c_pos.y, c_pos.x);

	return DirectX::XMConvertToDegrees(radian);
}

//void HLaser::SetMove(Math::Vector2 _pos)
//{
//	Math::Vector2 c_pos;
//	c_pos.x = _pos.x - m_pos.x;
//	c_pos.y = _pos.y - m_pos.y;
//	float radian = atan2(c_pos.y, c_pos.x);
//
//	m_move.x = cos(radian) * 5.0f;
//	m_move.y = sin(radian) * 5.0f;
//}

void HLaser::Release()
{

}
