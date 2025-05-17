#include "../Common/00. Global.fx"

Texture2D Texture0;

float4 LightAmbient;
float4 MaterialAmbient;

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, ViewProjection);
    
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);

    return output;
}

// Ambient Light
// 수많은 반사를 거쳐서 광원이 불분명한 상태의 빛을 Ambient Light라고 한다.
// 일정한 밝기와 색상을 가진다. (빛의 방향을 특정하지 않음)

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = LightAmbient * MaterialAmbient;
    
    return Texture0.Sample(LinearSampler, input.uv) * color;
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