// Alexandre Brochu - 12 055 465

#ifndef CURVE_H_
#define CURVE_H_

#include <vector>

#include "../Foundation/Vector3.h"

using namespace std;

class Curve
{
public:

	Curve(){};
	virtual ~Curve(){};

	//!@brief Assigne les points de contrôles désirés à notre courbe.
	//!@param[in] aPoints Liste des points de contrôles.
	//!
	//!Note :	Cette fonction est appellée automatiquement dans le code, vous n'avez pas besoin
	//!			de l'appeller.
	virtual void SetPointsControle(const vector<Vector3> &aPoints);

	//!@brief		Cette méthode doit retourner un point et sa tangeante pour une certaine
	//!				progression sur la courbe.
	//!@param[in]	aProgression Progression normalisée entre 0 et 1 sur la courbe. La progression doit être
	//!				remenée entre 0 et 1  si elle dépasse la contrainte dans les implémentations de cette méthode.
	//!@param[out]	aPoint Point évalué sur la courbe.
	//!@param[out]	aTangeante Tangeante évaluée sur la courbe.
	//!
	//!Note :	Cette fonction est appellée automatiquement dans le code, vous n'avez pas besoin
	//!			de l'appeller seulement de l'implémenter.
	virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante) = 0;

protected:

	//!@brief Liste des points de contrôle de notre courbe.
	vector<Vector3> mto_CtrlPoints;

};

inline void Curve::SetPointsControle(const vector<Vector3> &aPoints)
{
	mto_CtrlPoints = aPoints;
}

#endif //CURVE_H_
