#ifndef TemplateVector
#define TemplateVector
struct Vector2
{
	Vector2();
	Vector2(int a,int b);
	virtual ~Vector2() = default;
	double x;
	double y;
	//LOW: Make it so that normalize returns a normal vector instead 2015/13/02 
	//Normalize the vector to get a direction NOT Reverseable
	bool normalize();
	
	//LOW: Make a overload with primitive parameters (Int double etc);
	//The distance between this and target
	double distance(Vector2* target);

	//The angle between this and target
	double angle(Vector2* target);


#pragma region Operator
	void operator += (Vector2& right);
	void operator -= (Vector2& right);
	void operator *= (Vector2& right);
	Vector2 operator-(Vector2 left);
#pragma endregion
};


#endif