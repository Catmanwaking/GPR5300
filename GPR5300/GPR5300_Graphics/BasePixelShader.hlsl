struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}