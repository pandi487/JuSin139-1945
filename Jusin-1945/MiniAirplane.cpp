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
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;

	m_fSpeed = 5.f;
}

int CMiniAirplane::Update(void)
{
	m_tInfo.fX = m_pTarget->Get_Info().fX - 30.f;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMiniAirplane::Late_Update(void)
{
	if (m_dwTime + 1000 <= GetTickCount()) {
		m_pBullet->push_back(Create_NormalBullet(40, -25));
		m_dwTime = GetTickCount();
	}
}

void CMiniAirplane::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMiniAirplane::Release(void)
{
}

CObj* CMiniAirplane::Create_NormalBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 2; // 위쪽으로 발사시키기위함

	CObj* pNormalBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CNormalBullet* pTemp = dynamic_cast<CNormalBullet*>(pNormalBullet);

	pTemp->Set_Bulletinfo(fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY);
	pNormalBullet->Initialize();

	return pNormalBullet;
}
