// This is C2E1v_green from "The Cg Tutorial" (Addison-Wesley, ISBN
// 0321194969) by Randima Fernando and Mark J. Kilgard.  See page 38.

struct C2E1v_Output {
  float4 position : POSITION;
  float4 color    : COLOR;
};

float4 gConstantColor;

C2E1v_Output C2E1v_green( float2 position : POSITION 
                         , uniform float4 constantColor )
{	
  C2E1v_Output OUT;

  OUT.position = float4(position,0,1);
  OUT.color = constantColor; // float3(0,1,0);

  return OUT;	
}

technique t0
{
	pass p0
	{
		VertexProgram = compile arbvp1 C2E1v_green(gConstantColor);
	}
}
