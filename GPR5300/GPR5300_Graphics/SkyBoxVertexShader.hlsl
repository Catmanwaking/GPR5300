cbuffer MatrixBuffer
{
    float4x4 viewProjectionMatrix;
};

struct VertexInput
{
    float3 position : POSITION;
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
    
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), viewProjectionMatrix);
    OUTPUT.uv = INPUT.uv;
    
    return OUTPUT;
}