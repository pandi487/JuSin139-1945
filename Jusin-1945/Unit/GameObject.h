#pragma once

#include "framework.h"
#include "CObj.h"

typedef struct _CHARACTER_STATUS_INFO
{
    float   fMaxHP;
    float   fHP;
    // ����
    bool    bInvincible;
    
}CHARACTER_STATUS_INFO;

class CGameObject abstract : public CObj
{
public:
    CGameObject();
    virtual ~CGameObject();

public:
    // CObj��(��) ���� ��ӵ�
    virtual void Initialize(void)       override PURE;
    virtual int Update(void)            override PURE;
    virtual void Late_Update(void)      override PURE;
    virtual void Render(HDC hDC)        override PURE;
    virtual void Release(void)          override PURE;
    virtual void Collide(CObj& _rDst)   override PURE;

protected:
    // ü��, ������ ���� ���� ���� ���� ����ü
    CHARACTER_STATUS_INFO    m_StatusInfo;

public:
    CHARACTER_STATUS_INFO& Get_StatusInfo() { return m_StatusInfo; }
};