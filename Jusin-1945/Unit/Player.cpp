#include "Player.h"
#include "AbstractFactory.h"

CPlayer::CPlayer() : m_pBullet(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 500.f, 80.f, 80.f };
	m_fSpeed = 5.f;
	
	m_iTeam = 1;
}

int CPlayer::Update(void)
{
	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Draw_Body(hDC); // 너무 드러워서 아래로 보냈어요
}

void CPlayer::Release(void)
{
}

void CPlayer::Collide(CObj& _rDst)
{


}

void CPlayer::Key_Input(void)
{
	// GetKeyState();

	if (GetAsyncKeyState(VK_LEFT)) {
		if (GetAsyncKeyState(VK_UP)) {
			m_tInfo.fX -= m_fSpeed / sqrt(2.f);
			m_tInfo.fY -= m_fSpeed / sqrt(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_tInfo.fX -= m_fSpeed / sqrt(2.f);
			m_tInfo.fY += m_fSpeed / sqrt(2.f);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP)) {
			m_tInfo.fX += m_fSpeed / sqrt(2.f);
			m_tInfo.fY -= m_fSpeed / sqrt(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_tInfo.fX += m_fSpeed / sqrt(2.f);
			m_tInfo.fY += m_fSpeed / sqrt(2.f);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;


	// 총알 발사
	if (GetAsyncKeyState(VK_SPACE)) {
		m_pBullet->push_back(Create_NormalBullet(0.f, -60.f));
		m_pBullet->push_back(Create_NormalBullet(40.f, 25.f));
		m_pBullet->push_back(Create_NormalBullet(-40.f, 25.f));
		m_pBullet->push_back(Create_GuidedBullet(70.f, -10.f));
		m_pBullet->push_back(Create_GuidedBullet(-70.f, -10.f));
	}

	// 미사일 총알
	if (GetAsyncKeyState('M')) {
		m_pBullet->push_back((Create_MissileBullet(0.f, 0.f)));
	}

	// 중간에 떨어지는 총알
	if (GetAsyncKeyState('Z')) {
		m_pBullet->push_back((Create_ReturnBullet(0.f, 0.f)));
	}


	// 실드 생성
	if (GetAsyncKeyState('S') && m_icount == 0)
		m_icount = 4;

	if ((m_dwTime <= GetTickCount() - 275) && m_icount > 0) {
		m_pShield->push_back(Create_Shield());
		m_icount--;
		m_dwTime = GetTickCount();
	}

	// 레이저 발사
	if (GetAsyncKeyState('L')) {
		m_pLaser->push_back(Create_Laser());
	}

	// 미니 비행기 (보조 비행기) 생성 (1초마다 총알 발사)
	if (GetAsyncKeyState('A'))
		m_pMini->push_back(Create_Mini());
}

CObj* CPlayer::Create_NormalBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 2.f; // 위쪽으로 발사시키기위함

	CNormalBullet* pCreated = dynamic_cast<CNormalBullet*>(
									CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Bulletinfo(fRadian, m_tInfo.fX + _fMuzzleX, m_tInfo.fY + _fMuzzleY, 20.f, 5.f);

	return pCreated;
}

CObj* CPlayer::Create_GuidedBullet(float _fMuzzleX, float _fMuzzleY)
{
	CGuidedBullet* pCreated = dynamic_cast<CGuidedBullet*>(
									CAbstractFactory<CGuidedBullet>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Target(this);
	pCreated->Set_Bulletinfo(m_tInfo.fX + _fMuzzleX, m_tInfo.fY + _fMuzzleX);


	return pCreated;
}

CObj* CPlayer::Create_MissileBullet(float _fMuzzleX, float _fMuzzleY)
{
	CMissileBullet* pCreated = dynamic_cast<CMissileBullet*>(
								CAbstractFactory<CMissileBullet>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Target(this);

	return pCreated;
}

CObj* CPlayer::Create_ReturnBullet(float _fMuzzleX, float _fMuzzleY)
{
	CReturnBullet* pCreated = dynamic_cast<CReturnBullet*>(
		CAbstractFactory<CReturnBullet>::Create(m_tInfo.fX, m_tInfo.fY));

	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Target(this);

	return pCreated;

}
CObj* CPlayer::Create_Shield()
{
	CShield* pCreated = dynamic_cast<CShield*>(
							CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Target(this);

	return pCreated;
}

CObj* CPlayer::Create_Laser()
{
	CLaser* pCreated = dynamic_cast<CLaser*>(
							CAbstractFactory<CLaser>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Target(this);

	return pCreated;
}

CObj* CPlayer::Create_Mini()
{
	CMiniAirplane* pCreated = dynamic_cast<CMiniAirplane*>(
									CAbstractFactory<CMiniAirplane>::Create(m_tInfo.fX, m_tInfo.fY));
	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Target(this);

	return pCreated;
}

void CPlayer::Draw_Body(HDC hDC) {
	HBRUSH  hBrush, oldBrush;
	HPEN	hPen, oldPen;

	hBrush = CreateSolidBrush(RGB(255, 250, 250));		// 색 입히는 코드
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	hPen = CreatePen(PS_SOLID, 2, RGB(122, 62, 62));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 60, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - (20) * 0.7, (int)m_tInfo.fY - (50) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (20) * 0.7, (int)m_tInfo.fY - (20) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (30) * 0.7, (int)m_tInfo.fY - (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (80) * 0.7, (int)m_tInfo.fY - (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (90) * 0.7, (int)m_tInfo.fY - (10) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (86) * 0.7, (int)m_tInfo.fY + (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (20) * 0.7, (int)m_tInfo.fY + (20) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (15) * 0.7, (int)m_tInfo.fY + (50) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (40) * 0.7, (int)m_tInfo.fY + (55) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (40) * 0.7, (int)m_tInfo.fY + (70) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (5) * 0.7, (int)m_tInfo.fY + (70) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX - (5) * 0.7, (int)m_tInfo.fY + (75) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (5) * 0.7, (int)m_tInfo.fY + (75) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (5) * 0.7, (int)m_tInfo.fY + (70) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (40) * 0.7, (int)m_tInfo.fY + (70) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (40) * 0.7, (int)m_tInfo.fY + (55) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (15) * 0.7, (int)m_tInfo.fY + (50) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (20) * 0.7, (int)m_tInfo.fY + (20) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (86) * 0.7, (int)m_tInfo.fY + (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (90) * 0.7, (int)m_tInfo.fY - (10) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (80) * 0.7, (int)m_tInfo.fY - (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (90) * 0.7, (int)m_tInfo.fY - (10) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (80) * 0.7, (int)m_tInfo.fY - (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (30) * 0.7, (int)m_tInfo.fY - (15) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (20) * 0.7, (int)m_tInfo.fY - (20) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX + (20) * 0.7, (int)m_tInfo.fY - (50) * 0.7);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 60);
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 20, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY + 12);
	LineTo(hDC, (int)m_tInfo.fX - 6, (int)m_tInfo.fY - 8);
	LineTo(hDC, (int)m_tInfo.fX + 6, (int)m_tInfo.fY - 8);
	LineTo(hDC, (int)m_tInfo.fX + 10, (int)m_tInfo.fY + 12);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 20);

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);
}