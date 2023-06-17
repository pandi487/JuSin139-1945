#pragma once
#include "CObj.h"
class CLaser : public CObj
{
public:
	CLaser();
	virtual ~CLaser();

public:

	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};