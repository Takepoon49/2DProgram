#include "TrailA.h"
#include "../../../Scene/Scene.h"

TrailA::TrailA()
{

}

void TrailA::Init(Math::Vector2 _pos)
{
	m_life = 0;	// •\Ž¦ŽžŠÔ

	m_nowAnim = { 0.0f, 0.0f };

	m_frame = 0;
	m_flg = st_alive;

	m_pos.x = _pos.x;
	m_pos.y = _pos.y - 16.0f;

	m_move = {};
	m_moveVec = {};
	m_rad = { m_ImgSizeX / 2.0f, m_ImgSizeY / 2.0f };
	m_deg = 0;
	m_mat.Init();


	m_scale = { 0.7f, 0.7f };
	m_color = { 1.0f, 1.0f, 1.0f, 0.5f };
	//m_rect = { 64, 128, m_ImgSizeX, m_ImgSizeY };
	//m_rect = { 128, 128, m_ImgSizeX, m_ImgSizeY };
	m_rect = { 0, 128, m_ImgSizeX, m_ImgSizeY };

	m_type = ParticleType::MSLTrail;
}

void TrailA::Update()
{
	m_frame++;

	//m_deg += 15;
	//if (m_deg >= 360) m_deg = 0;

	//if (m_frame >= m_life)
	//{
	//	m_flg = st_dead;
	//}

	m_scale.x -= 1.0f / 70.0f;
	m_scale.y -= 1.0f / 70.0f;

	m_color.w -= 0.5f / 60.0f;

	if (m_frame > 60)
	{
		m_flg = st_dead;
	}

	//m_pos += m_move;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void TrailA::Draw()
{
	D3D.SetBlendState(BlendMode::Add);

	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);

	D3D.SetBlendState(BlendMode::Alpha);
}
