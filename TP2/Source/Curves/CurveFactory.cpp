#include "CurveFactory.h"

#include "JumpInterp.h"
#include "LinearInterp.h"
#include "CatmullRomInterp.h"
#include "CatmullRomReparamInterp.h"

Curve* CurveFactory::CreateCurve(CurveFactory::CurveType ae_Type)
{
	switch(ae_Type)
	{
	case Type_Jump :
		return new JumpInterp();
		break;

	case Type_Linear:
		return new LinearInterp();
		break;

	case Type_CatmullRom:
		return new CatmullRomInterp();
		break;

	case Type_CatmullRomWReparam:
		return new CatmullRomReparamInterp();
		break;

	default:
		return NULL;
		break;
	}
}
