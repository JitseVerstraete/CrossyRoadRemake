//************
// VARIABLES *
//************
float4x4 m_MatrixWorldViewProj : WORLDVIEWPROJECTION;
float4x4 m_MatrixWorld : WORLD;
float3 m_LightDirection : DIRECTION
<
	string Object="TargetLight";
> = float3(0.577f, -0.577f, 0.577f);

float3 gColorDiffuse : COLOR = float3(1,1,1);

float gSpikeLength
<
	string UIWidget="Slider";
	float UIMin=0.0f;
	float UIMax=0.5f;
	float UIStep=0.0001f;
> = 0.2f;

RasterizerState FrontCulling 
{ 
	CullMode = NONE; 
};

//**********
// STRUCTS *
//**********
struct VS_DATA
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
};

struct GS_DATA
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
};

//****************
// VERTEX SHADER *
//****************
VS_DATA MainVS(VS_DATA vsData)
{

    return vsData;
}

//******************
// GEOMETRY SHADER *
//******************
void CreateVertex(inout TriangleStream<GS_DATA> triStream, float3 pos, float3 normal)
{
	GS_DATA newVertex = (GS_DATA)0;
	newVertex.Position = mul(float4(pos, 1.f), m_MatrixWorldViewProj);
	newVertex.Normal = mul(normal, (float3x3)m_MatrixWorld);
	triStream.Append(newVertex);
}

[maxvertexcount(9)]
void SpikeGenerator(triangle VS_DATA vertices[3], inout TriangleStream<GS_DATA> triStream)
{
	//Use these variable names
    float3 basePoint, top, left, right, spikeNormal;

	
	CreateVertex(triStream, vertices[0].Position, vertices[0].Normal);
	CreateVertex(triStream, vertices[1].Position, vertices[1].Normal);
	CreateVertex(triStream, vertices[2].Position, vertices[2].Normal);

	//Step 1. Calculate CENTER_POINT
	float3 centerPoint = (vertices[0].Position + vertices[1].Position + vertices[2].Position) / 3;
	
	//Step 2. Calculate Face Normal (Original Triangle)
	float3 faceNormal = (vertices[0].Normal + vertices[1].Normal + vertices[2].Normal) / 3;
	
	//Step 3. Offset CENTER_POINT (use gSpikeLength)
	centerPoint = centerPoint + (normalize(faceNormal) * gSpikeLength);
	
	//Step 4 + 5. Calculate Individual Face Normals (Cross Product of Face Edges) & Create Vertices for every face
	

        //FACE 1
        float3 faceNormal1 = cross((centerPoint - vertices[0].Position),(vertices[1].Position - vertices[0].Position));
        CreateVertex(triStream, vertices[0].Position, faceNormal1);
        CreateVertex(triStream, vertices[1].Position, faceNormal1);
        CreateVertex(triStream, centerPoint, faceNormal1);
		
		triStream.RestartStrip();

        //FACE 2
        float3 faceNormal2 = cross((centerPoint - vertices[1].Position),(vertices[2].Position - vertices[1].Position));
        CreateVertex(triStream, vertices[1].Position, faceNormal2);
        CreateVertex(triStream, vertices[2].Position, faceNormal2);
        CreateVertex(triStream, centerPoint, faceNormal2);
		
		triStream.RestartStrip();

        //Face 3
		 float3 faceNormal3 = cross((centerPoint - vertices[2].Position),(vertices[0].Position - vertices[2].Position));
        CreateVertex(triStream, vertices[2].Position, faceNormal3);
        CreateVertex(triStream, vertices[0].Position, faceNormal3);
        CreateVertex(triStream, centerPoint, faceNormal3);
		
		triStream.RestartStrip();

}

//***************
// PIXEL SHADER *
//***************
float4 MainPS(GS_DATA input) : SV_TARGET
{
    input.Normal=normalize(input.Normal);
	float diffuseStrength = max(dot(normalize(m_LightDirection),-input.Normal),0.2f); 
	return float4(gColorDiffuse*diffuseStrength,1.0f);
}

//*************
// TECHNIQUES *
//*************
technique10 Default //FXComposer >> Rename to "technique10 Default"
{
    pass p0
    {
        SetRasterizerState(FrontCulling);
        SetVertexShader(CompileShader(vs_4_0, MainVS()));
        SetGeometryShader(CompileShader(gs_4_0, SpikeGenerator()));
        SetPixelShader(CompileShader(ps_4_0, MainPS()));
    }
}