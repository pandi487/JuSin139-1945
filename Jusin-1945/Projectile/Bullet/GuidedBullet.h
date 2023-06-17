#pragma once
#include "Projectile/Bullet/Bullet.h"


class CGuidedBullet
	: public CBullet
{

public:
	CGuidedBullet();
	virtual ~CGuidedBullet();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	
	float Distance(CObj* _obj);
	void SortTarget(list<CObj*>* _ObjList);
	void TargetChoice(list<CObj*>* _ObjList); // �ش� ����Ʈ�� ������ �Ÿ������� �����ϰ� ���� ���ǰ��� Ÿ������ ������

	CObj* m_Target;
	list<CObj*>*		m_TargetList;

	void Set_TargetList(list<CObj*>* _m_TargetList) { m_TargetList = _m_TargetList;} // Ÿ�ٸ���Ʈ ����

};

