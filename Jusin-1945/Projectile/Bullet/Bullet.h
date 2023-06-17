#pragma once

#include "CObj.h"

class CBullet abstract : public CObj
{

public:
	CBullet();
	virtual ~CBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) {};
	virtual int  Update(void) { return 0; };
	virtual void Late_Update(void) {};
	virtual void Render(HDC hDC) {};
	virtual void Release(void) {};

public:
	void Set_Bulletinfo(float _fRadian, float _Xpos, float _Ypos);
	void Set_Bulletinfo(float _Xpos, float _Ypos);


public:
    float m_fRadian;
};

