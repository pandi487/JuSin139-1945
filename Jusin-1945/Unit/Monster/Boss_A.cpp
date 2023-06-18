#include "Boss_A.h"
#include "AbstractFactory.h"
#include "Projectile/Bullet/NormalBullet.h"
#include "Projectile/Bullet/GuidedBullet.h"
#include "Manager/CMainGame.h"


void CBoss_A::Initialize(void)
{
	m_tInfo = { 400.f, 500.f, 40.f, 40.f };
	m_fSpeed = 2.f;
	m_spinspeed = 300.f;
	m_isOnField = false;
	m_fAngle = 270;

	m_pBullet = &CMainGame::Get_Instance().Get_ObjList()[BULLET];
}

int CBoss_A::Update(void)
{
	m_fMove_Radian = m_fAngle * (PI / 180);

	if (m_bDead) {
		return OBJ_DEAD;
	}
	else {
		if (!m_bArrive) {
			float fRelateX = m_tInfo.fX - 300;
			float fRelateY = m_tInfo.fY - 100;			// 300, 100 위치로 설정
			if (fRelateX >= 0)
				m_fMove_Radian = atan(fRelateY / fRelateX) + PI;
			else
				m_fMove_Radian = atan(fRelateY / fRelateX);
		}												// 방향 찾기
		if (m_fSpeed >= 0) {
			if (!m_bArrive) {
				m_fSpeed += -0.006f;
			}
		}
		if (m_fSpeed < 0) {
			if (!m_bArrive) {
				m_fAngle = 180;
				m_fMove_Radian = m_fAngle * (PI / 180);
				m_fSpeed = 1.5f;
				m_bArrive = true;					// 도착해서 멈추면 bArrive가 On되며
				//	좌우이동 시작
			}
		}
		else {
			m_tInfo.fX += (m_fSpeed * (cos(m_fMove_Radian)));
			m_tInfo.fY += (m_fSpeed * (sin(m_fMove_Radian)));	// m_fMove_Radian 방향으로 이동
		}

		if (m_bArrive)							// 도착하면 총알 발사 시작
		{
			TimeLimit();
			if (SwitchOn) {
				m_fRadian = PI / 2;
				m_pBullet->push_back(Create_NormalBullet(-m_fRadian, -90, -100));
				m_pBullet->push_back(Create_NormalBullet(-m_fRadian, +90, -100));
				m_fRadian = (PI / 2) + (PI / 9);
				m_pBullet->push_back(Create_NormalBullet(-m_fRadian, -90, -100));
				m_pBullet->push_back(Create_NormalBullet(-m_fRadian, +90, -100));
				m_fRadian = (PI / 2) - (PI / 9);
				m_pBullet->push_back(Create_NormalBullet(-m_fRadian, -90, -100));
				m_pBullet->push_back(Create_NormalBullet(-m_fRadian, +90, -100));
			}
		}





		__super::Update_Rect();

		return OBJ_NOEVENT;
	}

}

void CBoss_A::Late_Update(void)
{
	if (125 > m_tInfo.fX || WINCX - 125 < m_tInfo.fX
		|| 0 > m_tInfo.fY || WINCY - 125 < m_tInfo.fY)
		Change_Angle();

}

