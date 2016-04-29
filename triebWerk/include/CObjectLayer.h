#pragma once
#include <IMapLayer.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <CLayerObject.h>

namespace triebWerk
{
	class CObjectLayer : public IMapLayer
	{
	public:

		std::string m_Name;

		std::vector<CLayerObject> m_Objects;

	public:
		CObjectLayer();
		~CObjectLayer();

	private:
		ETypes::Type GetType() override;
	};

}

