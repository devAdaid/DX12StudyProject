#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include <ppltasks.h>

namespace DX12StudyProject
{
	// This sample renderer instantiates a basic rendering pipeline.
	class BaseSceneRenderer
	{
	public:
		BaseSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~BaseSceneRenderer();

		void CreateDeviceDependentResources();
		void CreateRootSigniture();
		Concurrency::task<void> CreateVertexShaderTask();
		Concurrency::task<void> CreatePixelShaderTask();
		void CreatePipelineState();
		void CreateAssets();
		void CreateGeometry();

		static Microsoft::WRL::ComPtr<ID3D12Resource> CreateDefaultBuffer(
			ID3D12Device* device,
			ID3D12GraphicsCommandList* cmdList,
			Microsoft::WRL::ComPtr<ID3D12Resource>& uploadedBuffer,
			const void* initData,
			UINT64 byteSize,
			D3D12_RESOURCE_STATES resourceState);

		void CreateWindowSizeDependentResources();

		void Update(DX::StepTimer const& timer);
		bool Render();
		void SaveState();

		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }

	private:
		void LoadState();
		void Rotate(float radians);

	private:
		// Constant buffers must be 256-byte aligned.
		static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_passConstantBuffer;
		//Microsoft::WRL::ComPtr<ID3D12Resource>				m_objectConstantBuffer;
		ModelViewProjectionConstantBuffer						m_passConstantBufferData;
		//DirectX::XMFLOAT4X4									m_objectConstantBufferData;
		UINT8* m_mappedConstantBuffer;
		UINT												m_cbvDescriptorSize;
		D3D12_RECT											m_scissorRect;
		std::vector<byte>									m_vertexShader;
		std::vector<byte>									m_pixelShader;
		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_radiansPerSecond;
		float	m_angle;
		bool	m_tracking;
	};
}

