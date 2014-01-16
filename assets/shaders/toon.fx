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
	float2 rampColor   : TEXCOORD1;
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

VS_OUTPUT myvs2( uniform float4x4 Model, uniform float4x4 View, uniform float4x4 ModelViewProj, uniform float deltaTime, const VS_INPUT vin)
{
        VS_OUTPUT vout;

        float4 position = mul(ModelViewProj, vin.position);
        vout.position = position;

		float4 worldPos = mul( Model, vin.position );
		float4 worldNormal = mul( Model, vin.normal );

		float3 lightDir = -normalize( lightPos.xyz - worldPos.xyz );

		float fDot = min( saturate( dot( worldNormal, lightDir ) ), 0.99);
		vout.rampColor = float2( fDot, fDot );

		vout.uv = vin.uv;

        return vout;
}

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

float4 myps( const VS_OUTPUT vin, uniform sampler2D decal : TEX0 ) : COLOR0
{
	return float4( 0,0,0, 1);
}

float4 myps2( const VS_OUTPUT vin, uniform sampler2D decal : TEX0, uniform sampler2D ramp : TEX1 ) : COLOR0
{
	float4 color = tex2D( decal, vin.uv );
	
	float4 rampColor = tex2D( ramp, float2(vin.rampColor.x,0) );
	rampColor.a = 1.0;

	return color * rampColor;
	//return rampColor;
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
				
                VertexShader = compile vs_3_0 myvs( __model, __modelViewProjection, __deltaTime, edge );
				PixelShader = compile ps_3_0 myps(decalSampler);
        }

		pass p1
        {
                Zenable = true;
                ZWriteEnable = true;
				PolygonMode = int2(Front, Solid);
				
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
