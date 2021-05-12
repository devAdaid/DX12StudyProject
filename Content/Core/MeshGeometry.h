#pragma once

#include "pch.h"
#include "ShaderStructures.h"
#include <string>
#include <vector>

using namespace std;

namespace DX12StudyProject
{
	class MeshGeometry
	{
	public:
		string Name;

		vector<VertexPositionColor> Vertices;
		vector<unsigned short> Indices;

		UINT VerticesByteSize;
		UINT IndicesByteSize;
		UINT VertexByteStride = 0;
		DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;

		Microsoft::WRL::ComPtr<ID3D12Resource> VertexBuffer = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> IndexBuffer = nullptr;

		MeshGeometry(string name,
			vector<VertexPositionColor> vertices,
			vector<unsigned short> indices,
			ID3D12Device* d3dDevice,
			ID3D12GraphicsCommandList* commandList);
		~MeshGeometry();

		D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() const;
		D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() const;
	};
}