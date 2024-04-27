#include "EnemyBase.h"

void EnemyBase::Update()
{
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void EnemyBase::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);
}

void EnemyBase::Init()
{
	//m_rect = { 0, 0, 115, 106 };

	//m_flg = st_dead;
	//m_pos = {};
	//m_move = {};
	//m_scale = { 1.0f, 1.0f };
	//m_rad = { m_rect.width * m_scale.x, m_rect.height * m_scale.y };
	//m_rad /= 2.0f;
	//m_deg = 0.0f;
	//m_mat.Init();
	//m_color = C_WHITE;

	//m_speed = {};
}

void EnemyBase::Release()
{
	m_tex.Release();
}