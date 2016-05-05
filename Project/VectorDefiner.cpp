#include <cmath>
/*
template<typename T>
inline Vector2t<T>::Vector2t():x(0),y(0)
{

}
//*/
/*
Vector2t<T>::Vector2(int a,int b)
{
x = a;
y = b;
}
//*/
/*
template<typename T>
inline Vector2t<T>::Vector2(T a,T b):x(a),y(b)
{

}
template<typename T>
inline double Vector2t<T>::distance(Vector2* target)
{
double px = ((target->x - x) * (target->x - x));
double py = ((target->y - y) * (target->y - y));

return  std::sqrt(px + py);
}

template<typename T>
inline double Vector2t<T>::angle(Vector2* target)
{
double deltaX = target->x - x;
double deltaY = target->y - y;

int angleInDegree = std::atan2(deltaY,deltaX) * 180 / 3.14159265358979323846;
return angleInDegree;
}
template<typename T>
inline Vector2t<T> Vector2t<T>::direction(Vector2t<T> target)
{
Vector2t<T> a(target.x - x,target.y - y);
a.normalize();

//LOW: use operator
return a;
}
template<typename T>
inline double Vector2t<T>::magnitude()
{
return sqrt(x*x + y*y);
}
template<typename T>
inline bool Vector2t<T>::normalize()
{
float len = magnitude();
//Avoid divide with 0
if(len != 0)
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

/*
#include <ostream>
std::ostream & operator<< (std::ostream &out,Vector2t<T> const &t)
{
out << t.x << t.y;
return out;
}
//*/

#pragma region Operators
/*
template<typename T>
inline Vector2t<T> Vector2t<T>::operator+=(Vector2t<T>& left,const Vector2t<T> right)
{
left.x += right.x;
left.y += right.y;
return *this;
}
template<typename T>
inline Vector2t<T> Vector2t<T>::operator-=(Vector2t<T>& left,const Vector2t<T> right)
{
left.x -= right.x;
left.y -= right.y;
return *this;

}
//*/
/*
template<typename T>
inline Vector2t<T> Vector2t<T>::operator*=(Vector2t<T>& left,const Vector2t<T> right)
{
left.x *= right.x;
left.y *= right.y;
return *this;

}
template<typename T>
inline Vector2t<T> Vector2t<T>::operator-(Vector2t<T>& left,const Vector2t<T> right)
{
//Vector2t<T> left(x,y);
left.x -= right.x;
left.y -= right.y;

return left;
}
template<typename T>
inline Vector2t<T> Vector2t<T>::operator+(Vector2t<T>& left,const Vector2t<T> right)
{
//Vector2t<T> left(x,y);
left.x += right.x;
left.y += right.y;

return left;
}
template<typename T>
inline Vector2t<T> Vector2t<T>::operator*(Vector2t<T>& left,double right)
{
//Vector2t<T> left(x,y);
left.x *= right;
left.y *= right;

return left;
}
//*/
#pragma endregion