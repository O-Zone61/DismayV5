#ifndef Color__
#define Color__

class Color
{
public:
	inline Color()
	{
		_color[0] = 0;
		_color[1] = 0;
		_color[2] = 0;
		_color[3] = 0;
	}
	inline Color(int r, int g, int b, int a)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	};
	inline Color(int r, int g, int b)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)255;
	};
	inline void r(int r)
	{
		_color[0] = (unsigned char)r;
	};
	inline void g(int g)
	{
		_color[1] = (unsigned char)g;
	};
	inline void b(int b)
	{
		_color[2] = (unsigned char)b;
	};
	inline void a(int a)
	{
		_color[3] = (unsigned char)a;
	};
	inline int r(void)
	{
		return (int)_color[0];
	}
	inline int g(void)
	{
		return (int)_color[1];
	}
	inline int b(void)
	{
		return (int)_color[2];
	}
	inline int a(void)
	{
		return (int)_color[3];
	}

private:
	unsigned char _color[4];
};

#endif // Color__