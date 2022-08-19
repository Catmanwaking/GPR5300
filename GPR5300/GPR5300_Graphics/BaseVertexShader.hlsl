struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    OUTPUT.position = float4(INPUT.position, 1.0f);
    OUTPUT.uv = INPUT.uv;
    OUTPUT.normal = INPUT.normal;
    OUTPUT.tangent = INPUT.tangent;
    OUTPUT.binormal = INPUT.binormal;
    
	return OUTPUT;
}