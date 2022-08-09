Texture2D MainTexture;
sampler MainSampler;

struct DirLightData
{
    float3 direction;
    float intensity;
    float4 color;
};

struct PointLightData
{
    float3 position;
    float intensity;
    float4 color;
};

cbuffer LightData
{
    DirLightData dirLight;
    PointLightData pointLights[8];
    uint pointLightCount;
    float3 padding;
};

cbuffer MaterialData
{
    float4 ambientColor;
    float4 diffuseColor;
    float4 specularColor;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD;
    float3 viewDir : NORMAL1;
};

float4 main(PixelInput INPUT) : SV_TARGET
{   
    float4 texColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 color = ambientColor;
    float3 normal = normalize(INPUT.normal);
    
     
    //diffuse
    float lightIntensity = saturate(dot(normal, -dirLight.direction));
    color += (dirLight.color * diffuseColor * lightIntensity);
    color = saturate(color);
    
    ////specular
    float3 halfDir = normalize((-dirLight.direction) + INPUT.viewDir);
    float4 specular = pow(max(dot(normal, halfDir), 0.0f), dirLight.intensity) * specularColor;
       
    color *= texColor;
    color = saturate(color + specular);
    
    return color;
}