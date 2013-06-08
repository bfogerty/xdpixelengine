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
Color::Color(int r, int g, int b)
{
	this->r = static_cast<float>(r);
	this->g = static_cast<float>(g);
	this->b = static_cast<float>(b);
	this->a = 1.0f;

	Normalize();
	this->a = 1.0f;
}

//-----------------------------------------------------------------------------------
Color::Color(int r, int g, int b, int a)
{
	this->r = static_cast<float>(r);
	this->g = static_cast<float>(g);
	this->b = static_cast<float>(b);
	this->a = static_cast<float>(a);
	Normalize();
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

		case YELLOW:
			{
				r = 1.0f;
				g = 1.0f;
				b = 0.0f;
			}
			break;
	}
}

//-----------------------------------------------------------------------------------
void Color::Normalize()
{
	this->r = this->r / 255.0f;
	this->g = this->g / 255.0f;
	this->b = this->b / 255.0f;
	this->a = this->a / 255.0f;
}
