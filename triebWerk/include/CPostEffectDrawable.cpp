#include "CPostEffectDrawable.h"

triebWerk::CPostEffectDrawable::CPostEffectDrawable()
{
}

triebWerk::CPostEffectDrawable::~CPostEffectDrawable()
{
}

triebWerk::IDrawable::EDrawableType triebWerk::CPostEffectDrawable::GetType()
{
	return IDrawable::EDrawableType::PostEffect;
}

void triebWerk::CPostEffectDrawable::SetTransform(const DirectX::XMMATRIX & a_rTransform)
{

}
