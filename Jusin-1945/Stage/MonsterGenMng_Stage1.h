#pragma once

#include "Manager/MonsterGenerateManager.h"



class CMonsterGenMng_Stage1 final : public CMonsterGenerateManager
{
public:
	CMonsterGenMng_Stage1();
	virtual ~CMonsterGenMng_Stage1();

public:
	// CMonsterGenerateManager을(를) 통해 상속됨
	virtual void Initialize(void)	    override;
	virtual int Update(void)		    override;
	virtual void Late_Update(void)	    override;
	virtual void Render(HDC hDC)	    override;
	virtual void Release(void)		    override;
    virtual void Collide(CObj& _rDst)   override;

public:
	void Test();
};

