cbuffer MatrixBuffer
{
    float4x4 worldViewProjectionMatrix;
    float4x4 worldMatrix;
};

struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPos : POSITION;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), worldViewProjectionMatrix);
    OUTPUT.uv = INPUT.uv;
    OUTPUT.normal = normalize(mul(INPUT.normal, (float3x3) worldMatrix));
    OUTPUT.worldPos = mul(float4(INPUT.position, 1.0f), worldMatrix).xyz;
    
    return OUTPUT;
}