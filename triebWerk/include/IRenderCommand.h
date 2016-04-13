#pragma once

namespace triebWerk
{
	class IRenderCommand
	{
	public:
		enum class ECommandType
		{
			Mesh,
			UI,
			None
		};

	public:

	protected:
		ECommandType m_CommandType;

	public:
		IRenderCommand();
		virtual ~IRenderCommand();

	public:
		virtual ECommandType GetType() = 0;
	};
}
