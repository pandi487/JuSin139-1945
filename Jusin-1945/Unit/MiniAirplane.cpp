#include "Unit/MiniAirplane.h"
#include "General/AbstractFactory.h"
#include "Manager/CMainGame.h"

CMiniAirplane::CMiniAirplane()
{
}

CMiniAirplane::~CMiniAirplane()
{
	Release();
}

void CMiniAirplane::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 5.f;

	m_pBullet = &CMainGame::Get_Instance().Get_ObjList()[BULLET];
}

int CMiniAirplane::Update(void)
{
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	// 1초마다 총알 발사	
	if (m_dwTime + 1000 < GetTickCount()) {
		m_pBullet->push_back(Create_NormalBullet(-50.f, 0));
		m_pBullet->push_back(Create_NormalBullet(50.f, 0));
		m_dwTime = GetTickCount();
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMiniAirplane::Late_Update(void)
{
}

void CMiniAirplane::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left - 50,
		m_tRect.top,
		m_tRect.right - 50,
		m_tRect.bottom);

	Ellipse(hDC,
		m_tRect.left + 50,
		m_tRect.top,
		m_tRect.right + 50,
		m_tRect.bottom);
}

void CMiniAirplane::Release(void)
{
}

void CMiniAirplane::Collide(CObj& _rDst)
{

}

CObj* CMiniAirplane::Create_NormalBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 2.f; // 위쪽으로 발사시키기위함

	CNormalBullet* pCreated = dynamic_cast<CNormalBullet*>(
								CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Bulletinfo(fRadian, m_tInfo.fX + _fMuzzleX, m_tInfo.fY + _fMuzzleY);
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);

	return pCreated;
}
