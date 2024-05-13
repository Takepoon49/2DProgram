#include "../../Scene/Scene.h"
#include "player.h"

Player::Player()
{
	m_objType = ObjType::Player;

	m_pOwner = nullptr;
	m_pBullet0Tex = nullptr;

	// 自機
	m_rect = {};
	m_ownAlphaRect = { 0, 0, 128, 128 };
	m_nowAnim = { 0.0f, 0.0f };

	m_flg = false;
	m_pos = { 0.0f, -250.0f };
	m_move = { 0.0f, 0.0f };
	m_speed = { 7.5f, 7.5f };
	m_scale = { 0.80f, 0.80f };

	m_rad = { m_ownAlphaRect.width * m_scale.x, m_ownAlphaRect.height * m_scale.y };
	m_rad = { m_rad.x / 3.0f, m_rad.y / 2.5f };
	m_Hrad = 15.0f;
	m_deg = 0.0f;
	//m_color = { 0.15f, 0.95f, 0.15f, 1.0f };
	//m_color = { 0.70f, 0.70f, 0.70f, 1.0f };
	//m_color	= { 0.1f, 0.80f, 0.80f, 1.0f };
	m_color	= { 1.0f, 1.0f, 1.0f, 1.0f };

	// 影
	m_shadow.pos = {};
	m_shadow.color = { 0.0f, 0.0f, 0.0f, 0.6f };
	m_shadow.mat.Init();

	// ローリング
	m_roll.flg = 0;
	m_roll.dir = Dir::Left;
	m_roll.frame1 = 0.0f;
	m_roll.frame2 = 0.0f;
	m_roll.frameMax = 50.0f;
	m_roll.move = 0.0f;
	m_roll.cnt = 0;

	// シーカー
	m_spos = { 0.0f, 0.0f };
	m_sscale = { 0.75f, 0.75f };
	m_sdeg = 0.0f;
	m_sColor = { 0.8f, 0.9f, 0.8f, 1.0f };
	m_seekerFlg = false;

	// ウェブ(A)
	m_webA.flg = false;
	m_webA.pos = {};
	m_webA.size = 0.0f;
	m_webA.sizeXAdd = 0.0f;
	m_webA.degAdd = 0.0f;
	m_webA.degMove = 0.0f;
	m_webA.frame = 0;

	// ウェブ(B)
	m_webB.flg = false;
	m_webB.pos = {};
	m_webB.size = 0.0f;
	m_webB.sizeXAdd = 0.0f;
	m_webB.degAdd = 0.0f;
	m_webB.degMove = 0.0f;
	m_webB.frame = 0;

	// 弾
	m_shootTime = 0;
	m_shootFlg = 0;

	// デバッグ
	m_DebugColor = C_GREEN;

	// フレーム
	m_frame = 0.0f;

	// チャージ
	m_charge.flg = 0;
	m_charge.frame = 0.0f;
}

void Player::Init(Math::Vector2 _anim)
{
	m_nowAnim = _anim;
}

void Player::CheckVec()
{
	// 弾
	std::vector<C_Bullet0*>::iterator _it;
	_it = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納
	while (_it != m_bulletList.end())
	{
		const int bAlive = (*_it)->GetFlg();
		if (bAlive == 0)
		{
			delete (*_it);
			_it = m_bulletList.erase(_it);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
		}
		else
		{
			_it++;
		}
	}
}

