#ifndef RECT_HPP
#define RECT_HPP

#include <glm/glm.hpp>
#include <algorithm>

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
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
	union
	{
		struct { glm::vec2 pos, size; };
		struct { T x, y, w, h; };
	};
#pragma warning(pop)

	bool contains(T tx, T ty) const
	{
		std::remove_reference<T>::type minX = std::min(this->x, std::remove_reference<T>::type(this->x + w));
		std::remove_reference<T>::type maxX = std::max(this->x, std::remove_reference<T>::type(this->x + w));
		std::remove_reference<T>::type minY = std::min(this->y, std::remove_reference<T>::type(this->y + h));
		std::remove_reference<T>::type maxY = std::max(this->y, std::remove_reference<T>::type(this->y + h));
		
		return (tx >= minX) && (tx < maxX) && (ty >= minY) && (ty < maxY);
	}

	bool contains_const(const T& tx, const T& ty) const
	{
		std::remove_reference<T>::type minX = std::min(this->x, std::remove_reference<T>::type(this->x + w));
		std::remove_reference<T>::type maxX = std::max(this->x, std::remove_reference<T>::type(this->x + w));
		std::remove_reference<T>::type minY = std::min(this->y, std::remove_reference<T>::type(this->y + h));
		std::remove_reference<T>::type maxY = std::max(this->y, std::remove_reference<T>::type(this->y + h));

		return (tx >= minX) && (tx < maxX) && (ty >= minY) && (ty < maxY);
	}

	inline bool contains(const Rect<T>& rect) const noexcept
	{
		return x <= rect.x && rect.getRight() <= getRight() &&
			y <= rect.y && rect.getBottom() <= getBottom();
	}

	inline bool intersects(const Rect<T>& rectangle) const
	{
		auto r1MinX = std::min<T>(x, std::remove_reference<T>::type(x + w));
		auto r1MaxX = std::max<T>(x, std::remove_reference<T>::type(x + w));
		auto r1MinY = std::min<T>(y, std::remove_reference<T>::type(y + h));
		auto r1MaxY = std::max<T>(y, std::remove_reference<T>::type(y + h));
		
		auto r2MinX = std::min<T>(rectangle.x, std::remove_reference<T>::type(rectangle.x + rectangle.w));
		auto r2MaxX = std::max<T>(rectangle.x, std::remove_reference<T>::type(rectangle.x + rectangle.w));
		auto r2MinY = std::min<T>(rectangle.y, std::remove_reference<T>::type(rectangle.y + rectangle.h));
		auto r2MaxY = std::max<T>(rectangle.y, std::remove_reference<T>::type(rectangle.y + rectangle.h));
		
		auto interLeft = std::max<T>(r1MinX, r2MinX);
		auto interTop = std::max<T>(r1MinY, r2MinY);
		auto interRight = std::min<T>(r1MaxX, r2MaxX);
		auto interBottom = std::min<T>(r1MaxY, r2MaxY);
		
		return (interLeft < interRight) && (interTop < interBottom);
	}

	inline bool operator==(const Rect<T>& right) const
	{
		return (x == right.x) && (y == right.y) && (w == right.w) && (h == right.h);
	}
	inline bool operator!=(const Rect<T>& right) const
	{
		return !(*this == right);
	}
	//inline Rect<T>& operator=(const Rect<T>& copy)
	//{
	//	x = copy.x;
	//	y = copy.y;
	//	w = copy.w;
	//	h = copy.h;
	//	return *this;
	//}

	inline T getRight() const noexcept
	{
		return x + w;
}

	inline T getBottom() const noexcept
	{
		return y + h;
	}

	inline glm::vec2 getTopLeft() const noexcept
	{
		return {(float)x, (float)y};
	}

	inline glm::vec2 getCenter() const noexcept
	{
		return {(float)x + w / 2, (float)y + h / 2};
	}

	inline glm::vec2 getSize() const noexcept
	{
		return {(float)w, (float)h};
	}

	template <class Archive>
	void save(Archive& saver) const
	{
		saver(x, y, w, h);
	}

	template <class Archive>
	void load(Archive& loader)
	{
		loader(x, y, w, h);
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