#pragma once

#include "VertexData.h"
#include <vector>

namespace DX12StudyProject
{
	struct MeshData
	{
		std::vector<VertexData> Vertices;
		std::vector<uint32> Indices;

		std::vector<uint16>& GetIndices16()
		{
			if (mIndices16.empty())
			{
				mIndices16.resize(Indices.size());
				for (size_t i = 0; i < Indices.size(); ++i)
					mIndices16[i] = static_cast<uint16>(Indices[i]);
			}

			return mIndices16;
		}

	private:
		std::vector<uint16> mIndices16;
	};
}