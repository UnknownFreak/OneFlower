#ifndef TemplateVector
#define TemplateVector
#include <ostream>
#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

template <typename T>
struct Vector2t
{
	T x;
	T y;

	Vector2t<T> lnormal() const
	{
		return {-y, x};
	}

	Vector2t<T> rnormal() const
	{
		return {y, -x };
	}

	bool normalize()
	{
		T len = magnitude();
		if (len != 0)
		{
			x = x / len;
			y = y / len;
			return true;
		}
		else
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Vector2t").Warning("Normalize failed, vector length is 0.", __FILE__, __LINE__);
			return false;
		}
	}

	void abs()
	{
		x = std::fabs(x);
		y = std::fabs(y);
	}

	T magnitude() const
	{
		return (T)sqrt(dot(*this));
	}

	template <class floating>
	floating angle(const Vector2t<T>& target) const
	{
		auto deltaX = target.x - x;
		auto deltaY = target.y - y;
		return std::atan2(deltaY, deltaX) * 180 / floating(3.14159265358979323846);
	}

	//LOW: Make a overload with primitive parameters (Int double etc);
	//The distance between this and target
	T distance(const Vector2t<T> & target) const
	{
		auto const px = ((x - target.x) * (x - target.x));
		auto const py = ((y - target.y) * (y - target.y));

		return (T)std::sqrt(px + py);
	}

	T dot(const Vector2t<T>& other) const
	{
		return x * other.x + y * other.y;
	}

	static T dot(const Vector2t<T>& a, const Vector2t<T>& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	double dot(const Vector2t<T>& other, double angle) const
	{
		return magnitude() * other.magnitude() * std::cos(angle);
	}

	static Vector2t<T> distanceWithAngle(const T& distance, const T& angle)
	{
		auto rangle = angle * (T(3.14159265358979323846)/ 180);
		return {distance * -std::sin(rangle), distance * std::cos(rangle)};
	}

	T cross(const Vector2t<T>& other) const
	{
		return (x * other.y) - (y * other.x);
	}

	//The Direction between this and target
	Vector2t<T> direction(Vector2t<T>& target)
	{
		return distance;
	}

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

	Vector2t<T>& operator/(const T div)
	{
		x /= div;
		y /= div;
		return *this;
	}

};
#pragma region Operator
template <typename T>
inline std::ostream& operator<< (std::ostream& out, Vector2t<T>  const& t)
{
	return out << t.x << t.y;
	return out;
}

template<typename T>
inline Vector2t<T>& operator +=(Vector2t<T>& left, const Vector2t<T>& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}
template<typename T>
inline Vector2t<T>& operator-=(Vector2t<T>& left, const Vector2t<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}
template<typename T>
inline Vector2t<T> operator*=(Vector2t<T>& left, const Vector2t<T> right)
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}
template<typename T>
inline Vector2t<T> operator-(const Vector2t<T>& left, const Vector2t<T> right)
{
	return Vector2t<T>{left.x - right.x, left.y - right.y};
}
template<typename T>
inline Vector2t<T> operator+(const Vector2t<T>& left, const Vector2t<T> right)
{
	return Vector2t<T>{left.x + right.x, left.y + right.y};
}
template<typename T>
inline Vector2t<T> operator*(const Vector2t<T>& left, T right)
{
	return Vector2t<T>{left.x* right, left.y* right};
}

template<typename T>
inline Vector2t<T> operator*(const Vector2t<T>& left, Vector2t<T>& right)
{
	return Vector2t<T>{left.x* right.x, left.y* right.y};
}

template<typename T>
inline bool operator==(const Vector2t<T>& left, const Vector2t<T>& right)
{
	return left.x == right.x && left.y == right.y;
}

template<typename T>
inline bool operator!=(const Vector2t<T>& left, const Vector2t<T>& right)
{
	return !(left == right);
}
#pragma endregion

namespace Core
{
	template <class T>
	using Vector2t = Vector2t<T>;
	typedef Vector2t<float> Vector2;
	typedef Vector2t<int> Vector2i;
	typedef Vector2t<float> Vector2f;
	typedef Vector2t<double> Vector2d;
}

#endif