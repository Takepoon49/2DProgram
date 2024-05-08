#include "boss.h"
#include "../../../Scene/Scene.h"

Boss::Boss()
{

}

void Boss::Init()
{
	// ì∑ëÃ
	m_rect = { 0, 128, 68, 92 };
	m_deg = 0.0f;
	m_scale = { 1.0f, 1.0f };

	m_flg = st_alive;
	m_mflg = 0;
	m_pos = { 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f };
	m_mat.Init();

	// óºóÉã§í 
	m_wingsRect = { 0, 128, 68, 92 };
	m_lmat.Init();
	m_rmat.Init();

	// ç∂óÉ
	m_lPos = { 0.0f, 0.0f };

	// âEóÉ
	m_lPos = { 0.0f, 0.0f };

	// ÇªÇÃëºïœêî
	m_nowAnim = { 0.0f, 0.0f };
	m_frame = 0;
	m_moveVec = Math::Vector2::Zero;
	m_rad = { 0.0f, 0.0f };

	m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Boss::Update()
{
	m_frame++;

	switch (m_mflg)
	{
	case 0:
		m_move = { 0.0f, 0.0f };
		break;

	case 1:

		break;
	}

	// ì∑ëÃ
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(m_deg);
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();
	
	// ç∂óÉ
	m_lmat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_lmat.r = Math::Matrix::CreateRotationZ(m_lDeg);
	m_lmat.t = Math::Matrix::CreateTranslation(m_lPos.x, m_lPos.y, 0.0f);
	m_lmat.Mix();

	// âEóÉ
	m_rmat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_rmat.r = Math::Matrix::CreateRotationZ(m_rDeg);
	m_rmat.t = Math::Matrix::CreateTranslation(m_rPos.x, m_rPos.y, 0.0f);
	m_rmat.Mix();
}

void Boss::Draw()
{
	// ì∑ëÃ
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rect, 1.0f);

	// ç∂óÉ
	SHADER.m_spriteShader.SetMatrix(m_lmat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_wingsRect, 1.0f);

	// âEóÉ
	SHADER.m_spriteShader.SetMatrix(m_rmat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_wingsRect, 1.0f);
}
