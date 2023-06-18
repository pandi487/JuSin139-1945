#pragma once
#include "CObj.h"
class CScore :	public CObj
{
public:
	CScore();
	~CScore();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(CObj& _rDst) override;

private:
	bool	m_bCheck();
};

