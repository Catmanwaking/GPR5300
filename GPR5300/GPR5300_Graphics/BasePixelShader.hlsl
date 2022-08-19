texture2D MainTexture;
texture2D NormalTexture;
sampler MainSampler;

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}