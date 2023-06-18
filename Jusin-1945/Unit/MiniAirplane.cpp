#include "Unit/MiniAirplane.h"
#include "General/AbstractFactory.h"

CMiniAirplane::CMiniAirplane()
{
}

CMiniAirplane::~CMiniAirplane()
{
	Release();
}

void CMiniAirplane::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CMiniAirplane::Update(void)
{
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	m_pBullet->push_back(Create_NormalBullet(-150.f, 0));
	m_pBullet->push_back(Create_NormalBullet(150.f, 0));

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMiniAirplane::Late_Update(void)
{

}

void CMiniAirplane::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left - 150,
		m_tRect.top,
		m_tRect.right - 150,
		m_tRect.bottom);

	Ellipse(hDC,
		m_tRect.left + 150,
		m_tRect.top,
		m_tRect.right + 150,
		m_tRect.bottom);
}

void CMiniAirplane::Release(void)
{
}

CObj* CMiniAirplane::Create_NormalBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 2; // �������� �߻��Ű������

	CObj* pNormalBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CNormalBullet* pTemp = dynamic_cast<CNormalBullet*>(pNormalBullet);

	pTemp->Set_Bulletinfo(fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY);
	pNormalBullet->Initialize();

	return pNormalBullet;
}