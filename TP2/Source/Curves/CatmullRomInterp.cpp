// Alexandre Brochu - 12 055 465

#include "CatmullRomInterp.h"

void CatmullRomInterp::GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante)
{
    //On clamp pour être sûr que la progression est entre 0 et 1.
    aProgression = (aProgression >= 1.0f) ? 1.0f : (aProgression < 0.0f) ? 0.0f : aProgression;

    CatmullRomPoints pts = getControlPoints(aProgression);

    // Calcul de la progression courante
    float u = (aProgression * (mto_CtrlPoints.size() - 1)) - pts.p1;

    // On obtient l'information complete sur les pts necessaires
    Vector3 p0 = mto_CtrlPoints[pts.p0];
    Vector3 p1 = mto_CtrlPoints[pts.p1];
    Vector3 p2 = mto_CtrlPoints[pts.p2];
    Vector3 p3 = mto_CtrlPoints[pts.p3];

    aPoint = getCatmullRomPoint(u, p0, p1, p2, p3);

    aTangeante = getCatmullRomTangeant(u, p0, p1, p2, p3);
}

CatmullRomInterp::CatmullRomPoints CatmullRomInterp::getControlPoints(float progress) const
{
    CatmullRomPoints result;

    //On trouve le point de contrôle de début du segment indiqué par la progression.
    result.p1 = (int)(progress*(mto_CtrlPoints.size() - 1));

    // On trouve les pts necessaire au calcul
    result.p0 = result.p1 - 1;
    if (result.p0 < 0) result.p0 = (mto_CtrlPoints.size() - 2);

    result.p2 = (result.p1 + 1) % (mto_CtrlPoints.size() - 1);
    result.p3 = (result.p1 + 2) % (mto_CtrlPoints.size() - 1);

    return result;
}

Vector3 CatmullRomInterp::getCatmullRomPoint(float u, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) const
{
    // Voir http://www.mvps.org/directx/articles/catmull/ pour le calcul de P(u)
    Vector3 a = (-1 * p0 + 3 * p1 - 3 * p2 + p3) * powf(u, 3);
    Vector3 b = (2 * p0 - 5 * p1 + 4 * p2 - p3) * powf(u, 2);
    Vector3 c = (-1 * p0 + p2) * u;
    Vector3 d = (2 * p1);

    return 0.5 * (a + b + c + d);
}

Vector3 CatmullRomInterp::getCatmullRomTangeant(float u, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) const
{
    // Calcul de la tangeante
    Vector3 aprime = (-1 * p0 + 3 * p1 - 3 * p2 + p3) * (3 * powf(u, 2));
    Vector3 bprime = (2 * p0 - 5 * p1 + 4 * p2 - p3) * (2 * u);
    Vector3 cprime = (-1 * p0 + p2);

    return 0.5 * (aprime + bprime + cprime);
}
