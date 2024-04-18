#pragma once

class BaseObject
{
public:

	BaseObject() {}
	virtual	~BaseObject() {}

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	void SetTexture(std::string _fileName);

protected:

	KdTexture		m_tex;
	
	bool			m_bAlive = false;

	Math::Vector2	m_pos;
	Math::Matrix	m_mat;

};