#include "../main.h"
#include "Scene.h"

#include "../Object/Enemy/enemyA/enemyA.h"

#include "../Object/Particle/explosion/explosion.h"

void Scene::Draw2D()
{
	switch (nowScene)
	{
	case SceneType::Title:
		DrawTitle();
		break;

	case SceneType::Game1:
		DrawGame1();
		break;

	case SceneType::Result:
		DrawResult();
		break;

	default:
		break;
	}

	// フェード用図形
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
	DrawHako(0.0f, 0.0f, 640.0f, 360.0f, &SceneFadeColor, true);

	// 以下文字列描画
	DrawString(nowScene);
}

void Scene::DrawTitle()
{
}

void Scene::DrawGame1()
{
	DrawHako(0.0f, 0.0f, 640.0f, 360.0f, &Math::Color(0.0f, 0.0f, 0.1f, 1.0f), true);

	// マップ
	m_map.Draw();

	// アイテム
	for (UINT i = 0; i < m_itemList.size(); i++)
	{
		m_itemList[i]->Draw();
	}

	// ビーム0
	m_beam.Draw(beamNum);

	// 敵機
	/*std::vector<C_Enemy*>::iterator _it;
	_it = m_enemy.begin();
	while (_it != m_enemy.end())
	{
		(*_it)->Draw();
	}*/
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Draw();
	}

	for (int i = 0; i < m_enemyAList.size(); i++)
	{
		m_enemyAList[i]->Draw();
	}

	// 自機
	m_player.Draw();

	// UI
	m_UI.Draw();
}

void Scene::DrawResult()
{
}