void CBoss_A::Render(HDC hDC)
{

	Rectangle(hDC, m_tInfo.fX - 100, m_tInfo.fY - 30,
		m_tInfo.fX + 100, m_tInfo.fY + 30);

	MoveToEx(hDC, m_tInfo.fX - 10, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY - 100);
	LineTo(hDC, m_tInfo.fX - 40, m_tInfo.fY - 80);
	LineTo(hDC, m_tInfo.fX - 40, m_tInfo.fY);
	LineTo(hDC, m_tInfo.fX + 40, m_tInfo.fY);
	MoveToEx(hDC, m_tInfo.fX + 40, m_tInfo.fY - 40, nullptr);
	LineTo(hDC, m_tInfo.fX + 140, m_tInfo.fY - 35);
	LineTo(hDC, m_tInfo.fX + 200, m_tInfo.fY + 50);
	LineTo(hDC, m_tInfo.fX + 150, m_tInfo.fY + 30);

	MoveToEx(hDC, m_tInfo.fX - 40, m_tInfo.fY - 40, nullptr);
	LineTo(hDC, m_tInfo.fX - 140, m_tInfo.fY - 35);
	LineTo(hDC, m_tInfo.fX - 200, m_tInfo.fY + 50);
	LineTo(hDC, m_tInfo.fX - 150, m_tInfo.fY + 30);
	LineTo(hDC, m_tInfo.fX + 150, m_tInfo.fY + 30);


	MoveToEx(hDC, m_tInfo.fX + 10, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY - 100);
	LineTo(hDC, m_tInfo.fX + 40, m_tInfo.fY - 80);
	LineTo(hDC, m_tInfo.fX + 40, m_tInfo.fY);

	MoveToEx(hDC, m_tInfo.fX - 10, m_tInfo.fY - 70, nullptr);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY - 70);

	MoveToEx(hDC, m_tInfo.fX + 20, m_tInfo.fY + 30, nullptr);
	LineTo(hDC, m_tInfo.fX + 5, m_tInfo.fY + 120);
	LineTo(hDC, m_tInfo.fX - 5, m_tInfo.fY + 120);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 30);

	MoveToEx(hDC, m_tInfo.fX + 20 + 90, m_tInfo.fY + 30, nullptr);
	LineTo(hDC, m_tInfo.fX + 5 + 90, m_tInfo.fY + 100);
	LineTo(hDC, m_tInfo.fX - 5 + 90, m_tInfo.fY + 100);
	LineTo(hDC, m_tInfo.fX - 20 + 90, m_tInfo.fY + 30);
	MoveToEx(hDC, m_tInfo.fX + 20 - 90, m_tInfo.fY + 30, nullptr);
	LineTo(hDC, m_tInfo.fX + 5 - 90, m_tInfo.fY + 100);
	LineTo(hDC, m_tInfo.fX - 5 - 90, m_tInfo.fY + 100);
	LineTo(hDC, m_tInfo.fX - 20 - 90, m_tInfo.fY + 30);

	MoveToEx(hDC, m_tInfo.fX + 5 - 40, m_tInfo.fY + 30, nullptr);
	LineTo(hDC, m_tInfo.fX - 40, m_tInfo.fY + 60);
	LineTo(hDC, m_tInfo.fX - 5 - 40, m_tInfo.fY + 30);

	MoveToEx(hDC, m_tInfo.fX + 5 + 40, m_tInfo.fY + 30, nullptr);
	LineTo(hDC, m_tInfo.fX + 40, m_tInfo.fY + 60);
	LineTo(hDC, m_tInfo.fX - 5 + 40, m_tInfo.fY + 30);




	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	Ellipse(hDC,
		m_tRect.left + 9,
		m_tRect.top + 15,
		m_tRect.right - 9,
		m_tRect.bottom - 3);
	Ellipse(hDC,
		m_tRect.left + 15,
		m_tRect.top + 22,
		m_tRect.right - 15,
		m_tRect.bottom - 8);

}

void CBoss_A::Release(void)
{
}

void CBoss_A::Collide(CObj& _rDst)
{
}

void CBoss_A::TimeLimit(void)
{

	DWORD dwCurrentTime = GetTickCount64();
	if (dwCurrentTime - m_dwTime >= 1)
	{
		SwitchOn = false;
	}
	if (dwCurrentTime - m_dwTime >= 800)
	{
		SwitchOn = true;
		m_dwTime = dwCurrentTime;
	}

}

CObj* CBoss_A::Create_NormalBullet(float _fRadian, float _fMuzzleX, float _fMuzzleY)
{
	CObj* pNormalBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CNormalBullet* pTemp = dynamic_cast<CNormalBullet*>(pNormalBullet);

	pTemp->Set_Bulletinfo(_fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY, 20, 1);


	return pNormalBullet;
}

CObj* CBoss_A::Create_GuidedBullet(float _fRadian, float _fMuzzleX, float _fMuzzleY)
{
	CObj* pGuidedBullet = CAbstractFactory<CGuidedBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CGuidedBullet* pTemp = dynamic_cast<CGuidedBullet*>(pGuidedBullet);

	pTemp->Set_Bulletinfo(_fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY);

	return pGuidedBullet;
}