void Player::Update()
{
	m_frame += 1.0f;

	// 当たり判定
	if (m_hitFrame > 0)
	{
		m_hitFrame--;
		//m_color.w = 0.3f;
		m_color.w = fabs(sin(DegToRad(m_frame*12.0f)));

		if (m_hitFrame > 110.0f - 24.0f)
		{
			m_pos.x = 0.0f;
			m_pos.y += 6.0f;
		}
	}
	else
	{
		m_color.w = 1.0f;
		m_hitFlg = true;
	}

	//m_DebugColor = { 1.0f, 0.5f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 7)))) * 0.5f, 0.0f, 0.8f };
	//m_DebugColor = { 1.0f, 0.5f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 7)))) * 0.5f, 0.0f, 0.8f };
	//m_DebugColor = { 0.5f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 6)))) * 0.5f, 0.0f, 1.0f, 0.8f };
	//m_DebugColor = { 0.5f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 6)))) * 0.5f, 0.0f, 0.0f, 1.0f };
	//m_DebugColor = { 0.0f, 1.0f, 0.5f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 7)))) * 0.5f, 1.0f };
	float _rValue = fabs(sin(DirectX::XMConvertToRadians(m_frame * 2 +  0)));
	float _gValue = fabs(sin(DirectX::XMConvertToRadians(m_frame * 2 + 90)));
	m_DebugColor = { _rValue, _gValue, 1.0f, 1.0f };
	//m_DebugColor = { 1.0f, 0.0f, 0.6f + (fabs(sin(DirectX::XMConvertToRadians(m_frame * 15)))) * 0.4f, 0.6f };
	//m_DebugColor = { sin(DegToRad(m_frame * 6)), sin(DegToRad(180 + m_frame * 6)), 1.0f, 0.8f};
	//m_DebugColor = { sin(DegToRad(m_frame * 5)), sin(DegToRad(180 + m_frame * 5)), 1.0f, 1.0f};
	//m_DebugColor = { 0.0f, 1.0f, 1.0f, 1.0f };

	switch (m_pOwner->GetNowScene())
	{
	case SceneType::Title:
		m_pos.x = 0.0f;
		m_pos.y = scrTop - 580.0f;

		// スキン左
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (!SCENE.keyFlg[k_left])
			{
				if (m_nowAnim.y > 0.0f)
				{
					m_nowAnim.y -= 1.0f;
				}
			}
			SCENE.keyFlg[k_left] = true;
		}
		else
		{
			SCENE.keyFlg[k_left] = false;
		}
		// スキン右
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (!SCENE.keyFlg[k_right])
			{
				if (m_nowAnim.y < 6.0f)
				m_nowAnim.y += 1.0f;
			}
			SCENE.keyFlg[k_right] = true;
		}
		else
		{
			SCENE.keyFlg[k_right] = false;
		}
		break;

	case SceneType::Game1:
		UpdateAttack();

		// 移動入力
		m_moveSpd = 7.5f;
		m_moveVec = { 0.0f, 0.0f };

		UpdateMove();

		if (GetKey(VK_LEFT))
		{
			m_nowAnim.x = 8.0f;			// 傾き:左
		}
		else if (GetKey(VK_RIGHT))
		{
			m_nowAnim.x = 1.0f;			// 傾き:右
		}
		else
		{
			m_nowAnim.x = 0;			// 傾き：なし
		}
		break;
		
	case SceneType::Result:
		m_pos = { scrLeft + 150.0f, 0.0f };
		m_color.w = 1.0f;
		break;
	}

	// スキンごとに拡大率変更
	if (m_nowAnim.y < 3.0f)
	{
		m_scale = { 0.85f, 0.85f };
	}
	else
	{
		m_scale = { 0.80f, 0.80f };
	}

	m_moveVec *= m_moveSpd;

	if (GetKey(VK_LEFT))
	{
		if (m_webB.size >= 100)
		{
			if (m_webB.degAdd < 35.0f) m_webB.degAdd += 1.5f;
		}

		//m_move.x = -m_speed.x;			// 移動量：左
	}
	else if (GetKey(VK_RIGHT))
	{
		if (m_webB.size >= 100)
		{
			if (m_webB.degAdd > -35.0f) m_webB.degAdd -= 1.5f;
		}

		//m_move.x = +m_speed.x;			// 移動量：右
	}
	//else if (GetKey('G'))
	//{
		//if ((int)m_frame % 2 == 0)
		//{
		//	m_nowAnim.x += 2.0f;
		//	if (m_nowAnim.x > 8.0f) m_nowAnim.x = 0.0f;
		//}
	//}
	else
	{
		//m_nowAnim.x = 0;			// 傾き：なし
		//m_ownAlphaRect.x = 0;
	}

	// 端判定
	if (m_pos.x + m_moveVec.x > scrRight - m_rad.x || m_pos.x + m_moveVec.x < scrLeft + m_rad.x) m_moveVec.x = 0;
	if (m_pos.y + m_moveVec.y > scrTop - m_rad.y || m_pos.y + m_moveVec.y < scrBottom + m_rad.y) m_moveVec.y = 0;
	
	// 移動量合成
	m_pos += m_moveVec;

	// ウェブ更新
	// A
	m_webA.frame += 6;
	if (m_webA.frame >= 360) m_webA.frame = 0;
	m_webA.degMove = m_webA.frame;
	if (m_webA.degMove >= 360.0f) m_webA.degMove -= 360.0f;
	m_webA.pos = m_pos;

	// B
	m_webB.frame += 3;
	if (m_webB.frame >= 360) m_webB.frame = 0;
	m_webB.degMove = m_webB.frame;
	if (m_webB.degMove >= 360.0f) m_webB.degMove -= 360.0f;
	m_webB.pos = { m_pos.x + cos(DegToRad(90.0f + m_webB.degAdd))* m_webB.size * 2.25f,
					m_pos.y + sin(DegToRad(90.0f + m_webB.degAdd)) * m_webB.size* 2.25f };

	//								 size() : 現在の配列要素数
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Update();
	}

	// シーカー
	//UpdateSeeker();

	// 行列作成
	m_mat.s = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0.0f);
	m_mat.r = Math::Matrix::CreateRotationZ(DegToRad(m_deg));
	m_mat.t = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_mat.m = m_mat.s * m_mat.r * m_mat.t;

	// 影
	m_shadow.pos.x = m_pos.x + 14.0f;
	m_shadow.pos.y = m_pos.y - 28.0f;
	m_shadow.mat.s = Math::Matrix::CreateScale(m_scale.x * 0.7f, m_scale.y * 0.7f, 0.0f);
	m_shadow.mat.r = m_mat.r;
	m_shadow.mat.t = Math::Matrix::CreateTranslation(m_shadow.pos.x, m_shadow.pos.y, 0.0f);
	m_shadow.mat.Mix();

	CheckVec();
}

