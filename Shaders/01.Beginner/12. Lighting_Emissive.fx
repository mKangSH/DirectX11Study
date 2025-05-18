#include "../Common/00. Global.fx"

float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, World);
    output.worldPosition = mul(input.position, World);
    
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);

    return output;
}

// Emissive (림라이트)
// 외각선을 구할 때 사용

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -View._41_42_43;
    float3 eyeDirection = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(eyeDirection, input.normal));
    float emissive = 1.0f - value;
    
    emissive = smoothstep(0.0f, 1.0f, emissive);
    emissive = pow(emissive, 2);
    
    float4 color = MaterialEmissive * emissive;
    
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