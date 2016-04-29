#pragma once
namespace triebWerk
{
	class IMapLayer
	{
	public:
		struct ETypes
		{
			enum Type
			{
				MapLayer,
				MapImageLayer,
                ObjectLayer
			};
		};
	public:
		IMapLayer();
		virtual ~IMapLayer();
	public:
		virtual ETypes::Type GetType() = 0;

	};
}

