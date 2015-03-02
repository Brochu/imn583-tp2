#include "CurveFactory.h"

#include "JumpInterp.h"

Curve* CurveFactory::CreateCurve(CurveFactory::CurveType ae_Type)
{
	switch(ae_Type)
	{
	case Type_Jump :
		return new JumpInterp();
		break;

	case Type_Linear:
		return NULL;
		break;

	case Type_CatmullRom:
		return NULL;
		break;

	case Type_CatmullRomWReparam:
		return NULL;
		break;

	default:
		return NULL;
		break;
	}
}
