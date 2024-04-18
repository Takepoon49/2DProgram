#pragma once

typedef unsigned int UINT;

#include "../utility.h"

#include "../Object/Player/player.h"

#include "../Object/Enemy/enemy.h"

#include "../Object/Attack/Beam/beam0.h"

#include "../Object/Attack/Bullet/bullet0.h"

#include "../Object/Map/map.h"

#include "../Object/Item/item.h"

#include "../Object/Hit/Hit.h"

class EnemyBase;

enum SceneType
{
	S_Title,
	S_Game1,
	S_Scene2,
	S_End
};

class Scene
{
private:

	bool abool;

	// シーン管理用変数
	SceneType nowScene;
	char nowSceneStr[100] = "";
	Math::Color SceneFadeColor;

	// デバッグ
	bool	m_debugFlg = 0;
	int		m_debugNowPage = 0;

	// キーフラグ
	bool keyFlg[key_End];

	// マウス座標関連
	bool bGetMousePos = true;

	//フレーム数
	int frame;

	// プレイヤー
	C_Player	m_player;
	KdTexture	m_playerTex;

	// 弾
	KdTexture	m_bullet0Tex;
	
	C_Beam0		m_beam;
	int			beamNum;
	float		beamDeg;

	// アイテム
	std::vector<C_Item*> m_itemList;
	std::vector <C_Item*>::iterator m_itemIt;
	KdTexture	m_itemTex;

	// エネミー
	C_Enemy		m_enemy;
	KdTexture	m_enemyTex;

	// 敵の可変長の継承
	std::vector<EnemyBase*>	m_enemyAList;
	std::vector <EnemyBase*>::iterator m_enemyAIt;
	//std::shared_ptr<EnemyBase>	m_enemyA;

	// マップ
	C_Map		m_map;
	KdTexture	m_mapTex;

	// ●
	KdTexture	m_MaruTex;

	// 当たり判定
	C_Hit		m_hit;

public:
	
	// デバッグ
	bool GetDebugFlg() { return m_debugFlg; }

	// キーフラグ
	bool GetKeyFlg(int num) { return keyFlg[num]; }
	void SetKeyFlg(int num, bool tf) { keyFlg[num] = tf; }

	// 初期設定
	void Init();
	void InitGame1();

	// 解放
	void Release();
	void ReleaseGame1();

	// 更新処理
	void Update();
	void CheckGame1Vec();
	void UpdateGame1();

	// 描画処理
	void Draw2D();
	void DrawGame1();

	void DrawString(SceneType nowScene);
	void DrawFilledMaru(float x, float y, float rad, Math::Color);

	// ゲッター
	C_Player* GetPlayer() { return &m_player; }

	C_Beam0* GetBeam() { return &m_beam; }
	
	C_Enemy* GetEnemy() { return &m_enemy; }
	
	C_Item* GetItem(int num) { return m_itemList[num]; }
	
	C_Map* GetMap() { return &m_map; }

	C_Hit* GetHit() { return &m_hit; }

	// GUI処理
	void ImGuiUpdate();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