void Scene::DrawString(SceneType nowScene)
{
	switch (nowScene)
	{
	case SceneType::Title:

		break;

	case SceneType::Game1:
		sprintf_s(nowSceneStr, sizeof(nowSceneStr), "SCORE:%06d", m_score);
		DrawMoji(250 + 3, 360 - 30 - 3, nowSceneStr, &Math::Color(0.0f, 0.0f, 0.0f, 1.0f));
		DrawMoji(250, 360 - 30, nowSceneStr, &Math::Color(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	default:
		break;
	}
}

void Scene::DrawFilledMaru(float x, float y, float rad, Math::Color color)
{
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateScale(1.0f / 360.0f * (rad * 2.0f)) *
		Math::Matrix::CreateTranslation(x, y, 0.0f));
	SHADER.m_spriteShader.DrawTex(&m_MaruTex, 0, 0, &Math::Rectangle(0, 0, 360, 360), &color);
}

void Scene::CreateEnemy(int _flg)
{
	C_Enemy* enemy;
	enemy = new C_Enemy();
	enemy->SetOwner(this);
	enemy->Init();
	enemy->SetEnemyTex(&m_enemyTex);
	enemy->SetBullet1Tex(&m_bullet0Tex);
	enemy->SetParticleTex(&m_particleTex);
	enemy->SetUITex(&m_UITex);
	m_enemyList.push_back(enemy);
}

void Scene::Update()
{
	// デバッグウィンドウの表示・非表示切り替え ( ctrl + '-' )
	if (GetAsyncKeyState(VK_OEM_MINUS) & 0x8000)
	{
		if (!keyFlg[k_any1])
		{
			m_bShowDebugWindow = !m_bShowDebugWindow;
		}
		keyFlg[k_any1] = true;
	}
	else
	{
		keyFlg[k_any1] = false;
	}

	switch (nowScene)
	{
	case SceneType::Title:
		UpdateTitle();
		break;

	case SceneType::Game1:
		CheckGame1Vec();
		UpdateGame1();
		break;

	case SceneType::Result:
		UpdateResult();
		break;

	default:

		break;
	}
}

void Scene::UpdateTitle()
{
}

void Scene::CheckGame1Vec()
{
	std::vector<C_Item*>::iterator _itemIt;
	_itemIt = m_itemList.begin();
	while (_itemIt != m_itemList.end())
	{
		const bool bAlive = (*_itemIt)->GetFlg();
		if (!bAlive)
		{
			delete (*_itemIt);
			_itemIt = m_itemList.erase(_itemIt);
		}
		else
		{
			_itemIt++;
		}
	}

	std::vector<EnemyA*>::iterator _enemyAIt;
	_enemyAIt = m_enemyAList.begin();
	if (GetAsyncKeyState('O') & 0x8000)
	{
		if (!keyFlg['O'])
		{
			if (m_enemyAList.size() > 0)
			{
				delete (*_enemyAIt);
				_enemyAIt = m_enemyAList.erase(_enemyAIt);
			}
			keyFlg['O'] = true;
		}
	}
	else
	{
		keyFlg['O'] = false;
	}

	_enemyAIt = m_enemyAList.begin();
	while (_enemyAIt != m_enemyAList.end())
	{
		const int bFlg = (*_enemyAIt)->GetFlg();
		if (bFlg & st_dead)
		{
			delete (*_enemyAIt);
			_enemyAIt = m_enemyAList.erase(_enemyAIt);
		}
		else
		{
			_enemyAIt++;
		}
	}
}

void Scene::UpdateGame1()
{
	// ビーム
	m_beam.Update(beamNum, beamDeg);

	if (GetKey('I'))
	{
		if (!keyFlg['I'])
		{
			C_Item* tempItem = new C_Item();
			tempItem->Init();
			tempItem->SetTexture(&m_itemTex);
			tempItem->Drop({ 0.0f, 300.0f }, 0);
			m_itemList.push_back(tempItem);

			tempItem = new C_Item();
			tempItem->Init();
			tempItem->SetTexture(&m_itemTex);
			tempItem->Drop({ -150.0f, 300.0f }, 1);
			m_itemList.push_back(tempItem);
		}
		keyFlg['I'] = true;
	}
	else
	{
		keyFlg['I'] = false;
	}

	if (GetKey(VK_NUMPAD0))
	{
		if (!keyFlg[k_np_0])
		{
			CreateEnemy(0);
		}
		keyFlg[k_np_0] = true;
	}
	else
	{
		keyFlg[k_np_0] = false;
	}

	// 敵機
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_enemyAList[0]->SetTest();
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_enemyAList[0]->ShootToPlayer(m_player.GetPos());
	}
	//for (int i = 0; i < m_enemy.size(); i++)
	//{
	//	m_enemy[i]->Update();
	//}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (!keyFlg['Q'])
		{
			EnemyA* tempEnemy = new EnemyA();
			m_enemyAList.push_back(tempEnemy);
			//m_enemy.SetRndPos();
		}
		keyFlg['Q'] = true;
	}
	else
	{
		keyFlg['Q'] = false;
	}

	// アイテム
	for (int i = 0; i < m_itemList.size(); i++)
	{
		m_itemList[i]->Update();

		// プレイヤーとアイテムの当たり判定
		if (m_hit.HitObjCircle(m_player.GetObj(), m_itemList[i]->GetObj()))
		{
			//m_player.SetB

			m_itemList[i]->SetFlg(0);
		}
	}

	// 自機
	m_player.Update();

	// シーカー当たり判定
	//if (m_hit.HitObjBox(m_player.GetSeekObj(), m_enemy.GetObj()))
	{
		//if (!m_enemy.GetbLock())
		{
			//m_player.LockOn(m_enemy.GetObj());

			//m_enemy.SetbLock(1);
		}
	}

	// 弾と敵の当たり判定
	for (int i = 0; i < m_player.GetBulletNum(); i++)
	{
		if (m_player.GetBulletFlg(i) == 2) continue;

		//if (m_player.GetBulletObj(i).pos.y > 200.0f)
		//{
		//	m_player.SetBulletActive(i, false);
		//}
		for (int j = 0; j < m_enemyList.size(); j++)
		{
			if (m_enemyList[j]->GetFlg() & st_alive)
			{
				if (m_hit.HitObjBox(m_player.GetBulletObj(i), m_enemyList[j]->GetObj()))
				{
					m_player.SetBulletFlg(i, 2);
					m_score += 10;
					m_enemyList[j]->m_hp -= 1;
					break;
				}
			}
		}
	}
	// ウェブと敵の当たり判定
	for (int e = 0; e < m_enemyList.size(); e++)
	{
		if (!m_enemyList[e]->GetbLock() && m_enemyList[e]->GetFlg())
		{
			if (m_hit.HitObjBox(m_player.GetWebBObj(), m_enemyList[e]->GetObj()))
			{
				m_enemyList[e]->SetbLock(true);
				//m_enemy[e]->SetFlg(st_dead);
			}
		}
	}

	// エネミー更新
	std::vector<C_Enemy*>::iterator _it;
	_it = m_enemyList.begin();
	while (_it != m_enemyList.end())
	{
		(*_it)->Update(m_player.GetPos());
		_it++;
	}
	// エネミーA更新
	for (int i = 0; i < m_enemyAList.size(); i++)
	{
		if (GetAsyncKeyState('P') & 0x8000)
		{
			m_enemyAList[i]->Test();
		}
		m_enemyAList[i]->Update();
	}

	// マップ
	m_map.Update();

	// UI
	m_UI.Update();
}

void Scene::UpdateResult()
{
}

void Scene::Init()
{
	srand(timeGetTime());

	nowScene = SceneType::Game1;

	SceneFadeColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	SceneFadeColor.w = 0.0f;

	for (int i = 0; i < 255; i++) keyFlg[i] = false;

	InitGame1();
}

void Scene::InitTitle()
{
}

