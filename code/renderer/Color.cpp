#include "Color.h"

//-----------------------------------------------------------------------------------
Color::Color()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}

//-----------------------------------------------------------------------------------
Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

//-----------------------------------------------------------------------------------
Color::Color(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
}

//-----------------------------------------------------------------------------------
Color::Color(ColorType c)
{
	this->a = 1.0f;

	switch(c)
	{
		case BLACK:
			{
				r = 0.0f;
				g = 0.0f;
				b = 0.0f;
			}
			break;

		case WHITE:
			{
				r = 1.0f;
				g = 1.0f;
				b = 1.0f;
			}
			break;

		case RED:
			{
				r = 1.0f;
				g = 0.0f;
				b = 0.0f;
			}
			break;

		case GREEN:
			{
				r = 0.0f;
				g = 1.0f;
				b = 0.0f;
			}
			break;

		case BLUE:
			{
				r = 0.0f;
				g = 0.0f;
				b = 1.0f;
			}
			break;

		case GRAY:
			{
				r = 0.5f;
				g = 0.5f;
				b = 0.5f;
			}
			break;
	}
}