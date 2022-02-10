//#ifdef _UNITTESTS_
//#include "CppUnitTest.h"
//
//#include <Helpers/Vector.hpp>
//#include <Interfaces/ICollider.hpp>
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;
//
//using Polygon = std::vector < Core::Vector2f>;
//using Axis = Polygon;
//using Projection = std::pair<double, double>;
//
//Projection project(const sf::ConvexShape& p, const Core::Vector2& axis)
//{
//	auto min = axis.dot(p.getPoint(0));
//	auto max = min;
//	for (auto i = 1u; i < p.getPointCount(); i++)
//	{
//		auto proj = axis.dot(p.getPoint(i));
//		if (proj < min)
//			min = proj;
//		if (proj > max)
//			max = proj;
//	}
//	return { min, max };
//}
//
//bool overlap(const Projection& a, const Projection& b)
//{
//	return !(a.first > b.second || b.first > a.second);
//}
//
//double getOverlap(const Projection& a, const Projection& b)
//{
//	if (overlap(a, b))
//		return std::min(a.second, b.second) - std::max(a.first, b.first);
//	return 0.0;
//}
//
//Axis getAxes(const sf::ConvexShape& p)
//{
//	Axis axes;
//	for (auto i = 0u; i < p.getPointCount(); i++)
//	{
//		auto current = p.getPoint(i);
//		auto next = p.getPoint(i + 1 == p.getPointCount() ? 0 : i + 1);
//		auto edge = next - current;
//		auto normal = Core::Vector2f{ edge.x, edge.y }.rnormal();
//		normal.normalize();
//		axes.push_back(normal);
//	}
//	return axes;
//}
//
//std::tuple<Core::Vector2f, double, bool> intersect(const sf::ConvexShape& a, const sf::ConvexShape& b)
//{
//	double _overlap = std::numeric_limits<double>::infinity();
//	Core::Vector2f smallest;
//	Axis axes = getAxes(a);
//	Axis axes2 = getAxes(b);
//	for (auto i = 0u; i < axes.size(); i++)
//	{
//		Core::Vector2f axis = axes[i];
//
//		Projection p1 = project(a, axis);
//		Projection p2 = project(b, axis);
//
//		if (!overlap(p1, p2))
//			return { {0,0}, 0 , false};
//		else
//		{
//			double o = getOverlap(p1, p2);
//			if (o < _overlap)
//			{
//				_overlap = o;
//				smallest = axis;
//			}
//		}
//	}
//	for (auto i = 0u; i < axes2.size(); i++)
//	{
//		Core::Vector2f axis = axes2[i];
//
//		Projection p1 = project(a, axis);
//		Projection p2 = project(b, axis);
//
//		if (!overlap(p1, p2))
//			return { {0,0}, 0, false};
//		double o = getOverlap(p1, p2);
//		if (o < _overlap)
//		{
//			_overlap = o;
//			smallest = axis;
//		}
//	}
//	return { smallest, _overlap, true };
//}
//
//namespace Tests
//{
//	TEST_CLASS(IColliderTest)
//	{
//	public:
//
//		TEST_METHOD(SquareBoxOutside)
//		{
//			ICollider c(0,0,0, Enums::ColliderType::Square);
//			ICollider c2(0, 0, 0, Enums::ColliderType::Square);
//			c.collider = sf::FloatRect(0, 0, 10, 10);
//			c2.collider = sf::FloatRect(-2, -1, 1, 1);
//
//			Assert::IsFalse(c.Collides(&c2));
//		}
//
//		TEST_METHOD(SquareBoxInside)
//		{
//			ICollider c(0, 0, 0, Enums::ColliderType::Square);
//			ICollider c2(0, 0, 0, Enums::ColliderType::Square);
//			c.collider = sf::FloatRect(0, 0, 10, 10);
//			c2.collider = sf::FloatRect(1, 1, 1, 1);
//
//			Assert::IsTrue(c.Collides(&c2));
//		}
//
//		TEST_METHOD(SATOutside)
//		{
//			/*std::vector<Core::Vector2f> a { {0, 0}, { 10, 0 }, { 10, 10 }, {0, 10} };
//			std::vector<Core::Vector2f> b { {-2, -2}, { 0, -2 }, { -1, -1 }, {-2, 0} };*/
//			ICollider c(0, 0, 0, Enums::ColliderType::SAT);
//			ICollider c2(0, 0, 0, Enums::ColliderType::SAT);
//			c.convexCollider = sf::ConvexShape(4);
//			c.convexCollider.setPoint(0, sf::Vector2f(0, 0));
//			c.convexCollider.setPoint(1, sf::Vector2f(10, 0));
//			c.convexCollider.setPoint(2, sf::Vector2f(10, 10));
//			c.convexCollider.setPoint(3, sf::Vector2f(0, 10));
//
//			c2.convexCollider = sf::ConvexShape(4);
//			c2.convexCollider.setPoint(0, sf::Vector2f(-2, -2));
//			c2.convexCollider.setPoint(1, sf::Vector2f(-2, -1));
//			c2.convexCollider.setPoint(2, sf::Vector2f(-1, -1));
//			c2.convexCollider.setPoint(3, sf::Vector2f(-1, -2));
//			auto [cc, o, inter] = intersect(c.convexCollider, c2.convexCollider);
//			Assert::IsFalse(inter);
//		}
//
//		TEST_METHOD(SATInside)
//		{
//			/*std::vector<Core::Vector2f> a{ {0, 0}, { 2, 0 }, { 2, 2 }, {0, 2} };
//			std::vector<Core::Vector2f> b{ {-1, -1}, { 1, 0 }, { 1, 1 }, {0, 1} };*/
//			
//			ICollider c(0, 0, 0, Enums::ColliderType::SAT);
//			ICollider c2(0, 0, 0, Enums::ColliderType::SAT);
//			c.convexCollider = sf::ConvexShape(4);
//			c.convexCollider.setPoint(0, sf::Vector2f(0, 0));
//			c.convexCollider.setPoint(1, sf::Vector2f(2, 0));
//			c.convexCollider.setPoint(2, sf::Vector2f(2, 2));
//			c.convexCollider.setPoint(3, sf::Vector2f(0, 2));
//
//			c2.convexCollider = sf::ConvexShape(4);
//			c2.convexCollider.setPoint(0, sf::Vector2f(0, 0));
//			c2.convexCollider.setPoint(1, sf::Vector2f(2, 0));
//			c2.convexCollider.setPoint(2, sf::Vector2f(2, 2));
//			c2.convexCollider.setPoint(3, sf::Vector2f(0, 2));
//			auto [cc, o, inter] = intersect(c.convexCollider, c2.convexCollider);
//			Assert::IsTrue(inter);
//		}
//
//	};
//}
//
//#endif