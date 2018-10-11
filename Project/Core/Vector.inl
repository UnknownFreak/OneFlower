#include <cmath>
#include "Vector.h"
template<typename T>
Vector2t<T>::Vector2t() : Vector2t<T>(0, 0)
{
}

template<typename T>
Vector2t<T>::Vector2t(T a, T b) : x(a), y(b)
{
}

template<typename T>
double Vector2t<T>::distance(Vector2t<T>* target) const
{
	double px = ((target->x - x) * (target->x - x));
	double py = ((target->y - y) * (target->y - y));

	return std::sqrt(px + py);
}

template<typename T>
double Vector2t<T>::angle(Vector2t<T>* target)
{
	double deltaX = (double)target->x - x;
	double deltaY = (double)target->y - y;

	return std::atan2(deltaY, deltaX) * 180 / 3.14159265358979323846;;
}
/*
template<typename T>
Vector2t<T> Vector2t<T>::direction (Vector2t<T> target)
{
}
//*/
template<typename T>
double Vector2t<T>::magnitude()
{
	return sqrt(x*x + y*y);
}
template<typename T>
inline Vector2t<T>& Vector2t<T>::operator=(const Vector2t<T>& right)
{
	if (*this == right)
		return *this;
	x = right.x;
	y = right.y;
	return *this;
}

template<typename T>
bool Vector2t<T>::normalize()
{
	float len = magnitude();
	//Avoid divide with 0
	if (len != 0)
	{
		x = x / len;
		y = y / len;
		return true;
	}
	else
	{
#ifdef _DEBUG
		//Engine::Window.debug.print("len = 0 Vector2t<T> Normalize failed, Error: Vector2Norm",__LINE__,__FILE__);
#endif
		return false;
	}
	//LOW: Fix this someday and be sure to check some math site this time to. 15/02/13
}

#pragma region Operators

template<typename T>
std::ostream & operator<< (std::ostream &out, Vector2t<T> const &t)
{
	out << t.x << t.y;
	return out;
}

template<typename T>
Vector2t<T>& operator +=(Vector2t<T>& left, const Vector2t<T>& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}
template<typename T>
Vector2t<T>& operator-=(Vector2t<T>& left, const Vector2t<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}
template<typename T>
Vector2t<T> operator*=(Vector2t<T>& left, const Vector2t<T> right)
{
	left.x *= right.x;
	left.y *= right.y;
	return *this;
}
template<typename T>
Vector2t<T> operator-(const Vector2t<T>& left, const Vector2t<T> right)
{
	return Vector2t<T>(left.x - right.x, left.y - right.y);
}
template<typename T>
Vector2t<T> operator+(const Vector2t<T>& left, const Vector2t<T> right)
{
	return Vector2t<T>(left.x + right.x, left.y + right.y);;
}
template<typename T>
Vector2t<T> operator*(const Vector2t<T>& left, T right)
{
	return Vector2t<T>(left.x * right, left.y * right);
}

template<typename T>
bool operator==(const Vector2t<T>& left, const Vector2t<T>& right)
{
	return left.x == right.x && left.y == right.y;
}

template<typename T>
bool operator!=(const Vector2t<T>& left, const Vector2t<T>& right)
{
	return !(left == right);
}

#pragma endregion