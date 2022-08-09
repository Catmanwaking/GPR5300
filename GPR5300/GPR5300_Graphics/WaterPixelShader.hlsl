Texture2D WaterTexture;
sampler MainSampler;

cbuffer LightData
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

//cbuffer WaterData
//{
//    float4 mainColor;
//    float4 sideColor;
//    float fresnelPower;
//    float fresnelMult;
//    float2 offset;
//};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 viewDir : TEXCOORD1;
};

float4 main(PixelInput INPUT) : SV_TARGET
{    
    //float2 uvX = INPUT.uv + float2(offset.x, 0.0f);
    //float2 uvY = INPUT.uv + float2(0.0f, offset.y);
    
    //float3 sampleX = WaterTexture.Sample(MainSampler, uvX).xyz;
    //float3 sampleY = WaterTexture.Sample(MainSampler, uvY).xyz;
    
    //float3 blend = normalize(float3(sampleX.rg + sampleY.rg, sampleX.b * sampleY.b));
    
    float4 texColor = WaterTexture.Sample(MainSampler, INPUT.uv);
    float4 color = ambientColor;
    float3 lightDir = -lightDirection;
    float lightIntensity = saturate(dot(INPUT.normal, lightDir));
    color += (diffuseColor * lightIntensity);
    color = saturate(color);
    
    float3 reflection = normalize(2 * lightIntensity * INPUT.normal - lightDir);
    float4 specular = pow(saturate(dot(reflection, INPUT.viewDir)), specularPower);
    
    color *= texColor;
    color = saturate(color + specular);
    
    return color;
}