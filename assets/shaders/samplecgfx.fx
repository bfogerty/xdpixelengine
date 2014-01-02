// Globals
float3 lightDir1 = normalize(float3(0,0,1.00));
float3 lightDir2 = normalize(float3(0,1.00,0));

float4 lightColor1 = float4(0.65,0.65,0.65,1);
float4 lightColor2 = float4(0.0,0.10,0.8,1);

struct VS_INPUT
{
      float4 position  : POSITION;
      float4 normal    : NORMAL;
      float4 color    : COLOR;
};

struct VS_OUTPUT
{
      float4 color   : COLOR0;
      float4 position  : POSITION;
};

VS_OUTPUT myvs( uniform float4x4 ModelViewProj, const VS_INPUT vin)
{

        VS_OUTPUT vout;
        float4 position = mul(ModelViewProj, vin.position);
        vout.position = position;

		float d1 = max( dot(vin.normal.xyz, lightDir1), 0 );
		float d2 = max( dot(vin.normal.xyz, lightDir2), 0 );

		vout.color = vin.color * (( lightColor1 * d1 ) + ( lightColor2 * d2 ));

        return vout;
}

float4 myps( const VS_OUTPUT vin ) : COLOR0
{
	return vin.color;
}

float4x4 mvp    :       WorldViewProjection;

technique main_dx9
{
        pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
				//PolygonMode = int2(FrontAndBack, Wireframe);
				PolygonMode = int2(Front, Solid);

                VertexShader = compile vs_3_0 myvs( mvp );
				PixelShader = compile ps_3_0 myps();
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

				VertexShader = compile glslv myvs( mvp );
				PixelShader = compile glslf myps();
        }
}
