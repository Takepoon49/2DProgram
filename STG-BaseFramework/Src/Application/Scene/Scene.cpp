#include "../main.h"
#include "Scene.h"

#include "../Object/Player/player.h"	// プレイヤー

#include "../Object/Attack/LSWM/bomb.h"			// ボム
#include "../Object/Particle/TrailA/TrailA.h"	// ミサイルの軌道

#include "../Object/Attack/H-Laser/H-Laser.h"	// 追尾レーザー

#include "../Object/Enemy/enemy/enemy.h"		// エネミー
#include "../Object/Enemy/enemy/enemy1.h"		// エネミー
#include "../Object/Enemy/enemy/boss.h"			// ボス

#include "../Object/Attack/Bullet1/bullet1.h"	// 敵の弾

// パーティクル
#include "../Object/Particle/explosion/explosion.h"	// 爆発A
#include "../Object/Particle/playerAB/playerAB.h"	// プレイヤーアフターバーナー
#include "../Object/Particle/PlayerShadow/PShadow.h"// プレイヤーの影
#include "../Object/Particle/forHLaser/HLTrail.h"	// 追尾弾軌道
#include "../Object/Particle/light0/lightH.h"		// 光０
#include "../Object/Particle/ShockWave/ShockWave.h"		// 衝撃波

#include "../Object/Map/map.h"	// マップ

#include "../Object/UI/UI.h"	// UI

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
	// 海
	for (int i = 0; i < 2; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_titleScrMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_titleTex2, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	}

	// パーティクル
	// アフターバーナー
	for (auto& pAB : m_abParticleList)
	{
		pAB->Draw();
	}

	m_player->Draw();

	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	// Press Enter
	SHADER.m_spriteShader.DrawTex(&m_titleTex0, Math::Rectangle(0, 0, 1280, 720), fabs(sin(DegToRad(m_frame*1.8f))));
	// Ray Seeker
	SHADER.m_spriteShader.DrawTex(&m_titleTex1, Math::Rectangle(0, 0, 1280, 720), 1.0f);
}

void Scene::DrawGame1()
{
	// マップ
	m_map->Draw();

	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
	DrawHako(0.0f, 0.0f, 640.0f, 360.0f, &Math::Color(0.0f, 0.0f, 0.1f, 0.25f), true);

	// アイテム
	for (UINT i = 0; i < m_itemList.size(); i++)
	{
		m_itemList[i]->Draw();
	}

	// 自機 ※この中にアフターバーナーの描画もある
	if (!m_gameOverFlg) m_player->Draw();

	// ビーム0
	m_beam.Draw(beamNum);

	// 弾更新
	for (auto& obj : m_bulletList)
	{
		obj->Draw();
	}

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

	// ボス
	//if (m_boss != nullptr)
	if (m_bossFlg > 0)
	{
		m_boss->Draw();
	}

	// パーティクル
	for (auto& particleList : m_particleList)
	{
		particleList->Draw();
	}

	// ボム
	for (auto& bomb : m_bombList)
	{
		bomb->Draw();
	}

	// 追尾レーザー
	for (auto& hLaser : m_hLaserList)
	{
		hLaser->Draw();
	}

	// デバッグ用
	if (m_debugFlg)
	{
		ResetMatrix();

		//Math::Vector2 _ppos = m_player->GetPos();
		//Math::Vector2 _mmpos = { (float)m_mousePos.x, (float)m_mousePos.y };
		//Math::Vector2 _v = _ppos - _mmpos;
		//Math::Color _color = { 0.0f, 1.0f, 0.0f, 1.0f };
		//
		//float _deg = DirectX::XMConvertToDegrees(atan2(_mmpos.y - _ppos.y, _mmpos.x - _ppos.x));

		//if (_v.Length() < 680.0f)
		//{
		//	if (_deg > 90.0f - 26.0f && _deg < 90.0f + 26.0f)
		//	{
		//		_color = { 1.0f, 0.0f, 0.0f, 1.0f };
		//	}
		//}
		//SHADER.m_spriteShader.DrawLine(_ppos.x, _ppos.y, m_mousePos.x, m_mousePos.y, &_color);
	}

	// UI
	m_UI->Draw();
}

