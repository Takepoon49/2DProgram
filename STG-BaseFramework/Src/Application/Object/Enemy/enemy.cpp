#include "../../Scene/Scene.h"
#include "enemy.h"

void C_Enemy::Init()
{
	m_pos = { 200.0f, 100.0f };
	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_color = { 0.95f, 0.2f, 0.2f, 1.0f };
	m_dColor = C_RED;
	m_deg = 0.0f;
	m_scale = { 0.7f, 0.7f };
	//m_rad = { m_ImgSizeX * m_scale.x, m_ImgSizeY * m_scale.y };
	m_rad = { m_AlphaRect.width * m_scale.x, m_AlphaRect.height * m_scale.y };
	m_rad /= 2.75f;

	m_flg = st_alive;
	m_bIsLock = false;
}

void C_Enemy::Update()
{
	switch (m_flg)
	{
	case BaseBitState::st_dead:

		return;
		break;
	case BaseBitState::st_alive:

		break;
	case BaseBitState::st_stat1:
		m_deg = -30.0f;
		break;
	}

	// 行列作成
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;
}

void C_Enemy::Draw()
{
	if (m_flg == st_dead) return;

	// 描画
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat.m);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(m_pTex, 0, 0, &m_AlphaRect, &m_color);

	if (m_pOwner->GetDebugFlg())
	{
		// デバッグ
		ResetMatrix();
		m_dColor = C_RED;
		KdShaderManager::GetInstance().m_spriteShader.DrawBox
			(m_pos.x, m_pos.y, m_rad.x, m_rad.y, &m_dColor, false);
	}
}

HitStruct C_Enemy::GetObj()
{
	HitStruct objTemp;
	objTemp.pos = m_pos;
	objTemp.rad = m_rad;
	objTemp.flg = m_flg;
	return objTemp;
}
