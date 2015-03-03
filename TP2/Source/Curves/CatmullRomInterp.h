#ifndef CATMULLROMINTERP_H_
#define CATMULLROMINTERP_H_

#include "Curve.h"
#include "../Foundation/Matrix4.h"
#include "../Foundation/Vector3.h"

class CatmullRomInterp : public Curve
{
public:
    CatmullRomInterp();
    virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante);

private:
    Matrix4 M;
};

#endif //CATMULLROMINTERP_H_
