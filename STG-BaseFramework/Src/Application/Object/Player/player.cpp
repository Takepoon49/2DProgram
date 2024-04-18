#include "../../Scene/Scene.h"
#include "player.h"

void C_Player::Init()
{
	// 自機
	m_flg = false;
	m_ownAlphaRect = { 0, 0, 115, 106 };

	m_pos = { 0.0f, -200.0f };
	m_move = { 0.0f, 0.0f };
	m_color = { 0.15f, 0.95f, 0.15f, 1.0f };
	m_scale = { 0.70f, 0.70f };
	m_rad = { m_ownAlphaRect.width * m_scale.x, m_ownAlphaRect.height * m_scale.y };
	m_rad = { m_rad.x / 3.0f, m_rad.y / 2.5f };
	m_Hrad = 15.0f;

	// シーカー
	m_spos = { 0.0f, 0.0f };
	m_sscale = { 0.75f, 0.75f };
	m_sdeg = 0.0f;
	m_sColor = { 0.8f, 0.9f, 0.8f, 1.0f };
	m_seekerFlg = false;

	// ウェブ(A)
	Aflg = 0;
	Aradius = 0;

	// ウェブ(B)
	Bflg = 0;
	Bsize = 0;

	// 弾
	m_bulletTime = 0;

	// デバッグ
	m_DebugColor = C_GREEN;
}

void C_Player::CheckVec()
{
	m_pLockIt = m_pLockList.begin();
	while (m_pLockIt != m_pLockList.end())
	{
		const bool bAlive = (*m_pLockIt)->bActive;
		if (!bAlive)
		{
			delete (*m_pLockIt);
			m_pLockIt = m_pLockList.erase(m_pLockIt);
		}
		else
		{
			m_pLockIt++;
		}
	}

	// 弾
	it = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納

	while (it != m_bulletList.end())
	{
		const bool bAlive = (*it)->GetFlg();
		if (!bAlive)
		{
			delete (*it);
			it = m_bulletList.erase(it);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
		}
		else
		{
			it++;
		}
	}
}

void C_Player::Update()
{
	m_move = { 0.0f, 0.0f };

	// 移動入力
	if (GetKey(VK_UP)) m_move.y = 7.5f;

	if (GetKey(VK_DOWN)) m_move.y = -7.5f;

	if (GetKey(VK_LEFT))
	{
		m_move.x = -7.5f;

		m_ownAlphaRect.x = 115*1;
	}
	else if (GetKey(VK_RIGHT))
	{
		m_move.x = 7.5f;

		m_ownAlphaRect.x = 115*2;
	}
	else
	{
		m_ownAlphaRect.x = 0;
	}

	// 端判定
	if (m_pos.x + m_move.x > scrRight - m_rad.x || m_pos.x + m_move.x < scrLeft + m_rad.x) m_move.x = 0;
	if (m_pos.y + m_move.y > scrTop - m_rad.y || m_pos.y + m_move.y < scrBottom + m_rad.y) m_move.y = 0;

	// 移動量合成
	m_pos += m_move;

	// 通常ショット
	if (GetKey('Z') && m_bulletTime == 0.0f)
	{
		m_bulletTime = 5.0f;

		CreateBullet(m_pos, 0);
	}

	if (GetKey(VK_SHIFT) && m_bulletTime == 0.0f)
	{
		m_bulletTime = 5.0f;

		CreateBullet(m_pos, 1);
	}

	if (m_bulletTime > 0.0f)
	{
		m_bulletTime--;
	}

	//								 size() : 現在の配列要素数
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Update();
	}

	// ウェブ展開
	// 拡散型
	if (GetKey('X'))
	{
		if (Aradius <= 300.0f)
		{
			Aradius += 12.0f;
		}
	}
	else
	{
		if (Aradius > 0.0f)
		{
			Aradius -= 18.0f;
			
		}
		else
		{
			Aradius = 0.0f;
		}
	}
	// 集中型
	if (GetKey('C'))
	{
		if (Bsize <= 500.0f) Bsize += 20.0f;
	}
	else
	{
		if (Bsize > 0.0f) Bsize -= 26.0f;
		else Bsize = 0.0f;
	}

	// シーカー
	UpdateSeeker();

	// 行列作成
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	CheckVec();
}

