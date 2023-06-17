#include "GuidedBullet.h"




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
	if (!m_TargetList->empty()) {
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
		if (fRelateX >= 0) {
			m_fRadian = atan(fRelateY / fRelateX) + PI;
		}
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

	if (120 > this->Get_Info().fX || WINCX - 120 < this->Get_Info().fX
		|| 120 > this->Get_Info().fY || WINCY - 120 < this->Get_Info().fY)
	{
		m_bDead = true;
	}
}

void CGuidedBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CGuidedBullet::Release(void)
{
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