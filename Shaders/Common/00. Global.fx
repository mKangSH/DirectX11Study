#ifndef _GLOBAL_FX_
#define _GLOBAL_FX_

///
// Const Buffer
///
cbuffer GlobalBuffer
{
    matrix View;
    matrix Projection;
    matrix ViewProjection;
    
    matrix ViewInverse;
};

cbuffer TransformBuffer
{
    matrix World;
    matrix WorldInverseTranspose;
};

///
// Vertex Data
///
struct Vertex
{
    float4 position : POSITION;
};

struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexColor
{
    float4 position : POSITION;
    float4 Color : COLOR;
};

struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VertexTextureNormalTangentBlend
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 blendIndices : BLEND_INDICES;
    float4 blendWeights : BLEND_WEIGHTS;
};

///
// Vertex Output
///
struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct MeshOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

///
// SamplerState
///
SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState PointSampler
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

///
// RasterizerState
///
RasterizerState FillModeSolid
{
    FillMode = Solid;
};

RasterizerState FillModeWireframe
{
    FillMode = Wireframe;
};

RasterizerState FrontCounterClockwiseTrue
{
    FrontCounterClockwise = true;
};

///
// Macro
///
#define PASS_VP(name, vs, ps)                       \
pass name                                           \
{                                                   \
    SetVertexShader(CompileShader(vs_5_0, vs()));   \
    SetPixelShader(CompileShader(ps_5_0, ps()));    \
}                     

#define PASS_RS_VP(name, rs, vs, ps)                \
pass name                                           \
{                                                   \
    SetRasterizerState(rs);                         \
    SetVertexShader(CompileShader(vs_5_0, vs()));   \
    SetPixelShader(CompileShader(ps_5_0, ps()));    \
}           
///
// Function
///
float3 CameraPosition()
{
    return ViewInverse._41_42_43;
}
#endif