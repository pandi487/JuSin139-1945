#pragma once
#include "GameObject.h"
class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

};

