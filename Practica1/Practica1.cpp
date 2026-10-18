#include <iostream>

#define ACTIVE_BULLET_MASK 0x00000002

#define BULLETS_NUMBER_MASK 0x00FF0000


int GetBulletNum(unsigned int _uData);

unsigned int AddBullets(unsigned int _uData, int _iBullets);

bool IsInfiniteBulletsModeActive(unsigned int _uData);

unsigned int ToggleInfiniteBulletMode(unsigned int _uData, bool _bActive);



int main()
{
    unsigned int uData = 0x8E252006;
    printf("Bullet Number is %d\n", GetBulletNum(uData));

    uData = AddBullets(uData, 5);

    printf("Bullet Number is %d\n", GetBulletNum(uData));

    printf("Infinite Bullets mode is %s\n", IsInfiniteBulletsModeActive(uData) ? "active" : "inactive");

    uData = ToggleInfiniteBulletMode(uData, false);

    printf("Infinite Bullets mode is %s\n", IsInfiniteBulletsModeActive(uData) ? "active" : "inactive");
}

int GetBulletNum(unsigned int _uData)
{
    unsigned int result = _uData;

    result <<= 8;

    result >>= 24;

    return result;
}

unsigned int AddBullets(unsigned int _uData, int _iBullets)
{
    unsigned int _uResult = GetBulletNum(_uData);

    _uResult += _iBullets;

    if (_uResult > 255)
    {
        _uResult = 255;
    }

    _uResult <<= 16;

    unsigned int _uTemp = _uData & ~BULLETS_NUMBER_MASK;

    _uResult = _uTemp | _uResult;

    return _uResult;
}

bool IsInfiniteBulletsModeActive(unsigned int _uData)
{
    bool bIsModeActive;

    bIsModeActive = _uData & ACTIVE_BULLET_MASK; //Check if that specific bit is true or false

    return bIsModeActive;
}


unsigned int ToggleInfiniteBulletMode(unsigned int _uData, bool _bActive)
{
    unsigned int result = _uData;

    if (_bActive)
    {
        result = _uData | ACTIVE_BULLET_MASK;
    }
    else
    {
        result = _uData & ~ACTIVE_BULLET_MASK;
    }

    return result;
}
