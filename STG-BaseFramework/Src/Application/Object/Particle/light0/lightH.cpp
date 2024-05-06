#include "lightH.h"
#include "../../../Scene/Scene.h"
#include "../../../Object/Attack/H-Laser/H-Laser.h"

LightH::LightH()
{
	
}

void LightH::Init(std::shared_ptr<BaseObject> _pair, int _type)
{
	m_pair = _pair;

	m_life = 0;	// •\Ž¦ŽžŠÔ

	m_nowAnim = { 0.0f, 0.0f };

	m_frame = 0;
	m_flg = st_alive;
	m_pos = m_pair->GetPos();
	m_move = {};
	m_moveVec = {};
	m_rad = { m_ImgSizeX / 2.0f, m_ImgSizeY / 2.0f };
	m_deg = m_pair->GetDeg();
	m_mat.Init();

	if (_type == 0)
	{
		//m_scale.x = 1.5f;
		m_scale.x = m_pOwner->LightHSize;
		m_scale.y = m_scale.x;
		m_color = { 1.0f, 1.0f, 1.0f, 0.5f };
		m_rect = { 0, 128, m_ImgSizeX, m_ImgSizeY };
	}
	else
	{
		m_scale = { 1.1f, 2.0f };
		m_color = { 1.0f, 0.6f, 0.0f, 0.3f };
		//m_rect = { 64, 128, m_ImgSizeX, m_ImgSizeY };
		m_rect = { 0, 128, m_ImgSizeX, m_ImgSizeY };
	}

	m_type = ParticleType::Light0;
}

void LightH::Update()
{
	m_frame++;

	m_deg += 15;
	if (m_deg >= 360) m_deg = 0;
	
	//if (m_frame >= m_life)
	//{
	//	m_flg = st_dead;
	//}

	m_pos = m_pair->GetPos();
	if (m_pair->GetFlg() == st_dead) m_flg = st_dead;

	//m_pos += m_move;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
}

void LightH::Draw()
{
	D3D.SetBlendState(BlendMode::Add);

	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);

	D3D.SetBlendState(BlendMode::Alpha);
}