void Scene::DrawResult()
{	
	// 海
	/*for (int i = 0; i < 2; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_titleScrMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_titleTex2, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	}*/

	SHADER.m_spriteShader.SetMatrix(m_resultCPMat);
	// 滑走路と海
	SHADER.m_spriteShader.DrawTex(&m_resultBackTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

	// 文字
	SHADER.m_spriteShader.DrawTex(&m_resultCTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	SHADER.m_spriteShader.DrawTex(&m_resultPTex, Math::Rectangle(0, 0, 1280, 720), fabs(sin(DegToRad(m_frame*1.5f))) );

	// パーティクル
	// アフターバーナー
	/*for (auto& pAB : m_abParticleList)
	{
		pAB->Draw();
	}*/

	m_player->Draw();

	SHADER.m_spriteShader.SetMatrix(m_resultMat.m);
	SHADER.m_spriteShader.DrawTex(&m_resultTex, Math::Rectangle(0, 0, 335, 62), 1.0f);

	DrawNumber( m_score, { m_resultPos.x + 500.0f, 10.0f }, 1);
}

void Scene::DrawString(SceneType nowScene)
{
	float _alpha = 1.0f - SceneFadeColor.w;

	switch (nowScene)
	{
	case SceneType::Title:
		sprintf_s(nowSceneStr, sizeof(nowSceneStr), "[←]  SKIN : %s  [→]", m_skinStr);
		DrawMoji(scrLeft + 430.0f, scrTop - 660.0f, nowSceneStr, &Math::Color(0.0f, 0.0f, 0.0f, _alpha));
		DrawMoji(scrLeft + 430.0f + 3.0f, scrTop - 660.0f - 3, nowSceneStr, &Math::Color(1.0f, 1.0f, 1.0f, _alpha));

		break;

	case SceneType::Game1:
		m_UI->DrawStr();

		sprintf_s(nowSceneStr, sizeof(nowSceneStr), "%02d:%02d", m_min, 59 - m_sec);
		SHADER.m_spriteShader.DrawString(-60.0f + scrGap, 350.0f - scrGap, nowSceneStr, Math::Color(0.0f, 0.0f, 0.0f, _alpha));
		SHADER.m_spriteShader.DrawString(-60.0f + scrGap + 3, 350.0f - scrGap - 3, nowSceneStr, Math::Color(1.0f, 1.0f, 1.0f, _alpha));

		sprintf_s(nowSceneStr, sizeof(nowSceneStr), "Player\n%06d", m_score);
		DrawMoji(scrLeft + scrGap + 10.0f, scrTop - scrGap, nowSceneStr, & Math::Color(0.0f, 0.0f, 0.0f, _alpha));
		DrawMoji(scrLeft + scrGap + 10.0f + 3.0f, scrTop - scrGap - 3, nowSceneStr, &Math::Color(1.0f, 1.0f, 1.0f, _alpha));

		//sprintf_s(nowSceneStr, sizeof(nowSceneStr), "Player:%d", m_playerLife);
		//DrawMoji(scrLeft + 1145.0f, scrTop - 85.0f, nowSceneStr, &Math::Color(0.0f, 0.0f, 0.0f, _alpha));
		//DrawMoji(scrLeft + 1145.0f + 3.0f, scrTop - 85.0f - 3, nowSceneStr, &Math::Color(1.0f, 1.0f, 1.0f, _alpha));
		break;

	case SceneType::Result:
		//sprintf_s(nowSceneStr, sizeof(nowSceneStr), "RESULTS");
		//SHADER.m_spriteShader.DrawString(-300.0f, 200.0f, nowSceneStr, Math::Color(1.0f, 1.0f, 1.0f, 1.0f));

		//sprintf_s(nowSceneStr, sizeof(nowSceneStr), "Press 'SPACE' to title");
		//DrawMoji(scrLeft + 640.0f, scrTop - 500.0f, nowSceneStr, &Math::Color(0.0f, 0.0f, 0.0f, _alpha));
		//DrawMoji(scrLeft + 640.0f + 3.0f, scrTop - 500.0f - 3, nowSceneStr, &Math::Color(1.0f, 1.0f, 1.0f, _alpha));
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

void Scene::DeleteBullet1()
{
	m_bulletIt = m_bulletList.begin();	// 可変長配列の先頭アドレスを格納
	while (m_bulletIt != m_bulletList.end())
	{
		const int bAlive = (*m_bulletIt)->GetFlg();
		if (bAlive == 0)
		{
			m_bulletIt = m_bulletList.erase(m_bulletIt);	// 箱を削除して削除する箱の次のアドレスをイテレーターに格納
		}
		else
		{
			m_bulletIt++;
		}
	}
}

void Scene::CreateBullet1(Math::Vector2 _pos, float _deg)
{
	std::shared_ptr<Bullet1> temp = std::make_shared<Bullet1>();
	temp->Init();
	temp->SetTexture("Data/Texture/Bullet/Bullet-100x100.png");
	temp->SetOwner(this);
	temp->Shot(_pos, _deg, 1);
	m_bulletList.push_back(temp);
}

int Scene::GetLockOnNum()
{
	int num = 0;
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		if (m_enemyList[i]->GetLockFlg() == 2)
		{
			num++;
		}
	}

	return num;
}

float Scene::GetPlayerRollVal()
{
	return m_player->GetRollingVal();
}

float Scene::GetPlayerRollValMax()
{
	return m_player->GetRollingValMax();
}

Math::Vector2 Scene::GetPlayerNowAnim()
{
	return m_player->GetNowAnim();
}

Math::Color Scene::GetPlayerDColor()
{
	return m_player->GetDebugColor();
}

void Scene::SetAllLock(int _flg)
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		if (m_enemyList[i]->GetLockFlg() == 2)
		{
			m_enemyList[i]->SetLockFlg(0);
		}
	}
}

void Scene::CreateEnemy(Math::Vector2 _pos, int _flg, int _frame)
{
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
	enemy->SetOwner(this);
	enemy->Init(_flg, _frame);
	enemy->SetPos(_pos);
	enemy->SetTexture("Data/Texture/Enemy/enemy0.png");
	enemy->SetUITex(&m_UITex);
	m_enemyList.push_back(enemy);
}

void Scene::CreateEnemy1(Math::Vector2 _pos, int _flg, int _frame)
{
	std::shared_ptr<Enemy1> enemy1 = std::make_shared<Enemy1>();
	enemy1->SetOwner(this);
	enemy1->Init(_flg, _frame);
	enemy1->SetPos(_pos);
	enemy1->SetTexture("Data/Texture/Enemy/enemy0.png");
	enemy1->SetUITex(&m_UITex);
	m_enemyList.push_back(enemy1);
}

void Scene::CreateBoss(Math::Vector2 _pos, int _flg)
{
	m_boss = std::make_shared<Boss>();
	m_boss->SetOwner(this);
	m_boss->Init();
	m_boss->SetTexture("Data/Texture/Enemy/enemy0.png");
}

void Scene::ResetBoss()
{
	m_boss.reset();
}

void Scene::CreateItem(Math::Vector2 _pos, int _flg)
{
	//C_Item* tempItem = new C_Item();
	std::shared_ptr<C_Item> tempItem = std::make_shared<C_Item>();
	tempItem->Init();
	tempItem->SetTexture(&m_itemTex);
	tempItem->Drop(_pos, _flg);
	m_itemList.push_back(tempItem);
}

void Scene::CreateHLaser(Math::Vector2 _pos, float _deg)
{
	std::shared_ptr<HLaser> temp = std::make_shared<HLaser>();
	temp->SetOwner(this);
	temp->SetTexture("Data/Texture/Bullet/bullet-100x100.png");
	temp->Init(_pos, _deg);

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		if (m_enemyList[i]->GetLockFlg() == 1)
		{
			m_enemyList[i]->SetLockFlg(2);
			temp->SetTarget(m_enemyList[i]);
			break;
		}
	}

	if (AddBlend)
	{
		CreateLightH(temp, 0);
	}

	m_hLaserList.push_back(temp);
	//CreateLightH(m_hLaserList.back(), 0);
}

void Scene::ShotBomb(Math::Vector2 _ppos, int _flg)
{
	m_bomb = std::make_shared<Bomb>();
	m_bomb->Init(m_player->GetPos(), _flg);
	m_bomb->SetOwner(this);
	m_bomb->SetTexture("Data/Texture/Bullet/bullet-100x100.png");
	m_bombList.push_back(m_bomb);
}

void Scene::EraseAll()
{
	m_abParticleList.clear();
	m_bombList.clear();
	m_bulletList.clear();
	m_hLaserList.clear();
	m_itemList.clear();
	m_enemyList.clear();
	m_particleList.clear();
}

void Scene::CreateHLTrail(Math::Vector2 _pos, float _deg, Math::Color _color)
{
	std::shared_ptr<HLTrail> temp = std::make_shared<HLTrail>();
	temp->SetOwner(this);
	temp->SetTexture("Data/Texture/Bullet/bullet-100x100.png");
	temp->Init(_pos, _deg, _color);

	if (AddBlend)
	{
		//CreateLightH(temp, 1);
	}

	m_particleList.push_back(temp);
}

void Scene::CreateParticle(ParticleType _type, Math::Vector2 _pos)
{

}

void Scene::CreateExplosionA(ParticleType _type, Math::Vector2 _pos)
{
	std::shared_ptr<Explosion> tempAB;
	tempAB = std::make_shared<Explosion>();
	tempAB->Init(_type, _pos);
	tempAB->SetTexture("Data/Texture/Particle/particle0.png");
	tempAB->SetOwner(this);
	m_particleList.push_back(tempAB);
}

