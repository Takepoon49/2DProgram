#include "HLTrail.h"

HLTrail::HLTrail()
{
}

void HLTrail::Init(Math::Vector2 _pos, float _deg, Math::Color _color)
{
	//m_alphaRect = { 28, 0, m_ImgSizeX, m_ImgSizeY };
	m_rect = { 28, 14, m_ImgSizeX, m_ImgSizeY };

	m_flg = 1;
	m_pos = _pos;
	m_move = { 0.0f, 3.0f };
	m_scale = { 1.3f, 2.0f };
	m_rad = { m_rect.width * m_scale.x / 2.0f, m_rect.height * m_scale.y / 2.0f };
	m_deg = _deg;
	m_mat.Init();
	m_color = _color;
	m_color.w = 1.0f;
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.20f };

	m_radian = 0.0f;
	m_speed = 1.0f;

	m_frame = 0;
}

void HLTrail::Update()
{
	m_frame++;

	if (m_frame > m_life)
	{
		//if (m_speed < 15.0f)
		//{
		//	m_speed *= 1.2f;
		//}
		m_flg = st_dead;
	}

	//m_color.w -= 1.0f / m_life;
	m_scale.x -= 0.8f / m_life;

	// ˆÚ“®—ÊŒvZ
	//m_radian = DirectX::XMConvertToRadians(m_deg);
	//m_move.x = cos(m_radian) * m_speed;
	//m_move.y = sin(m_radian) * m_speed;

	// ˆÚ“®ˆ—
	//m_pos += m_move;

	m_mat.s = Math::Matrix::CreateScale(m_scale.x / 1.5f, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();

	// ‰e‚Ìs—ñ
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x / 1.5f - 0.3f, m_scale.y - 0.3f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_pos.x + 30.0f, m_pos.y - 25.0f, 0.0f);
	m_shadow.mat.Mix();
}

void HLTrail::Draw()
{

	//D3D.SetBlendState(BlendMode::Add);

	DrawImgEX(m_shadow.mat.m, &m_tex, m_rect, m_shadow.color);

	//DrawImgEX(m_mat.m, &m_tex, m_rect, m_color);
	DrawImgEX(m_mat.m, &m_tex, m_rect, m_color);

	//D3D.SetBlendState(BlendMode::Alpha);

}