void C_Player::Draw()
{
	// 自機
	DrawImgEX(m_mat.m, m_pTex, Math::Rectangle(m_ownAlphaRect.x, m_ownAlphaRect.y,
												m_ownAlphaRect.width, m_ownAlphaRect.height), m_color);

	// シーカー
	DrawSeeker();

	// 弾
	for (int b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw();
	}

	ResetMatrix();

	// === 以下デバッグ ==============
	
	// 自機当たり判定
	if (m_pOwner->GetDebugFlg())
	{
		m_DebugColor = C_RED;
		DrawMaru(m_pos.x, m_pos.y, m_rad.x, &m_DebugColor, false);
		DrawMaru(m_pos.x, m_pos.y, m_Hrad, &m_DebugColor, false);
		SHADER.m_spriteShader.DrawBox(m_pos.x, m_pos.y, m_rad.x, m_rad.y, &m_DebugColor, false);
	}

	// ウェブ
	m_DebugColor = { 0.0f, 0.0f, 1.0f, 0.1f };
	
	// シーカー
	
	// 当たり判定
	//DrawMaru(m_pos.x, m_pos.y, Bradius, &m_DebugColor, true);
	m_pOwner->DrawFilledMaru(m_pos.x, m_pos.y, Aradius, m_DebugColor);

	ResetMatrix();
	
	// 集中型ウェブ
	m_DebugColor = C_RED;
	for (int i = 0; i < 5; i++)
	{
		DrawSen(m_pos.x, m_pos.y, m_pos.x + cos(DegToRad( 90.0f + 20.0f - i*10.0f )) * Bsize,
			m_pos.y + sin(DegToRad( 90.0f + 20.0f - i*10.0f )) * Bsize, &m_DebugColor);
	}

	// 拡散型ウェブ
	m_DebugColor = C_BLUE;
	/*if (Aradius > 1)
	{
		DrawMaru(m_pos.x, m_pos.y, Aradius - 1, &m_DebugColor, false);
		DrawMaru(m_pos.x, m_pos.y, Aradius + 1, &m_DebugColor, false);
	}*/
	DrawMaru(m_pos.x, m_pos.y, Aradius, &m_DebugColor, false);
}

void C_Player::UpdateSeeker()
{
	m_spos.x = m_pos.x;
	m_spos.y = m_pos.y + 300.0f;

	m_seekerMat.s = Math::Matrix::CreateScale(m_sscale.x, m_sscale.y, 0.0f);
	m_seekerMat.r = Math::Matrix::CreateRotationZ(DegToRad(m_sdeg));
	m_seekerMat.t = Math::Matrix::CreateTranslation(m_spos.x, m_spos.y, 0.0f);
	m_seekerMat.m = m_seekerMat.s * m_seekerMat.r * m_seekerMat.t;
}

void C_Player::DrawSeeker()
{
	DrawImgEX(m_seekerMat.m, m_pTex, Math::Rectangle(m_SImgPosX, m_SImgPosY, m_SImgSizeX, m_SImgSizeY), m_sColor);
}

void C_Player::CreateBullet(Math::Vector2 a_pos, bool a_num)
{
	if (a_num == 0)
	{
		C_Bullet0* tempBullet = new C_Bullet0();
		tempBullet->Init();
		tempBullet->SetTexture(m_pBullet0Tex);
		tempBullet->Shot(a_pos);
		m_bulletList.push_back(tempBullet);
	}
	else if (a_num == 1)
	{
		for (int i = -1; i < 3; i +=2)
		{
			C_Bullet0* tempBullet = new C_Bullet0();
			tempBullet->Init();
			tempBullet->SetTexture(m_pBullet0Tex);
			tempBullet->Shot({ a_pos.x + (i * 15.0f) , a_pos.y });
			m_bulletList.push_back(tempBullet);
		}
	}
}

HitStruct C_Player::GetObj()
{
	HitStruct objTemp;

	objTemp.pos = m_pos;
	objTemp.rad = m_rad;
	objTemp.flg = m_flg;

	return objTemp;
}

HitStruct C_Player::GetSeekObj()
{
	HitStruct tempObj;
	tempObj.pos = m_spos;
	tempObj.rad = { m_SImgSizeX * m_sscale.x, m_SImgSizeY * m_sscale.y };
	tempObj.flg = m_seekerFlg;

	return tempObj;
}

bool C_Player::GetKeyFlg(int num)
{
	return m_pOwner->GetKeyFlg(num);
}

void C_Player::SetKeyFlg(int num, bool tf)
{
	m_pOwner->SetKeyFlg(num, tf);
}
