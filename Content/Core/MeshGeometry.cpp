#include "pch.h"
#include "MeshGeometry.h"
#include "DXUtil.h"
#include "..\Common\DirectXHelper.h"

namespace DX12StudyProject
{
	MeshGeometry::MeshGeometry(string name, 
		vector<VertexPositionColor> vertices, 
		vector<unsigned short> indices,
		ID3D12Device* d3dDevice,
		ID3D12GraphicsCommandList* pCommandList)
		: Name(name), Vertices(vertices), Indices(indices)
	{
		VerticesByteSize = (UINT)Vertices.size() * sizeof(VertexPositionColor);
		IndicesByteSize = (UINT)Indices.size() * sizeof(unsigned short);
		VertexByteStride = sizeof(VertexPositionColor);
		IndexFormat = DXGI_FORMAT_R16_UINT;

		Microsoft::WRL::ComPtr<ID3D12Resource> vertexBufferUpload;
		VertexBuffer = DXUtil::CreateDefaultBuffer(d3dDevice, pCommandList, vertexBufferUpload, Vertices.data(), VerticesByteSize, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
		NAME_D3D12_OBJECT(VertexBuffer);

		Microsoft::WRL::ComPtr<ID3D12Resource> indexBufferUpload;
		IndexBuffer = DXUtil::CreateDefaultBuffer(d3dDevice, pCommandList, indexBufferUpload, Indices.data(), IndicesByteSize, D3D12_RESOURCE_STATE_INDEX_BUFFER);
		NAME_D3D12_OBJECT(IndexBuffer);
	}

	D3D12_VERTEX_BUFFER_VIEW MeshGeometry::GetVertexBufferView() const
	{
		D3D12_VERTEX_BUFFER_VIEW vbv;
		vbv.BufferLocation = VertexBuffer->GetGPUVirtualAddress();
		vbv.StrideInBytes = VertexByteStride;
		vbv.SizeInBytes = VerticesByteSize;
		return vbv;
	}

	D3D12_INDEX_BUFFER_VIEW MeshGeometry::GetIndexBufferView() const
	{
		D3D12_INDEX_BUFFER_VIEW ibv;
		ibv.BufferLocation = IndexBuffer->GetGPUVirtualAddress();
		ibv.Format = IndexFormat;
		ibv.SizeInBytes = IndicesByteSize;
		return ibv;
	}
}