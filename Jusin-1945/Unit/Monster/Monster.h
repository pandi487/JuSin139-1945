#pragma once
#include "GameObject.h"
class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

public:
	float		m_fMuzzleX;
	float		m_fMuzzleY;			// �ѱ��� ��ǥ
	float		m_spinspeed;		//�ѱ� ȸ���ӵ�
	bool		SwitchOn = false;	//�� �߻� ����ġ
	list<CObj*>* m_pBullet;			//�Ѿ� ���

	bool		m_isOnField;		//�ʵ� �� Ȯ��
	float		m_fRadian;		
	
	bool		m_dead = false;

	DWORD		m_dwTime = GetTickCount64();

public:

	void		Change_Angle();	// ���� �ε������� ������ȯ


	virtual void		TimeLimit(void)		PURE;	//
	

public:
	virtual void Initialize(void) override		PURE;
	virtual int  Update(void) override			PURE;
	virtual void Late_Update(void) override		PURE;
	virtual void Render(HDC hDC) override		PURE;
	virtual void Release(void) override			PURE;
	virtual void Collide(CObj& _rDst) override 	PURE;
};

