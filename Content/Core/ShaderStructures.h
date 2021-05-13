﻿#pragma once

namespace DX12StudyProject
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ObjectConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
	};

	struct PassConstantBuffer
	{
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}