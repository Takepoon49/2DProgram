#pragma once

#define C_RED Math::Color(1.0f, 0.0f, 0.0f, 1.0f);
#define C_GREEN Math::Color(0.0f, 1.0f, 0.0f, 1.0f);
#define C_BLUE Math::Color(0.0f, 0.0f, 1.0f, 1.0f);
#define C_YELLOW Math::Color(1.0f, 1.0f, 0.0f, 1.0f);
#define C_BLACK Math::Color(0.0f, 0.0f, 0.0f, 1.0f);
#define C_WHITE Math::Color(1.0f, 1.0f, 1.0f, 1.0f);
#define C_SELECTR Math::Color(1.0f, 0.7f, 0.7f, 1.0f);
#define C_SELECTG Math::Color(0.7f, 1.0f, 0.7f, 1.0f);
#define C_SELECTB Math::Color(0.7f, 0.7f, 1.0f, 1.0f);

// 画面座標関係
static const int scrWidth = 640*2;
static const int scrHeight = 360*2;
static const float scrLeft = -scrWidth / 2;
static const float scrRight = scrWidth / 2;
static const float scrTop = scrHeight / 2;
static const float scrBottom = -scrHeight / 2;

enum E_keyFlg
{
	k_tab,
	k_shift,
	k_z,
	k_x,
	k_c,
	k_up,
	k_down,
	k_left,
	k_right,
	k_np_0,
	k_np_1,
	k_np_2,
	k_np_3,
	k_np_4,
	k_np_5,
	k_np_6,
	k_np_7,
	k_np_8,
	k_np_9,
	k_any1,	// ctrl + '-'
	k_any2,
	k_any3,
	k_end
};

enum class Dir
{
	Up,
	Down,
	Left,
	Right
};

enum EColor
{
	red,
	green,
	blue
};

enum EParticle
{
	Pa_BulletHit,
	Pa_Bomb1,
	Pa_End
};

enum BaseBitState
{
	st_dead		= 0,				// 非アクティブ
	st_alive	= 1 << 1,		// アクティブ
	st_stat1	= 1 << 2,		// フラグ１

};

struct MathSet
{
	Math::Matrix	s;
	Math::Matrix	r;
	Math::Matrix	t;
	Math::Matrix	m;

	void			Init();
	Math::Matrix	Mix();
};

struct image
{
	Math::Vector2 pos;
	Math::Vector2 move;
	Math::Vector2 size;
	float		  deg;

	MathSet		  mat;
	KdTexture	  tex;
};

struct ImgPosSize
{
	Math::Vector2	pos;
	Math::Vector2	size;
};

struct HitStruct
{
	Math::Vector2	pos;
	Math::Vector2	rad;

	UINT			flg;
};

// 引数をラジアンに変換（宣言）
float DegToRad(float a_deg);

// 0.0～1.0の乱数取得
float Rnd();

// キー状態取得
bool GetKey(int key);

// マウス座標取得用
void GetMousePos2(POINT* apMousePos);

// 文字列が整数だけかどうかチェック
bool isInt(std::string s);

// ==== 自作の描画系関数 =============================

void ResetMatrix();

// １行で画像描画宣言 ( 行列, テクスチャ, 切り取り範囲, アルファ値)
void DrawImg(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, float a_alpha);

// １行で色付き画像描画 (行列, テクスチャ, 切り取り範囲, 色)
void DrawImgEX(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, Math::Color a_color);

//〇描画
void DrawMaru(float x, float y, float rad, Math::Color* color, bool nuri);

//△描画
void DrawSankaku(float x1, float y1, float x2, float y2, float x3, float y3, Math::Color* color, bool nuri);

//箱描画
void DrawHako(float x, float y, float xs, float ys, Math::Color* color, bool nuri);

//線描画
void DrawSen(float x, float y, float xx, float yy, Math::Color* color);

//点描画
void DrawTen(float x, float y, Math::Color* color);

//文字描画　引数(X, Y, 文字, 色(R,G,B,A), 影を付けるかどうか)
void DrawMoji(float x, float y, char* p_str, Math::Color* color, bool Shadow = false);

// 図形描画でバー表示 ※ハーフサイズではないので注意
// x, y, xs, ys, Value, MaxV, MinV, aColor, bFill
void DrawBar(float x, float y, float xs, float ys, float Value, float MaxV, Math::Color* aColor, bool bFill, Dir dir = Dir::Right, bool bDebug = false);