void Scene::InitGame1()
{
	// UI
	m_UI.SetOwner(this);
	m_UI.Init();
	m_UITex.Load("Data/Texture/UI/UI-0.png");
	m_UI.SetTexture0(&m_UITex);

	// パーティクル
	m_particleTex.Load("Data/Texture/Particle/effect0.png");

	// プレイヤー
	m_player.Init();
	m_player.SetOwner(this);
	m_player.SetTexture("Data/Texture/Player/player128x128.png");

	// 弾
	m_bullet0Tex.Load("Data/Texture/Bullet/bullet-100x100.png");
	m_player.SetBullet0Tex(&m_bullet0Tex);

	// ビーム0
	m_beam.SetOwner(this);
	m_beam.SetTexture(&m_bullet0Tex);
	m_beam.Init();
	beamNum = 0;

	// アイテム
	m_itemTex.Load("Data/Texture/Item/item0.png");

	// エネミー
	// 敵を１体生成
	m_enemyTex.Load("Data/Texture/Enemy/enemy0.png");
	CreateEnemy(0);

	// マップ
	m_map.SetOwner(this);
	m_map.Init();
	m_mapTex[0].Load("Data/Texture/Map/MiniWorld1280x720.png");
	m_mapTex[1].Load("Data/Texture/Map/Desert01.png");
	m_map.SetImg0(&m_mapTex[0]);
	m_map.SetImg1(&m_mapTex[1]);

	// ●
	m_MaruTex.Load("Data/Texture/Misc/Maru360x360.png");

	// 当たり判定
	m_hit.SetOwner(this);
}

void Scene::InitResult()
{
}

void Scene::Release()
{
	ReleaseTitle();
	ReleaseGame1();
	ReleaseResult();

	// プレイヤー
	m_bullet0Tex.Release();

	// アイテム
	m_itemTex.Release();

	// エネミー
	m_enemyTex.Release();

	// マップ
	m_mapTex[0].Release();
	m_mapTex[1].Release();

	// パーティクル
	m_particleTex.Release();

	// UI
	m_UITex.Release();
}

void Scene::ReleaseTitle()
{
}

void Scene::ReleaseGame1()
{
}

void Scene::ReleaseResult()
{
}

void Scene::ImGuiUpdate()
{
	if (!m_bShowDebugWindow) return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(250, 200), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin(u8"でばっぐうぃんどう"))
	{
		if (ImGui::Button(u8"＜")) if (m_debugNowPage > 0) m_debugNowPage--;
		ImGui::SameLine();
		ImGui::Text("P.%d", m_debugNowPage);	
		ImGui::SameLine();
		if (ImGui::Button(u8"＞")) if (m_debugNowPage < 10) m_debugNowPage++;
		ImGui::SameLine();
		ImGui::Text("FPS:%d|Scene:%s", APP.m_fps, nowSceneStr);

		Math::Vector4 _DebugColor = m_player.GetDebugColor();

		switch (m_debugNowPage)
		{
		case 0:
			ImGui::Text(u8"いろいろ");
			ImGui::Checkbox(":Debug", &m_debugFlg);
			ImGui::Text("roll.flg:%d frame:%.1f", m_player.GetRollFlg(), m_player.GetRollFrame1());
			ImGui::Text("PBullet[%d] Item[%d]", m_player.GetBulletNum(), m_itemList.size());
			ImGui::Text("Enemy.size[%d]", m_enemyList.size());
			ImGui::Text("EnemyFlg[0]:%d HP:%d", (int)m_enemyList[0]->GetFlg(), m_enemyList[0]->m_hp);
			ImGui::Text("PShootFlg:%d PShootTime:%d", m_player.GetShootFlg(), m_player.GetShootTime());
			ImGui::Text("EnemyA.size:%d", m_enemyAList.size());
			ImGui::SliderInt("beamNum", &beamNum, 0, 300, "%d");
			ImGui::SliderFloat("beamDeg", &beamDeg, 0.0f, 720.0f);
			break;

		case 1:
			ImGui::Text(u8"[プレイヤー関連]");
			// プレイヤーの移動速度
			ImGui::Text("moveVec : %.2f, %.2f", m_player.GetMoveVec().x, m_player.GetMoveVec().y);
			// プレイヤー切り取り範囲
			ImGui::SliderInt("PNowAnimY", &m_playerNowAnimY, 0, 9);
			m_player.SetNowAnimY(m_playerNowAnimY);
			// プレイヤーの色
			ImGui::ColorEdit4("PlayerColor", &m_playerColor.x);
			m_player.SetPColor(m_playerColor);

			break;

		case 2:
			ImGui::Text(u8"[ウェブ関連]");
			// 色
			ImGui::SliderFloat("DebugColor:R", &_DebugColor.x, 0.0f, 1.0f);
			ImGui::SliderFloat("DebugColor:G", &_DebugColor.y, 0.0f, 1.0f);
			ImGui::SliderFloat("DebugColor:B", &_DebugColor.z, 0.0f, 1.0f);
			ImGui::SliderFloat("DebugColor:A", &_DebugColor.w, 0.0f, 1.0f);

			//ImGui::Text("webA.deg:%.2f", m_player.m_webA.degMove);
			break;
		
		case 3:
			ImGui::Text(u8"[マップ関連]");
			ImGui::SliderInt("nowTex", &m_map.m_nowTex, 0, 1);
			break;

		default:
			ImGui::Text(u8"There's nothing here, yet\n[このページにはまだ何も有馬温泉]");
			break;
		}
	}
	ImGui::End();
}
