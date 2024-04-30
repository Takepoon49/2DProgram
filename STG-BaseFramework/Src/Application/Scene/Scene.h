#pragma once

#include "../utility.h"

#include "../Object/Attack/Beam/beam0.h"	// ビーム

#include "../Object/Attack/Bullet/bullet0.h"	// 弾

#include "../Object/Item/item.h"	// アイテム

#include "../Object/Hit/Hit.h"	// 当たり判定


class Player;
class C_Enemy;
class EnemyBase;
class EnemyA;
class Explosion;
class Map;
class UI;

enum class SceneType
{
	Title,
	Game1,
	Result
};

class Scene
{
private:

	// シーン管理用変数
	SceneType nowScene;
	char nowSceneStr[100] = "";
	Math::Color SceneFadeColor;

	// デバッグ
	bool	m_bShowDebugWindow = false;
	bool	m_debugFlg = 0;
	int		m_debugNowPage = 0;

	// マウス座標関連
	bool bGetMousePos = true;
	// フレーム数
	int frame;
	// スコア
	int	m_score;

	// プレイヤー
	std::shared_ptr<Player>		m_player;
	int			m_playerNowAnimY = 0;
	Math::Color m_playerColor = C_WHITE;

	// 弾
	KdTexture	m_bullet0Tex;
	C_Beam0		m_beam;
	int			beamNum;
	float		beamDeg;

	// アイテム
	std::vector<std::shared_ptr<C_Item>>	m_itemList;
	KdTexture	m_itemTex;

	// エネミー
	std::vector<std::shared_ptr<C_Enemy>>	m_enemyList;
	KdTexture	m_enemyTex;

	// 敵の可変長の継承
	std::vector<std::shared_ptr<EnemyA>>	m_enemyAList;

	// パーティクル
	KdTexture	m_particleTex;

	// マップ
	std::shared_ptr<Map>	m_map;
	KdTexture	m_mapTex[2];

	// UI
	std::shared_ptr<UI>		m_UI;
	KdTexture	m_UITex;

	// ●
	KdTexture	m_MaruTex;

	// 当たり判定
	C_Hit		m_hit;

public:
	
	// キーフラグ
	bool keyFlg[255];

	// デバッグ
	bool GetDebugFlg() { return m_debugFlg; }

	// 初期設定
	void Init();
	// 更新処理
	void Update();
	// 描画処理
	void Draw2D();
	// 解放
	void Release();

	// タイトル
	void InitTitle();
	void UpdateTitle();
	void DrawTitle();
	void ReleaseTitle();
	
	// ゲーム１
	void InitGame1();
	void CheckGame1Vec();
	void UpdateGame1();
	void DrawGame1();
	void ReleaseGame1();

	// リザルト
	void InitResult();
	void UpdateResult();
	void DrawResult();
	void ReleaseResult();

	void DrawString(SceneType nowScene);
	void DrawFilledMaru(float x, float y, float rad, Math::Color);

	// ポインタ関連
	void CreateEnemy(int _flg);

	// (実体の)ゲッターか...あいつは良い奴だったよ...
	//Player* GetPlayer() { return &m_player; }

	C_Beam0* GetBeam() { return &m_beam; }
	
	//C_Enemy* GetEnemy() { return m_enemy; }
	
	//C_Item* GetItem(int num) { return m_itemList[num]; }
	
	//Map* GetMap() { return &m_map; }

	C_Hit* GetHit() { return &m_hit; }

	//UI* GetUI() { return &m_UI; }

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