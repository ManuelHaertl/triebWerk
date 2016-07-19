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

		struct SD3D11States
		{
			SD3D11States() : m_pRasterizerState(nullptr), m_pBlendState(nullptr) {};

			ID3D11RasterizerState* m_pRasterizerState;
			ID3D11BlendState* m_pBlendState;
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

		SD3D11States m_D3DStates;

	public:
		CMeshDrawable();
		~CMeshDrawable();

	public:
		EDrawableType GetType() final;
		void SetTransform(const DirectX::XMMATRIX& a_rTransform) final;
		bool IsDrawableValid() final;
	};
}
