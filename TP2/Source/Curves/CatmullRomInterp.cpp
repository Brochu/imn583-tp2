#include <iostream>
#include "CatmullRomInterp.h"


CatmullRomInterp::CatmullRomInterp()
{
    // Creation de la matrice de Catmull Rom
    M = Matrix4(-1.0, 3.0, -3.0, 1.0,
        2.0, -5.0, 4.0, -1.0,
        -1.0, 0.0, 1.0, 0.0,
        0.0, 2.0, 0.0, 0.0);
}
void CatmullRomInterp::GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante)
{
    //On clamp pour être sûr que la progression est entre 0 et 1.
    aProgression = (aProgression >= 1.0f) ? 1.0f : (aProgression < 0.0f) ? 0.0f : aProgression;

    //On trouve le point de contrôle de début du segment indiqué par la progression.
    int PointMin = (int)(aProgression*(mto_CtrlPoints.size() - 1));

    // On trouve les pts necessaire au calcul
    int Pm1 = (PointMin != 0) ? (PointMin - 1) : (mto_CtrlPoints.size() - 1);
    int Pp1 = (PointMin + 1) % mto_CtrlPoints.size();
    int Pp2 = (PointMin + 2) % mto_CtrlPoints.size();

    float u = (aProgression * (mto_CtrlPoints.size() - 1)) - PointMin;

    // Calculer P(u)
    Matrix4 B(mto_CtrlPoints[Pm1].X(), mto_CtrlPoints[Pm1].Y(), mto_CtrlPoints[Pm1].Z(), 0.0,
        mto_CtrlPoints[PointMin].X(), mto_CtrlPoints[PointMin].Y(), mto_CtrlPoints[PointMin].Z(), 0.0,
        mto_CtrlPoints[Pp1].X(), mto_CtrlPoints[Pp1].Y(), mto_CtrlPoints[Pp1].Z(), 0.0,
        mto_CtrlPoints[Pp2].X(), mto_CtrlPoints[Pp2].Y(), mto_CtrlPoints[Pp2].Z(), 0.0);

    // see http://www.mvps.org/directx/articles/catmull/ pour le calcul de P(u)
}
