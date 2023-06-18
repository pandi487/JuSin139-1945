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
	virtual int  Update(void)		    override;
	virtual void Late_Update(void)	    override;
	virtual void Render(HDC hDC) override {}
	virtual void Release(void)		    override;
    virtual void Collide(CObj& _rDst) override {}

public:
	void Phase_1();
    void Phase_2();
    void Phase_3();
    void Phase_4();
    void Phase_5();
    void Phase_Boss();
};

