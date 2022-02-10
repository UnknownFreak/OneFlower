#ifndef TemplateVector3
#define TemplateVector3
#include <ostream>

#include <Module/Random.hpp>

#include <Helpers/Vector.hpp>
#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

template <typename T>
struct Vector3t
{
	static Vector3t EMPTY;
	T x;
	T y;
	T z;

	Vector3t<T> lnormal() const
	{
		return { -y, x };
	}

	Vector3t<T> rnormal() const
	{
		return { y, -x };
	}

	bool normalize()
	{
		T len = magnitude();
		if (len != 0)
		{
			x = x / len;
			y = y / len;
			z = z / len;
			return true;
		}
		else
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Normalize failed, vector length is 0.", __FILE__, __LINE__);
			return false;
		}
	}

	template<typename A=T>
	typename std::enable_if_t<std::is_floating_point_v<A> && std::is_same_v<A, float>, Vector3t<T>>
	randomize(const T& random_direction) const
	{
		auto& randGen = Engine::GetModule<EngineModule::RandomGen>();
		
		return {
			x + randGen.random_float(-random_direction, random_direction),
			y + randGen.random_float(-random_direction, random_direction),
			z};
	}

	template<typename A=T>
	std::enable_if_t<std::is_floating_point_v<A> && std::is_same_v<A, double>, Vector3t<T>>
		randomize(const T& random_direction) const
	{
		auto& randGen = Engine::GetModule<EngineModule::RandomGen>();

		return {
			x + randGen.random_double(-random_direction, random_direction),
			y + randGen.random_double(-random_direction, random_direction),
			z};
	}

	template<typename A=T>
	std::enable_if_t<!std::is_floating_point_v<A>, Vector3t<T>>
		randomize(const T& random_direction) const
	{
		auto& randGen = Engine::GetModule<EngineModule::RandomGen>();

		return {
			x + randGen.random_int(-random_direction, random_direction),
			y + randGen.random_int(-random_direction, random_direction),
			z };
	}

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(x, y, z);
	}
	template <class Archive>
	void load(Archive& ar)
	{
		ar(x, y, z);
	}

	Vector3t<T>& operator/(const T div)
	{
		x /= div;
		y /= div;
		z /= div;
		return *this;
	}

	Vector2t<T> toVector2() const
	{
		return { x, y };
	}

};
#pragma region Operator
template <typename T>
inline std::ostream& operator<< (std::ostream& out, Vector3t<T>  const& t)
{
	return out << t.x << t.y << t.z;
}

template<typename T>
inline Vector3t<T>& operator +=(Vector3t<T>& left, const Vector3t<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;

	return left;
}
template<typename T>
inline Vector3t<T>& operator +=(Vector3t<T>& left, const Vector2t<T>& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}
template<typename T>
inline Vector3t<T>& operator-=(Vector3t<T>& left, const Vector3t<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;

	return left;
}
template<typename T>
inline Vector3t<T>& operator-=(Vector3t<T>& left, const Vector2t<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}
template<typename T>
inline Vector3t<T> operator*=(Vector3t<T>& left, const Vector3t<T> right)
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	return *this;
}
template<typename T>
inline Vector3t<T> operator-(const Vector3t<T>& left, const Vector3t<T> right)
{
	return Vector3t<T>{left.x - right.x, left.y - right.y, left.z - right.z};
}
template<typename T>
inline Vector3t<T> operator+(const Vector3t<T>& left, const Vector3t<T> right)
{
	return Vector3t<T>{left.x + right.x, left.y + right.y, left.z + right.z};
}
template<typename T>
inline Vector3t<T> operator*(const Vector3t<T>& left, T right)
{
	return Vector3t<T>{left.x* right, left.y* right, left.z* right};
}

template<typename T>
inline bool operator==(const Vector3t<T>& left, const Vector3t<T>& right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

template<typename T>
inline bool operator!=(const Vector3t<T>& left, const Vector3t<T>& right)
{
	return !(left == right);
}
#pragma endregion


namespace Core
{
	template <class T>
	using Vector3t = Vector3t<T>;
	typedef Vector3t<float> Vector3;
	typedef Vector3t<int> Vector3i;
	typedef Vector3t<float> Vector3f;
	typedef Vector3t<double> Vector3d;
}

#endif