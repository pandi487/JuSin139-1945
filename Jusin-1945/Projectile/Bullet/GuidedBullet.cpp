#include "GuidedBullet.h"
#include "Manager/CMainGame.h"
#include "Unit/Player.h"

CGuidedBullet::CGuidedBullet()
{
}

CGuidedBullet::~CGuidedBullet()
{
}

void CGuidedBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 7.f;

	m_TargetList = &CMainGame::Get_Instance().Get_ObjList()[MONSTER];

	if (m_TargetList != nullptr && !m_TargetList->empty()) {
		TargetChoice(m_TargetList);
		m_Target = m_TargetList->front();
	}
	else {
		m_Target = nullptr;
		m_fRadian = -PI / 2; // 타겟 없을때 -Y방향으로 날아감
	}
	
}

int CGuidedBullet::Update(void)
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}

	if (m_Target != nullptr) {			// 타겟을 향해 라디안 수정
		float fRelateX = m_tInfo.fX - m_Target->Get_Info().fX;
		float fRelateY = m_tInfo.fY - m_Target->Get_Info().fY;
		if (fRelateX >= 0)
			m_fRadian = atan(fRelateY / fRelateX) + PI;
		else
			m_fRadian = atan(fRelateY / fRelateX);

		// 라디안 방향으로 이동
		m_tInfo.fX += (m_fSpeed * (cos(m_fRadian)));
		m_tInfo.fY += (m_fSpeed * (sin(m_fRadian)));
	}
	else {
		m_tInfo.fX += (m_fSpeed * (cos(m_fRadian)));
		m_tInfo.fY += (m_fSpeed * (sin(m_fRadian)));
	}
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CGuidedBullet::Late_Update(void)
{
	if (m_Target != nullptr && m_Target->Get_Dead() ) {
		m_Target = nullptr;
	}
	if (120 > this->Get_Info().fX || WINCX - 120 < this->Get_Info().fX
		|| 120 > this->Get_Info().fY || WINCY - 120 < this->Get_Info().fY)
		m_bDead = true;
}

void CGuidedBullet::Render(HDC hDC)
{
	//HBRUSH  hBrush, oldBrush;
	//HPEN	hPen, oldPen;

	//hBrush = CreateSolidBrush(RGB(51, 153, 255));		// 색 입히는 코드
	//oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	//hPen = CreatePen(PS_SOLID, 2, RGB(51, 153, 255));
	//oldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	//SelectObject(hDC, oldBrush);
	//DeleteObject(hBrush);

	//SelectObject(hDC, oldPen);
	//DeleteObject(hPen);

}

void CGuidedBullet::Release(void)
{
}

void CGuidedBullet::Collide(CObj& _rDst)
{
    CGameObject* pGObj = dynamic_cast<CGameObject*>(&_rDst);
	if (nullptr != pGObj && this->Get_Owner() != pGObj 
		&& this->Get_TeamID() != pGObj->Get_TeamID())
	{
		if (pGObj->Get_StatusInfo().fHP > 0)
			pGObj->Get_StatusInfo().fHP -= 5;
		else if (pGObj->Get_StatusInfo().fHP <= 0)
			pGObj->Set_Dead();

		this->Set_Dead();
	}

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(&_rDst);
	if (nullptr != pPlayer && this->Get_Owner() != pPlayer
		&& this->Get_TeamID() != pPlayer->Get_TeamID())
	{
		if (pPlayer->Get_StatusInfo().fHP > 0)
			pPlayer->Get_StatusInfo().fHP -= 5;
		else if (pPlayer->Get_StatusInfo().fHP <= 0)
			pPlayer->Set_Dead();

		this->Set_Dead();
	}

	CMiniAirplane* pMini = dynamic_cast<CMiniAirplane*>(&_rDst);
	if (nullptr != pMini && this->Get_Owner() != pMini
		&& this->Get_TeamID() != pMini->Get_TeamID())
	{
		if (pMini->Get_StatusInfo().fHP > 0)
			pMini->Get_StatusInfo().fHP -= 5;
		else if (pMini->Get_StatusInfo().fHP <= 0)
			pMini->Set_Dead();

		this->Set_Dead();
	}

}

float CGuidedBullet::Distance(CObj* _obj)
{
	float dist = sqrt((_obj->Get_Info().fX) * (_obj->Get_Info().fX) + (_obj->Get_Info().fY * (_obj->Get_Info().fY)));
	return dist;
}

void CGuidedBullet::SortTarget(list<CObj*>* _ObjList)
{
	_ObjList->sort([&](CObj* a, CObj* b) { return Distance(a) < Distance(b); });
}

void CGuidedBullet::TargetChoice(list<CObj*>* _ObjList)
{
	SortTarget(_ObjList);
}