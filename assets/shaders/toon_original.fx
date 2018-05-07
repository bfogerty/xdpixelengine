// Globals
float4 lightPos = float4(0, 0, -20.0f, 1);

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
	float3 viewDir   : TEXCOORD1;
	float3 lightDir   : TEXCOORD2;
	float3 Normal   : TEXCOORD3;
};

texture decalTexture;
sampler2D decalSampler = sampler_state
{
	Texture = <decalTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = int(Wrap);
	AddressV = int(Wrap);
};

texture rampTexture;
sampler2D rampSampler = sampler_state
{
	Texture = <rampTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	AddressU = int(Wrap);
	AddressV = int(Wrap);
};

VS_OUTPUT myvs( uniform float4x4 Model, uniform float4x4 ModelViewProj, uniform float deltaTime, uniform float edge, const VS_INPUT vin)
{
	VS_OUTPUT vout;

	float4 position = float4(vin.position.xyz + (vin.normal.xyz * edge), 1);
	position = mul(ModelViewProj, position);
	vout.position = position;

	vout.uv = vin.uv;

	return vout;
}

float4 myps( const VS_OUTPUT vin, uniform sampler2D decal : TEX0 ) : COLOR0
{
	return float4( 0,0,0, 1);
}

VS_OUTPUT myvs2( uniform float4x4 Model, uniform float4x4 View, uniform float4x4 ModelViewProj, uniform float deltaTime, const VS_INPUT vin)
{
	VS_OUTPUT vout;

	float4 position = mul(ModelViewProj, vin.position);
	vout.position = position;

	float4 worldPos = mul( Model, vin.position );
	float4 worldNormal = normalize(mul( Model, vin.normal ));

	float3 fromWorldPosToLightPos = lightPos.xyz - worldPos.xyz;
	float3 lightDir = normalize( fromWorldPosToLightPos );

	vout.lightDir = lightDir.xyz;
	vout.Normal = worldNormal.xyz;

	float4 viewDir = mul( Model, worldPos );
	vout.viewDir = normalize( viewDir.xyz );

	vout.uv = vin.uv;
	 
	return vout;
}

float4 myps2( const VS_OUTPUT vin, uniform sampler2D decal : TEX0, uniform sampler2D ramp : TEX1 ) : COLOR0
{
	float4 color = tex2D( decal, vin.uv );

	float fDot = clamp(dot( normalize(vin.lightDir), normalize(vin.Normal) ), 0.00, 1.00 );
	float4 rampColor = tex2D( ramp, float2(fDot, 0.50) );
	rampColor.a = fDot;

	color = color * rampColor.x;
	//color = rampColor;
	//color = color;
	color.w = 1.0;

	return color;
}

VS_OUTPUT myvs3( uniform float4x4 Model, uniform float4x4 View, uniform float4x4 ModelViewProj, uniform float deltaTime, const VS_INPUT vin)
{
	VS_OUTPUT vout;

	float4 position = mul(ModelViewProj, vin.position);
	vout.position = position;
	vout.color = float4(0,1,0,1);

	return vout;
}

float4 myps3( const VS_OUTPUT vin ) : COLOR0
{
	return vin.color;
}

float4x4 __modelViewProjection    :       WorldViewProjection;
float4x4 __model    :       World;
float4x4 __view    :       World;

float __deltaTime;
float edge = 0.10;

technique main_dx9
{
	
	pass p0
	{
	Zenable = false;
	ZWriteEnable = false;
	PolygonMode = int2(Front, Solid);
	//PolygonMode = int2(FrontAndBack, Wireframe);

	VertexShader = compile vs_3_0 myvs( __model, __modelViewProjection, __deltaTime, edge );
	PixelShader = compile ps_3_0 myps(decalSampler);
	}
	
	pass p1
	{
		Zenable = true;
		ZWriteEnable = true;
		PolygonMode = int2(FrontAndBack, Solid);

		VertexShader = compile vs_3_0 myvs2( __model, __view, __modelViewProjection, __deltaTime);
		PixelShader = compile ps_3_0 myps2(decalSampler, rampSampler);
	}
}


technique main_opengl
{

	pass p0
	{
		Zenable = false;
		ZWriteEnable = false;
		PolygonMode = int2(Front, Solid);

		VertexShader = compile glslv myvs( __model, __modelViewProjection, __deltaTime, edge );
		PixelShader = compile glslf myps(decalSampler);
	}		

	pass p1
	{
		Zenable = true;
		ZWriteEnable = true;
		PolygonMode = int2(Front, Solid);

		VertexShader = compile glslv myvs2( __model, __view, __modelViewProjection, __deltaTime);
		PixelShader = compile glslf myps2(decalSampler, rampSampler);
	}
}
