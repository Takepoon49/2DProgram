#include "../../Scene/Scene.h"
#include "ParticleBase.h"

void ParticleBase::Init(int _type, Math::Vector2 _pos)
{
	m_type = _type;
	m_pos = _pos;
}

void ParticleBase::Update()
{
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void ParticleBase::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(m_pTex, m_rect, 1.0f);
}