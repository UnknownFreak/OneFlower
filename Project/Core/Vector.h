#ifndef TemplateVector
#define TemplateVector
#include <ostream>
template <typename T>
struct Vector2t
{
	Vector2t<T>();
	//Vector2(int a,int b);
	Vector2t<T>(T a, T b);
	//virtual ~Vector2() = default;
	T x;
	T y;
	//LOW: Make it so that normalize returns a normal vector instead 2015/13/02
	//Normalize the vector to get a direction NOT Reverseable
	bool normalize();
	double magnitude();
	//LOW make it when a vector2 is reassigned it is no longer normalized
	//bool isNormalize();// = false;

	//The angle between this and target
	double angle(Vector2t<T> * target);

	//LOW: Make a overload with primitive parameters (Int double etc);
	//The distance between this and target
	double distance(Vector2t<T> * target);

	//The Direction between this and target
	Vector2t<T> direction(Vector2t<T> & target);

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(x, y);
	}
	template <class Archive>
	void load(Archive& ar)
	{
		ar(x, y);
	}
};
#pragma region Operator
template <typename T>
std::ostream & operator<< (std::ostream &out, Vector2t<T>  const &t);

//& instead of void, for copy/move sesmatic optimization

template <typename T>
Vector2t<T> & operator *= (Vector2t<T>& left, const Vector2t<T> & right);

template <typename T>
Vector2t<T> & operator += (Vector2t<T>& left, const Vector2t<T> & right);

template <typename T>
Vector2t<T> & operator -= (Vector2t<T>& left, const Vector2t<T> & right);

//TODO: Make these inline cause primitive covert type, V.x + Left.x while the other is assignment operator (+= etc)
template <typename T>
Vector2t<T>  operator - (const Vector2t<T>& left, const Vector2t<T>  right);

template <typename T>
Vector2t<T>  operator + (const Vector2t<T>& left, const Vector2t<T>  right);

template <typename T>
Vector2t<T>  operator * (const Vector2t<T>& left, T right);

template <typename T>
bool		operator == (const Vector2t<T>& left, const Vector2t<T>& right);

//*/
#pragma endregion

#include "Vector.inl"
namespace Core
{
	typedef Vector2t<float> Vector2;
	typedef Vector2t<int> Vector2i;
	typedef Vector2t<float> Vector2f;
	typedef Vector2t<double> Vector2d;
}

#endif