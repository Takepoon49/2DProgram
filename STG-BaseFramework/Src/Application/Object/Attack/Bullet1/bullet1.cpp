#include "bullet1.h"

void Bullet1::Init()
{
	m_pTex = nullptr;

	m_AlphaRect = { 42, 0, 12, 12 };
	//m_AddRect = { 7, 0, 7, 19 };

	m_flg = 0;

	m_pos = { 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f };
	m_scale = { 1.4f, 1.4f };

	m_rad = { m_AlphaRect.width * m_scale.x / 2.0f,
				m_AlphaRect.height * m_scale.y / 2.0f };

	m_deg = 45.0f;

	m_mat.Init();

	m_color = C_RED;
	m_color = { 1.0f, 0.7f, 0.0f, 1.0f };

	m_speed = { 0.0f, 27.0f };

	m_frame = 0;
}

void Bullet1::Shot(Math::Vector2 _pos, float _deg, int _flg)
{
	m_pos = _pos;
	m_move.x = cos(DirectX::XMConvertToRadians(_deg)) * 5.0f;
	m_move.y = sin(DirectX::XMConvertToRadians(_deg)) * 5.0f;
	m_flg = _flg;

	switch (_flg)
	{
	case 0:
		break;

	default:
		break;
	}
}

void Bullet1::Update()
{
	m_frame++;
	if (m_frame > 600) m_frame = 0;

	m_pos += m_move;

	// í[îªíË
	if (m_pos.x < scrLeft - m_rad.x || m_pos.x > scrRight + m_rad.x ||
		m_pos.y < scrBottom - m_rad.y|| m_pos.y > scrTop + m_rad.y)
	{
		m_flg = 0;
	}

	// âÒì]
	if (m_frame % 5 == 0)
	{
		m_deg += 90;
		if (m_deg >= 360) m_deg = 0;
	}

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.Mix();
}

void Bullet1::Draw()
{
	switch (m_flg)
	{
	case 0:
		return;	// ëÅä˙ÉäÉ^Å[Éì

	case 1:	// î≠éÀíÜ
		SHADER.m_spriteShader.SetMatrix(m_mat.m);
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &m_AlphaRect, &m_color);

		//DrawImg(m_mat.m, m_pTex, m_AlphaRect, 1.0f);

		//D3D.SetBlendState(BlendMode::Add);

		//DrawImgEX(m_mat.m, m_pTex, Math::Rectangle(m_AddRect.x, m_AddRect.y,
		//	m_AddRect.width, m_AddRect.height), m_color);

		//D3D.SetBlendState(BlendMode::Alpha);
		break;

	case 2:	// ìñÇΩÇ¡ÇΩ
		SHADER.m_spriteShader.SetMatrix(m_mat.m);
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &m_AlphaRect, &m_color);
		break;
	}
}
