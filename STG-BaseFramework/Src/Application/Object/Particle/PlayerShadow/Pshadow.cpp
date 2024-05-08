#include "Pshadow.h"
#include "../../../Scene/Scene.h"
#include "../../../Object/Player/player.h"

void PShadow::Init(std::shared_ptr<Player> _pair)
{
	m_pair = _pair;

	m_type = ParticleType::PShadow;

	m_nowAnim.x = m_pair->GetNowAnim().x * 128;
	m_nowAnim.y = m_pair->GetNowAnim().y * 128;

	m_life = 20;

	m_frame = 0;
	m_flg = st_alive;
	m_pos = _pair->GetPos();
	m_move = {};
	m_moveVec = {};
	m_scale = { 0.8f, 0.8f };
	m_rad = {};
	m_deg = 0.0f;
	m_mat.Init();
	m_color = { 0.0f, 0.0f, 0.0f, 0.5f };
}

void PShadow::Update()
{
	m_frame++;

	m_scale *= 0.97f;
	m_color.w *= 0.99f;

	if (m_frame >= m_life)
	{
		m_flg = st_dead;
	}

	m_nowAnim.x = m_pair->GetNowAnim().x;
	m_nowAnim.y = m_pair->GetNowAnim().y;
	m_rect = { (int)m_nowAnim.x * 128, (int)m_nowAnim.y * 128, m_ImgSizeX, m_ImgSizeY };

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void PShadow::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);
}
