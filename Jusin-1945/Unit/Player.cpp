#include "Player.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()  : m_pBullet(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 500.f, 80.f, 80.f  };
	m_fSpeed = 5.f;
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

void CPlayer::Key_Input(void)
{
	// GetKeyState();

	if (GetAsyncKeyState(VK_LEFT)) {
		
		m_tInfo.fX -= m_fSpeed;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		m_tInfo.fX += m_fSpeed;
	}
	if (GetAsyncKeyState(VK_UP)) {
		m_tInfo.fY -= m_fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		m_tInfo.fY += m_fSpeed;
	}


	if (GetAsyncKeyState(VK_SPACE))
	{
		
		m_pBullet->push_back(Create_NormalBullet(0 , +60));
		m_pBullet->push_back(Create_NormalBullet(40 , -25));
		m_pBullet->push_back(Create_NormalBullet(-40 , -25));
		m_pBullet->push_back(Create_GuidedBullet(70 , 10));
		m_pBullet->push_back(Create_GuidedBullet(-70 , 10));
	}

	
}

CObj* CPlayer::Create_Shield()
{
	CObj* pShield = CAbstractFactory<CShield>::Create(m_tInfo.fX, m_tInfo.fY);
	pShield->Set_Target(this);

	return pShield;
}

CObj* CPlayer::Create_Laser()
{
	CObj* pLaser = CAbstractFactory<CLaser>::Create(m_tInfo.fX, m_tInfo.fY);
	pLaser->Set_Target(this);

	return pLaser;
}

CObj * CPlayer::Create_NormalBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 2; // 위쪽으로 발사시키기위함

	CObj* pNormalBullet = CAbstractFactory<CNormalBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CNormalBullet* pTemp = dynamic_cast<CNormalBullet*>(pNormalBullet);
	
	pTemp->Set_Bulletinfo(fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY);
	pNormalBullet->Initialize();

	return pNormalBullet;
	
}

CObj* CPlayer::Create_GuidedBullet(float _fMuzzleX, float _fMuzzleY)
{
	CObj* pGuidedBullet = CAbstractFactory<CGuidedBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	CGuidedBullet* pTemp = dynamic_cast<CGuidedBullet*>(pGuidedBullet);

	pTemp->Set_Bulletinfo(m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY);
	pTemp->Set_TargetList(m_pEnemy);
	pGuidedBullet->Initialize();

	return pGuidedBullet;
}

void CPlayer::Draw_Body(HDC hDC){
	HBRUSH hBrush, oldBrush;

	hBrush = CreateSolidBrush(RGB(255, 175, 175));		// 색 입히는 코드
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
			  m_tRect.left,
			  m_tRect.top,
			  m_tRect.right,
			  m_tRect.bottom);
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY-60, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - (20) * 0.7, (int)m_tInfo.fY - (50) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (20) * 0.7, (int)m_tInfo.fY - (20) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (30) * 0.7, (int)m_tInfo.fY - (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (80) * 0.7, (int)m_tInfo.fY - (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (90) * 0.7, (int)m_tInfo.fY - (10) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (86) * 0.7, (int)m_tInfo.fY + (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (20) * 0.7, (int)m_tInfo.fY + (20) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (15) * 0.7, (int)m_tInfo.fY + (50) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (40) * 0.7, (int)m_tInfo.fY + (55) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (40) * 0.7, (int)m_tInfo.fY + (70) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (5) * 0.7, (int)m_tInfo.fY + (70) *0.7);
	LineTo(hDC, (int)m_tInfo.fX - (5) * 0.7, (int)m_tInfo.fY + (75) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (5) * 0.7, (int)m_tInfo.fY + (75) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (5) * 0.7, (int)m_tInfo.fY + (70) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (40) * 0.7, (int)m_tInfo.fY + (70) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (40) * 0.7, (int)m_tInfo.fY + (55) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (15) * 0.7, (int)m_tInfo.fY + (50) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (20) * 0.7, (int)m_tInfo.fY + (20) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (86) * 0.7, (int)m_tInfo.fY + (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (90) * 0.7, (int)m_tInfo.fY - (10) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (80) * 0.7, (int)m_tInfo.fY - (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (90) * 0.7, (int)m_tInfo.fY - (10) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (80) * 0.7, (int)m_tInfo.fY - (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (30) * 0.7, (int)m_tInfo.fY - (15) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (20) * 0.7, (int)m_tInfo.fY - (20) *0.7);
	LineTo(hDC, (int)m_tInfo.fX + (20) * 0.7, (int)m_tInfo.fY - (50) *0.7);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 60);
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 20, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY + 12);
	LineTo(hDC, (int)m_tInfo.fX - 6, (int)m_tInfo.fY - 8);
	LineTo(hDC, (int)m_tInfo.fX + 6, (int)m_tInfo.fY - 8);
	LineTo(hDC, (int)m_tInfo.fX + 10, (int)m_tInfo.fY +12);
	LineTo(hDC, (int)m_tInfo.fX , (int)m_tInfo.fY + 20);
	
	SelectObject(hDC, oldBrush);

	DeleteObject(hBrush);
}