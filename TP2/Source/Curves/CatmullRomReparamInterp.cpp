// Alexandre Brochu - 12 055 465

#include <iostream>
#include "CatmullRomReparamInterp.h"

CatmullRomReparamInterp::CatmullRomReparamInterp()
{
    // Creer la table de relation u <-> s
    // Modifier cette variable pour un echantillonnage different
    lut = new usMapping[sampleCount + 1];
}

void CatmullRomReparamInterp::SetPointsControle(const vector<Vector3> &aPoints)
{
    mto_CtrlPoints = aPoints;

    // Echantillonnage
    float sampleStep = (float)1.0 / sampleCount;
    float sample = 0.0f;

    float s = 0.0f;
    Vector3 lastPoint = mto_CtrlPoints[0];
    Vector3 currentPoint = Vector3::Zero;

    CatmullRomPoints pts;
    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;
    for (int currentSample = 0; currentSample <= sampleCount; ++currentSample)
    {

        pts = getControlPoints(sample);
        p0 = mto_CtrlPoints[pts.p0];
        p1 = mto_CtrlPoints[pts.p1];
        p2 = mto_CtrlPoints[pts.p2];
        p3 = mto_CtrlPoints[pts.p3];
        currentPoint = getCatmullRomPoint(sample, p0, p1, p2, p3);

        float distWlastPoint = (currentPoint - lastPoint).Length();
        s += distWlastPoint;

        lut[currentSample].u = sample;
        lut[currentSample].s = s;

        sample += sampleStep;
    }

    // Normalisation des donnees (s)
    for (int x = 0; x <= sampleCount; ++x)
    {
        lut[x].s /= s;
    }
}

CatmullRomReparamInterp::~CatmullRomReparamInterp()
{
    delete[] lut;
}

void CatmullRomReparamInterp::GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante)
{
    //On clamp pour être sûr que la progression est entre 0 et 1.
    aProgression = (aProgression >= 1.0f) ? 1.0f : (aProgression < 0.0f) ? 0.0f : aProgression;

    CatmullRomPoints pts = getControlPoints(aProgression);
    float s = (aProgression * (mto_CtrlPoints.size() - 1)) - pts.p1;

    // Traduire s en u
    int idx = 0;
    for (int x = 0; x < sampleCount; ++x)
    {
        if (s < lut[x].s) break;
        idx = x;
    }

    float w = (s - lut[idx].s) / (lut[idx + 1].s - lut[idx].s);
    float u = ((1 - w) * lut[idx].u) + ((w) * lut[idx + 1].u);

    // On obtient l'information complete sur les pts necessaires
    Vector3 p0 = mto_CtrlPoints[pts.p0];
    Vector3 p1 = mto_CtrlPoints[pts.p1];
    Vector3 p2 = mto_CtrlPoints[pts.p2];
    Vector3 p3 = mto_CtrlPoints[pts.p3];

    aPoint = getCatmullRomPoint(u, p0, p1, p2, p3);

    aTangeante = getCatmullRomTangeant(u, p0, p1, p2, p3);
}

CatmullRomReparamInterp::CatmullRomPoints CatmullRomReparamInterp::getControlPoints(float progress) const
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

Vector3 CatmullRomReparamInterp::getCatmullRomPoint(float u, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) const
{
    // Voir http://www.mvps.org/directx/articles/catmull/ pour le calcul de P(u)
    Vector3 a = (-1 * p0 + 3 * p1 - 3 * p2 + p3) * powf(u, 3);
    Vector3 b = (2 * p0 - 5 * p1 + 4 * p2 - p3) * powf(u, 2);
    Vector3 c = (-1 * p0 + p2) * u;
    Vector3 d = (2 * p1);

    return 0.5 * (a + b + c + d);
}

Vector3 CatmullRomReparamInterp::getCatmullRomTangeant(float u, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) const
{
    // Calcul de la tangeante
    Vector3 aprime = (-1 * p0 + 3 * p1 - 3 * p2 + p3) * (3 * powf(u, 2));
    Vector3 bprime = (2 * p0 - 5 * p1 + 4 * p2 - p3) * (2 * u);
    Vector3 cprime = (-1 * p0 + p2);

    return 0.5 * (aprime + bprime + cprime);
}