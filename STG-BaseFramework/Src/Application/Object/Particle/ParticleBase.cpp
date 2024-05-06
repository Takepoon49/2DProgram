#include "../../Scene/Scene.h"
#include "ParticleBase.h"

ParticleBase::ParticleBase()
{
	m_type = ParticleType::Test;

	m_nowAnim = { 0.0f, 0.0f };
	m_rect = { 0, 0, 64, 64 };

	m_flg = st_dead;
	m_frame = 0;

	m_pos = {};
	m_move = {};
	m_scale = { 1.0f, 1.0f };
	m_deg = 0.0f;
	m_mat.Init();
	m_color = C_WHITE;
}

void ParticleBase::Init(ParticleType _type, Math::Vector2 _pos)
{
	m_type = _type;
	m_pos = _pos;
}

void ParticleBase::Update()
{
	m_frame++;
	
	if (m_frame % 30 == 0) m_nowAnim.x += 1.0f;
	if (m_nowAnim.x > 3) m_nowAnim.x = 0.0f;

	m_rect = { m_ImgSizeX * (int)m_nowAnim.x, m_ImgSizeY * (int)m_nowAnim.y, m_ImgSizeX, m_ImgSizeY };

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void ParticleBase::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rect, 1.0f);
}

void ParticleBase::Release()
{
	m_tex.Release();
}
