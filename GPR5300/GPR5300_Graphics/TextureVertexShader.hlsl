cbuffer MatrixBuffer
{
    float4x4 worldViewProjectionMatrix;
    float4 tilingOffset;
};

struct VertexInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), worldViewProjectionMatrix);
    OUTPUT.uv = INPUT.uv * tilingOffset.xy + tilingOffset.zw;
    
    return OUTPUT;
}