#pragma once
#include "CObj.h"
class CCollision : public CObj
{
public:
	CCollision();
	~CCollision();

public:
	static void Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
};

