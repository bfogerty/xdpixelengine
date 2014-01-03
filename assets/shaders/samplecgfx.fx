// Globals
float3 lightDir1 = normalize(float3(0,0,1.00));
float3 lightDir2 = normalize(float3(0,-1.00,0));

float4 lightColor1 = float4(1.0,1.00,1.0,1);
float4 lightColor2 = float4(0.0,0.10,0.8,1);

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

VS_OUTPUT myvs( uniform float4x4 Model, uniform float4x4 ModelViewProj, uniform float deltaTime, const VS_INPUT vin)
{

        VS_OUTPUT vout;
        float4 position = mul(ModelViewProj, vin.position);
        vout.position = position;

	float4 n = normalize( mul(Model, vin.normal) );

		float d1 = max( dot(n.xyz, lightDir1), 0 );
		float d2 = max( dot(n.xyz, lightDir2), 0 );

		vout.color = vin.color + ( lightColor1 * d1 ) + ( lightColor2 * d2 );
	vout.uv = vin.uv;

        return vout;
}

texture decalTexture;
sampler2D decalSampler = sampler_state
{
    Texture = <decalTexture>;
    MinFilter = Linear;
    MagFilter = Linear;
	AddressU = Repeat;
	AddressV = Repeat;
};

float4 myps( const VS_OUTPUT vin, uniform sampler2D decal : TEX0 ) : COLOR0
{
	return tex2D( decal, vin.uv ) * vin.color;
	//return vin.color;
}

float4x4 __modelViewProjection    :       WorldViewProjection;
float4x4 __model    :       World;

float __deltaTime;

technique main_dx9
{
        pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				//PolygonMode = int2(FrontAndBack, Wireframe);
				PolygonMode = int2(Front, Solid);

                VertexShader = compile vs_3_0 myvs( __model, __modelViewProjection, __deltaTime );
				PixelShader = compile ps_3_0 myps(decalSampler);
        }
}


technique main_opengl
{
        pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				//PolygonMode = int2(FrontAndBack, Wireframe);
				PolygonMode = int2(Front, Solid);

				VertexShader = compile glslv myvs( __model, __modelViewProjection, __deltaTime );
				PixelShader = compile glslf myps(decalSampler);
        }
}