void Player::Draw()
{
	// 集中型の当たり判定表示(仮)
	//SHADER.m_spriteShader.DrawBox(m_pos.x, m_pos.y + m_webB.size, m_webB.size + m_webB.sizeXAdd, m_webB.size, &Math::Color(1.0f, 0.0f, 0.0f, 0.3f), true);

	// 自機影
	DrawImgEX(m_shadow.mat.m, &m_tex, Math::Rectangle(
		m_ownAlphaRect.width * m_nowAnim.x, m_ownAlphaRect.height * m_nowAnim.y,
		m_ownAlphaRect.width, m_ownAlphaRect.height), m_shadow.color);

	if (m_hitFlg) m_pOwner->DrawPlayerAB();

	// 自機
	DrawImgEX(m_mat.m, &m_tex, Math::Rectangle(
		m_ownAlphaRect.width * m_nowAnim.x, m_ownAlphaRect.height * m_nowAnim.y,
		m_ownAlphaRect.width,				m_ownAlphaRect.height					), m_color);

	//行列の初期化 (図形描画の前に書く)
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());

	if (m_pOwner->GetNowScene() == SceneType::Game1)
	{
		// ローリングクールタイム
		DrawBar(m_pos.x - m_rad.x, m_pos.y - 24.0f, 64.0f, 10.0f, m_roll.frame1, 45.0f, &Math::Color(0.0f, 1.0f, 0.0f, 0.9f), true, Dir::Right);
	}

	// 拡散型
	if (m_webA.size >= 3.0f) DrawWebA();

	// 集中型
	if (m_webB.size >= 3.0f) DrawWebB();

	// シーカー
	//DrawSeeker();

	// 弾
	for (UINT b = 0; b < m_bulletList.size(); b++)
	{
		m_bulletList[b]->Draw();
	}

	// === 以下デバッグ ==============
	
	// 自機当たり判定
	if (m_pOwner->GetDebugFlg())
	{

	}
}

