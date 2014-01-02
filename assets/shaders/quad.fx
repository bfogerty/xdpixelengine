struct VS_INPUT
{
	float4 position	: POSITION;
	float4 normal	: NORMAL;
	float4 color	: COLOR;
	float3 uv	: TEXCOORD0;
};

struct VS_OUTPUT
{
      float4 color   : COLOR0;
      float4 position  : POSITION;
};

VS_OUTPUT myvs( const VS_INPUT vin )
{
        VS_OUTPUT vout;

	float4 position = float4(vin.position.xy,0,1);
	vout.position = position;
        vout.color = vin.color;

        return vout;

}


technique main_dx9
{
        pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
		//FillMode = int(Wireframe);
		PolygonMode = int2(FrontAndBack, Wireframe);

                VertexShader = compile vs_3_0 myvs();
		//VertexShader = compile glslv myvs();
        }
}

technique main_opengl
{
        pass p0
        {
                Zenable = true;
                ZWriteEnable = true;
		//FillMode = int(Wireframe);
		PolygonMode = int2(FrontAndBack, Wireframe);

                //VertexShader = compile vs_3_0 myvs();
		VertexShader = compile glslv myvs();
        }
}



