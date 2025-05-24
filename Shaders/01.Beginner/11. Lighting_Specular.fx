#include "../Common/00. Global.fx"

float3 LightDirection;
float4 LightSpecular;
float4 MaterialSpecular;

Texture2D DiffuseMap;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, World);
    output.worldPosition = input.position;
    
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);

    return output;
}

// Specular (반사광)
// 한방향으로 완전히 반사되는 및 (Phong)

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 R = reflect(LightDirection, normalize(input.normal));
    // float3 R = LightDirection - 2 * dot(LightDirection, normalize(input.normal)) * normalize(input.normal);
    
    float3 cameraPosition = -View._41_42_43;
    float3 eyeDirection = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(R, eyeDirection)); // clamp(0, 1)
    float specular = pow(value, 10); // shininess
    
    float4 color = LightSpecular * MaterialSpecular * specular;
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)

    pass P1
    {
        SetRasterizerState(FillModeWireframe);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};