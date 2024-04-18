#include "main.h"	// utility�ł�APP�ɃA�N�Z�X�o����悤�ɂ��܂����B

#include "utility.h"

float DegToRad(float a_deg)
{
	return DirectX::XMConvertToRadians(a_deg);
}

float Rnd()
{
	return rand() / (float)RAND_MAX;
}

bool GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GetMousePos2(POINT* apMousePos)
{
	// �f�B�X�v���C��̃}�E�X���W���擾�i�f�B�X�v���C�̍��オ(0,0))
	GetCursorPos(apMousePos);	// �ϐ��̃A�h���X��n��

	// �w��̃E�B���h�E��}�E�X���W�ɕϊ��i�E�B���h�E�̍��オ(0,0))
	ScreenToClient(APP.m_window.GetWndHandle(), apMousePos);

	// �}�E�X�̍��W�n�����s�E�B���h�E�̍��W�n�ɕ␳����
	apMousePos->x -= scrWidth / 2;
	apMousePos->y -= scrHeight / 2;
	apMousePos->y *= -1;
}

bool isInt(std::string s)
{
	for (const char c : s)
	{
		if (c == '-') continue;		// �}�C�i�X���X�L�b�v

		if (isdigit(c) == 0)	// ������0�`9�̐�������Ȃ�������
		{
			return false;
		}
	}

	return true;
}

void ResetMatrix()
{
	//�s��̏����� (�}�`�`��̑O�ɏ���)
	SHADER.m_spriteShader.SetMatrix(DirectX::XMMatrixIdentity());
}

void DrawImg(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, float a_alpha)
{
	SHADER.m_spriteShader.SetMatrix(a_mat);
	SHADER.m_spriteShader.DrawTex(a_tex, a_rect, a_alpha);
}

void DrawImgEX(Math::Matrix a_mat, KdTexture* a_tex, Math::Rectangle a_rect, Math::Color a_color)
{
	SHADER.m_spriteShader.SetMatrix(a_mat);
	SHADER.m_spriteShader.DrawTex(a_tex, 0, 0, &a_rect, &a_color);
}

void DrawMaru(float x, float y, float rad, Math::Color* color, bool nuri)
{
	SHADER.m_spriteShader.DrawCircle(x, y, rad, color, nuri);
}

void DrawSankaku(float x1, float y1, float x2, float y2, float x3, float y3, Math::Color* color, bool nuri)
{
	SHADER.m_spriteShader.DrawTriangle(x1, y1, x2, y2, x3, y3, color, nuri);
}

void DrawHako(float x, float y, float xs, float ys, Math::Color* color, bool nuri)
{
	SHADER.m_spriteShader.DrawBox(x, y, xs, ys, color, nuri);
}

void DrawSen(float x, float y, float xx, float yy, Math::Color* color)
{
	SHADER.m_spriteShader.DrawLine(x, y, xx, yy, color);
}

void DrawTen(float x, float y, Math::Color* color)
{
	SHADER.m_spriteShader.DrawPoint(x, y, color);
}

void DrawMoji(float x, float y, char* p_str, Math::Color* color, bool Shadow)
{
	if (Shadow) SHADER.m_spriteShader.DrawString(x + 3.0f, y - 3.0f, p_str, Math::Vector4(0.1f, 0.1f, 0.1f, color->w));
	SHADER.m_spriteShader.DrawString(x, y, p_str, *color);
}

void DrawBar(float x, float y, float xs, float ys, float Value, float MaxV, Math::Color *aColor, bool bFill, Dir dir, bool bDebug)
{
	float diff = ((Value / MaxV) * xs) / 2.0f;

	//if ((Value / MaxV) > 1.0f) diff = (MaxV * xs) / 2.0f;

	float HSize = ys / 2.0f;

	switch (dir)
	{
	case Dir::Up:	// �����
		DrawHako(x, y + diff, HSize, diff, aColor, bFill);
		break;

	case Dir::Down:	// ������
		DrawHako(x, y - diff, HSize, diff, aColor, bFill);
		break;

	case Dir::Left:	// ������
		DrawHako(x - diff, y, diff, HSize, aColor, bFill);
		break;

	case Dir::Right:// �E����
		DrawHako(x + diff, y, diff, HSize, aColor, bFill);
		break;
	}
	if (bDebug) DrawMaru(x, y, 10.0f, &Math::Color(1.0f, 0.0f, 0.0f, 0.5f), true);	// ���W�ɁZ�`��
}

Math::Matrix MathSet::Mix()
{
	m = s * r * t;

	return Math::Matrix(m);
}

void MathSet::Init()
{
	s = Math::Matrix::Identity;
	r = s;
	t = s;
	m = s;
}
