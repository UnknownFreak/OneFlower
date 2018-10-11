#ifndef RECT_HPP
#define RECT_HPP
#include <SFML\Graphics\Rect.hpp>
#include "Vector.h"
 // based of SFML Rect but this can handle references as well.

#ifdef min
#undef min
#define min_udef
#endif
#ifdef max
#undef max
#define max_udef
#endif
template<class T>
struct Rect
{
	T x, y, w, h;

	inline Rect() : x(0), y(0), w(0), h(0) { }
	inline Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h)
	{
	}
	inline Rect(const Core::Vector2t<T>& topLeft, const Core::Vector2t<T>& bottomRight):  x(topLeft.x), y(topLeft.y), w(bottomRight.x), h(bottomRight.y) {}
	inline Rect(const Rect& rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h) {}

	bool contains(T x, T y) const
	{
		std::remove_reference<T>::type minX = std::min(this->x, std::remove_reference<T>::type(this->x + w));
		std::remove_reference<T>::type maxX = std::max(this->x, std::remove_reference<T>::type(this->x + w));
		std::remove_reference<T>::type minY = std::min(this->y, std::remove_reference<T>::type(this->y + h));
		std::remove_reference<T>::type maxY = std::max(this->y, std::remove_reference<T>::type(this->y + h));
		
		return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
	}
	inline bool contains(Core::Vector2t<T>& pos)
	{
		return contains(pos.x, pos.y);
	}

	inline bool intersects(const Rect<T>& rectangle) const
	{
		auto r1MinX = std::min(x, std::remove_reference<T>::type(x + w));
		auto r1MaxX = std::max(x, std::remove_reference<T>::type(x + w));
		auto r1MinY = std::min(y, std::remove_reference<T>::type(y + h));
		auto r1MaxY = std::max(y, std::remove_reference<T>::type(y + h));
		
		auto r2MinX = std::min(rectangle.x, std::remove_reference<T>::type(rectangle.x + rectangle.w));
		auto r2MaxX = std::max(rectangle.x, std::remove_reference<T>::type(rectangle.x + rectangle.w));
		auto r2MinY = std::min(rectangle.y, std::remove_reference<T>::type(rectangle.y + rectangle.h));
		auto r2MaxY = std::max(rectangle.y, std::remove_reference<T>::type(rectangle.y + rectangle.h));
		
		auto interLeft = std::max(r1MinX, r2MinX);
		auto interTop = std::max(r1MinY, r2MinY);
		auto interRight = std::min(r1MaxX, r2MaxX);
		auto interBottom = std::min(r1MaxY, r2MaxY);
		
		if ((interLeft < interRight) && (interTop < interBottom))
			return true;
		return false;
	}

	inline bool operator==(const Rect<T>& right) const
	{
		return (x == right.x) && (y == right.y) && (w == right.w) && (h == right.h);
	}
	inline bool operator!=(const Rect<T>& right) const
	{
		return !(*this == right);
	}
	inline Rect<T>& operator=(const Rect<T>& copy)
	{
		x = copy.x;
		y = copy.y;
		w = copy.w;
		h = copy.h;
		return *this;
	}
};

#ifdef min_udef
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef max_udef
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

namespace Core
{
	template <class T>
	using Rect = Rect<T>;
	typedef Rect<float> FloatRect;
	typedef Rect<int> IntRect;
	typedef Rect<double> DoubleRect;
}

#endif