//void Scene::CreateLightH(std::shared_ptr<HLaser> _pair)
void Scene::CreateLightH(std::shared_ptr<BaseObject> _pair, int _type)
{
	std::shared_ptr<LightH> temp;
	temp = std::make_shared<LightH>();
	temp->SetOwner(this);
	temp->Init(_pair, _type);
	temp->SetTexture("Data/Texture/Particle/particle0.png");
	m_particleList.push_back(temp);
}

void Scene::CreatePlayerAB(std::shared_ptr<BaseObject> _obj)
{
	// プレイヤーアフターバーナー これだけはプレイヤーより奥に表示させたいのでパーティクルリストに入れない。
	std::shared_ptr<PlayerAB> tempAfterBurner = std::make_shared<PlayerAB>();
	tempAfterBurner->SetPlayer(_obj);
	tempAfterBurner->Init();
	tempAfterBurner->SetTexture("Data/Texture/Particle/particle0.png");
	tempAfterBurner->SetOwner(this);
	m_abParticleList.push_back(tempAfterBurner);
}

void Scene::CreatePShadow(Math::Vector2 _pos)
{
	std::shared_ptr<PShadow> temp = std::make_shared<PShadow>();
	temp->SetOwner(this);
	temp->Init(m_player);
	temp->SetTexture("Data/Texture/Player/player384x1280.png");
	m_particleList.push_back(temp);
}

void Scene::CreateShockWave(Math::Vector2 _pos)
{
	std::shared_ptr<ShockWave> temp = std::make_shared<ShockWave>();
	temp->SetOwner(this);
	temp->Init(_pos);
	temp->SetTexture("Data/Texture/Particle/particle0.png");
	m_particleList.push_back(temp);
}

void Scene::CreateMSLTrail(Math::Vector2 _pos)
{
	std::shared_ptr<TrailA> temp;
	temp = std::make_shared<TrailA>();
	temp->SetOwner(this);
	temp->Init(_pos);
	temp->SetTexture("Data/Texture/Particle/particle0.png");
	m_particleList.push_back(temp);
}

bool Scene::GetPlayerHitFlg()
{
	return 	m_player->GetHitFlg();
}

void Scene::DrawPlayerAB()
{
	// 自機アフターバーナー
	for (auto& ab : m_abParticleList)
	{
		ab->Draw();
	}
}

void Scene::Update()
{
	if (m_bDebugKey)
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

		// デバッグフラグの切り替え ( [Ctrl] + [D] )
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		{
			if (GetAsyncKeyState('D') & 0x8000)
			{
				if (!keyFlg[k_any2])
				{
					m_debugFlg = !m_debugFlg;
				}
				keyFlg[k_any2] = true;
			}
			else
			{
				keyFlg[k_any2] = false;
			}
		}
	}

	// マウス座標取得
	if (m_bGetMousePos)
	{
		GetMousePos2(&m_mousePos);
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
	m_frame++;

	Math::Vector2 _nowAnim = m_player->GetNowAnim();

	// スキンに合わせて変更
	// -- Berkut ----------------------
	if (_nowAnim.y == 0.0f)
	{
		m_skinStr[0] = 'A';
		m_skinStr[1] = '1';
	}
	if (_nowAnim.y == 1.0f)
	{
		m_skinStr[0] = 'A';
		m_skinStr[1] = '2';
	}
	if (_nowAnim.y == 2.0f)
	{
		m_skinStr[0] = 'A';
		m_skinStr[1] = '3';
	}
	// -- Rafale ----------------------
	if (_nowAnim.y == 3.0f)
	{
		m_skinStr[0] = 'B';
		m_skinStr[1] = '1';
	}
	if (_nowAnim.y == 4.0f)
	{
		m_skinStr[0] = 'B';
		m_skinStr[1] = '2';
	}
	if (_nowAnim.y == 5.0f)
	{
		m_skinStr[0] = 'B';
		m_skinStr[1] = '3';
	}
	// -- Maitake ----------------------
	if (_nowAnim.y == 6.0f)
	{
		m_skinStr[0] = 'M';
		m_skinStr[1] = '0';
	}

	// 海のスクロール
	m_titleScrPos.y -= 2.0f;
	if (m_titleScrPos.y <= -720)
	{
		m_titleScrPos.y = 0.0f;
	}
	m_titleScrMat[0] = Math::Matrix::CreateTranslation(m_titleScrPos.x, m_titleScrPos.y, 0.0f);
	m_titleScrMat[1] = Math::Matrix::CreateTranslation(m_titleScrPos.x, m_titleScrPos.y + 720.0f, 0.0f);

	// 自機
	m_player->Update();

	// 自機アフターバーナー
	if (m_player->GetMoveVec().y >= 0.0f)
	{
		if (m_frame % 2 == 0)
		{
			CreatePlayerAB(m_player);
		}
	}

	// アフターバーナー
	for (auto& pAB : m_abParticleList)
	{
		pAB->Update();
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!keyFlg[k_return])
		{
			if (m_sceneFlg == 0)
			{
				m_sceneFlg = 1;
				m_frame = 0;
			}
		}
		keyFlg[k_return] = true;
	}
	else
	{
		keyFlg[k_return] = false;
	}
	// 明るく
	if (m_sceneFlg == 3)
	{
		if (m_frame > 20)
		{
			SceneFadeColor.w -= 1.0f / 30.0f;
		}

		if (m_frame > 20 + 30)
		{
			m_sceneFlg = 0;
		}
	}
	// 暗く
	if (m_sceneFlg == 1)
	{
		SceneFadeColor.w += 1.0f / 30.0f;

		if (m_frame > 30)
		{
			m_pNowAnim = m_player->GetNowAnim();

			nowScene = SceneType::Game1;
			EraseAll();
			InitGame1();
			m_sceneFlg = 2;
		}
	}


	CheckGame1Vec();
}

