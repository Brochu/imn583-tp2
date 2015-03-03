#ifndef CATMULLROMINTERP_H_
#define CATMULLROMINTERP_H_

#include "Curve.h"

class CatmullRomInterp : public Curve
{
public:
    virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante);
};

#endif //CATMULLROMINTERP_H_
