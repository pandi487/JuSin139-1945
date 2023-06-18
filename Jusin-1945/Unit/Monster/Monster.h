#pragma once
#include "GameObject.h"
class CMonster : public CGameObject
{
public:
	CMonster();
	virtual ~CMonster();

public:
	float		m_fMuzzleX;
	float		m_fMuzzleY;			// 총구의 좌표
	float		m_spinspeed;		//총구 회전속도
	bool		SwitchOn = false;	//총 발사 스위치
	list<CObj*>* m_pBullet;			//총알 목록

	bool		m_isOnField;		//필드 안 확인
	float		m_fRadian;		
	
	bool		m_dead = false;

	DWORD		m_dwTime = GetTickCount64();

public:

	void		Change_Angle();	// 벽에 부딛혔을때 방향전환


	virtual void		TimeLimit(void)		PURE;	//
	

public:
	virtual void Initialize(void) override		PURE;
	virtual int  Update(void) override			PURE;
	virtual void Late_Update(void) override		PURE;
	virtual void Render(HDC hDC) override		PURE;
	virtual void Release(void) override			PURE;
	virtual void Collide(CObj& _rDst) override 	PURE;
};

