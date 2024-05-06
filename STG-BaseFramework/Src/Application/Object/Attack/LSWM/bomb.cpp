#include "bomb.h"
#include "../../../Scene/Scene.h"

void Bomb::Init(Math::Vector2 _pos, int _flg)
{
	m_rect = { 0, 29, 32, 8 };
	m_nowAnim = { 0.0f, 0.0f };

	m_frame = 0;
	m_flg = st_alive;
	m_pos = _pos;
	m_moveVec = Math::Vector2::Zero;
	m_scale = { 1.0f, 2.0f };
	m_rad = { 0.0f, 0.0f };
	if (_flg == 0)
	{
		m_deg = 90 - 25.0f;
		m_move.x = cos(DegToRad(m_deg)) * 7.5f;
		m_move.y = sin(DegToRad(m_deg)) * 7.5f;
	}
	else
	{
		m_deg = 90 + 25.0f;
		m_move.x = cos(DegToRad(m_deg)) * 7.5f;
		m_move.y = sin(DegToRad(m_deg)) * 7.5f;
	}

	m_mat.Init();
	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_shadow.pos = _pos;
	m_shadow.mat.Init();
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.5f };
}

void Bomb::Update()
{
	m_frame++;

	m_pos += m_move;

	//if (m_pos.y >= 160.0f)
	if (m_frame >= 50)
	{
		m_flg = st_dead;
		m_pOwner->MakeShockWave(m_pos);
	}

	//if (m_frame % 2 == 0)
	{
		m_pOwner->CreateMSLTrail(m_pos);
	}

	// çsóÒçÏê¨
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	// âe
	m_shadow.pos.x = m_pos.x + 14.0f;
	m_shadow.pos.y = m_pos.y - 28.0f;
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x * 0.7f, m_scale.y * 0.7f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_shadow.pos.x, m_shadow.pos.y, 0.0f);
	m_shadow.mat.Mix();
}

void Bomb::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_shadow.mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_shadow.color);

	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);
}
