float4x4 gWorld : WORLD;
float4x4 gWorldViewProj : WORLDVIEWPROJECTION;
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);
float4x4 gBones[70];

Texture2D gDiffuseMap;
SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;// or Mirror or Clamp or Border
	AddressV = Wrap;// or Mirror or Clamp or Border
};

RasterizerState Solid
{
	FillMode = SOLID;
	CullMode = FRONT;
};

struct VS_INPUT {
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
	float4 blendIndices : BLENDINDICES;
	float4 blendWeights : BLENDWEIGHTS;
};
struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};

RasterizerState NoCulling
{
	CullMode = NONE;
};

BlendState NoBlending
{
	BlendEnable[0] = FALSE;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input) {

	VS_OUTPUT output;
	float4 blendedPosition;
	float3 blendedNormal;

	for (int i = 0; i < 4; i++)
	{
		int boneIndex = input.blendIndices[i];
		if (boneIndex >= 0)
		{
			//tranform the vertex based on the relevant bone and boneWeight
			float4 boneSpacePos = mul(float4(input.pos, 1.f), gBones[boneIndex]);
			float3 boneSpaceNormal = mul(input.normal, (float3x3)gBones[boneIndex]);


			//add the position and normal to the blended Position/normal according to the weight
			blendedPosition = blendedPosition + mul(boneSpacePos, input.blendWeights[i]);
			blendedNormal = blendedNormal + mul(boneSpaceNormal, input.blendWeights[i]);

		}
	}

	//make sure the blended position w-component is 1
	blendedPosition.w = 1.f;

	output.pos = mul(float4(blendedPosition.xyz, 1.f), gWorldViewProj);
	output.normal = normalize(mul(blendedNormal, (float3x3)gWorld));
	output.texCoord = input.texCoord;
	return output;


}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_TARGET{

	float4 diffuseColor = gDiffuseMap.Sample(samLinear,input.texCoord);
	float3 color_rgb = diffuseColor.rgb;
	float color_a = diffuseColor.a;

	//HalfLambert Diffuse :)
	float diffuseStrength = dot(input.normal, -gLightDirection);
	diffuseStrength = diffuseStrength * 0.5 + 0.5;
	diffuseStrength = saturate(diffuseStrength);
	color_rgb = color_rgb * diffuseStrength;

	return float4(color_rgb , color_a);
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique11 Default
{
	pass P0
	{
		SetRasterizerState(NoCulling);
		SetDepthStencilState(EnableDepth, 0);
		SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}

