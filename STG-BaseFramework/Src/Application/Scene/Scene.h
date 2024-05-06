#pragma once

#include "../utility.h"

#include "../Object/Attack/Beam/beam0.h"	// ビーム

#include "../Object/Attack/Bullet/bullet0.h"	// 弾

#include "../Object/Item/item.h"	// アイテム

#include "../Hit/Hit.h"	// 当たり判定

class Player;
class HLaser;
class PlayerAB;

class Bullet1;
class Bomb;

class Enemy;
class Boss;

class ParticleBase;

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

	// ターゲット
	int m_targetNum;

	// シーン管理用変数
	SceneType nowScene;
	char nowSceneStr[100] = "";
	Math::Color SceneFadeColor;

	// デバッグ
	bool	m_bShowDebugWindow = false;
	bool	m_debugFlg = 0;
	int		m_debugNowPage = 0;

	// マウス座標関連
	bool m_bGetMousePos = true;
	POINT m_mousePos;

	// フレーム数
	int m_frame = 0;

	// タイトル
	Math::Matrix m_titleMat;	// 行列 
	KdTexture m_titleTex0;		// Press Enter
	KdTexture m_titleTex1;		// Ray Seeker
	KdTexture m_titleTex2;		// 右のやつ

	// プレイヤー
	std::shared_ptr<Player> m_player;

	// プレイヤーの弾
	KdTexture	m_bullet0Tex;
	C_Beam0		m_beam;
	int			beamNum;
	float		beamDeg;
	//std::shared_ptr<PlayerAB> m_abParticle;	// 自機用アフターバーナー
	std::vector<std::shared_ptr<PlayerAB>> m_abParticleList;

	// ボム
	std::shared_ptr<Bomb>	m_bomb;
	std::vector<std::shared_ptr<Bomb>>	m_bombList;

	// 敵の弾
	// 弾
	std::vector<std::shared_ptr<Bullet1>>			m_bulletList;
	std::vector<std::shared_ptr<Bullet1>>::iterator m_bulletIt;
	KdTexture* m_pBullet1Tex;

	// 追尾レーザー
	std::vector<std::shared_ptr<HLaser>>	m_hLaserList;

	// アイテム
	std::vector<std::shared_ptr<C_Item>>	m_itemList;
	KdTexture	m_itemTex;

	// エネミー
	std::vector<std::shared_ptr<Enemy>>		m_enemyList;
	KdTexture	m_enemyTex;

	// ボス
	std::shared_ptr<Boss>					m_boss;
	KdTexture								m_bossTex;

	// パーティクル
	std::vector<std::shared_ptr<ParticleBase>>	m_particleList;	// 全パーティクルのリスト
	KdTexture	m_particleTex;

	// マップ
	std::shared_ptr<Map>	m_map;
	KdTexture				m_mapTex[3];

	// UI
	std::shared_ptr<UI>		m_UI;
	KdTexture				m_UITex;

	// ●
	KdTexture	m_MaruTex;

	// 当たり判定
	C_Hit		m_hit;

public:

	// 残機
	int m_playerLife = 3;

	// ボム
	int			m_bombNum = 0;

	// スコア
	int m_score;
	void AddScore(int _num) { m_score += _num; }

	// フラグ
	bool	m_gameOverFlg = false;	// ゲームオーバー
	bool	keyFlg[k_end];			// キーフラグ
	bool	AddBlend = true;		// 加算合成
	float	LightHSize = 1.8f;		// 追尾弾の光のサイズ

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

	// 敵出す用
	void UpdateEnemyTL();

	// デバッグ用
	void UpdateDebugEnemy();
	void DebugKey1();
	void DebugKey2();
	void DebugKey3();

	// 弾関連
	void DeleteBullet1();
	void CreateBullet1(Math::Vector2 _pos, float _deg);

	// ゲッター
	int	GetTargetNum() { return m_targetNum; }
	int GetLockOnNum();
	int GetPlayerLife() { return m_playerLife; }
	float GetPlayerRollVal();
	float GetPlayerRollValMax();
	Math::Vector2 GetPlayerNowAnim();
	Math::Color GetPlayerDColor();
	std::shared_ptr<Player> GetPlayer() { return m_player; }

	// セッター
	void SetAllLock(int _flg);

	// ポインタ関連
	void CreateEnemy(Math::Vector2 _pos, int _flg);		// 敵出現 (あぱっち)
	void CreateEnemy1(Math::Vector2 _pos, int _flg);	// 敵出現 (おすぷれい)

	void CreateBoss(Math::Vector2 _pos, int _flg);		// ボス出現
	void ResetBoss();									// ボスクリア

	void CreateItem(Math::Vector2 _pos, int _flg);		// アイテム出現 
	void CreateHLaser(Math::Vector2 _pos, float _deg);	// 追尾レーザー出現
	void ShotBomb(Math::Vector2 _ppos, int _flg);		// ボム発射

	void EraseAll();

	// パーティクル
	void CreateLightH(std::shared_ptr<BaseObject> _pair, int _type);			// 追尾レーザーの光
	void CreateHLTrail(Math::Vector2 _pos, float _deg, Math::Color _color);		// 追尾レーザーの軌道
	void CreateParticle(ParticleType _type, Math::Vector2 _pos);				// ？
	void CreateExplosionA(ParticleType _type, Math::Vector2 _pos);				// 爆発
	//void CreateLightH(std::shared_ptr<HLaser> _pair);							// ？
	void CreatePlayerAB(std::shared_ptr<BaseObject> _obj);						// プレイヤーAB
	void CreatePShadow(Math::Vector2 _pos);										// プレイヤー高速移動時の影
	void MakeShockWave(Math::Vector2 _pos);										// 衝撃波
	void CreateMSLTrail(Math::Vector2 _pos);									// ミサイルの軌道

	void DrawPlayerAB();

	C_Beam0* GetBeam() { return &m_beam; }

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