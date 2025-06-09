#include "../Common/00. Global.fx"
#include "../Common/00. Light.fx"

#define MAX_MODEL_TRANSFORMS 255
#define MAX_MODEL_KEYFRAMES 510

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

struct KeyframeDesc
{
    int animationIndex;
    uint currentFrame;
    uint nextFrame;
    float ratio;
    float sumTime;
    float speed;
    float2 padding;
};

struct TweenFrameDesc
{
    float tweenDuration;
    float tweenRatio;
    float tweenSumTime;
    float padding;
    KeyframeDesc current;
    KeyframeDesc next;
};

cbuffer TweenFrameBuffer
{
    TweenFrameDesc Tweenframes;
};
    
cbuffer BoneBuffer
{
    matrix BoneTransforms[MAX_MODEL_TRANSFORMS];
};
  
uint BoneIndex;
Texture2DArray TransformMap;

matrix GetAnimationMatrix(VertexTextureNormalTangentBlend input)
{
    float indices[4] = { input.blendIndices.x, input.blendIndices.y, input.blendIndices.z, input.blendIndices.w };
    float weights[4] = { input.blendWeights.x, input.blendWeights.y, input.blendWeights.z, input.blendWeights.w };

    int animationIndex[2];
    int currentFrame[2];
    int nextFrame[2];
    float ratio[2];
    
    animationIndex[0] = Tweenframes.current.animationIndex;
    currentFrame[0] = Tweenframes.current.currentFrame;
    nextFrame[0] = Tweenframes.current.nextFrame;
    ratio[0] = Tweenframes.current.ratio;
    
    animationIndex[1] = Tweenframes.next.animationIndex;
    currentFrame[1] = Tweenframes.next.currentFrame;
    nextFrame[1] = Tweenframes.next.nextFrame;
    ratio[1] = Tweenframes.next.ratio;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    matrix current = 0;
    matrix next = 0;
    matrix transform = 0;
    
    for (int i = 0; i < 4; i++)
    {
        c0 = TransformMap.Load(int4(indices[i] * 4 + 0, currentFrame[0], animationIndex[0], 0));
        c1 = TransformMap.Load(int4(indices[i] * 4 + 1, currentFrame[0], animationIndex[0], 0));
        c2 = TransformMap.Load(int4(indices[i] * 4 + 2, currentFrame[0], animationIndex[0], 0));
        c3 = TransformMap.Load(int4(indices[i] * 4 + 3, currentFrame[0], animationIndex[0], 0));
        current = matrix(c0, c1, c2, c3);
        
        n0 = TransformMap.Load(int4(indices[i] * 4 + 0, nextFrame[0], animationIndex[0], 0));
        n1 = TransformMap.Load(int4(indices[i] * 4 + 1, nextFrame[0], animationIndex[0], 0));
        n2 = TransformMap.Load(int4(indices[i] * 4 + 2, nextFrame[0], animationIndex[0], 0));
        n3 = TransformMap.Load(int4(indices[i] * 4 + 3, nextFrame[0], animationIndex[0], 0));
        next = matrix(n0, n1, n2, n3);
        
        matrix result = lerp(current, next, ratio[0]);
        
        if (animationIndex[1] >= 0)
        {
            c0 = TransformMap.Load(int4(indices[i] * 4 + 0, currentFrame[1], animationIndex[1], 0));
            c1 = TransformMap.Load(int4(indices[i] * 4 + 1, currentFrame[1], animationIndex[1], 0));
            c2 = TransformMap.Load(int4(indices[i] * 4 + 2, currentFrame[1], animationIndex[1], 0));
            c3 = TransformMap.Load(int4(indices[i] * 4 + 3, currentFrame[1], animationIndex[1], 0));
            current = matrix(c0, c1, c2, c3);
        
            n0 = TransformMap.Load(int4(indices[i] * 4 + 0, nextFrame[1], animationIndex[1], 0));
            n1 = TransformMap.Load(int4(indices[i] * 4 + 1, nextFrame[1], animationIndex[1], 0));
            n2 = TransformMap.Load(int4(indices[i] * 4 + 2, nextFrame[1], animationIndex[1], 0));
            n3 = TransformMap.Load(int4(indices[i] * 4 + 3, nextFrame[1], animationIndex[1], 0));
            next = matrix(n0, n1, n2, n3);
            
            matrix nextResult = lerp(current, next, ratio[1]);
            result = lerp(result, nextResult, Tweenframes.tweenRatio);
        }
        
        transform += mul(weights[i], result);
    }
    
    return transform;
}

MeshOutput VS(VertexTextureNormalTangentBlend input)
{
    MeshOutput output;
    
    // TODO
    matrix animationMatrix = GetAnimationMatrix(input);
    
    output.position = mul(input.position, animationMatrix);
    output.position = mul(output.position, World);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) World);
    output.tangent = mul(input.tangent, (float3x3) World);
    
    return output;
}

MeshOutput VS_Model(VertexTextureNormalTangent input)
{
    MeshOutput output;
    output.position = mul(input.position, BoneTransforms[BoneIndex]);
    output.position = mul(output.position, World);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) World);
    output.tangent = mul(input.tangent, (float3x3) World);
    
    return output;
}

MeshOutput VS_Mesh(VertexTextureNormalTangent input)
{
    MeshOutput output;
    output.position = mul(input.position, World);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, ViewProjection);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3) World);
    output.tangent = mul(input.tangent, (float3x3) World);
    
    return output;
}

VS_OUT VS_Sky(VertexTextureNormalTangent input)
{
    VS_OUT output;
    
    float4 viewPosition = mul(float4(input.position.xyz, 0), View);
    float4 clipPosition = mul(viewPosition, Projection);
    
    output.position = clipPosition;
    // Adjust the z position to avoid depth issues with the skybox
    output.position.z = clipPosition.w * 0.9999999f;
    
    output.uv = input.uv;
    
    return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    //float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

float4 PS_Mesh(MeshOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    //float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

float4 PS_Sky(VS_OUT input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

technique11 T0
{
    PASS_VP(P0, VS, PS)

    PASS_RS_VP(P1, FillModeWireframe, VS, PS)

    PASS_VP(P2, VS, PS_RED)

    PASS_RS_VP(P3, FillModeWireframe, VS, PS_RED)
};

technique11 T1
{
    PASS_VP(P0, VS_Model, PS)

    PASS_RS_VP(P1, FillModeWireframe, VS_Model, PS)

    PASS_VP(P2, VS_Model, PS_RED)

    PASS_RS_VP(P3, FillModeWireframe, VS_Model, PS_RED)
};

technique11 T2
{
    PASS_VP(P0, VS_Mesh, PS_Mesh)

    PASS_RS_VP(P1, FillModeWireframe, VS_Mesh, PS_Mesh)

    PASS_VP(P2, VS_Mesh, PS_RED)

    PASS_RS_VP(P3, FillModeWireframe, VS_Mesh, PS_RED)
};

technique11 T3
{
    pass P0
    {
        SetRasterizerState(FrontCounterClockwiseTrue);
        SetVertexShader(CompileShader(vs_5_0, VS_Sky()));
        SetPixelShader(CompileShader(ps_5_0, PS_Sky()));
    }
};
