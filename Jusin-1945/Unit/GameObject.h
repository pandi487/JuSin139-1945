#pragma once

#include "CObj.h"


class CGameObject abstract : public CObj
{
public:
    CGameObject();
    virtual ~CGameObject();

public:
    // CObj을(를) 통해 상속됨
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
};