void Scene::CheckGame1Vec()
{
	//std::vector<std::shared_ptr<Bomb>>::iterator _bombIt;
	auto _bombIt = m_bombList.begin();
	while (_bombIt != m_bombList.end())
	{
		const bool bAlive = (*_bombIt)->GetFlg();
		if (!bAlive)
		{
			_bombIt = m_bombList.erase(_bombIt);
		}
		else
		{
			_bombIt++;
		}
	}

	std::vector<std::shared_ptr<C_Item>>::iterator _itemIt;
	_itemIt = m_itemList.begin();
	while (_itemIt != m_itemList.end())
	{
		const bool bAlive = (*_itemIt)->GetFlg();
		if (!bAlive)
		{
			//delete (*_itemIt);	// ←スマポなのでdeleteしなくて良い。
			_itemIt = m_itemList.erase(_itemIt);
		}
		else
		{
			_itemIt++;
		}
	}

	// 敵
	std::vector<std::shared_ptr<Enemy>>::iterator _enemyIt;
	_enemyIt = m_enemyList.begin();
	while (_enemyIt != m_enemyList.end())
	{
		const int bFlg = (*_enemyIt)->GetFlg();
		if (bFlg == st_dead)
		{
			//delete (*_enemyAIt);	// ←スマポなので(ry
			_enemyIt = m_enemyList.erase(_enemyIt);
		}
		else
		{
			_enemyIt++;
		}
	}

	// 追尾レーザー
	std::vector<std::shared_ptr<HLaser>>::iterator _hLaserIt;
	_hLaserIt = m_hLaserList.begin();
	while (_hLaserIt != m_hLaserList.end())
	{
		const int bFlg = (*_hLaserIt)->GetFlg();
		if (bFlg == st_dead)
		{
			_hLaserIt = m_hLaserList.erase(_hLaserIt);
		}
		else
		{
			_hLaserIt++;
		}
	}

	// 弾
	DeleteBullet1();

	// パーティクル
	std::vector<std::shared_ptr<ParticleBase>>::iterator _particleListIt;
	_particleListIt = m_particleList.begin();
	while (_particleListIt != m_particleList.end())
	{
		const int bFlg = (*_particleListIt)->GetFlg();
		if (bFlg == st_dead)
		{
			_particleListIt = m_particleList.erase(_particleListIt);
		}
		else
		{
			_particleListIt++;
		}
	}

	// プレイヤーのアフターバーナー
	std::vector<std::shared_ptr<PlayerAB>>::iterator _playerABIt;
	_playerABIt = m_abParticleList.begin();
	while (_playerABIt != m_abParticleList.end())
	{
		const int bFlg = (*_playerABIt)->GetFlg();
		if (bFlg == st_dead)
		{
			_playerABIt = m_abParticleList.erase(_playerABIt);
		}
		else
		{
			_playerABIt++;
		}
	}
}

void Scene::UpdateGame1()
{
	m_frame++;

	// デバッグキー更新
	if (m_bDebugKey)
	{
		// 敵出現、ライフ、ボムなど
		UpdateDebugEnemy();

		// =デバッグ= アイテム出現
		if (GetKey('I'))
		{
			if (!keyFlg[k_i])
			{
				CreateItem({ 0.0f, 200.0f }, 0);
				CreateItem({ 100.0f, 200.0f }, 1);
			}
			keyFlg[k_i] = true;
		}
		else
		{
			keyFlg[k_i] = false;
		}
	}

	// 敵のタイムライン更新
	UpdateEnemyTL();

	// ビーム
	m_beam.Update(beamNum, beamDeg);

	// 自機
	if (!m_gameOverFlg)
	{
		m_player->Update();

		// 自機アフターバーナー
		if (m_player->GetMoveVec().y >= 0.0f)
		{
			if (m_frame % 2 == 0)
			{
				CreatePlayerAB(m_player);
			}
		}
		for (auto& ab : m_abParticleList)
		{
			ab->Update();
		}
	}
	else	// もしゲームオーバーになったら
	{
		if (m_frame >= 120)
		{
			InitTitle();
			nowScene = SceneType::Title;
		}
	}

	// 追尾弾と敵の当たり判定
	// H-Laser.cpp内参照

	// ボム
	for (auto& bomb : m_bombList)
	{
		bomb->Update();
	}

	if (m_player->GetHitFlg() && m_playerLife > 0)
	{
		// 高速移動中は当たり判定小さめ(体感しづらい)
		float _pBrad = 0.0f;
		float _pErad = 0.0f;
		if (m_player->GetRollFlg() != 2)
		{
			_pBrad = 26.0f;
			_pErad = 34.0f;
		}
		else
		{
			_pBrad = 13.0f;
			_pErad = 17.0f;
		}

		// 敵の弾と自機の当たり判定
		for (int i = 0; i < m_bulletList.size(); i++)
		{
			Math::Vector2 _ppos = m_player->GetPos();
			Math::Vector2 _bpos = m_bulletList[i]->GetPos();
			Math::Vector2 _v = _ppos - _bpos;

			if (_v.Length() < _pBrad)
			{
				m_player->OnHit();
				m_playerLife -= 1;
				break;
			}
		}
		// 敵と自機の当たり判定
		for (int i = 0; i < m_enemyList.size(); i++)
		{
			Math::Vector2 _ppos = m_player->GetPos();
			Math::Vector2 _bpos = m_enemyList[i]->GetPos();
			Math::Vector2 _v = _ppos - _bpos;
			if (_v.Length() < _pErad)
			{
				m_player->OnHit();
				m_enemyList[i]->SetHP(0);
				m_score += 10;
				m_playerLife -= 1;
				break;
			}
		}
	}

	// ゲームオーバー判定
	if (m_playerLife <= 0)
	{
		if (!m_gameOverFlg)
		{
			CreateExplosionA(ParticleType::ExplosionA, m_player->GetPos());
			m_gameOverFlg = true;
			m_frame = 0;
			m_sceneFlg = 3;
		}
	}


	// 弾と敵の当たり判定
	for (int i = 0; i < m_player->GetBulletNum(); i++)
	{
		if (m_player->GetBulletFlg(i) == 2) continue;

		for (int j = 0; j < m_enemyList.size(); j++)
		{
			if (m_enemyList[j]->GetFlg() & st_alive)
			{
				if (m_hit.HitObjBox(m_player->GetBulletObj(i), m_enemyList[j]->GetObj()))
				{
					m_player->SetBulletFlg(i, 2);
					m_enemyList[j]->m_hp -= 1;
					break;
				}
			}
		}
	}
	// ウェブと敵の当たり判定
	for (int e = 0; e < m_enemyList.size(); e++)
	{
		if (m_enemyList[e]->GetLockFlg() == 0 && m_enemyList[e]->GetFlg())
		{
			Math::Vector2 _ppos = m_player->GetPos();
			Math::Vector2 _epos = m_enemyList[e]->GetPos();
			Math::Vector2 _v = _ppos - _epos;
			float _deg = DirectX::XMConvertToDegrees(atan2(_epos.y - _ppos.y, _epos.x - _ppos.x));
			float _webDeg = m_player->GetWebBdegAdd();
			if (_v.Length() < m_player->GetWebBsize() * 2.70f)
			{
				if (_deg > 90.0f + _webDeg - 22.0f && _deg < 90.0f + _webDeg + 22.0f)
				{
					m_enemyList[e]->SetLockFlg(1);
				}
			}
		}
	}

	// 追尾レーザーと敵の当たり判定

	// アイテム
	for (int i = 0; i < m_itemList.size(); i++)
	{
		m_itemList[i]->Update();

		// プレイヤーとアイテムの当たり判定
		if (m_hit.HitObjCircle(m_player->GetObj(), m_itemList[i]->GetObj()))
		{
			m_itemList[i]->SetFlg(0);
		}
	}

	// エネミー更新
	m_targetNum = 0;
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->Update(m_player->GetPos());
		if (m_enemyList[i]->GetLockFlg() == 1)
		{
			m_targetNum++;
		}
	}

	// ボス
	//if (m_boss != nullptr)
	if (m_bossFlg > 0)
	{
		m_boss->Update();
	}

	// 弾更新
	for (auto& obj : m_bulletList)
	{
		obj->Update();
	}

	// 追尾レーザー
	for (auto& laser : m_hLaserList)
	{
		//laser->SetMove({ 0.0f, 360.0f});
		laser->Update();
	}

	// マップ
	m_map->Update();

	// UI
	m_UI->Update();

	// パーティクル
	for (auto& particleList : m_particleList)
	{
		particleList->Update();
	}

	// 強制シーン遷移
	if (m_bDebugKey)
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (!keyFlg[k_return])
			{
				if (m_sceneFlg == 0)
				{
					m_sceneFlg = 4;
					m_frame = 0;
				}
			}
			keyFlg[k_return] = true;
		}
		else
		{
			keyFlg[k_return] = false;
		}
	}

	// 明るく & フレーム初期化
	if (m_sceneFlg == 2)
	{
		SceneFadeColor.w -= 1.0f / 30.0f;

		if (m_frame > 30)
		{
			m_sceneFlg = 0;
			m_frame = 0;

			m_min = 0;
			m_sec = 0;
		}
	}
	// 暗く→タイトル
	if (m_sceneFlg == 3)
	{
		if (m_frame > 60)
		{
			SceneFadeColor.w += 1.0f / 60.0f;
		}

		if (m_frame > 60 + 60)
		{
			m_sceneFlg = 3;
			InitTitle();
			nowScene = SceneType::Title;
		}
	}
	// 暗く→リザルト
	if (m_sceneFlg == 4)
	{
		if (m_frame > 60)
		{
			SceneFadeColor.w += 1.0f / 60.0f;
		}

		if (m_frame > 60 + 60)
		{
			m_sceneFlg = 2;

			EraseAll();
			nowScene = SceneType::Result;
			InitResult();
		}
	}
}

