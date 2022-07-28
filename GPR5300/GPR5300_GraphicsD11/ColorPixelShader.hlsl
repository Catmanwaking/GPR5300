struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    return INPUT.color;
}