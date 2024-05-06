#include "UI.h"
#include "../../Scene/Scene.h"

void UI::Init()
{
	// ゲームオーバー
	m_GO.rect = { 0, 0, 526, 57 };
	m_GO.pos = { 0.0f, 0.0f };
	m_GO.mat.s = Math::Matrix::CreateScale(1.0f);
	m_GO.mat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_GO.mat.t = Math::Matrix::CreateTranslation(m_GO.pos.x, m_GO.pos.y, 0.0f);
	m_GO.mat.Mix();
	m_GO.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 残機
	m_playerNumPos = { 560.0f - scrGap, 330.0f - scrGap };
	// 1100 37
	m_playerPos = { scrLeft + 1155.0f, scrTop - 40.0f };

	// 緊急回避ゲージ
	m_moveVal = 50.0f;
	m_moveValMax = 100.0f;
	m_moveGagePos = { m_playerNumPos.x + 2.0f, m_playerNumPos.y - 60.0f };
	m_moveFrameMat.Init();
	m_moveGageMat.Init();
	m_moveFrameColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_moveGageColor = { 1.0f, 1.0f, 0.0f, 0.9f };
}

void UI::Update()
{
	// 自機用
	m_playerMat.s = Math::Matrix::CreateScale(0.5f, 0.5f, 0.0f);
	m_playerMat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_playerMat.t = Math::Matrix::CreateTranslation(m_playerPos.x, m_playerPos.y, 0.0f);
	m_playerMat.Mix();

	// ゲージの枠
	m_moveFrameMat.s = Math::Matrix::CreateScale(1.4f, 0.7f, 0.0f);
	m_moveFrameMat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_moveFrameMat.t = Math::Matrix::CreateTranslation(m_moveGagePos.x, m_moveGagePos.y, 0.0f);
	m_moveFrameMat.Mix();
	// ゲージそのもの
	//m_moveGageColor = m_pOwner->GetPlayerDColor();
	//m_moveVal = m_pOwner->GetPlayerRollVal();
	//m_moveValMax = m_pOwner->GetPlayerRollValMax();

	m_moveGageMat.s = m_moveFrameMat.s;
	m_moveGageMat.r = m_moveFrameMat.r;
	m_moveGageMat.t = Math::Matrix::CreateTranslation(m_moveGagePos.x - ((m_moveVal/m_moveValMax) * (100.0f*1.4f))/2.0f, m_moveGagePos.y, 0.0f);
	m_moveGageMat.Mix();
}

void UI::Draw()
{
	// ゲームオーバー
	if (SCENE.m_gameOverFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_GO.mat.m);
		SHADER.m_spriteShader.DrawTex(&m_pGameOverTex, 0, 0, &m_GO.rect, &m_GO.color);
	}

	// 残機の自機表示
	SHADER.m_spriteShader.SetMatrix(m_playerMat.m);
	SHADER.m_spriteShader.DrawTex(&m_playerTex, Math::Rectangle(0, m_pOwner->GetPlayerNowAnim().y * 128.0f, 128, 128), 1.0f);

	// ゲージ
	//SHADER.m_spriteShader.SetMatrix(m_moveGageMat.m);
	//SHADER.m_spriteShader.DrawTex(m_pTex0, 0, 0, &Math::Rectangle(170, 30, 
	//((m_moveValMax - m_moveVal) / m_moveValMax) * 100, 30), &m_moveGageColor);

	// ゲージの枠
	//SHADER.m_spriteShader.SetMatrix(m_moveFrameMat.m);
	//SHADER.m_spriteShader.DrawTex(m_pTex0, 0, 0, &Math::Rectangle(170, 0, 100, 30), &m_moveFrameColor);
}

void UI::DrawStr()
{
	sprintf_s(text, sizeof(text), "x %d\n", m_pOwner->GetPlayerLife());
	SHADER.m_spriteShader.DrawString(m_playerNumPos.x, m_playerNumPos.y, text, Math::Color(0.0f, 0.0f, 0.0f, 1.0f));
	SHADER.m_spriteShader.DrawString(m_playerNumPos.x + 3, m_playerNumPos.y - 3, text, Math::Color(1.0f, 1.0f, 1.0f, 1.0f));
}