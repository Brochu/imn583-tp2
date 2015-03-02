#ifndef FIREFLY_H_
#define FIREFLY_H_

#include <string>

#include "RenderObject.h"
#include "../Curves/CurveFactory.h"
#include "../Foundation/ColorRGBA.h"
#include "../ThirdParty/glut.h"

#define BILLBOARD_WIDTH 2
#define REFLECTION_WIDTH 3

class Firefly : public RenderObject
{
public:
	
	Firefly(const string& ao_FireflyTexture, const string& ao_ReflectionTexture, const string& ao_PathFile);
	virtual ~Firefly();

	void		SetSpeed(float af_Speed);
	float		GetSpeed() const;

	void		SetTrailWidth(float af_Width);
	float		GetTrailWidth() const;

	void		SetPathType(CurveFactory::CurveType ae_Type);

	void		SetReflectionColor(const ColorRGBA& ao_Color);
	ColorRGBA	GetReflectionColor() const;

	virtual void Render(float af_DeltaT);

protected:

	float			mf_ProgressOnPath;
	float			mf_Speed;
	float			mf_TrailWidth;

	GLuint			mu32_ParticleTextureId;
	GLuint			mu32_ReflectionTextureId;

	ColorRGBA		mo_ReflectionColor;

	Curve*			mpo_CurrentPath;

	vector<Vector3>	mo_CachedPathWaypoints;
};

inline void Firefly::SetSpeed(float af_Speed)
{
	mf_Speed = af_Speed;
}

inline float Firefly::GetSpeed() const
{
	return mf_Speed;
}

inline void Firefly::SetPathType(CurveFactory::CurveType ae_Type)
{
	if(mpo_CurrentPath != NULL)
	{
		delete mpo_CurrentPath;
	}

	mpo_CurrentPath = CurveFactory::CreateCurve(ae_Type);
	if(mpo_CurrentPath != NULL)
	{
		mpo_CurrentPath->SetPointsControle(mo_CachedPathWaypoints);	
	}
}

inline void Firefly::SetReflectionColor(const ColorRGBA& ao_Color)
{
	mo_ReflectionColor = ao_Color;
}

inline ColorRGBA Firefly::GetReflectionColor() const
{
	return mo_ReflectionColor;
}

inline void Firefly::SetTrailWidth(float af_Width)
{
	mf_TrailWidth = af_Width;	
}

inline float Firefly::GetTrailWidth() const
{
	return mf_TrailWidth;
}

#endif //RENDER_OBJECT_H_