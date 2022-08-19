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
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float maxDist;
};

cbuffer LightData
{
    DirLightData dirLight;
    PointLightData pointLights[8];
    float4 ambientLight;
    uint pointLightCount;
    float3 padding0;
};

cbuffer MaterialData
{
    float dissolve;
    float specularPower;
    float2 padding1;
};

cbuffer CameraData
{
    float3 camPos;
    float padding2;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 worldPos : POSITION;
};

float4 main(PixelInput INPUT) : SV_TARGET
{    
    float3 normal = normalize(INPUT.normal);
    float3 viewDir = normalize(camPos - INPUT.worldPos);
    float3 textureColor = MainTexture.Sample(MainSampler, INPUT.uv).rgb;
    float3 light = ambientLight.rgb;
    float3 specular;

    //light
    //directional
    //diffuse
    float lightIntensity = max(dot(normal, -dirLight.direction), 0.0f);
    light += (dirLight.color.rgb * lightIntensity * dirLight.intensity);
    //specular
    float3 halfDir = normalize((-dirLight.direction) + viewDir);
    specular = pow(max(dot(normal, halfDir), 0.0f), specularPower * dirLight.intensity);
    
    for (uint i = 0; i < pointLightCount; i++)
    {
        PointLightData pLight = pointLights[i];
        
        //attenuation
        float lightDistance = distance(INPUT.worldPos, pLight.position);
        float attenuationFactor = 1.0f / (
            pLight.constantAttenuation +
            pLight.linearAttenuation * lightDistance +
            pLight.quadraticAttenuation * lightDistance * lightDistance
        );
        //diffuse
        float3 lightDir = normalize(pLight.position - INPUT.worldPos);
        float lightIntensity = max(dot(normal, lightDir), 0.0f);
        lightIntensity *= attenuationFactor;
        lightIntensity = (lightDistance > pLight.maxDist) ? 0.0f : lightIntensity;
        light += saturate(lightIntensity * pLight.intensity * pLight.color.rgb);
        
        //specular
        float3 halfDir = normalize((lightDir) + viewDir);
        specular += pow(max(dot(normal, halfDir), 0.0f), specularPower * pLight.intensity) * lightIntensity;
    }
    
    //texture   
    float3 color = textureColor * saturate(light);   
       
    color = saturate(color + specular);   
    return float4(color, dissolve);
}