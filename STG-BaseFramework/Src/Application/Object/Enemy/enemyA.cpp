#include "enemyA.h"

void EnemyA::Update()
{
	m_pos += m_move;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void EnemyA::Init()
{
	SetTexture("Data/Texture/enemy0.png");

	m_rect = { 0, 0, 115, 106 };

	m_flg = st_alive;
	m_pos = {};
	m_pos = { Rnd() * 1280.0f - 640.0f, Rnd() * 720.0f - 360.0f };
	m_move = {};
	m_scale = { 0.7f, 0.7f };
	m_rad = { m_rect.width * m_scale.x, m_rect.height * m_scale.y };
	m_rad /= 2.0f;
	m_deg = 0.0f;
	m_mat.Init();
	m_color = C_BLUE;

	m_speed = {};
}

void EnemyA::Release()
{
	m_tex.Release();
}
