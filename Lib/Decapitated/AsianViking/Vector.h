#ifndef TemplateVector
#define TemplateVector
//typedef Vector2<int> Vector2i;
//*/
template<typename T>
struct Vector2 
{
	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(T a,T b)
	{
		x = a;
		y = b;
	}
	T x;// = 0;
	T y;// = 0;
		
};
//*/
#endif