void Player::UpdateMove()
{
	switch (m_roll.flg)
	{
	case 0:	// 通常移動、Xで方向キー待機
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_moveVec.y = 0.8f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_moveVec.y = -0.8f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_moveVec.x = -1.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_moveVec.x = 1.0f;
		}

		if (m_roll.frame1 > 0.0f)
		{
			m_roll.frame1 -= 1.0f;
		}

		// 移動入力がされてなければ
		if (m_moveVec == Math::Vector2::Zero)
		{
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
			{
				if (m_roll.frame1 <= 0.0f)
				{
					m_roll.flg = 1;
				}
			}
		}
		break;

	case 1:
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			m_roll.flg = 1;
		}
		else
		{
			m_roll.flg = 0;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_roll.dir = Dir::Left;
			m_roll.flg = 2;
			m_roll.frame1 = 0.0f;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_roll.dir = Dir::Right;
			m_roll.flg = 2;
			m_roll.frame1 = 0.0f;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_moveVec.y = 1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_moveVec.y = -1.0f;
		}
		break;

	case 2:
		if (m_roll.frame1 <= 7.0f)
		{
			m_roll.frame1 += 1.0f;

			m_pOwner->CreatePShadow(m_pos);

			switch (m_roll.dir)
			{
			case Dir::Up:
				break;
			case Dir::Down:
				break;
			case Dir::Left:
				m_moveVec = { -2.0f, 0.0f };
				break;			
			case Dir::Right:
				m_moveVec = { +2.0f, 0.0f };
				break;
			}
		}
		else
		{
			m_roll.flg = 0;
			m_roll.frame1 = m_roll.frameMax;
		}
		break;
	}
}

void Player::UpdateMove1()
{
	switch (m_roll.flg)
	{
	case 0:
	case 1:
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_moveVec.y = 1.0f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_moveVec.y = -1.0f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_moveVec.x = -1.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_moveVec.x = 1.0f;
		}
		break;

	case 2:
		m_moveVec = { 2.0f, 0.0f };

		m_roll.frame1 += 1.0f;
		if (m_roll.frame1 > 10.0f)
		{
			m_roll.frame1 = 0.0f;
			m_roll.flg = 0;
		}

		break;
	}

	switch (m_roll.flg)
	{
	case 1:
		if (m_roll.frame2 <= 13.0f)
		{
			m_roll.frame2 += 1.0f;
		}
		else
		{
			m_roll.frame2 = 0.0f;
			m_roll.flg = 0;
		}
		break;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (!m_pOwner->keyFlg[k_right])
		{
			if (m_roll.flg == 0)
			{
				m_roll.flg = 1;
			}
			else if (m_roll.flg == 1)
			{
				m_roll.flg = 2;
			}
		}
		m_pOwner->keyFlg[k_right] = true;
	}
	else
	{
		m_pOwner->keyFlg[k_right] = false;
	}
}

