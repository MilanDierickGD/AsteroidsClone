#pragma once
#include <string>

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );

	float x;
	float y;
};

template<typename T>
struct Point2D
{
	static_assert(std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value, "Only int, float or double can be used as template types.");

	Point2D();
	explicit Point2D(T x, T y);

	T x;
	T y;
};

template <typename T>
Point2D<T>::Point2D() : Point2D(0.0f, 0.0f)
{
}

template <typename T>
Point2D<T>::Point2D(T x, T y) : x(x), y(y)
{
}

struct Rectf
{
	Rectf( );
	explicit Rectf( float left, float bottom, float width, float height );
	
	float left;
	float bottom;
	float width;
	float height;

};


struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};



