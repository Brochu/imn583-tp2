#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

class RenderObject
{
public:
	
	RenderObject(){};
	virtual ~RenderObject(){};

	virtual void Render(float af_DeltaT) = 0;
};

#endif //RENDER_OBJECT_H_