#pragma once

#define C_RED Math::Color(1.0f, 0.0f, 0.0f, 1.0f);
#define C_GREEN Math::Color(0.0f, 1.0f, 0.0f, 1.0f);
#define C_BLUE Math::Color(0.0f, 0.0f, 1.0f, 1.0f);
#define C_BLACK Math::Color(0.0f, 0.0f, 0.0f, 1.0f);
#define C_WHITE Math::Color(1.0f, 1.0f, 1.0f, 1.0f);
#define C_SELECTR Math::Color(1.0f, 0.7f, 0.7f, 1.0f);
#define C_SELECTG Math::Color(0.7f, 1.0f, 0.7f, 1.0f);
#define C_SELECTB Math::Color(0.7f, 0.7f, 1.0f, 1.0f);

// ��ʍ��W�֌W
static const int scrWidth = 640*2;
static const int scrHeight = 360*2;
static const float scrLeft = -scrWidth / 2;
static const float scrRight = scrWidth / 2;
static const float scrTop = scrHeight / 2;
static const float scrBottom = -scrHeight / 2;

enum keynum
{
	key_I,
	key_M,
	key_Left,
	key_Right,
	key_Up,
	key_Down,
	key_LBUTTON,
	key_RBUTTON,
	key_MBUTTON,
	key_End
};

enum Dir
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

enum BaseBitState
{
	st_dead		= 0,				// ��A�N�e�B�u
	st_alive	= 1 << 1,		// �A�N�e�B�u
	st_stat1	= 1 << 2,		// �t���O�P

};

struct image
{
	Math::Vector2 pos;
	Math::Vector2 move;
	Math::Vector2 size;
	float		  deg;

	Math::Matrix  smat;
	Math::Matrix  rmat;
	Math::Matrix  tmat;
	Math::Matrix  mat;
	KdTexture*	  Tex1;
	KdTexture*	  Tex2;
};

struct ImgPosSize
{
	Math::Vector2	pos;
	Math::Vector2	size;
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

struct HitStruct
{
	Math::Vector2	pos;
	Math::Vector2	rad;

	UINT			flg;
};

// ���������W�A���ɕϊ��i�錾�j
float DegToRad(float a_deg);

// 0.0�`1.0�̗����擾
float Rnd();

// �L�[��Ԏ擾
bool GetKey(int key);

// �}�E�X���W�擾�p
void GetMousePos2(POINT* apMousePos);

// �����񂪐����������ǂ����`�F�b�N
bool isInt(std::string s);

// ==== ����̕`��n�֐� =============================

void ResetMatrix();

// �P�s�ŉ摜�`��錾 ( �s��, �e�N�X�`��, �؂���͈�, �A���t�@�l)
void DrawImg(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, float a_alpha);

// �P�s�ŐF�t���摜�`�� (�s��, �e�N�X�`��, �؂���͈�, �F)
void DrawImgEX(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, Math::Color a_color);

//�Z�`��
void DrawMaru(float x, float y, float rad, Math::Color* color, bool nuri);

//���`��
void DrawSankaku(float x1, float y1, float x2, float y2, float x3, float y3, Math::Color* color, bool nuri);

//���`��
void DrawHako(float x, float y, float xs, float ys, Math::Color* color, bool nuri);

//���`��
void DrawSen(float x, float y, float xx, float yy, Math::Color* color);

//�_�`��
void DrawTen(float x, float y, Math::Color* color);

//�����`��@����(X, Y, ����, �F(R,G,B,A), �e��t���邩�ǂ���)
void DrawMoji(float x, float y, char* p_str, Math::Color* color, bool Shadow = false);

// �}�`�`��Ńo�[�\�� ���n�[�t�T�C�Y�ł͂Ȃ��̂Œ���
// x, y, xs, ys, Value, MaxV, MinV, aColor, bFill
void DrawBar(float x, float y, float xs, float ys, float Value, float MaxV, Math::Color* aColor, bool bFill, Dir dir = Dir::Right, bool bDebug = false);