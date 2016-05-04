#pragma once
#include <IDrawable.h>
#include <CMaterial.h>
#include <CMesh.h>

namespace triebWerk
{
	class CMeshDrawable : public IDrawable
	{
	public:
		enum class EDrawType
		{
			Draw,
			DrawInstanced,
			DrawIndexed,
			DrawIndexedInstanced,
		};

	public:
		//BEBUG
		float DEBUG_Distance;

		CMaterial m_Material;
		CMesh* m_pMesh;

		CMeshDrawable::EDrawType m_DrawType;
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
		DirectX::XMMATRIX m_Transformation;
		UINT m_Stride;
		bool m_Transparency;

	public:
		CMeshDrawable();
		~CMeshDrawable();

	public:
		EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform);
	};
}
