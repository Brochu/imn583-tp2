#include "Cube.h"

#include "../Foundation/RGBImage.h"
#include "../Foundation/BitmapHandling.h"

Cube::Cube()
:	mu32_TextureId(0)
,	mo_TransformationMatrix()
{}

void Cube::SetTransformation(const Matrix4& ao_TransformationMatrix)
{
	mo_TransformationMatrix = ao_TransformationMatrix;
}

void Cube::SetTexture(const string& ao_FileName)
{
	if(mu32_TextureId != 0)
	{
		glDeleteTextures(1,&mu32_TextureId);
	}

	glGenTextures(1,&mu32_TextureId);

	RGBImage o_TmpImage;
	glBindTexture(GL_TEXTURE_2D,mu32_TextureId);

	LoadBmp(ao_FileName,o_TmpImage);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpImage.GetWidth(),o_TmpImage.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpImage.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Cube::Render(float af_DeltaT)
{	
	float tf_Black[4] = {0,0,0,0};
	float tf_White[4] = {1,1,1,1};

	glMaterialfv(GL_FRONT,GL_AMBIENT,tf_White);
	glMaterialfv(GL_FRONT,GL_EMISSION,tf_Black);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,tf_White);
	glMaterialfv(GL_FRONT,GL_SPECULAR,tf_Black);

	glBindTexture(GL_TEXTURE_2D,mu32_TextureId);

	glPushMatrix();
	glMultMatrixf(mo_TransformationMatrix.ToOpenGLMatrix());

	glBegin(GL_QUADS);

	//Top
	glNormal3f(0,1,0);
	glTexCoord2f(0,0),glVertex3f(-1,  1, -1);
	glTexCoord2f(0,1),glVertex3f(-1,  1,  1);
	glTexCoord2f(1,1),glVertex3f( 1,  1,  1);
	glTexCoord2f(1,0),glVertex3f( 1,  1, -1);

	//Bottom
	glNormal3f(0,-1,0);
	glTexCoord2f(1,0),glVertex3f( 1, -1, -1);
	glTexCoord2f(1,1),glVertex3f( 1, -1,  1);
	glTexCoord2f(0,1),glVertex3f(-1, -1,  1);
	glTexCoord2f(0,0),glVertex3f(-1, -1, -1);

	//Back
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0),glVertex3f(-1,  1, -1);
	glTexCoord2f(1,0),glVertex3f( 1,  1, -1);
	glTexCoord2f(1,1),glVertex3f( 1, -1, -1);
	glTexCoord2f(0,1),glVertex3f(-1, -1, -1);

	//Front
	glNormal3f(0,0,1);
	glTexCoord2f(0,1),glVertex3f(-1, -1,  1);
	glTexCoord2f(1,1),glVertex3f( 1, -1,  1);
	glTexCoord2f(1,0),glVertex3f( 1,  1,  1);
	glTexCoord2f(0,0),glVertex3f(-1,  1,  1);
	
	//Right
	glNormal3f(1,0,0);
	glTexCoord2f(0,0),glVertex3f( 1,  1,  1);
	glTexCoord2f(0,1),glVertex3f( 1, -1,  1);
	glTexCoord2f(1,1),glVertex3f( 1, -1, -1);
	glTexCoord2f(1,0),glVertex3f( 1,  1, -1);

	//Left
	glNormal3f(-1,0,0);
	glTexCoord2f(1,0),glVertex3f(-1,  1, -1);
	glTexCoord2f(1,1),glVertex3f(-1, -1, -1);
	glTexCoord2f(0,1),glVertex3f(-1, -1,  1);
	glTexCoord2f(0,0),glVertex3f(-1,  1,  1);
	
	glEnd();

	glPopMatrix();
}

Cube::~Cube()
{
	if(mu32_TextureId != 0)
	{
		glDeleteTextures(1,&mu32_TextureId);
		mu32_TextureId = 0;
	}
}

