#ifndef LINEARINTERP_H_
#define LINEARINTERP_H_

#include "Curve.h"

class LinearInterp : public Curve
{
public:
    virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante);

private:
};

#endif //LINEARINTERP_H_
