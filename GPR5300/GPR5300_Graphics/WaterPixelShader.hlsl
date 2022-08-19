Texture2D MainTexture;
Texture2D NormalTexture;
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

//AdditionalData
cbuffer WaterData 
{
    float4 mainColor;
    float4 sideColor;
    float fresnelPower;
    float fresnelMult;
    float2 tiling;
    float2 offset;
    float2 padding3;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL0;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 worldPos : POSITION;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    float3 InputNormal = normalize(INPUT.normal);
    float3 tangent = normalize(INPUT.tangent);
    float3 binormal = normalize(INPUT.binormal);
    float3 viewDir = normalize(camPos - INPUT.worldPos);    
    float3 textureColor = MainTexture.Sample(MainSampler, INPUT.uv).rgb;
    float3 light = ambientLight.rgb;
    float3 specular;
    float3 normalMapX = (NormalTexture.Sample(MainSampler, INPUT.uv + float2(offset.x, 0.0f)).xyz * 2.0f) - 1.0f;
    float3 normalMapY = (NormalTexture.Sample(MainSampler, INPUT.uv + float2(0.0f, offset.y)).xyz * 2.0f) - 1.0f;
    float3 normalBlend = normalize(float3(normalMapX.xy + normalMapY.xy, normalMapX.z * normalMapY.z));   
    float3 normal = normalize(tangent * normalBlend.x + binormal * normalBlend.y + InputNormal * normalBlend.z);
    
    //fresnel
    float fresnel = pow(1.0 - saturate(dot(InputNormal, viewDir)), fresnelPower);
    fresnel = pow(fresnel, fresnelMult);
    textureColor *= lerp(mainColor.rgb, sideColor.rgb, fresnel);
    
    //light
    //directional
    //diffuse
    float lightIntensity = max(dot(normal, -dirLight.direction), 0.0f);
    light += (lightIntensity * dirLight.intensity * dirLight.color.rgb);
    //specular
    float3 halfDir = normalize((-dirLight.direction) + viewDir);
    specular = pow(max(dot(normal, halfDir), 0.0f), specularPower * dirLight.intensity);
    
    //point
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
        lightIntensity = max(dot(normal, lightDir), 0.0f);
        lightIntensity *= attenuationFactor;
        lightIntensity = (lightDistance > pLight.maxDist) ? 0.0f : lightIntensity;        
        light += saturate(lightIntensity * pLight.intensity * pLight.color.rgb);
        
        //specular
        halfDir = normalize((lightDir) + viewDir);
        specular += pow(max(dot(normal, halfDir), 0.0f), specularPower * pLight.intensity) * lightIntensity;
    }
    
    //texture   
    float3 color = textureColor * saturate(light);
    
    color = saturate(color + specular);
    return float4(color, dissolve);
}