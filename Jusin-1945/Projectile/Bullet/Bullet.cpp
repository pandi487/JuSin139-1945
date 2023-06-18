#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}



void CBullet::Set_Bulletinfo(float _fRadian, float _Xpos, float _Ypos)
{
	m_fRadian = _fRadian;
	m_tInfo.fX = _Xpos;
	m_tInfo.fY = _Ypos;
}

void CBullet::Set_Bulletinfo(float _Xpos, float _Ypos)
{	
	m_tInfo.fX = _Xpos;
	m_tInfo.fY = _Ypos;
}