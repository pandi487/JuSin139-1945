#include "Player.h"
#include "AbstractFactory.h"

CPlayer::CPlayer() 
	: m_pBullet(nullptr), m_pLaser(nullptr), m_pMini(nullptr), m_pTarget(nullptr), m_pShield(nullptr)
{
	ZeroMemory(m_szHp, sizeof(m_szHp));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 500.f, 40.f, 40.f };
	m_fSpeed = 5.f;

	m_StatusInfo = { 100.f, 100.f, false };

	m_iTeam = 1;
}

int CPlayer::Update(void)
{
	Key_Input();


	// 정규화용 역길이 변수
	float normalLen = 0.f;
	try
	{
		if (0.f == m_tInfo.fDirX && 0.f == m_tInfo.fDirY)
			throw 0.f;
		normalLen = 1 / sqrtf(m_tInfo.fDirX * m_tInfo.fDirX + m_tInfo.fDirY * m_tInfo.fDirY);
	}
	catch (float) {}

	// 정규화된 벡터로 동일한 속도로 이동
	m_tInfo.fX += m_tInfo.fDirX * normalLen * m_fSpeed;
	m_tInfo.fY += m_tInfo.fDirY * normalLen * m_fSpeed;

	// 주무기 딜레이값 변화
	if (m_iPrimaryWeapon_MaxDelay < ++m_iPrimaryWeapon_Delay)
		m_iPrimaryWeapon_Delay = m_iPrimaryWeapon_MaxDelay;

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
	m_tInfo.fDirX = 0.f;
	m_tInfo.fDirY = 0.f;
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (100 < m_tRect.left)
			m_tInfo.fDirX = -1.f;
	}
	
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (WINCX - 100 > m_tRect.right)
			m_tInfo.fDirX = 1.f;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (100 < m_tRect.top)
			m_tInfo.fDirY = -1.f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (WINCY - 100 > m_tRect.bottom)
			m_tInfo.fDirY = 1.f;
	}


	// 총알 발사
	if (GetAsyncKeyState(VK_SPACE)
		&& m_iPrimaryWeapon_MaxDelay <= m_iPrimaryWeapon_Delay)
	{
		m_pBullet->push_back(Create_NormalBullet(-15.f, -5.f));
		m_pBullet->push_back(Create_NormalBullet(15.f, -5.f));
		m_pBullet->push_back(Create_GuidedBullet(0.f, -60.f));

		m_iPrimaryWeapon_Delay = 0;
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

	if ((m_dwTime <= GetTickCount64() - 275) && m_icount > 0) {
		m_pShield->push_back(Create_Shield());
		m_icount--;
		m_dwTime = GetTickCount64();
	}

	// 레이저 발사
	if (GetAsyncKeyState('L')) {
		m_pLaser->push_back(Create_Laser());
	}

	// 미니 비행기 (보조 비행기) 생성 (1초마다 총알 발사)
	if (GetAsyncKeyState('A'))
		m_pMini->push_back(Create_Mini());

	// 네이팜탄 발사
	if (GetAsyncKeyState('N') && m_dwTime <= GetTickCount64())
		m_iNapalm_Bomb_Count = 5;

	if (m_dwTime <= GetTickCount64() - 30 && m_iNapalm_Bomb_Count > 0)
	{
		m_pBullet->push_back(Create_NapalmBullet(0, 60));

		if (m_iNapalm_Bomb_Count == 0)
			//m_pBullet->push_back(Create_Bomb());

		m_iNapalm_Bomb_Count--;
		m_dwTime = GetTickCount64();
	}

	// 폭격기
	if (GetAsyncKeyState('B') && m_dwTime + 1000 <= GetTickCount64())
		m_pBullet->push_back(Create_Bomb());

	// 음파 발사
	if (GetAsyncKeyState('X') && m_dwTime + 1000 <= GetTickCount64())
		m_iSonicWaveCount = 15;

	if (m_dwTime <= GetTickCount64() - 30 && m_iSonicWaveCount > 0)
	{
		m_pShield->push_back(Create_CSonicWaveBullet(0, 60));
		m_iSonicWaveCount--;
		m_dwTime = GetTickCount64();
	}
	
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
	pCreated->Set_Follow_Speed(m_tInfo.fDirX * m_fSpeed * 0.5f);

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


CObj* CPlayer::Create_NapalmBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 90; // 위쪽으로 발사시키기위함

	CNapalmBullet* pCreated = dynamic_cast<CNapalmBullet*>(
									CAbstractFactory<CNapalmBullet>::Create(m_tInfo.fX, m_tInfo.fY));

	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Bulletinfo(fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY, 20.f, 50.f);

	return pCreated;
}

