#pragma once
#include <CText.h>
#include <CFontDrawable.h>
#include <CCamera.h>

namespace triebWerk
{
	class CInstancedFontBatch
	{
	private:
		ID3D11Buffer* m_pInstanceBuffer;

	public:
		CInstancedFontBatch();
		~CInstancedFontBatch();

	public:
		void static Draw(CFontDrawable* a_pDrawable, ID3D11Device* a_pDevice, ID3D11DeviceContext* a_pDeviceContext, CCamera* a_pCamera);


	};
}