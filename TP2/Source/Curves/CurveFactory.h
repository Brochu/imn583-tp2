// Alexandre Brochu - 12 055 465

#ifndef CURVE_FACTORY_H_
#define CURVE_FACTORY_H_

#include "Curve.h"

class CurveFactory
{
public : 

	//!@brief Enumeration de chacun des types de courbe � impl�menter.
	enum CurveType
	{
		Type_Jump,					//Courbe qui saute d'un point de contr�le � l'autre, sans interpoler.
		Type_Linear,				//Courbe avec interpolation lin�aire.
		Type_CatmullRom,			//Courbe avec interpolation de catmull rom.
		Type_CatmullRomWReparam,	//Courbe avec interpolation de catmull rom et reparam�trisation par longueur d'arc.
	};

	//!@brief Fonction statique servant retourner une nouvelle instance de la courbe demand�e par le param�tre ae_Type.
	//!@param[in] ae_Type Param�tre correspondant � la courbe que le factory doit retourner.
	static Curve* CreateCurve(CurveType ae_Type);

private:
	CurveFactory(){};
	~CurveFactory(){};
};

#endif //CURVE_FACTORY_H_
