// Globals
float3 lightPos = float3(0,0,-20.00);

struct VS_INPUT
{
      float4 position  : POSITION;
      float4 normal    : NORMAL;
      float4 color    : COLOR;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
      float4 color   : COLOR0;
      float4 position  : POSITION;
	float2 uv : TEXCOORD0;
};

VS_OUTPUT myvs( uniform float4x4 Model, uniform float4x4 View, uniform float4x4 ModelViewProj, uniform float deltaTime, const VS_INPUT vin)
{
        VS_OUTPUT vout;

        float4 position = mul(ModelViewProj, vin.position);
        vout.position = position;
		vout.uv = vin.uv;

        return vout;
}

texture texture1;
sampler2D texSampler1 = sampler_state
{
    Texture = <texture1>;
    MinFilter = Linear;
    MagFilter = Linear;
	AddressU = int(Wrap);
	AddressV = int(Wrap);
};

texture texture2;
sampler2D texSampler2 = sampler_state
{
    Texture = <texture2>;
    MinFilter = Linear;
    MagFilter = Linear;
	AddressU = int(Wrap);
	AddressV = int(Wrap);
};

float4 myps( const VS_OUTPUT vin, uniform sampler2D texSampler1 : TEX0, uniform sampler2D texSampler2 : TEX1, uniform int op) : COLOR0
{
	float4 color1 = tex2D( texSampler1, vin.uv );
	float4 color2 = tex2D( texSampler2, vin.uv );

	if( op == 0 )
	{
		return color1 + color2;
	}
	else if( op == 1 )
	{
		return color1 - color2;
	}
	else if( op == 2 )
	{
		return color1 * color2;
	}
	
	return float4(0,0,0,1);
}

float4x4 __modelViewProjection    :       WorldViewProjection;
float4x4 __model    :       World;
float4x4 __view    :       World;

float __deltaTime;
int op = 0;

technique main_dx9
{
		pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				PolygonMode = int2(Front, Solid);
				
                VertexShader = compile vs_3_0 myvs( __model, __view, __modelViewProjection, __deltaTime);
				PixelShader = compile ps_3_0 myps(texSampler1, texSampler2, op);
        }
}


technique main_opengl
{	
	pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				PolygonMode = int2(Front, Solid);
				
                VertexShader = compile glslv myvs( __model, __view, __modelViewProjection, __deltaTime);
				PixelShader = compile glslf myps(texSampler1, texSampler2, op);
        }
}
