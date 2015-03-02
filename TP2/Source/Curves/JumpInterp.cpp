#include "JumpInterp.h"

void JumpInterp::GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante)
{
	//On clamp pour être sûr que la progression est entre 0 et 1.
	aProgression = (aProgression >= 1.0f)? 1.0f : (aProgression < 0.0f)? 0.0f : aProgression;

	//On trouve le point de contrôle de début du segment indiqué par la progression.
	int PointMin = (int)(aProgression*(mto_CtrlPoints.size()-1));

	aPoint = mto_CtrlPoints[PointMin];
	//La tangeante est calculée fort simplement en donnant directement un vecteur donné par le segment de courbe.
	aTangeante = Vector3(0,0,0);
}
