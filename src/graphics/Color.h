#ifndef __COLOR__
#define __COLOR__

class Color
{
public:

	enum ColorType
	{
		BLACK = 0,
		WHITE,
		RED,
		GREEN,
		BLUE,
		GRAY,
		YELLOW,
	};

	Color();
	Color(float r, float g, float b, float a);
	Color(float r, float g, float b);
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	Color(ColorType c);

	void Normalize();

	float r,g,b,a;

protected:

};

#endif