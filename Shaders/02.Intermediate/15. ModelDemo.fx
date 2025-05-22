#include "../Common/00. Global.fx"
#include "../Common/00. Light.fx"

float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormalTangent input)
{
    MeshOutput output;
    output.position = mul(input.position, World);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);
    output.tangent = mul(input.tangent, (float3x3)World);
    
    return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
    //float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

technique11 T0
{
    PASS_VP(P0, VS, PS)

    PASS_RS_VP(P1, FillModeWireframe, VS, PS)

    PASS_VP(P2, VS, PS_RED)

    PASS_RS_VP(P3, FillModeWireframe, VS, PS_RED)
};