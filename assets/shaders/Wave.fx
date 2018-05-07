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

VS_OUTPUT myvs( uniform float4x4 Model, uniform float4x4 View, uniform float4x4 ModelViewProj, uniform float time, const VS_INPUT vin)
{
        VS_OUTPUT vout;

		float4 p = vin.position;
		p.z += sin(time) * ( sin(p.x+p.y+p.z)*2 );
		p.x += sin(time)*10;
		p.y += cos(time)*10;
		p.w = 1.0;

        float4 position = mul(ModelViewProj, p);

        vout.position = position;

		float d = max(0.00, dot( vin.normal, float3(0,0,1) ) );
		float3 amb = (vout.position.xyz)/length(vout.position.xyz);
		amb.x += (amb.x*0.50f);
		amb.y += (amb.y*0.30f);
		amb.z += (amb.z*0.10f);

		vout.color = float4(amb * d,1);

        return vout;
}


float4 myps( const VS_OUTPUT vin ) : COLOR0
{
	float4 c = vin.color;
	
	return c;
}

float4x4 __modelViewProjection    :       WorldViewProjection;
float4x4 __model    :       World;
float4x4 __view    :       World;

float __time;

technique main_dx9
{
		pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				PolygonMode = int2(Front, Solid);
				
                VertexShader = compile vs_3_0 myvs( __model, __view, __modelViewProjection, __time);
				PixelShader = compile ps_3_0 myps();
        }
}


technique main_opengl
{	
	pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				PolygonMode = int2(Front, Solid);
				
                VertexShader = compile glslv myvs( __model, __view, __modelViewProjection, __time);
				PixelShader = compile glslf myps();
        }
}
