#pragma once

#include "pch.h";

namespace DX12StudyProject
{
	class DXUtil
	{
	public:
		static Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
			ID3D12Device* d3dDevice,
			ID3D12GraphicsCommandList* commandList,
			Microsoft::WRL::ComPtr<ID3D12Resource>& uploadedBuffer,
			const void* bufferData,
			UINT64 bufferSize,
			D3D12_RESOURCE_STATES resourceState);
	};
}