#include "pch.h";
#include "DXUtil.h";
#include "..\Common\DirectXHelper.h"

namespace DX12StudyProject
{
	Microsoft::WRL::ComPtr<ID3D12Resource> DXUtil::CreateDefaultBuffer(
		ID3D12Device* d3dDevice,
		ID3D12GraphicsCommandList* commandList,
		Microsoft::WRL::ComPtr<ID3D12Resource>& uploadedBuffer,
		const void* data,
		UINT64 dataByteSize,
		D3D12_RESOURCE_STATES resourceState)
	{
		// Create the vertex buffer resource in the GPU's default heap and copy vertex data into it using the upload heap.
		// The upload resource must not be released until after the GPU has finished using it.
		Microsoft::WRL::ComPtr<ID3D12Resource> defaultBuffer;

		CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
		CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(dataByteSize);
		DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
			&defaultHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&bufferDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&defaultBuffer)));

		CD3DX12_HEAP_PROPERTIES uploadHeapProperties(D3D12_HEAP_TYPE_UPLOAD);
		DX::ThrowIfFailed(d3dDevice->CreateCommittedResource(
			&uploadHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&bufferDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&uploadedBuffer)));

		// Upload the vertex buffer to the GPU.
		{
			D3D12_SUBRESOURCE_DATA subResourceData = {};
			subResourceData.pData = data;
			subResourceData.RowPitch = dataByteSize;
			subResourceData.SlicePitch = subResourceData.RowPitch;

			UpdateSubresources(commandList, defaultBuffer.Get(), uploadedBuffer.Get(), 0, 0, 1, &subResourceData);

			CD3DX12_RESOURCE_BARRIER resourceBarrier =
				CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, resourceState);
			commandList->ResourceBarrier(1, &resourceBarrier);
		}

		return defaultBuffer;
	}
}