#ifndef CUBE_H_
#define CUBE_H_

#include <string>

#include "RenderObject.h"
#include "../Foundation/Matrix4.h"
#include "../ThirdParty/glut.h"

using namespace std;

class Cube : public RenderObject
{
public:

	Cube();
	~Cube();

	virtual void SetTexture(const string& ao_FileName);
	virtual void SetTransformation(const Matrix4& ao_TransformationMatrix);

	virtual void Render(float af_DeltaT);

protected:

	GLuint	mu32_TextureId;
	Matrix4 mo_TransformationMatrix;
};

#endif //CUBE_H_