Texture2D MainTexture;
sampler MainSampler;

cbuffer LightData
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightColor;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);

    float3 normal = normalize(INPUT.normal);
    float3 direction = normalize(-lightDirection);
    
    float diffuse = max(dot(normal, direction), 0.0f) * lightIntensity;
    float4 diffuseColor = diffuse * lightColor;
    
    return textureColor * diffuseColor;
}