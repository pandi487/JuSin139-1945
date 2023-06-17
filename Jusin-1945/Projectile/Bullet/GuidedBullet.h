#pragma once
#include "Projectile/Bullet/Bullet.h"


class CGuidedBullet
	: public CBullet
{

public:
	CGuidedBullet();
	virtual ~CGuidedBullet();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	
	float Distance(CObj* _obj);
	void SortTarget(list<CObj*>* _ObjList);
	void TargetChoice(list<CObj*>* _ObjList); // 해당 리스트의 순서를 거리순으로 정렬하고 제일 앞의것을 타겟으로 설정함

	CObj* m_Target;
	list<CObj*>*		m_TargetList;

	void Set_TargetList(list<CObj*>* _m_TargetList) { m_TargetList = _m_TargetList;} // 타겟리스트 세팅

};

