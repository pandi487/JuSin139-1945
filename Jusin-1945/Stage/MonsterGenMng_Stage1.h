#pragma once

#include "Manager/MonsterGenerateManager.h"



class CMonsterGenMng_Stage1 final : public CMonsterGenerateManager
{
public:
	CMonsterGenMng_Stage1();
	virtual ~CMonsterGenMng_Stage1();

public:
	// CMonsterGenerateManager��(��) ���� ��ӵ�
	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

public:
	void Test();
};

