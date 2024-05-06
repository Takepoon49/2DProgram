#include "../../../Scene/Scene.h"
#include "explosion.h"

Explosion::Explosion()
{
	m_type = ParticleType::ExplosionA;

	// ”š”­
	m_nowAnim = { 0.0f, 0.0f };
	m_rect = { 0, m_ImgSizeY, m_ImgSizeX, m_ImgSizeY };

	// ”š•—
	m_wsSize = { 0.0f, 0.0f };
	m_wsMat.Init();
	m_wsRect = { 96, 128, m_ImgSizeX, m_ImgSizeY };
	m_wsAlpha = 0.3f;

	m_flg = st_alive;
	m_frame = 0;

	m_pos = {};
	m_move = {};
	m_scale = { 1.85f, 1.85f };
	m_scale = { 3.2f, 3.2f };
	m_deg = 0.0f;
	m_mat.Init();
	m_color = C_WHITE;
}

void Explosion::Init(ParticleType _type, Math::Vector2 _pos)
{
	m_pos = _pos;
	m_type = _type;
}

void Explosion::Update()
{
	m_frame++;

	m_wsSize.x += 0.35f;
	m_wsSize.y += 0.35f;

	m_wsAlpha -= 0.015f;

	if (m_frame % 2 == 0) m_nowAnim.x += 1.0f;
	if (m_nowAnim.x >= 16) m_flg = st_dead;

	m_rect = { m_ImgSizeX * (int)m_nowAnim.x, m_ImgSizeY * (int)m_nowAnim.y, m_ImgSizeX, m_ImgSizeY };

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();

	m_wsMat.s = Math::Matrix::CreateScale(m_wsSize.x, m_wsSize.y, 0.0f);
	m_wsMat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_wsMat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_wsMat.Mix();
}

void Explosion::Draw()
{
	//if (m_flg == st_dead) return;

	D3D.SetBlendState(BlendMode::Add);

	SHADER.m_spriteShader.SetMatrix(m_wsMat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_wsRect, m_wsAlpha);

	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rect, 0.8f);

	D3D.SetBlendState(BlendMode::Alpha);
}
