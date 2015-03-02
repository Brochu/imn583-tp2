#include "Firefly.h"

#include "../Utilities/PointReader.h"
#include "../Foundation/BitmapHandling.h"

using namespace std;

Firefly::Firefly(const string &ao_FireflyTexture, const string &ao_ReflectionTexture, const string &ao_PathFile)
:	mf_ProgressOnPath(0.0f)
,	mf_Speed(1.0f)
,	mo_ReflectionColor(0,0,0,1)
,	mpo_CurrentPath(NULL)
,	mo_CachedPathWaypoints(0)
,	mf_TrailWidth(0.5f)
{	
	mo_CachedPathWaypoints = ReadPoints(ao_PathFile);

	//////////////////////////////////////////////////////////////////////////
	//Particule
	glGenTextures(1,&mu32_ParticleTextureId);

	RGBImage o_TmpImage;
	glBindTexture(GL_TEXTURE_2D,mu32_ParticleTextureId);

	LoadBmp(ao_FireflyTexture,o_TmpImage);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpImage.GetWidth(),o_TmpImage.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpImage.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	//////////////////////////////////////////////////////////////////////////
	//Reflection
	glGenTextures(1,&mu32_ReflectionTextureId);

	glBindTexture(GL_TEXTURE_2D,mu32_ReflectionTextureId);

	LoadBmp(ao_ReflectionTexture,o_TmpImage);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpImage.GetWidth(),o_TmpImage.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpImage.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Firefly::Render(float af_DeltaT)
{
	if(mpo_CurrentPath == NULL)
	{
		return;
	}

	mf_ProgressOnPath += af_DeltaT * mf_Speed;

	if(mf_ProgressOnPath > 1.0f)
	{
		mf_ProgressOnPath -=1.0f;
	}
	else if(mf_ProgressOnPath < 0.0f)
	{
		mf_ProgressOnPath += 1.0f;
	}

	Vector3 o_TmpPosition; 
	Vector3 o_TmpTangeante;
	mpo_CurrentPath->GetPointTangeante(mf_ProgressOnPath,o_TmpPosition,o_TmpTangeante);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ColorRGBA::Black);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,ColorRGBA::Black);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ColorRGBA::White);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
	glBindTexture(GL_TEXTURE_2D,mu32_ParticleTextureId);

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);

	glPushMatrix();

	float f_TmpModelViewMat[16];

	//Billboard
	//////////////////////////////////////////////////////////////////////////
	glGetFloatv(GL_MODELVIEW_MATRIX,f_TmpModelViewMat);

	f_TmpModelViewMat[0] = 1;
	f_TmpModelViewMat[1] = 0;
	f_TmpModelViewMat[2] = 0;

	f_TmpModelViewMat[4] = 0;
	f_TmpModelViewMat[5] = 1;
	f_TmpModelViewMat[6] = 0;

	f_TmpModelViewMat[8] = 0;
	f_TmpModelViewMat[9] = 0;
	f_TmpModelViewMat[10] = 1;

	glLoadMatrixf(f_TmpModelViewMat);


	glTranslatef(o_TmpPosition.X(),o_TmpPosition.Y(),o_TmpPosition.Z());



	glBegin(GL_QUADS);

	glTexCoord2d(0,0);
	glVertex3f(-BILLBOARD_WIDTH,-BILLBOARD_WIDTH,0);

	glTexCoord2d(1,0);
	glVertex3f(BILLBOARD_WIDTH,-BILLBOARD_WIDTH,0);

	glTexCoord2d(1,1);
	glVertex3f(BILLBOARD_WIDTH,BILLBOARD_WIDTH,0);

	glTexCoord2d(0,1);
	glVertex3f(-BILLBOARD_WIDTH,BILLBOARD_WIDTH,0);

	glEnd();

	glPopMatrix();

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ColorRGBA::White);

	//Trail
	//////////////////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLE_STRIP);

	for(int i = 0; i < 40; ++i)
	{

		float f_ClampedProgress;
		
		if(mf_Speed < 0.0)
		{
			f_ClampedProgress = mf_ProgressOnPath+(0.004f * i);
		}
		else
		{
			f_ClampedProgress = mf_ProgressOnPath-(0.004f * i);
		}

		if(f_ClampedProgress < 0.0f)
		{
			f_ClampedProgress += 1.0f;
		}
		else if(f_ClampedProgress > 1.0f)
		{
			f_ClampedProgress -= 1.0f;
		}

		Vector3 o_TmpPos; 
		Vector3 o_TmpTan;
		mpo_CurrentPath->GetPointTangeante(f_ClampedProgress,o_TmpPos,o_TmpTan);
		o_TmpTan.Normalise();
		Vector3 o_WidthVec = o_TmpTan.CrossProduct(Vector3(0.5,0.5,0.5));
		o_WidthVec.Normalise();

		o_WidthVec *= mf_TrailWidth;

		o_WidthVec *= ((40-i)/40.0f);

		Vector3 o_Pt1 = o_TmpPos + o_WidthVec;
		Vector3 o_Pt2 = o_TmpPos - o_WidthVec;

		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mo_ReflectionColor * ((40-i)/40.0f));

		glVertex3f(o_Pt1.X(),o_Pt1.Y(),o_Pt1.Z());
		glVertex3f(o_Pt2.X(),o_Pt2.Y(),o_Pt2.Z());
	}

	glEnd();

	glPopMatrix();


	//Reflection
	//////////////////////////////////////////////////////////////////////////
	if(o_TmpPosition.Y() > 4.0f)
	{
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ColorRGBA::Black);
	}
	else
	{
		float f_Intensity = (4.0 - o_TmpPosition.Y())/4.0f;

		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mo_ReflectionColor * (f_Intensity* f_Intensity));
	}
	glBindTexture(GL_TEXTURE_2D,mu32_ReflectionTextureId);

	glPushMatrix();

	glTranslatef(o_TmpPosition.X(), -1, o_TmpPosition.Z());

	glBegin(GL_QUADS);

	glTexCoord2d(0,0);
	glVertex3f(-REFLECTION_WIDTH,0,-REFLECTION_WIDTH);

	glTexCoord2d(1,0);
	glVertex3f(REFLECTION_WIDTH,0,-REFLECTION_WIDTH);

	glTexCoord2d(1,1);
	glVertex3f(REFLECTION_WIDTH,0,REFLECTION_WIDTH);

	glTexCoord2d(0,1);
	glVertex3f(-REFLECTION_WIDTH,0,REFLECTION_WIDTH);

	glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

Firefly::~Firefly()
{
	if(mu32_ParticleTextureId != 0)
	{
		glDeleteTextures(1,&mu32_ParticleTextureId);
		mu32_ParticleTextureId = 0;
	}

	if(mu32_ReflectionTextureId != 0)
	{
		glDeleteTextures(1,&mu32_ReflectionTextureId);
		mu32_ReflectionTextureId = 0;
	}

	if(mpo_CurrentPath != NULL)
	{
		delete mpo_CurrentPath;
		mpo_CurrentPath = NULL;
	}
}