void Scene::UpdateResult()
{
	m_frame++;

	m_resultMat.s = Math::Matrix::CreateScale(1.0f);
	m_resultMat.r = Math::Matrix::CreateRotationZ(0.0f);
	m_resultMat.t = Math::Matrix::CreateTranslation(m_resultPos.x, m_resultPos.y, 0.0f);
	m_resultMat.Mix();

	m_resultCPMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	// 海のスクロール
	m_titleScrPos.y -= 2.0f;
	if (m_titleScrPos.y <= -720)
	{
		m_titleScrPos.y = 0.0f;
	}
	m_titleScrMat[0] = Math::Matrix::CreateTranslation(m_titleScrPos.x, m_titleScrPos.y, 0.0f);
	m_titleScrMat[1] = Math::Matrix::CreateTranslation(m_titleScrPos.x, m_titleScrPos.y + 720.0f, 0.0f);

	// 自機
	m_player->Update();

	// 自機アフターバーナー
	/*if (m_player->GetMoveVec().y >= 0.0f)
	{
		if (m_frame % 2 == 0)
		{
			CreatePlayerAB(m_player);
		}
	}*/

	// アフターバーナー
	/*for (auto& pAB : m_abParticleList)
	{
		pAB->Update();
	}*/

	
	// 明るく
	if (m_sceneFlg == 2)
	{
		SceneFadeColor.w -= 1.0f / 30.0f;

		if (m_frame > 30.0f)
		{
			m_sceneFlg = 0;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!keyFlg[k_return])
		{
			if (m_sceneFlg == 0)
			{
				m_sceneFlg = 1;
				m_frame = 0;
			}
		}
		keyFlg[k_return] = true;
	}
	else
	{
		keyFlg[k_return] = false;
	}

	if (m_sceneFlg == 1)
	{
		SceneFadeColor.w += 1.0f / 60.0f;

		if (m_frame > 60)
		{
			m_sceneFlg = 3;
			nowScene = SceneType::Title;
			InitTitle();
		}
	}
}

void Scene::Init()
{
	srand(timeGetTime());

	nowScene = SceneType::Title;

	SceneFadeColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	SceneFadeColor.w = 0.0f;

	for (int i = 0; i < k_end; i++)
	{
		keyFlg[i] = false;
	}

	m_frame = 0;
	m_titleMat = Math::Matrix::Identity;
	m_titleTex0.Load("Data/Texture/Title/PressEnter.png");
	m_titleTex1.Load("Data/Texture/Title/RaySeeker.png");
	m_titleTex2.Load("Data/Texture/Title/right.png");

	m_resultTex.Load("Data/Texture/Misc/ResultScore.png");
	m_resultPos = { -180.0f + 200.0f, 0.0f };
	m_resultMat.Init();

	m_resultBackTex.Load("Data/Texture/Misc/resultBack.png");
	m_resultCTex.Load("Data/Texture/Misc/ResultClear.png");
	m_resultPTex.Load("Data/Texture/Misc/pressenterR.png");

	InitTitle();
}

void Scene::InitTitle()
{
	m_frame = 0;

	m_titleScrPos = { 0.0f, 0.0f };	// スクロール用
	m_titleScrMat[0] = Math::Matrix::Identity;
	m_titleScrMat[1] = Math::Matrix::Identity;

	// プレイヤー
	m_player = std::make_shared<Player>();
	m_player->SetOwner(this);
	m_player->Init(m_pNowAnim);
	m_player->SetTexture("Data/Texture/Player/player384x1280.png");

	CreatePlayerAB(m_player);
}

void Scene::InitGame1()
{
	m_gameOverFlg = false;
	m_score = 0;
	m_playerLife = 3;
	m_bombNum = 3;
	m_bossFlg = 0;

	m_frame = 0;
	m_min = 0;
	m_sec = 0;

	// ターゲット
	m_targetNum = 0;

	// UI
	m_UI = std::make_shared<UI>();
	m_UI->SetOwner(this);
	m_UI->Init();
	m_UITex.Load("Data/Texture/UI/UI-0.png");
	m_UI->SetTexture0(&m_UITex);
	m_UI->SetPlayerTex("Data/Texture/Player/player384x1280.png");
	m_UI->SetGameOverTex("Data/Texture/Misc/GameOver.png");

	// パーティクル
	m_particleTex.Load("Data/Texture/Particle/particle0.png");

	// プレイヤー
	m_player = std::make_shared<Player>();
	m_player->SetOwner(this);
	m_player->Init(m_pNowAnim);
	m_player->SetTexture("Data/Texture/Player/player384x1280.png");

	CreatePlayerAB(m_player);

	// 弾
	m_bullet0Tex.Load("Data/Texture/Bullet/bullet-100x100.png");
	m_player->SetBullet0Tex(&m_bullet0Tex);

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
	//CreateEnemy(0);
	// ボスを生成
	//CreateBoss({ 0.0f, 0.0f }, 0);

	// マップ
	m_map = std::make_shared<Map>();
	m_map->SetOwner(this);
	m_map->Init();
	m_mapTex[0].Load("Data/Texture/Map/MiniWorld1280x720.png");
	m_mapTex[1].Load("Data/Texture/Map/Desert01.png");
	m_mapTex[2].Load("Data/Texture/Map/world.png");
	m_map->SetImg0(&m_mapTex[0]);
	m_map->SetImg1(&m_mapTex[1]);
	m_map->SetLargeMapTex(&m_mapTex[2]);

	// ●
	m_MaruTex.Load("Data/Texture/Misc/Maru360x360.png");
}

