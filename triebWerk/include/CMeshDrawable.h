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

		enum class ERenderMode
		{
			Opaque,
			CutOut,
			Transparent
		};

	public:
		//BEBUG
		float DEBUG_Distance;

		CMaterial m_Material;
		CMesh* m_pMesh;

		CMeshDrawable::EDrawType m_DrawType;
		CMeshDrawable::ERenderMode m_RenderMode;

		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
		DirectX::XMMATRIX m_Transformation;
		UINT m_Stride;

	public:
		CMeshDrawable();
		~CMeshDrawable();

	public:
		//Return if this is a valid drawable to render properly
		static bool IsValidDrawable(const CMeshDrawable* a_pDrawableToTest);
	public:
		EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform);
	};
}