void Player::DrawWebA()
{
	float a = 0.0f, b = 0.0f, deg = 0.0f;
	float aNext = 0.0f, bNext = 0.0f, degNext = 0.0f;

	float a2[2] = {};
	float b2[2] = {};

	float gapDeg = 360.0f / 8.0f;

	for (deg = 0; deg < 360; deg += gapDeg)
	{
		a = cos(DegToRad(deg + m_webA.degMove)) * (m_webA.size);
		b = sin(DegToRad(deg + m_webA.degMove)) * (m_webA.size / 4.0f);

		degNext = deg + gapDeg;
		aNext = cos(DegToRad(degNext + m_webA.degMove)) * (m_webA.size);
		bNext = sin(DegToRad(degNext + m_webA.degMove)) * (m_webA.size / 4.0f);

		SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a, m_webA.pos.y + b,
			m_webA.pos.x + aNext, m_webA.pos.y + bNext, &m_DebugColor);

		if (deg < 180*2)
		{
			SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a, m_webA.pos.y + b,
				m_webA.pos.x + a, m_webA.pos.y + b + 30, &m_DebugColor);
		}

		if (deg == 0.0f)
		{
			a2[0] = a;
			b2[0] = b;
		}
		if (deg == 180.0f)
		{
			a2[1] = a;
			b2[1] = b;
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		SHADER.m_spriteShader.DrawCircle((int)(m_webA.pos.x + a2[i]), m_webA.pos.y + b2[i], 10, &m_DebugColor, false);
	}

	//SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a2[0], m_webA.pos.y + b2[0],
	//								m_webA.pos.x + a2[1], m_webA.pos.y + b2[1], &m_DebugColor);	

	float size2 = (a2[0]);

	gapDeg = 360.0f / 16.0f;
	for (deg = 0; deg < 180; deg += gapDeg)
	{
		//a = cos(DegToRad(deg + m_webA.degMove)) * fabs(a2[0] - m_webA.pos.x);
		//b = sin(DegToRad(deg + m_webA.degMove)) * fabs(a2[0] - m_webA.pos.x);

		a = cos(DegToRad(deg)) * size2;
		b = sin(DegToRad(deg)) * m_webA.size;

		degNext = deg + gapDeg;
		aNext = cos(DegToRad(degNext)) * size2;
		bNext = sin(DegToRad(degNext)) * m_webA.size;

		SHADER.m_spriteShader.DrawLine(m_webA.pos.x + a, m_webA.pos.y + b,
			m_webA.pos.x + aNext, m_webA.pos.y + bNext, &m_DebugColor);
	}
}

