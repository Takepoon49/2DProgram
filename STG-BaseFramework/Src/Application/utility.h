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

// ��ʍ��W�֌W
static const int scrWidth = 640*2;
static const int scrHeight = 360*2;
static const float scrLeft = -scrWidth / 2;
static const float scrRight = scrWidth / 2;
static const float scrTop = scrHeight / 2;
static const float scrBottom = -scrHeight / 2;
static const float scrGap = 10.0f;

enum E_keyFlg
{
	k_return,
	k_tab,
	k_shift,
	k_i,
	k_l,
	k_h,
	k_z,
	k_x,
	k_c,
	k_up,
	k_down,
	k_left,
	k_right,
	k_1,
	k_2,
	k_3,
	k_4,
	k_5,
	k_6,
	k_7,
	k_8,
	k_9,
	k_0,
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
	k_any2,	// ctrl + 'd'
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

enum class ObjType
{
	Base,
	Player,
	Enemy,
	Enemy1
};

enum class ParticleType
{
	PlayerAB,	// �v���C���[�A�t�^�[�o�[�i�[
	PShadow,	// �v���C���[�����ړ����̉e
	ExplosionA,	// �����P
	HLTrail,	// �ǔ��e�O��	
	MSLTrail,	// �~�T�C���̋O��
	Light0,		// �ǔ��e��
	Test		// ���g�p
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
	st_dead		= 0,			// ��A�N�e�B�u
	st_alive	= 1 << 1,		// �A�N�e�B�u
	st_stat1	= 1 << 2,		// �t���O�P
	st_stat2	= 1 << 3
};

enum EnemyPattern
{
	ep_stop,	// �f�o�b�O�p �����Ȃ����
	ep_d1,		// ���E�ɃT�C���J�[�u�ňړ�
	ep_d2,		// ���邮����G
	ep_1,		// ������
	ep_2,		// �����E
	ep_3,		// ������E�Ƀ��[�v
	ep_4,		// �E���獶�Ƀ��[�v
	ep_5,		// �ォ�牺�Ƀ��[�v
	ep_6,		// �������Ƀ��[�v
	ep_7,		// 
	ep_8,		// 
	ep_9,		// 
	ep_10,		// 
	ep_end
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