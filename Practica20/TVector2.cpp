#include <iostream>
#include "TVector2.h"

TVector2::TVector2() 
    : x(0)
    , y(0) 
{
}
TVector2::TVector2(float _x, float _y)
    : x(_x)
    , y(_y)
{
}

TVector2& TVector2::operator+=(const TVector2& _rOther)
{
	x += _rOther.x;
    y += _rOther.y;
    return *this;
}

TVector2& TVector2::operator-=(const TVector2& _rOther)
{
    x -= _rOther.x;
    y -= _rOther.y;
    return *this;
}

TVector2& TVector2::operator*=(const TVector2& _rOther)
{
    x *= _rOther.x;
    y *= _rOther.y;
    return *this;
}

TVector2 operator+(TVector2 _a, const TVector2& _b)
{
    return _a += _b;
}
/*TVector2 operator+(const TVector2& _a, const TVector2& _b)
{
    return TVector2(_a.x + _b.x, _a.y + _b.y);
}*/

TVector2 operator-(TVector2& _a, const TVector2& _b)
{
    return _a -= _b;
}

TVector2 operator*(const float& _f, const TVector2& _in)
{
    return TVector2(_in.x * _f, _in.y * _f);
}

TVector2 operator*(const TVector2& _in, const float& _f)
{
    return TVector2(_in.x * _f, _in.y * _f);
}

TVector2 operator-(const TVector2& _in)
{
    return TVector2(-_in.x, -_in.y);
}

bool operator==(const TVector2& _a, const TVector2& _b)
{
    return _a.x == _b.x && _a.y == _b.y;
}

bool operator!=(const TVector2& _a, const TVector2& _b)
{
    return _a.x == _b.x && _a.y == _b.y;
}

std::ostream& operator<<(std::ostream& os, const TVector2& _in)
{
    
    return os << "( " << _in.x << ", " << _in.y << ")";
}
