#pragma once

#include "CObj.h"


class CGameObject abstract : public CObj
{
public:
    CGameObject();
    virtual ~CGameObject();

public:
    // CObj��(��) ���� ��ӵ�
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
};