void Player::DrawWebB()
{
	float a = 0.0f , b = 0.0f, deg = 0.0f;
	float aNext = 0.0f, bNext = 0.0f, degNext = 0.0f;
	float gapDeg = 360.0f / 8.0f;	// ←８角形

	for (deg = 0; deg < 360; deg += gapDeg)	// ←８回ループ
	{
		// 現在の頂点
		a = cos(DegToRad(deg + m_webB.degMove)) * (m_webB.size + m_webB.sizeXAdd*2.0f);
		b = sin(DegToRad(deg + m_webB.degMove)) * (m_webB.size/2.0f);

		degNext = deg + gapDeg;	// 次の頂点を計算
		aNext = cos(DegToRad(degNext + m_webB.degMove)) * (m_webB.size + m_webB.sizeXAdd*2.0f);
		bNext = sin(DegToRad(degNext + m_webB.degMove)) * (m_webB.size/2.0f);

		SHADER.m_spriteShader.DrawLine(m_webB.pos.x + a, m_webB.pos.y + b, 
										m_webB.pos.x + aNext, m_webB.pos.y + bNext, &m_DebugColor);

		//if ((int)deg % 45 == 0)
		{
			SHADER.m_spriteShader.DrawLine(m_pos.x, m_pos.y, m_webB.pos.x + a, m_webB.pos.y + b, &m_DebugColor);
		}
	}

	if (m_pOwner->GetDebugFlg())
	{
		SHADER.m_spriteShader.DrawLine(m_pos.x, m_pos.y,
			m_pos.x + cos(DegToRad(m_webB.degAdd + 90.0f - 24.0f)) * m_webB.size * 2.75f,
			m_pos.y + sin(DegToRad(m_webB.degAdd + 90.0f - 24.0f)) * m_webB.size * 2.75f,
			&Math::Color(0.0f, 1.0f, 0.0f, 1.0f));

		SHADER.m_spriteShader.DrawLine(m_pos.x, m_pos.y,
			m_pos.x + cos(DegToRad(m_webB.degAdd + 90.0f)) * m_webB.size * 2.75f,
			m_pos.y + sin(DegToRad(m_webB.degAdd + 90.0f)) * m_webB.size * 2.75f,
			&Math::Color(0.0f, 1.0f, 0.0f, 1.0f));

		SHADER.m_spriteShader.DrawLine(m_pos.x, m_pos.y,
			m_pos.x + cos(DegToRad(m_webB.degAdd + 90.0f + 24.0f)) * m_webB.size * 2.75f,
			m_pos.y + sin(DegToRad(m_webB.degAdd + 90.0f + 24.0f)) * m_webB.size * 2.75f,
			&Math::Color(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

void Player::UpdateSeeker()
{
	m_spos.x = m_pos.x;
	m_spos.y = m_pos.y + 300.0f;

	m_seekerMat.s = Math::Matrix::CreateScale(m_sscale.x, m_sscale.y, 0.0f);
	m_seekerMat.r = Math::Matrix::CreateRotationZ(DegToRad(m_sdeg));
	m_seekerMat.t = Math::Matrix::CreateTranslation(m_spos.x, m_spos.y, 0.0f);
	m_seekerMat.m = m_seekerMat.s * m_seekerMat.r * m_seekerMat.t;
}

void Player::DrawSeeker()
{
	DrawImgEX(m_seekerMat.m, &m_tex, Math::Rectangle(m_SImgPosX, m_SImgPosY, m_SImgSizeX, m_SImgSizeY), m_sColor);
}

void Player::UpdateAttack()
{
	// 通常ショット
	if (GetKey('Z'))
	{
		if (m_shootFlg == 0 && m_webB.size <= 3.0f)
		{
			m_shootFlg = 2;
		}

		//if (!keyFlg[k_z] && m_pOwner->GetLockOnNum() > 0)
		if (!m_pOwner->keyFlg[k_z])
		{
			CreateHLaser();
			m_webB.size = 0.0f;
			m_webB.sizeXAdd = 0.0f;
			m_webB.degAdd = 0.0f;
		}
		m_pOwner->keyFlg[k_z] = true;
	}
	else
	{
		m_pOwner->keyFlg[k_z] = false;
	}

	// 集中型
	if (GetKey('X'))
	{
		if (!m_pOwner->keyFlg[k_z])
		{

			if (m_webB.size <= 250.0f) m_webB.size += 4.0f;
			//if (m_webB.size <= 150.0f) m_webB.size += 5.0f;

			if (m_webB.size >= 250.0f)
				//if (m_webB.size >= 150.0f)
			{
				//if (m_webB.sizeXAdd <= 135.0f)
				//{
				//	m_webB.sizeXAdd += 3.0f;
				//}
			}

		}
	}
	else
	{
		if (m_webB.size > 0.0f)
		{
			m_webB.size -= 18.0f;
			m_webB.sizeXAdd = 0.0f;
		}
		else
		{
			m_webB.size = 0.0f;
			m_webB.sizeXAdd = 0.0f;
			m_webB.degAdd = 0;
		}
	}

	if (m_webB.size <= 0.0f)
	{
		m_webB.flg = false;
	}
	else
	{
		m_webB.flg = true;
	}

	if (m_pOwner->GetPlayerWIPFlg())
	{
		// ボム ※作業中
		if (GetAsyncKeyState('C') & 0x8000)
		{
			if (!SCENE.keyFlg[k_c])
			{
				if (SCENE.m_bombNum > 0)
				{
					SCENE.m_bombNum--;
					SCENE.ShotBomb(m_pos, 0);
					SCENE.ShotBomb(m_pos, 1);
				}
			}
			SCENE.keyFlg[k_c] = true;
		}
		else
		{
			SCENE.keyFlg[k_c] = false;
		}

		// ３連ショット ※作業中
		if (GetKey('A')) {
			if (m_shootFlg == 0) {
				m_shootFlg = 3;
			}
		}

		// ウェブ展開
		// 拡散型
		if (GetKey('S'))
		{
			if (m_webA.size <= 300.0f)
			{
				m_webA.size += 12.0f;
			}
		}
		else
		{
			if (m_webA.size > 0.0f)
			{
				m_webA.size -= 18.0f;

			}
			else
			{
				m_webA.size = 0.0f;
			}
		}
	}

	// 弾作成
	switch (m_shootFlg)
	{
	case 1:	// １列
		if (m_shootTime % 3 == 0 && m_shootTime < 3*3)
		{
			CreateBullet(m_pos.x, m_pos.y);
		}
		m_shootTime++;
		if (m_shootTime >= 3*6)
		{
			m_shootFlg = 0;
			m_shootTime = 0;
		}
		break;
	case 2:	// ２列
		if (m_shootTime % 3 == 0 && m_shootTime < 3 * 4)
		{
			CreateBullet(m_pos.x - 12.0f, m_pos.y);
			CreateBullet(m_pos.x + 12.0f, m_pos.y);
		}
		m_shootTime++;
		if (m_shootTime >= 3 * 6)
		{
			m_shootFlg = 0;
			m_shootTime = 0;
		}
		break;
	case 3:	// ２列
		if (m_shootTime % 3 == 0 && m_shootTime < 3 * 3)
		{
			CreateBullet(m_pos.x +  0.0f, m_pos.y + 6.0f);
			CreateBullet(m_pos.x - 14.0f, m_pos.y);
			CreateBullet(m_pos.x + 14.0f, m_pos.y);
		}
		m_shootTime++;
		if (m_shootTime >= 3 * 6)
		{
			m_shootFlg = 0;
			m_shootTime = 0;
		}
		break;
	}
}

void Player::CreateHLaser()
{
	// ホーミング弾
	//if (GetAsyncKeyState('X') & 0x8000)
	{
		for (int i = 0; i < m_pOwner->GetTargetNum(); i++)
		{
			float addDeg = 0;

			//switch ((i + 1) % 3)
			//{
			//case 0:
			//	addDeg = -30.0f;
			//	break;
			//case 1:
			//	addDeg = 0.0f;
			//	break;
			//case 2:
			//	addDeg = +30.0f;
			//	break;
			//default:
			//	addDeg = 90.0f;
			//	break;
			//}
			//m_pOwner->CreateHLaser({ m_pos.x, m_pos.y - 10.0f }, 270.0f + addDeg);

			switch ((i + 1) % 2)
			{
			case 0:
				addDeg = 180.0f + (rand() % 5) * 10;
				break;
			default:
				addDeg = 0.0f - (rand() % 5) * 10;
				break;
			}
			m_pOwner->CreateHLaser({ m_pos.x, m_pos.y - 10.0f }, 0.0f + addDeg);
		}
	}
	m_pOwner->SetAllLock(0);
}

void Player::AddNowAnim(int _addX, int _addY)
{
	m_nowAnim.x += (int)_addX;
	m_nowAnim.y += (int)_addY;

	if (m_nowAnim.x < 0.0f) m_nowAnim.x = 0.0f;
	if (m_nowAnim.y < 0.0f) m_nowAnim.y = 0.0f;
}

void Player::CreateBullet(Math::Vector2 a_pos)
{
	C_Bullet0* tempBullet = new C_Bullet0();
	tempBullet->Init();
	tempBullet->SetTexture("Data/Texture/Bullet/bullet-100x100.png");
	tempBullet->Shot(a_pos);
	m_bulletList.push_back(tempBullet);
}

void Player::CreateBullet(float _x, float _y)
{
	C_Bullet0* tempBullet = new C_Bullet0();
	tempBullet->Init();
	tempBullet->SetTexture("Data/Texture/Bullet/bullet-100x100.png");
	tempBullet->Shot({_x, _y});
	m_bulletList.push_back(tempBullet);
}

HitStruct Player::GetObj()
{
	HitStruct objTemp;

	objTemp.pos = m_pos;
	objTemp.rad = m_rad;
	objTemp.flg = m_flg;

	return objTemp;
}

HitStruct Player::GetSeekObj()
{
	HitStruct tempObj;
	tempObj.pos = m_spos;
	tempObj.rad = { m_SImgSizeX * m_sscale.x, m_SImgSizeY * m_sscale.y };
	tempObj.flg = m_seekerFlg;

	return tempObj;
}

HitStruct Player::GetWebBObj()
{
	HitStruct obj;
	obj.pos = { m_pos.x, m_pos.y + m_webB.size };
	obj.rad = { m_webB.size + m_webB.sizeXAdd, m_webB.size };
	obj.flg = m_webB.flg;

	return HitStruct(obj);
}

void Player::OnHit()
{
	m_hitFrame = 110.0f;
	m_hitFlg = false;
	m_pOwner->CreateExplosionA(ParticleType::ExplosionA, m_pos);

	m_pos = { 0.0f, scrBottom - 64.0f };
}
