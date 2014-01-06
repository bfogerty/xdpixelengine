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

VS_OUTPUT myvs( uniform float4x4 Model, uniform float4x4 ModelViewProj, uniform float deltaTime, uniform float edge, const VS_INPUT vin)
{
        VS_OUTPUT vout;
		
	float4 position = float4(vin.position.xyz + (vin.normal.xyz * edge), 1);
        position = mul(ModelViewProj, position);
        vout.position = position;

		vout.uv = vin.uv;

        return vout;
}

VS_OUTPUT myvs2( uniform float4x4 Model, uniform float4x4 ModelViewProj, uniform float deltaTime, const VS_INPUT vin)
{
        VS_OUTPUT vout;
        float4 position = mul(ModelViewProj, vin.position);
        vout.position = position;

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

float4 myps( const VS_OUTPUT vin, uniform sampler2D decal : TEX0 ) : COLOR0
{
	return float4( 0,0,0, 1);
}

float4 myps2( const VS_OUTPUT vin, uniform sampler2D decal : TEX0 ) : COLOR0
{
	float4 color = tex2D( decal, vin.uv );

	return color;
}

float4x4 __modelViewProjection    :       WorldViewProjection;
float4x4 __model    :       World;

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
				
                VertexShader = compile vs_3_0 myvs2( __model, __modelViewProjection, __deltaTime);
				PixelShader = compile ps_3_0 myps2(decalSampler);
        }
}


technique main_opengl
{

        pass p0
        {
                Zenable = false;
                ZWriteEnable = false;
				//PolygonMode = int2(FrontAndBack, Wireframe);
				PolygonMode = int2(Front, Solid);

				VertexShader = compile glslv myvs( __model, __modelViewProjection, __deltaTime, edge );
				PixelShader = compile glslf myps(decalSampler);
        }		
	
	pass p1
        {
                Zenable = true;
                ZWriteEnable = true;
				PolygonMode = int2(Front, Solid);
				
                VertexShader = compile glslv myvs2( __model, __modelViewProjection, __deltaTime);
				PixelShader = compile glslf myps2(decalSampler);
        }
}
