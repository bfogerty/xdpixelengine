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
	};

	Color();
	Color(float r, float g, float b, float a);
	Color(float r, float g, float b);
	Color(ColorType c);


	float r,g,b,a;

protected:

};

#endif