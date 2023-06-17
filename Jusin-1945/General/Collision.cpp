#include "Collision.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

void CCollision::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst) {
		for (auto& Src : _Src) {
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect()))) {
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollision::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst) {
		for (auto& Src : _Src) {
			if (Check_Sphere(Dst, Src)) {
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

bool CCollision::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float fWidth = _Dst->Get_Info().fX - _Src->Get_Info().fX;
	float fHeight = _Dst->Get_Info().fY - _Src->Get_Info().fY;

	float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;

	return fDiagonal <= fRadius;
}
