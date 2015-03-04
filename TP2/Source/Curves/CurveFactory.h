// Alexandre Brochu - 12 055 465

#ifndef CURVE_FACTORY_H_
#define CURVE_FACTORY_H_

#include "Curve.h"

class CurveFactory
{
public : 

	//!@brief Enumeration de chacun des types de courbe à implémenter.
	enum CurveType
	{
		Type_Jump,					//Courbe qui saute d'un point de contrôle à l'autre, sans interpoler.
		Type_Linear,				//Courbe avec interpolation linéaire.
		Type_CatmullRom,			//Courbe avec interpolation de catmull rom.
		Type_CatmullRomWReparam,	//Courbe avec interpolation de catmull rom et reparamétrisation par longueur d'arc.
	};

	//!@brief Fonction statique servant retourner une nouvelle instance de la courbe demandée par le paramètre ae_Type.
	//!@param[in] ae_Type Paramètre correspondant à la courbe que le factory doit retourner.
	static Curve* CreateCurve(CurveType ae_Type);

private:
	CurveFactory(){};
	~CurveFactory(){};
};

#endif //CURVE_FACTORY_H_
