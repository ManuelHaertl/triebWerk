#pragma once
#include <d3d11.h>
namespace triebWerk
{
	template<typename t>static inline void SafeDirectXRelease(t** a_pPointerToRelease)
	{
		if (*a_pPointerToRelease != nullptr)
		{
			IUnknown* pPointer = reinterpret_cast<IUnknown*>(*a_pPointerToRelease);
			pPointer->Release();
			*a_pPointerToRelease = nullptr;
		}
	}

	template<typename t>static inline void SafeDelete(t** a_pPointerToDelete)
	{
		if (*a_pPointerToDelete != nullptr)
		{
			delete *a_pPointerToDelete;
			*a_pPointerToDelete = nullptr;
		}
	}
}
