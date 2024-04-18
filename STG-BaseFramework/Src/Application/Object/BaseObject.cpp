#include "BaseObject.h"

void BaseObject::Update()
{
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
}

void BaseObject::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);
}

void BaseObject::Init()
{
	m_pos = { 0.0f, 0.0f };
	m_mat = Math::Matrix::Identity;
}

void BaseObject::Release()
{

}

void BaseObject::SetTexture(std::string _fileName)
{

}
