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

///
// Vertex Output
///
struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
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

///
// Macro
///


#endif