void Scene::InitResult()
{
	m_frame = 0;

	// ===== スコア ===================================================
	m_NumberTex.Load("Data/Texture/Misc/number.png");
	zeroFlg = false;
	d_numFont = 0;
	digit = 0;
	for (int i = 0; i < Max_digit; i++) d_num[i] = 0;
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
	for (int i = 0; i < 3; i++)
	{
		m_mapTex[i].Release();
	}

	// パーティクル
	m_particleTex.Release();

	// UI
	m_UITex.Release();
}

void Scene::ReleaseTitle()
{
	m_titleTex0.Release();
	m_titleTex1.Release();
	m_titleTex2.Release();
	
}

void Scene::ReleaseGame1()
{

}

void Scene::ReleaseResult()
{
	m_resultTex.Release();
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
		ImGui::Text("FPS:%d", APP.m_fps);

		//Math::Vector4 _DebugColor = m_player->GetDebugColor();

		if (nowScene == SceneType::Title)
		{
			switch (m_debugNowPage)
			{
			case 0:
				ImGui::Text(u8"いろいろ");

				break;

			case 1:

				break;

			case 2:

				break;

			default:
				ImGui::Text(u8"There's nothing here, yet\n[このページにはまだ何も有馬温泉]");
				break;
			}
		}
		if (nowScene == SceneType::Game1)
		{
			if (m_frame % (60 * 60) == 0) m_min++;
			if (m_frame % 60 == 0) m_sec++;

			switch (m_debugNowPage)
			{
			case 0:
				ImGui::Text(u8"いろいろ"); ImGui::SameLine();
				ImGui::Checkbox(":Debug", &m_debugFlg);
				ImGui::Text("m_frame:[%d] TIME:[%02d:%02d]", m_frame, m_min, m_sec);
				//ImGui::Text("PBullet[%d] Item[%d]", m_player->GetBulletNum(), m_itemList.size());
				ImGui::Text("Enemy.size[%d] BulletList.size[%d]", m_enemyList.size(), m_bulletList.size());
				ImGui::Text("PShootFlg:%d PShootTime:%d", m_player->GetShootFlg(), m_player->GetShootTime());
				ImGui::SliderInt("beamNum", &beamNum, 0, 300, "%d");
				ImGui::SliderFloat("beamDeg", &beamDeg, 0.0f, 720.0f);
				break;

			case 1:
				ImGui::Text(u8"[プレイヤー関連]");

				// フレームとか変数
				ImGui::Text("m_frame:%.1f", m_player->GetFrame0());

				ImGui::Text("hLaser.size:%d", m_hLaserList.size());

				// プレイヤーの移動速度
				ImGui::Text("moveVec : %.2f, %.2f", m_player->GetMoveVec().x, m_player->GetMoveVec().y);

				// プレイヤー切り取り範囲
				ImGui::Text("NowAnim:");
				ImGui::SameLine();
				if (ImGui::Button("-")) m_player->AddNowAnim(0, -1);
				ImGui::SameLine();
				if (ImGui::Button("+")) m_player->AddNowAnim(0, +1);

				// プレイヤーの色
				//ImGui::ColorEdit4("PlayerColor", &m_playerColor.x);
				//m_player->SetPColor(m_playerColor);

				break;

			case 2:
				ImGui::Text(u8"[ウェブ関連]");
				// サイズ
				ImGui::Text("Length:%.1f", m_player->GetWebBsize());
				// 角度
				ImGui::Text("Deg:%.1f", m_player->GetWebBdegAdd());
				// 色
				//ImGui::SliderFloat("DebugColor:R", &_DebugColor.x, 0.0f, 1.0f);
				//ImGui::SliderFloat("DebugColor:G", &_DebugColor.y, 0.0f, 1.0f);
				//ImGui::SliderFloat("DebugColor:B", &_DebugColor.z, 0.0f, 1.0f);
				//ImGui::SliderFloat("DebugColor:A", &_DebugColor.w, 0.0f, 1.0f);

				//ImGui::Text("webA.deg:%.2f", m_player->m_webA.degMove);
				break;

			case 3:
				ImGui::Text(u8"[マップ関連]");
				ImGui::SliderInt("nowTex", &m_map->m_nowTex, 0, 1);
				break;

			case 4:
				ImGui::Checkbox(u8":加算合成", &AddBlend);
				ImGui::Text("ParticleList.size[%d]", m_particleList.size());
				ImGui::Text("abParticleList.size[%d]", m_abParticleList.size());
				ImGui::SliderFloat("LightHSize", &LightHSize, 0.0f, 100.0f, "%.2f");
				break;
			case 5:
				ImGui::Text(u8"[UI関連]");

			default:
				ImGui::Text(u8"There's nothing here, yet\n[このページにはまだ何も有馬温泉]");
				break;
			}
		}
		if (nowScene == SceneType::Result)
		{
			switch (m_debugNowPage)
			{
			case 0:
				ImGui::Text(u8"いろいろ");
				ImGui::Text("frame[%d]", m_frame);
				break;

			case 1:

				break;

			case 2:

				break;

			default:
				ImGui::Text(u8"There's nothing here, yet\n[このページにはまだ何も有馬温泉]");
				break;
			}
		}
	}
	ImGui::End();
}

