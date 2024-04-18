#pragma once

class Scene;

class C_Beam0
{
public:

	void Init();
	void Update(int aNum, float aDeg);
	void Draw(int aNum);

	void SetOwner(Scene* a_pOwner) { m_pOwner = a_pOwner; }
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }

private:

	Scene* m_pOwner;

	KdTexture* m_pTex;

	static const int	MaxNum = 300;
	
	Math::Vector2		m_pos[MaxNum];		// ���W
	Math::Vector2		m_size;				// �T�C�Y
	float				m_deg;				// �p�x
	MathSet				m_mat[MaxNum];		// �s��
	Math::Color			m_color;			// �F

};