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
		vout.color = vin.color;

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
				PolygonMode = int2(FrontAndBack, Wireframe);
				//PolygonMode = int2(Front, Solid);

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
				PolygonMode = int2(FrontAndBack, Wireframe);
				//PolygonMode = int2(Front, Solid);

				VertexShader = compile glslv myvs( mvp );
				PixelShader = compile glslf myps();
        }
}