CObj* CPlayer::Create_Bomb()
{
	CBomb* pCreated = dynamic_cast<CBomb*>(
								CAbstractFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY));

	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Bulletinfo( rand() % WINCX + 1, rand() % WINCY + 1);

	return pCreated;
}

CObj* CPlayer::Create_CSonicWaveBullet(float _fMuzzleX, float _fMuzzleY)
{
	float fRadian = PI / 2; // 위쪽으로 발사시키기위함

	CSonicWaveBullet* pCreated = dynamic_cast<CSonicWaveBullet*>(
										CAbstractFactory<CSonicWaveBullet>::Create(m_tInfo.fX, m_tInfo.fY));

	pCreated->Set_Owner(this);
	pCreated->Set_Team(this->m_iTeam);
	pCreated->Set_Bulletinfo(fRadian, m_tInfo.fX - _fMuzzleX, m_tInfo.fY - _fMuzzleY, 20.f, 5.f);

	return pCreated;
}

void CPlayer::Draw_Body(HDC hDC) {
	HPEN	hPen, oldPen;

	hPen = CreatePen(PS_SOLID, 2, RGB(122, 62, 62));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	float fSize = 0.3f;
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 60, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - (20) * fSize, (int)m_tInfo.fY - (50) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (20) * fSize, (int)m_tInfo.fY - (20) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (30) * fSize, (int)m_tInfo.fY - (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (80) * fSize, (int)m_tInfo.fY - (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (90) * fSize, (int)m_tInfo.fY - (10) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (86) * fSize, (int)m_tInfo.fY + (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (20) * fSize, (int)m_tInfo.fY + (20) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (15) * fSize, (int)m_tInfo.fY + (50) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (40) * fSize, (int)m_tInfo.fY + (55) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (40) * fSize, (int)m_tInfo.fY + (70) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (5) * fSize, (int)m_tInfo.fY + (70) * fSize);
	LineTo(hDC, (int)m_tInfo.fX - (5) * fSize, (int)m_tInfo.fY + (75) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (5) * fSize, (int)m_tInfo.fY + (75) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (5) * fSize, (int)m_tInfo.fY + (70) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (40) * fSize, (int)m_tInfo.fY + (70) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (40) * fSize, (int)m_tInfo.fY + (55) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (15) * fSize, (int)m_tInfo.fY + (50) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (20) * fSize, (int)m_tInfo.fY + (20) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (86) * fSize, (int)m_tInfo.fY + (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (90) * fSize, (int)m_tInfo.fY - (10) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (80) * fSize, (int)m_tInfo.fY - (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (90) * fSize, (int)m_tInfo.fY - (10) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (80) * fSize, (int)m_tInfo.fY - (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (30) * fSize, (int)m_tInfo.fY - (15) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (20) * fSize, (int)m_tInfo.fY - (20) * fSize);
	LineTo(hDC, (int)m_tInfo.fX + (20) * fSize, (int)m_tInfo.fY - (50) * fSize);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 60);
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 20, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY + 12);
	LineTo(hDC, (int)m_tInfo.fX - 6, (int)m_tInfo.fY - 8);
	LineTo(hDC, (int)m_tInfo.fX + 6, (int)m_tInfo.fY - 8);
	LineTo(hDC, (int)m_tInfo.fX + 10, (int)m_tInfo.fY + 12);
	LineTo(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 20);

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);
}