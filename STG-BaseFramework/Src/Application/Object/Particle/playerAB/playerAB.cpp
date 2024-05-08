#include "playerAB.h"
#include "../../../Scene/Scene.h"
#include "../../../Object/Player/player.h"

PlayerAB::PlayerAB()
{

}

void PlayerAB::Init()
{
	m_type = ParticleType::PlayerAB;
	m_life = 0;	// ‘å‚«‚³‚ª0.05ˆÈ‰º‚É‚È‚Á‚½‚çÁ‚·
	
	m_rect = { 0, 128, m_ImgSizeX, m_ImgSizeY };
	m_nowAnim = {};
	
	m_frame = 0;
	m_flg = st_alive;
	m_pos.x = m_player->GetPos().x;
	m_pos.y = m_player->GetPos().y + m_player->GetMoveVec().y - 45.0f;
	m_move = { 0.0f, -3.0f };
	m_moveVec = Math::Vector2::Zero;
	m_scale.x = Rnd() * 0.65f + 1.1f;
	m_scale.y = m_scale.x * 1.5f;

	m_rad = {};
	m_deg = 0.0f;
	m_mat.Init();
	//m_color = { 0.8f, 0.2f, 0.2f, 0.8f };
	//m_color = { 0.7f, 0.3f, 0.0f, 1.0f }; 
	m_color = { 0.7f, 0.3f, 0.0f, 0.8f }; 

	m_shadow.pos = {};
	m_shadow.mat.Init();
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.2f };
	m_shadowRect = { m_ImgSizeX, 128, m_ImgSizeX, m_ImgSizeY };
}

void PlayerAB::Update()
{
	m_frame++;

	m_pos.x = m_player->GetPos().x;

	if (m_player->GetMoveVec().y > 0.0f)
	{
		m_pos.y -= 0.5f;
	}
	if (m_player->GetMoveVec().y < 0.0f)
	{
		m_pos.y = m_player->GetPos().y + m_player->GetMoveVec().y - 45.0f;
	}
	if (m_player->GetMoveVec().y == 0.0f)
	{
		//m_pos.y -= 0.8f;
	}

	m_scale *= 0.93f;
	if (m_scale.x <= 0.5f)
	{
		m_flg = st_dead;
	}

	//m_pos.x = m_player->GetPos().x;
	//m_pos.y = m_player->GetPos().y - 45.0f;

	//m_scale.x = 0.5f + fabs( sin(DegToRad(m_frame*8))) * 0.5f;
	//m_scale.y = m_scale.x;

	//m_pos.x = m_player->GetPos().x;

	//m_pos += m_move;
	//if (m_frame > 6)
	//{
	//	m_pos.y = m_player->GetPos().y - 48.0f;

	//	m_frame = 0;
	//}

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();

	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x * 0.35f, m_scale.y * 0.35f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_pos.x + 14.0f, m_pos.y - 12.0f, 0.0f);
	m_shadow.mat.Mix();
}

void PlayerAB::Draw()
{
	D3D.SetBlendState(BlendMode::Add);

	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);

	D3D.SetBlendState(BlendMode::Alpha);

	SHADER.m_spriteShader.SetMatrix(m_shadow.mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_shadowRect, &m_color);
}
