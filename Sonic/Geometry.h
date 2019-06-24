#pragma once


// �^�����m��̂܂܎g����(�g���Ƃ��Ɍ^�����肷��)
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
	Vector2D<T> operator-(const Vector2D<T>& in)
	{
		return Vector2D<T>(x - in.x, y - in.y);
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

// �����^�޸��
typedef Vector2D<int> Vector2;

// �����^�޸��
typedef Vector2D<float> Vector2f;

/// ���ނ�\���\����
struct Size
{
	Size() : width(0), height(0) {}
	Size(int inw, int inh) : width(inw), height(inh) {}
	int width;	// ��
	int height;	// ����
};

/// ��`��\������\����
struct Rect
{
	Rect() : center(0, 0), size(0, 0) {}
	Rect(int x, int y, int inw, int inh) : center(x, y), size(inw, inh) {}
	Rect(const Vector2& inc, const Size& ins) : center(inc), size(ins) {}

	Vector2 center;	// ���S
	Size size;		// ���ƍ���


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

	// ��`��`�悷��
	// @param	color	��`�̐F
	void Draw(const unsigned int& color = 0xffffff);
};



struct Circle
{
	Circle() : pos(0, 0), radius(0) {};
	Circle(Vector2f invec, int inr) : pos(invec), radius(inr) {};

	Vector2f pos;	// ���W
	int radius;		// ���a

	// �~��`�悷��
	// @param	color	��`�̐F
	void Draw(const unsigned int& color = 0xffffff);
	
};

//�����\����
struct Segment
{
	Segment() : posA(0, 0), posB(0, 0) {};
	Segment(const Vector2f& ina, const Vector2f& inb) : posA(ina), posB(inb) {};
	Segment(const float& ax, const float& ay, const float& bx, const float& by) : posA(ax, ay), posB(bx, by) {};

	Vector2f posA;	// �[�_A
	Vector2f posB;	// �[�_B
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

