#pragma once
#include "CObj.h"
class CShield : public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(CObj& _rDst) override;

private:
	int		m_iTime;	// 시간
	
};

