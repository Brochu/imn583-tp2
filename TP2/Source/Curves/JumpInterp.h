#ifndef JUMPINTERP_H_
#define JUMPINTERP_H_

#include "Curve.h"

class JumpInterp : public Curve
{
public:
	virtual void GetPointTangeante(float aProgression, Vector3 &aPoint, Vector3 &aTangeante);
};

#endif //JUMPINTERP_H_
