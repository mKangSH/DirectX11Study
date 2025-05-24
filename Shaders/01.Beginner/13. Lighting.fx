#include "../Common/00. Global.fx"
#include "../Common/00. Light.fx"

float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, World);
    output.worldPosition = input.position.xyz;
    
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);

    return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
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