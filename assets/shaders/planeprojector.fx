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

VS_OUTPUT myvs( uniform float4x4 Model, uniform float4x4 View, uniform float4x4 Projection, uniform float deltaTime, uniform float3 planeNormal, uniform float3 pointOnPlane, uniform float3 offset, const VS_INPUT vin)
{

        VS_OUTPUT vout;

	float3 wPos = mul(Model, vin.position);
	float3 wNormal = mul(Model, vin.normal);

	float d1 = dot( pointOnPlane, planeNormal);
	
	float3 lPos = float3(-4,10,1);
	float3 fromLightToVert = normalize( wPos - lPos );
	
	float t = (-d1 - dot( planeNormal, lPos)) /  dot( planeNormal, fromLightToVert );
	wPos = lPos + (t * fromLightToVert);
	
	float d2 = dot( wPos, planeNormal);

	float3 newPos = wPos + ((d1-d2)*planeNormal) + offset;
	

	float4x4 vp = mul(Projection, View);
        float4 position = mul(vp, float4(newPos, 1.0));
        vout.position = position;

	vout.uv = vin.uv;

        return vout;
}


float4 myps( const VS_OUTPUT vin, uniform float3 meshColor ) : COLOR0
{
	return float4(meshColor,1);
}

float4x4 __model    :       World;
float4x4 __view    :       View;
float4x4 __projection    :       Projection;

float __deltaTime;

float3 meshColor;
float3 planeNormal;
float3 pointOnPlane;
float3 offset;

technique main_dx9
{
        pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				//PolygonMode = int2(FrontAndBack, Wireframe);
				PolygonMode = int2(Front, Solid);

                VertexShader = compile vs_3_0 myvs( __model, __view, __projection, __deltaTime, planeNormal, pointOnPlane, offset );
				PixelShader = compile ps_3_0 myps(meshColor);
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

				VertexShader = compile glslv myvs( __model, __view, __projection, __deltaTime, planeNormal, pointOnPlane, offset );
				PixelShader = compile glslf myps(meshColor);
        }
}
