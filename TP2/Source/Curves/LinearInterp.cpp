#include <iostream>
#include "LinearInterp.h"

void LinearInterp::GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante)
{
    //On clamp pour être sûr que la progression est entre 0 et 1.
    aProgression = (aProgression >= 1.0f) ? 1.0f : (aProgression < 0.0f) ? 0.0f : aProgression;

    //On trouve le point de contrôle de début du segment indiqué par la progression.
    int PointMin = (int)(aProgression*(mto_CtrlPoints.size() - 1));
    int PointNext = (PointMin + 1) % mto_CtrlPoints.size();

    float currProgression = aProgression * (mto_CtrlPoints.size() - 1);
    float normProgression = currProgression - PointMin;

    aPoint = ((1 - normProgression) * mto_CtrlPoints[PointMin]) + ((normProgression) * mto_CtrlPoints[PointNext]);

    aTangeante = mto_CtrlPoints[PointMin] - mto_CtrlPoints[PointNext];
}
