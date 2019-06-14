#pragma once

// 矩形の形
enum class RectType
{
	non,		// 無効
	circle,		// 〇
	box,		// □
};


// 型が未確定のまま使える(使うときに型が決定する)
template<typename T>
struct Vector2D
{
	Vector2D() : x(0), y(0) {}
	Vector2D(T inx, T iny) : x(inx), y(iny) {}
	T x;
	T y;

	Vector2D<T> operator+(const Vector2D<T>& in)
	{
		return Vector2D<T>(in.x + x, in.y + y);
	}
	void operator+=(const Vector2D<T>& in)
	{
		x += in.x;
		y += in.y;
	}
	void operator-=(const Vector2D<T>& in)
	{
		x -= in.x;
		y -= in.y;
	}
	void operator*=(const T& in)
	{
		x *= in;
		y *= in;
	}
	void operator/=(const T& in)
	{
		x /= in;
		y /= in;
	}
	void operator/=(const Vector2D<T>& in)
	{
		x /= in.x;
		y /= in.y;
	}

	bool operator==(const Vector2D<T>& in)const
	{
		return ((x == in.x) && (y == in.y));
	}
	bool operator!=(const Vector2D<T>& in)const
	{
		return ((x != in.x) || (y != in.y));
	}
	bool operator|=(const Vector2D<T>& in)const
	{
		return ((x == in.x) || (y == in.y));
	}
};

// 整数型ﾍﾞｸﾄﾙ
typedef Vector2D<int> Vector2;

// 実数型ﾍﾞｸﾄﾙ
typedef Vector2D<float> Vector2f;

/// ｻｲｽﾞを表す構造体
struct Size {
	Size() : width(0), height(0) {}
	Size(int inw, int inh) : width(inw), height(inh) {}
	int width;	// 幅
	int height;	// 高さ
};

/// 矩形を表現する構造体
struct Rect {
	Rect() : center(0, 0), size(0, 0) {}
	Rect(float x, float y, int inw, int inh) : center(x, y), size(inw, inh) {}
	Rect(const Vector2& inc, const Size& ins) : center(inc), size(ins) {}

	Vector2 center;	// 中心
	Size size;		// 幅と高さ


	const int Left()const
	{
		return center.x - size.width / 2;
	}
	const int Top()const
	{
		return center.y - size.height / 2;
	}
	const int Right()const
	{
		return center.x + size.width / 2;
	}
	const int Bottom()const
	{
		return center.y + size.height / 2;
	}
	const int Width()const
	{
		return size.width;
	}
	const int Height()const
	{
		return size.height;
	}
};



struct Box
{
	Box() : dotA(0, 0), dotB(0, 0) {};
	Box(Vector2f invecA, Vector2f invecB);
	Box(int ax, int ay, int bx, int by);

	Vector2f dotA;
	Vector2f dotB;

	bool operator==(const Box& box)
	{
		return ((box.dotA == dotA) && (box.dotB == dotB));
	}
};

struct Circle
{
	Circle() : pos(0, 0), radius(0) {};
	Circle(Vector2f invec, int inr) : pos(invec), radius(inr) {};

	Vector2f pos;	// 座標
	int radius;		// 半径

	// 他の円との当たり判定
	// @param True...当たってる, False...当たってない
	bool HitCircle(Circle& c);
	
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

