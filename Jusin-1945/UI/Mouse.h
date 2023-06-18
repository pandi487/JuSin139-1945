#pragma once
#include "CObj.h"
class CMouse :
    public CObj
{
public:
    CMouse();
    virtual ~CMouse();

public:

    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Collide(CObj& _rDst) override;
};

