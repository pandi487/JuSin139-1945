#pragma once

#include "CObj.h"

class CBullet abstract : public CObj
{
public:
    CBullet();
    virtual ~CBullet();

public:
    void Set_Bulletinfo(float _fRadian, float _Xpos, float _Ypos);
    // �Ѿ��� ������ ������ǥ�� �������ִ� �Լ�
    void Set_Bulletinfo(float _Xpos, float _Ypos);
    // ������ �ʿ����� ���� �Ѿ��� ������ǥ ����
};

