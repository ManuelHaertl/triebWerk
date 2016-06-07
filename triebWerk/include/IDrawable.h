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


	protected:
		EDrawableType m_Type;

	public:
		IDrawable();
		virtual ~IDrawable();

	public:
		virtual EDrawableType GetType() = 0;

		virtual void SetTransform(const DirectX::XMMATRIX& a_rTransform) = 0;

		void SetActive(bool a_State);
		bool IsActive() const;
	};
}
