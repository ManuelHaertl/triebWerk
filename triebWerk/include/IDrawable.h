#pragma once

#include <DirectXMath.h>

namespace triebWerk
{

	class CEntity;

	class IDrawable
	{
	public:
		enum class EDrawableType
		{
			Mesh,
			UI,
			Empty
		};

	private:
		bool m_ActiveState;
		unsigned int m_RenderTargetSlot;

	protected:
		EDrawableType m_Type;

	public:
		IDrawable();
		virtual ~IDrawable();

	public:
		virtual EDrawableType GetType() = 0;
		virtual void SetTransform(const DirectX::XMMATRIX& a_rTransform) = 0;

		//Set the RenderTarget where it will be drawn
		//If the slot doesnt exist it wont be drawn
		//The slot 0 is the default RenderTarget
		void SetRenderTarget(unsigned int a_Slot);
		unsigned int GetRenderTargetSlot() const;
		void SetActive(bool a_State);
		bool IsActive() const;
	};
}
