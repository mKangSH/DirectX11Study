#include "pch.h"
#include "Pass.h"

void Pass::Draw(UINT vertexCount, UINT startVertexLocation)
{
	BeginDraw();
	{
		DEVICECONTEXT->Draw(vertexCount, startVertexLocation);
	}
	EndDraw();
}

void Pass::DrawIndexed(UINT indexCount, UINT startIndexLocation, INT baseVertexLocation)
{
	BeginDraw();
	{
		DEVICECONTEXT->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
	}
	EndDraw();
}

void Pass::DrawInstanced(UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT startInstanceLocation)
{
	BeginDraw();
	{
		DEVICECONTEXT->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
	}
	EndDraw();
}

void Pass::DrawIndexedInstanced(UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation)
{
	BeginDraw();
	{
		DEVICECONTEXT->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startIndexLocation);
	}
	EndDraw();
}

void Pass::BeginDraw()
{
	pass->ComputeStateBlockMask(&stateblockMask);

	DEVICECONTEXT->IASetInputLayout(inputLayout.Get());
	pass->Apply(0, DEVICECONTEXT.Get());
}

void Pass::EndDraw()
{
	if (stateblockMask.RSRasterizerState == 1)
	{
		DEVICECONTEXT->RSSetState(stateBlock->RSRasterizerState.Get());
	}
	
	if (stateblockMask.OMDepthStencilState == 1)
	{
		DEVICECONTEXT->OMSetDepthStencilState(stateBlock->OMDepthStencilState.Get(), stateBlock->OMStencilRef);
	}

	if (stateblockMask.OMBlendState == 1)
	{
		DEVICECONTEXT->OMSetBlendState(stateBlock->OMBlendState.Get(), stateBlock->OMBlendFactor, stateBlock->OMSampleMask);
	}
	
	DEVICECONTEXT->HSSetShader(NULL, NULL, 0);
	DEVICECONTEXT->DSSetShader(NULL, NULL, 0);
	DEVICECONTEXT->GSSetShader(NULL, NULL, 0);
}

void Pass::Dispatch(UINT x, UINT y, UINT z)
{
	pass->Apply(0, DEVICECONTEXT.Get());
	DEVICECONTEXT->Dispatch(x, y, z);

	ID3D11ShaderResourceView* null[1] = { 0 };
	DEVICECONTEXT->CSSetShaderResources(0, 1, null);

	ID3D11UnorderedAccessView* nullUav[1] = { 0 };
	DEVICECONTEXT->CSSetUnorderedAccessViews(0, 1, nullUav, NULL);

	DEVICECONTEXT->CSSetShader(NULL, NULL, 0);
}