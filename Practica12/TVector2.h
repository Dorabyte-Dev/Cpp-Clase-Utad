#pragma once
class TVector2 
{
public:
	float x;
	float y;

	TVector2();
	TVector2(float _x, float _y);

	TVector2& operator+=(const TVector2& _rOther);
	TVector2& operator-=(const TVector2& _rOther);
	TVector2& operator*=(const TVector2& _rOther);
};

TVector2 operator+(const TVector2& _a, const TVector2& _b);
TVector2 operator-(const TVector2& _a, const TVector2& _b);
TVector2 operator*(const float _a, const TVector2& _b);
TVector2 operator*(const TVector2& _a, const float _b);
TVector2 operator-(const TVector2& _in);
bool operator==(const TVector2& _a, const TVector2& _b);
bool operator!=(const TVector2& _a, const TVector2& _b);
std::ostream& operator<<(std::ostream& os, const TVector2& s);