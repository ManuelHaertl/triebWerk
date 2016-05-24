#pragma once
#include <IShader.h>
#include <CGraphics.h>
#include <CDebugLogfile.h>

namespace triebWerk
{
	class CVertexShader : public IShader
	{
	public:
		ID3D11VertexShader* m_pD3DVertexShader;
		size_t m_SizeOfInstanceDataBytes;
		char* m_pCustomInstanceData;

	public:
		CVertexShader();
		~CVertexShader();

	public:
		void* GetD3D11Shader() final;

		//Set data per instance
		//Keep in mind that for the moment a matrix has 4 indices because four times float4
		//Also the first value must be a transfromation matrix of 4x4 to transform the object
		void SetInstanceData(int a_Index, void* a_pAdressOfData, size_t a_ByteSize);

		//Creates a Buffer for per Instance Data
		void CreateInstanceData();
	};
}