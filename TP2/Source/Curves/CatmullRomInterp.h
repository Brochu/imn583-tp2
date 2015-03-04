// Alexandre Brochu - 12 055 465

#ifndef CATMULLROMINTERP_H_
#define CATMULLROMINTERP_H_

#include "Curve.h"

class CatmullRomInterp : public Curve
{
public:
    virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante);

private:
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

#endif //CATMULLROMINTERP_H_
