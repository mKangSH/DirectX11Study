#include "../Common/00. Global.fx"

float3 LightDirection;

float4 LightDiffuse;
float4 MaterialDiffuse;

Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, ViewProjection);
    
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);

    return output;
}

// Diffuse (분산광)
// 물체의 표면에서 산란된 빛을 표현하는 조명 모델입니다.
// 각도에 따라 물체의 색상이 변하는 효과를 제공합니다. (Lambert 공식)

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    
    float value = dot(-LightDirection, normalize(input.normal));
    color = color * value * LightDiffuse * MaterialDiffuse;
    
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