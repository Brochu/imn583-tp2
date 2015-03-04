#ifndef CATMULLROMREPARAMINTERP_H_
#define CATMULLROMREPARAMINTERP_H_

#include "Curve.h"

class CatmullRomReparamInterp : public Curve
{
public:
    CatmullRomReparamInterp();
    ~CatmullRomReparamInterp();

    virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante);
    virtual void SetPointsControle(const vector<Vector3> &aPoints);

private:
    int sampleCount = 50;
    typedef struct usMapping {
        float u;
        float s;
    } usMapping;

    usMapping* lut;

    typedef struct CatmullRomPoints{
        int p0;
        int p1;
        int p2;
        int p3;
    } CatmullRomPoints;

    CatmullRomPoints getControlPoints(float) const;
    Vector3 getCatmullRomPoint(float, Vector3, Vector3, Vector3, Vector3) const;
    Vector3 getCatmullRomTangeant(float, Vector3, Vector3, Vector3, Vector3) const;
};

#endif //CATMULLROMREPARAMINTERP_H_
