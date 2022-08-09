Texture2D MainTexture;
sampler MainSampler;

cbuffer MaterialData
{
    float4 ambientColor;
    float4 diffuseColor;
    float4 specularColor;
};

struct PixelOutput
{
    float4 color : SV_TARGET;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

PixelOutput main(PixelInput INPUT)
{  
    PixelOutput OUTPUT;
    
    OUTPUT.color = MainTexture.Sample(MainSampler, INPUT.uv);
    
    return OUTPUT;
}