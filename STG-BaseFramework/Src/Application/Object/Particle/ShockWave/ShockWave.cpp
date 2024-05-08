#include "ShockWave.h"
#include "../../../Scene/Scene.h"

ShockWave::ShockWave()
{

}

void ShockWave::Init(Math::Vector2 _pos)
{
	m_type = ParticleType::ShockWave;

	m_rect = { 64, 64, 64, 64 };

	m_life = 0;

	m_frame = 0;
	m_flg = st_alive;
	m_pos = _pos;
	m_move = {};
	m_moveVec = {};
	m_scale = { 0.1f, 0.1f };
	m_rad = {};
	m_deg = 0.0f;
	m_mat.Init();
	m_color = { 1.0f, 1.0f, 1.0f, 0.4f };

	m_nowAnim = {};

	// ‰e
	m_shadow.pos = {};
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.4f };
	m_shadow.mat.Init();

	//struct st_smoke
	//{
	//	Math::Vector2	pos;
	//	Math::Vector2	move;
	//	MathSet			mat;
	//	float			alpha;
	//}m_smoke[50];
	m_mat2.Init();

	m_rect2 = { 0, 64, 64, 64 };
	//for (int i = 0; i < m_smokeMax; i++)
	//{
	//	m_smoke[i].pos.x = m_pos.x + Rnd() * 5.0f - 2.5f;
	//	m_smoke[i].pos.y = m_pos.y + Rnd() * 5.0f - 2.5f;

	//	m_smoke[i].move.x = Rnd() * 4 - 2;
	//	m_smoke[i].move.y = Rnd() * 4 - 2;

	//	m_smoke[i].mat.Init();

	//	m_smoke[i].scale = Rnd() * 1.0f + 0.5f;

	//	m_smoke[i].alpha = 1.0f;
	//}
}

void ShockWave::Update()
{
	m_frame++;

	//if (m_frame < 24)
	//{
	//	m_scale = { 0.1f, 0.1f };
	//}

	if (m_frame < 30*2)
	{
		if (m_scale.x < 9.0f)
		{
			m_scale *= 1.3f;
		}
	}
	else if (m_frame > 45*2)
	{
		m_scale *= 0.997f;
		m_color.w *= 0.97f;
	}

	if (m_color.w <= 0.01f)
	{
		m_flg = st_dead;
	}

	//for (int i = 0; i < m_smokeMax; i++)
	//{
	//	if (m_frame > 60)
	//	{
	//		m_smoke[i].alpha -= 0.01f;
	//		m_smoke[i].scale *= 0.98f;
	//	}

	//	m_smoke[i].pos += m_smoke[i].move;

	//	m_smoke[i].mat.s = Math::Matrix::CreateScale(m_smoke[i].scale);
	//	m_smoke[i].mat.r = Math::Matrix::CreateRotationZ(0.0f);
	//	m_smoke[i].mat.t = Math::Matrix::CreateTranslation(m_smoke[i].pos.x, m_smoke[i].pos.y, 0.0f);
	//	m_smoke[i].mat.Mix();
	//}

	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.Mix();

	m_mat2.s = Math::Matrix::CreateScale(m_scale.x * 0.75f, m_scale.y * 0.75f, 0.0f);
	m_mat2.r = Math::Matrix::CreateRotationZ(0.0f);
	m_mat2.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat2.Mix();

	// ‰e
	m_shadow.pos.x = m_pos.x + 24.0f;
	m_shadow.pos.y = m_pos.y - 18.0f;
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x * 0.8f, m_scale.y * 0.8f, 0.0f);
	m_shadow.mat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_shadow.pos.x, m_shadow.pos.y, 0.0f);
	m_shadow.mat.Mix();
}

void ShockWave::Draw()
{
	D3D.SetBlendState(BlendMode::Add);

	// ŽU‚é‰Œ‚è
	/*for (int i = 0; i < m_smokeMax; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_smoke[i].mat.m);
		SHADER.m_spriteShader.DrawTex(&m_tex, m_rect2, m_smoke[i].alpha);
	}*/

	// ‰e
	SHADER.m_spriteShader.SetMatrix(m_shadow.mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_shadow.color);

	// ÕŒ‚”g
	SHADER.m_spriteShader.SetMatrix(m_mat2.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);

	// ÕŒ‚”g
	SHADER.m_spriteShader.SetMatrix(m_mat.m);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &m_rect, &m_color);

	D3D.SetBlendState(BlendMode::Alpha);
}
