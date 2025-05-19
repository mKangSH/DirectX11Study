#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "../Common/00. Global.fx"

///
// Struct
///
struct LightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction;
    float padding; // 배열을 사용할 때 4바이트 정렬이 되어야 하므로 패딩을 추가
};

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};

///
// Constant Buffer
///
cbuffer LightBuffer
{
    LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
    MaterialDesc Material;
};

/// 
// SRV
///
Texture2D DiffuseMap;
Texture2D NormalMap;
Texture2D SpecularMap;


/// 
// Function
///
float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    // Ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
    }
    
    // Diffuse
    {
        float4 color = DiffuseMap.Sample(LinearSampler, uv);
        float value = dot(-GlobalLight.direction, normalize(normal));
        diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
    }
    
    // Specular
    {
        float3 reflectionValue = reflect(GlobalLight.direction, normalize(normal));
        // float3 R = LightDirection - 2 * dot(LightDirection, normalize(input.normal)) * normalize(input.normal);
    
        float3 cameraPosition = CameraPosition();
        float3 eyeDirection = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(reflectionValue, eyeDirection)); // clamp(0, 1)
        float specularValue = pow(value, 10);
    
        specularColor = GlobalLight.specular * Material.specular * specularValue;
    }
    
    // Emissive
    {
        float3 cameraPosition = CameraPosition();
        float3 eyeDirection = normalize(cameraPosition - worldPosition);
    
        float value = saturate(dot(eyeDirection, normal));
        float emissive = 1.0f - value;
    
        emissive = smoothstep(0.0f, 1.0f, emissive);
        emissive = pow(emissive, 2);
    
        emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
    }
    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
}

void ComputeNormalMapping(inout float3 normal, float3 tangent, float2 uv)
{
    float4 map = NormalMap.Sample(LinearSampler, uv);
    if (any(map.rgb) == false)
    {
        return;
    }

    float3 N = normalize(normal); // Z Axis
    float3 T = normalize(tangent); // x Axis
    float3 B = normalize(cross(N, T)); // y Axis
    float3x3 TBN = float3x3(T, B, N); // TBN Matrix
    
    // [0, 1] 범위에서 [-1, 1] 범위로 변환
    float3 tangentSpaceNormal = (map.rgb * 2.0f) - 1.0f;
    float3 worldNormal = mul(tangentSpaceNormal, TBN); // TBN Matrix를 곱해줌
    
    normal = worldNormal;
}
#endif