void Scene::UpdateEnemyTL()
{
	if (m_sceneFlg == 0)
	{
		if (m_frame > (60*60))
		{
			m_min += 1;
		}
		if (m_frame % 60 == 0)
		{
			m_sec += 1;
		}

		switch (m_frame)
		{
		// - - - - - - - - - - [00:00] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		case 60 * 0:
			break;

		case 60 * 1:

			break;

		case 60 * 2:
			CreateEnemy({ -250.0f, 370.0f }, ep_5, 80);
			CreateEnemy1({   0.0f, 370.0f }, ep_5, 60);
			CreateEnemy({ +250.0f, 370.0f }, ep_5, 50);
			break;

		case 60 * 3:
			//CreateEnemy({ -100.0f, 370.0f }, ep_1, 50);	// 下→左
			break;

		case 60 * 4:
			CreateEnemy({ -100.0f, 370.0f }, ep_1, 50);
			break;
		// - - - - - - - - - - [00:05] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
		case 60 * 5:

			break;

		case 60 * 6:
			CreateEnemy({ 100.0f, 370.0f }, ep_2, 50);	// 下→右
			break;

		case 60 * 7:
			//CreateEnemy({ 100.0f, 370.0f }, ep_2, 50);
			break;

		case 60 * 8:
			CreateEnemy({ 100.0f, 370.0f }, ep_2, 50);
			break;

		case 60 * 9:

			break;
		// - - - - - - - - - - [00:10] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 10:
			CreateEnemy1({ scrLeft + 110.0f, 370.0f }, ep_5, 75);	// 停止
			break;

		case 60 * 11:
			CreateEnemy({ scrLeft + 180.0f, 400.0f }, ep_5, 30);	// 停止
			break;

		case 60 * 12:
			CreateEnemy1({ scrRight - 110.0f, 370.0f }, ep_5, 75);	// 停止
			break;

		case 60 * 13:
			CreateEnemy({ scrRight - 180.0f, 400.0f }, ep_5, 30);	// 停止
			break;

		case 60 * 14:
			CreateEnemy({ 0.0f, 370.0f }, ep_5, 50);	// 上から下
			break;
		// - - - - - - - - - - [00:15] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 15:

			break;

		case 60 * 16:
			CreateEnemy({ scrLeft + 200.0f, 370.0f }, ep_2, 50);	// 右へ
			break;

		case 60 * 17:
			CreateEnemy({ scrLeft + 200.0f, 370.0f }, ep_2, 50);
			break;

		case 60 * 18:

			break;

		case 60 * 19:
			CreateEnemy({ scrRight - 200.0f, 370.0f }, ep_1, 50);
			break;
		// - - - - - - - - - - [00:20] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 20:

			break;

		case 60 * 21:
			CreateEnemy({ scrRight - 200.0f, 370.0f }, ep_1, 50); // 左へ
			break;

		case 60 * 22:

			break;

		case 60 * 23:
			CreateEnemy({ scrLeft - 64.0f, 200.0f }, ep_3, 90);	// 左から右へ
			CreateEnemy1({ scrLeft+ 200.0f, 370.0f }, ep_5, 60);
			break;

		case 60 * 24:

			break;
		// - - - - - - - - - - [00:25] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 25:
			CreateEnemy1({ scrLeft - 64.0f, 280.0f }, ep_3, 90);	// 左から右へ
			CreateEnemy({ scrRight - 200.0f, 370.0f }, ep_5, 60);
			break;

		case 60 * 26:

			break;

		case 60 * 27:
			CreateEnemy({ scrRight + 64.0f, 200.0f }, ep_4, 90);	// 左から右へ
			break;

		case 60 * 28:

			break;

		case 60 * 29:
			// 並べて配置
			CreateEnemy({ scrLeft + 150.0f, 370.0f }, ep_5, 80);
			CreateEnemy1({ scrLeft + 350.0f, 450.0f }, ep_5, 80);
			CreateEnemy1({ scrLeft + 640.0f, 450.0f }, ep_5, 80);
			CreateEnemy1({ scrRight - 350.0f, 450.0f }, ep_5, 80);
			CreateEnemy({ scrRight - 150.0f, 370.0f }, ep_5, 80);
			break;
		// - - - - - - - - - - [00:30] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 30:

			break;

		case 60 * 31:
			CreateEnemy1({ -200.0f, 370.0f }, ep_5, 70);	// 停止
			CreateEnemy1({ +200.0f, 370.0f }, ep_5, 70);	// 停止
			break;

		case 60 * 32:
			CreateEnemy({ scrRight + 64.0f, 280.0f }, ep_4, 90);	// 左から右へ
			break;

		case 60 * 33:
			CreateEnemy1({ scrLeft + 100.0f, 370.0f }, ep_5, 70);	// 停止
			CreateEnemy1({ scrRight - 200.0f, 370.0f }, ep_5, 70);	// 停止
			break;

		case 60 * 34:
			CreateEnemy1({ -200.0f, 370.0f }, ep_5, 60);	// 停止
			CreateEnemy1({ +200.0f, 370.0f }, ep_5, 60);	// 停止
			break;
		// - - - - - - - - - - [00:35] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 35:
			CreateEnemy({ scrRight + 64.0f, 200.0f }, ep_4, 60);
			break;

		case 60 * 36:
			CreateEnemy({ scrLeft - 64.0f, 300.0f }, ep_3, 60);
			break;

		case 60 * 37:
			CreateEnemy({ scrLeft - 64.0f, 200.0f }, ep_6, 90);	// 左から右へ
			break;

		case 60 * 38:
			CreateEnemy1({ -200.0f, 370.0f }, ep_5, 60);	// 停止
			CreateEnemy1({ +200.0f, 370.0f }, ep_5, 60);	// 停止
			break;

		case 60 * 39:
			CreateEnemy({ scrRight + 64.0f, 300.0f }, ep_7, 90);	// 右から左へ
			break;
		// - - - - - - - - - - [00:40] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 40:
			CreateEnemy({ 200.0f, 370.0f }, ep_5, 70);	// 上から下→停止
			break;

		case 60 * 41:
			CreateEnemy1({ scrLeft + 150.0f, 370.0f }, ep_8, 80);	// 左から右
			CreateEnemy1({ scrRight - 150.0f, 370.0f }, ep_9, 80);	// 右から左
			break;

		case 60 * 42:
			CreateEnemy1({ -200.0f, 370.0f }, ep_5, 50);	// 上から下→停止
			break;

		case 60 * 43:

			break;

		case 60 * 44:
			CreateEnemy({ scrLeft - 64.0f, 200.0f }, ep_3, 60);
			break;
		// - - - - - - - - - - [00:45] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 45:
			CreateEnemy({ scrLeft - 64.0f, 300.0f }, ep_4, 60);
			break;

		case 60 * 46:
			CreateEnemy({ -200.0f, 370.0f }, ep_5, 60);	// 停止
			CreateEnemy({ +200.0f, 370.0f }, ep_5, 60);	// 停止
			break;

		case 60 * 47:
			CreateEnemy1({ scrLeft - 64.0f, 250.0f }, ep_3, 60);
			break;

		case 60 * 48:
			CreateEnemy1({ scrRight - 64.0f, 300.0f }, ep_4, 60);
			break;

		case 60 * 49:
			CreateEnemy({ 0.0f, 370.0f }, ep_5, 60);
			break;
		// - - - - - - - - - - [00:50] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 50:
			// 並べて配置
			CreateEnemy({ scrLeft + 150.0f, 370.0f }, ep_5, 80);
			//CreateEnemy1({ scrLeft + 300.0f, 450.0f }, ep_5, 80);
			CreateEnemy1({ scrLeft + 640.0f, 450.0f }, ep_5, 80);
			//CreateEnemy1({ scrRight - 150.0f, 370.0f }, ep_5, 80);
			CreateEnemy({ scrRight - 350.0f, 370.0f }, ep_5, 80);
			break;

		case 60 * 51:

			break;

		case 60 * 52:

			break;

		case 60 * 53:
			CreateEnemy({ scrLeft - 64.0f, 200.0f }, ep_6, 70);	// 左から右へ
			break;

		case 60 * 54:
			CreateEnemy({ scrRight + 64.0f, 200.0f }, ep_7, 70);	// 右から左へ
			break;
		// - - - - - - - - - - [00:55] - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
		case 60 * 55:
			// 並べて配置
			CreateEnemy({ scrLeft + 150.0f, 370.0f }, ep_5, 80);
			//CreateEnemy1({ scrLeft + 350.0f, 450.0f }, ep_5, 80);
			CreateEnemy1({ scrLeft + 640.0f, 450.0f }, ep_5, 80);
			//CreateEnemy1({ scrRight - 350.0f, 450.0f }, ep_5, 80);
			CreateEnemy({ scrRight - 150.0f, 370.0f }, ep_5, 80);
			break;

		case 60 * 56:
			//CreateEnemy({ scrRight + 100.0f, 370.0f }, ep_4, 70);
			//CreateEnemy({ scrRight + 200.0f, 370.0f }, ep_4, 70);
			break;

		case 60 * 57:

			break;

		case 60 * 58:

			break;

		case 60 * 59:
			m_sceneFlg = 4;
			m_frame = 0;
			break;


		// ===== １分３０秒 ===================================================
		case 60 * (60 + 30) :
			//CreateBoss({ -100.0f, 100.0f }, 1);
			//m_bossFlg = 1;
			break;


		}

	}
}

