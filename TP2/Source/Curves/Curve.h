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

	//!@brief Assigne les points de contr�les d�sir�s � notre courbe.
	//!@param[in] aPoints Liste des points de contr�les.
	//!
	//!Note :	Cette fonction est appell�e automatiquement dans le code, vous n'avez pas besoin
	//!			de l'appeller.
	virtual void SetPointsControle(const vector<Vector3> &aPoints);

	//!@brief		Cette m�thode doit retourner un point et sa tangeante pour une certaine
	//!				progression sur la courbe.
	//!@param[in]	aProgression Progression normalis�e entre 0 et 1 sur la courbe. La progression doit �tre
	//!				remen�e entre 0 et 1  si elle d�passe la contrainte dans les impl�mentations de cette m�thode.
	//!@param[out]	aPoint Point �valu� sur la courbe.
	//!@param[out]	aTangeante Tangeante �valu�e sur la courbe.
	//!
	//!Note :	Cette fonction est appell�e automatiquement dans le code, vous n'avez pas besoin
	//!			de l'appeller seulement de l'impl�menter.
	virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante) = 0;

protected:

	//!@brief Liste des points de contr�le de notre courbe.
	vector<Vector3> mto_CtrlPoints;

};

inline void Curve::SetPointsControle(const vector<Vector3> &aPoints)
{
	mto_CtrlPoints = aPoints;
}

#endif //CURVE_H_
