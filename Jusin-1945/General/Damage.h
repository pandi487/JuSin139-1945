#pragma once
#include "CObj.h"
#include "Unit/GameObject.h"

class CDamage
{
public:
	CDamage();
	~CDamage();

public:
	static void Apply_Damage(CObj& _Dst, CObj& _Src);
};

