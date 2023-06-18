#pragma once

#include "framework.h"
#include "CObj.h"

typedef struct _CHARACTER_STATUS_INFO
{
    float   fMaxHP;
    float   fHP;
    // 무적
    bool    bInvincible;
    
}CHARACTER_STATUS_INFO;

class CGameObject abstract : public CObj
{
public:
    CGameObject();
    virtual ~CGameObject();

public:
    // CObj을(를) 통해 상속됨
    virtual void Initialize(void)       override PURE;
    virtual int Update(void)            override PURE;
    virtual void Late_Update(void)      override PURE;
    virtual void Render(HDC hDC)        override PURE;
    virtual void Release(void)          override PURE;
    virtual void Collide(CObj& _rDst)   override PURE;

protected:
    // 체력, 무적과 같은 상태 정보 저장 구조체
    CHARACTER_STATUS_INFO    m_StatusInfo;

public:
    CHARACTER_STATUS_INFO& Get_StatusInfo() { return m_StatusInfo; }
};