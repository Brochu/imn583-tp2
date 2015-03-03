#include "CatmullRomInterp.h"

void CatmullRomInterp::GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante)
{
    //On clamp pour être sûr que la progression est entre 0 et 1.
    aProgression = (aProgression >= 1.0f) ? 1.0f : (aProgression < 0.0f) ? 0.0f : aProgression;

    //On trouve le point de contrôle de début du segment indiqué par la progression.
    int PointMin = (int)(aProgression*(mto_CtrlPoints.size() - 1));

    // On trouve les pts necessaire au calcul
    int Pm1 = PointMin - 1;
    if (Pm1 < 0) Pm1 = (mto_CtrlPoints.size() - 2);

    int Pp1 = (PointMin + 1) % (mto_CtrlPoints.size() - 1);
    int Pp2 = (PointMin + 2) % (mto_CtrlPoints.size() - 1);

    // Calcul de la progression courante
    float u = (aProgression * (mto_CtrlPoints.size() - 1)) - PointMin;

    // On obtient l'information complete sur les pts necessaires
    Vector3 p0 = mto_CtrlPoints[Pm1];
    Vector3 p1 = mto_CtrlPoints[PointMin];
    Vector3 p2 = mto_CtrlPoints[Pp1];
    Vector3 p3 = mto_CtrlPoints[Pp2];

    // Voir http://www.mvps.org/directx/articles/catmull/ pour le calcul de P(u)
    Vector3 a = (-1 * p0 + 3 * p1 - 3 * p2 + p3) * powf(u, 3);
    Vector3 b = (2 * p0 - 5 * p1 + 4 * p2 - p3) * powf(u, 2);
    Vector3 c = (-1 * p0 + p2) * u;
    Vector3 d = (2 * p1);

    aPoint = 0.5 * (a + b + c + d);

    // Calcul de la tangeante
    Vector3 aprime = (-1 * p0 + 3 * p1 - 3 * p2 + p3) * (3 * powf(u, 2));
    Vector3 bprime = (2 * p0 - 5 * p1 + 4 * p2 - p3) * (2 * u);
    Vector3 cprime = (-1 * p0 + p2);

    aTangeante = 0.5 * (aprime + bprime + cprime);
}
