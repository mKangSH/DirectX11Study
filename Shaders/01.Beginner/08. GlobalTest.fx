#include "../Common/00. Global.fx"

Texture2D Texture0;
float3 LightDirection;

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, ViewProjection);
    
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);

    return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    float3 light = -LightDirection;
    
    return Texture0.Sample(LinearSampler, input.uv) * dot(normal, light);
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