void Scene::UpdateDebugEnemy()
{
	// 敵push_back
	if (GetKey(VK_NUMPAD0))
	{
		if (!keyFlg[k_np_0])
		{
			for (int i = 0; i < 3; i++)
			{
				CreateEnemy1({ -300.0f + i * 300.0f, 150.0f }, 0, 60);
			}
		}
		keyFlg[k_np_0] = true;
	}
	else
	{
		keyFlg[k_np_0] = false;
	}

	// デバッグキー（スコアを０にする）
	if (GetAsyncKeyState('0') & 0x80000)
	{
		if (!keyFlg[k_0])
		{
			m_score = 0;
		}
		keyFlg[k_0] = true;
	}
	else
	{
		keyFlg[k_0] = false;
	}

	// デバッグキー１
	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (!keyFlg[k_1])
		{
			DebugKey1();
		}
		keyFlg[k_1] = true;
	}
	else
	{
		keyFlg[k_1] = false;
	}
	// デバッグキー２
	if (GetAsyncKeyState('2') & 0x8000)
	{
		if (!keyFlg[k_2])
		{
			DebugKey2();
		}
		keyFlg[k_2] = true;
	}
	else
	{
		keyFlg[k_2] = false;
	}
	//デバッグキー３
	if (GetAsyncKeyState('3') & 0x8000)
	{
		if (!keyFlg[k_3])
		{
			DebugKey3();
		}
		keyFlg[k_3] = true;
	}
	else
	{
		keyFlg[k_3] = false;
	}
	// デバッグ（ボム増やす）
	if (GetAsyncKeyState('L') & 0x8000)
	{
		if (!keyFlg[k_l])
		{
			if (m_bombNum < 9)
			{
				m_bombNum++;
			}
		}
		keyFlg[k_l] = true;
	}
	else
	{
		keyFlg[k_l] = false;
	}
	// デバッグ（残機増やす）
	if (GetAsyncKeyState('O') & 0x8000)
	{
		if (!keyFlg[k_o])
		{
			if (m_playerLife < 9)
			{
				m_playerLife++;
			}
		}
		keyFlg[k_o] = true;
	}
	else
	{
		keyFlg[k_o] = false;
	}
}

void Scene::DebugKey1()
{
	//CreateEnemy({ scrLeft +  160.0f, scrTop -  200.0f }, ep_stop);
	CreateEnemy({ scrLeft +  300.0f, scrTop -  115.0f }, ep_stop, 40);
	CreateEnemy({ scrLeft +  490.0f, scrTop -   82.0f }, ep_stop, 35);

	CreateEnemy({ scrLeft +  711.0f, scrTop -   71.0f }, ep_stop, 45);

	CreateEnemy({ scrLeft +  900.0f, scrTop -   91.0f }, ep_stop, 30);
	CreateEnemy({ scrLeft + 1045.0f, scrTop -  145.0f }, ep_stop, 40);
	//CreateEnemy({ scrLeft + 1160.0f, scrTop -  230.0f }, ep_stop);
}

void Scene::DebugKey2()
{
	CreateEnemy({ scrLeft + 300.0f, scrTop - 170.0f }, ep_d1, 40);
	CreateEnemy({ scrLeft + 600.0f, scrTop - 200.0f }, ep_d1, 30);
	CreateEnemy({ scrLeft + 900.0f, scrTop - 170.0f }, ep_d1, 40);

	CreateEnemy({ scrLeft + 100.0f, scrTop - 60.0f }, ep_d1, 40);
	CreateEnemy({ scrLeft + 400.0f, scrTop - 100.0f }, ep_d1,30);
	CreateEnemy({ scrLeft + 700.0f, scrTop - 60.0f }, ep_d1, 40);

	CreateEnemy({ scrLeft + 150.0f, scrTop - 400.0f }, ep_d2, 30);
	CreateEnemy({ scrRight - 150.0f, scrTop - 400.0f }, ep_d2, 40);
}

void Scene::DebugKey3()
{
	CreateEnemy1({ scrLeft + 300.0f, scrTop }, ep_5, 35);
}


void Scene::DrawNumber(int x, Math::Vector2 num_Pos, int s)
{
	digit = (int)log10(x);	// 桁数
	if (x <= 0) digit = 0;	// これがないとなぜか-114514になるので追加

	//d_num[7] = x / 10000000; // 一千万

	//x -= d_num[7] * 10000000;

	d_num[6] = x / 1000000; // 百万

	x -= d_num[6] * 1000000;

	d_num[5] = x / 100000; // 十万

	x -= d_num[5] * 100000;

	d_num[4] = x / 10000; // 一万

	x -= d_num[4] * 10000;

	d_num[3] = x / 1000; // 千

	x -= d_num[3] * 1000;

	d_num[2] = x / 100; // 百

	x -= d_num[2] * 100;

	d_num[1] = x / 10; // 十

	x -= d_num[1] * 10;

	d_num[0] = x; //一

	zeroFlg = false;

	switch (s)
	{
	case 0:

		//for (int i = 0; i < Max_digit; i++)
		for (int i = 0; i <= digit; i++)
		{
			//if (d_num[i] > 0) zeroFlg = true;

			//if (zeroFlg == true)
			{
				Math::Matrix l_smat = Math::Matrix::CreateScale(1.25f);
				Math::Matrix l_mat = l_smat * Math::Matrix::CreateTranslation(num_Pos.x + i * -40, num_Pos.y, 0);
				DrawImg(l_mat, &m_NumberTex, Math::Rectangle(d_num[i] * 40, 0, 40, 60), 1.0f);
			}
		}
		break;
	case 1:

		for (int i = 0; i < 6; i++)
		{
			Math::Matrix l_smat = Math::Matrix::CreateScale(1.25f);
			Math::Matrix l_mat = l_smat *  Math::Matrix::CreateTranslation(num_Pos.x + i * (-40.0f * 1.25f), num_Pos.y, 0);
			DrawImg(l_mat, &m_NumberTex, Math::Rectangle(d_num[i] * 40, 0, 40, 60), 1.0f);
		}
		break;
	}
}