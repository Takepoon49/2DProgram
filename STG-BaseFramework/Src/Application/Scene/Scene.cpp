#include "../main.h"
#include "Scene.h"

#include "../Object/Enemy/enemyA.h"

void Scene::Draw2D()
{
	switch (nowScene)
	{
	case SceneType::S_Title:

		break;

	case SceneType::S_Game1:
		DrawGame1();
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

void Scene::DrawGame1()
{
	//m_map.Draw();
	DrawHako(0.0f, 0.0f, 640.0f, 360.0f, &Math::Color(0.0f, 0.0f, 0.1f, 1.0f), true);

	// アイテム
	for (UINT i = 0; i < m_itemList.size(); i++)
	{
		m_itemList[i]->Draw();
	}

	// ビーム0
	m_beam.Draw(beamNum);

	// 敵機
	m_enemy.Draw();

	for (UINT i = 0; i < m_enemyAList.size(); i++)
	{
		m_enemyAList[i]->Draw();
	}

	// 自機
	m_player.Draw();
}

void Scene::DrawString(SceneType nowScene)
{
	switch (nowScene)
	{
	case SceneType::S_Title:

		break;

	case SceneType::S_Game1:
		sprintf_s(nowSceneStr, sizeof(nowSceneStr), "S_Game1");
		DrawMoji(0, 0, nowSceneStr, &Math::Color(1.0f, 1.0f, 1.0f, 1.0f));
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

void Scene::Update()
{
	switch (nowScene)
	{
	case SceneType::S_Title:

		break;

	case SceneType::S_Game1:
		CheckGame1Vec();
		UpdateGame1();
		break;

	default:

		break;
	}
}

void Scene::CheckGame1Vec()
{
	m_itemIt = m_itemList.begin();
	while (m_itemIt != m_itemList.end())
	{
		const bool bAlive = (*m_itemIt)->GetFlg();
		if (!bAlive)
		{
			delete (*m_itemIt);
			m_itemIt = m_itemList.erase(m_itemIt);
		}
		else
		{
			m_itemIt++;
		}
	}

	m_enemyAIt = m_enemyAList.begin();
	while (m_enemyAIt != m_enemyAList.end())
	{
		const bool bActive = (*m_enemyAIt)->GetFlg();
		if (!bActive)
		{
			delete (*m_enemyAIt);
			m_enemyAIt = m_enemyAList.erase(m_enemyAIt);
		}
		else
		{
			m_enemyAIt++;
		}
	}
}

void Scene::UpdateGame1()
{
	// ビーム
	m_beam.Update(beamNum, beamDeg);

	if (GetKey('I'))
	{
		if (!keyFlg[key_I])
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

			EnemyA* tempEnemy = new EnemyA();
			m_enemyAList.push_back(tempEnemy);
		}
		keyFlg[key_I] = true;
	}
	else
	{
		keyFlg[key_I] = false;
	}

	// 敵機
	m_enemy.Update();

	for (UINT i = 0; i < m_enemyAList.size(); i++)
	{
		m_enemyAList[i]->Update();
	}

	// アイテム
	for (UINT i = 0; i < m_itemList.size(); i++)
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
	if (m_hit.HitObjBox(m_player.GetSeekObj(), m_enemy.GetObj()))
	{
		if (!m_enemy.GetbIsLock())
		{
			//m_player.LockOn(m_enemy.GetObj());

			m_enemy.SetbIsLock(1);
		}
	}

	// 弾と敵の当たり判定
	for (int i = 0; i < m_player.GetBulletNum(); i++)
	{
		if (m_player.GetBulletFlg(i) == st_dead) continue;

		//if (m_player.GetBulletObj(i).pos.y > 200.0f)
		//{
		//	m_player.SetBulletActive(i, false);
		//}
		if (m_hit.HitObjBox(m_player.GetBulletObj(i), m_enemy.GetObj()))
		{
			m_player.SetBulletFlg(i, false);
			m_enemy.SetFlg(st_stat1);
		}
	}

	//m_map.Update();
}

void Scene::Init()
{
	nowScene = SceneType::S_Game1;

	SceneFadeColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	SceneFadeColor.w = 0.0f;

	InitGame1();
}

void Scene::InitGame1()
{
	// プレイヤー
	m_player.SetOwner(this);
	m_player.Init();
	m_playerTex.Load("Data/Texture/player345x345.png");
	m_player.SetPlayerTex(&m_playerTex);

	// 弾
	m_bullet0Tex.Load("Data/Texture/bullet-100x100.png");
	m_player.SetBullet0Tex(&m_bullet0Tex);

	// ビーム0
	m_beam.SetOwner(this);
	m_beam.SetTexture(&m_bullet0Tex);
	m_beam.Init();
	beamNum = 0;

	// アイテム
	m_itemTex.Load("Data/Texture/item0.png");

	// エネミー
	m_enemy.SetOwner(this);
	m_enemy.Init();
	m_enemyTex.Load("Data/Texture/enemy0.png");
	m_enemy.SetEnemyTex(&m_enemyTex);

	

	// マップ
	m_map.SetOwner(this);
	m_map.Init();
	m_mapTex.Load("Data/Texture/Back720p.png");
	m_map.SetImg0(&m_mapTex);
	// ●
	m_MaruTex.Load("Data/Texture/Maru360x360.png");

	// 当たり判定
	m_hit.SetOwner(this);
}

void Scene::Release()
{
	// プレイヤー
	m_playerTex.Release();
	m_bullet0Tex.Release();

	// アイテム
	m_itemTex.Release();

	// エネミー
	m_enemyTex.Release();

	//m_enemyA->Release();

	// マップ
	m_mapTex.Release();
}

void Scene::ReleaseGame1()
{
}

void Scene::ImGuiUpdate()
{
	//return;

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

		switch (m_debugNowPage)
		{
		case 0:
			ImGui::Checkbox(":Debug", &m_debugFlg);

			ImGui::Text("PBullet[%d] Item[%d]", m_player.GetBulletNum(), m_itemList.size());
			ImGui::Text("EnemyFlg[0]:%d", (int)m_enemy.GetFlg());
			ImGui::SliderInt("beamNum", &beamNum, 0, 300, "%d");
			ImGui::SliderFloat("beamDeg", &beamDeg, 0.0f, 720.0f);
			break;
		
		default:
			ImGui::Text(u8"There's nothing here, yet\nこのページにはまだ何も有馬温泉");
			break;
		}
	}
	ImGui::End();
}
