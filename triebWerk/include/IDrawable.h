#pragma once
#include <IRenderCommand.h>

namespace triebWerk
{
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
		IRenderCommand* m_RenderCommand;
		EDrawableType m_Type;

	public:
		IDrawable();
		virtual ~IDrawable();

	public:
		virtual IRenderCommand* GetRenderCommand() = 0;
		virtual EDrawableType GetType() = 0;

		void SetActive(bool a_State);
		bool IsActive();
	};
}