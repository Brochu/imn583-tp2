#include <vector>
#include <iostream>

#include "ApplicationSettings.h"
#include "Camera/CameraMouse.h"
#include "RenderObjects/Cube.h"
#include "RenderObjects/Firefly.h"
#include "Curves/CurveFactory.h"
#include "ThirdParty/glut.h"

void InitDisplay(int* apu32_ArgCount, char** apc_ArgVal);
void InitScene();
void WelcomeMessage();

void DrawFrameCallback();
void MouseMotionCallback(int as32_X, int as32_Y);
void MouseButtonCallback(int as32_Button, int as32_State, int as32_X, int as32_Y);
void FrameExpireCallback(int as32_Value);
void KeyboardCallback(unsigned char ac_Key,int as32_X, int as32_Y);

CameraMouse go_MouseCam;

vector<RenderObject*> gtpo_SceneList;
vector<Firefly*> gtpo_Fireflies;

using namespace std;

int main(int aps32_ArgCount, char** apc_ArgVal)
{
	WelcomeMessage();

	InitDisplay(&aps32_ArgCount, apc_ArgVal);
	InitScene();

	glutMainLoop();
	return 0;
}

void WelcomeMessage()
{
	cout << "TP2 du cours IMN538 - Courbes et Trajets" << endl;
	cout << "----------------------------------------" << endl << endl;
	cout << "Controle de la camera:" << endl;
	cout << "Bouton gauche -> rotation" << endl;
	cout << "Bouton droit -> zoom" << endl << endl;
	cout << "Touches:" << endl;
	cout << "Q -> Quitter" << endl;
	cout << "1 -> Saut d'un point a l'autre." << endl;
	cout << "2 -> Interpolation lineaire." << endl;
	cout << "3 -> Interpolation de Catmull-Rom sans reparametrisation." << endl;
	cout << "4 -> Interpolation de Catmull-Rom avec reparametrisation." << endl;
}

void InitDisplay(int* apu32_ArgCount, char** apc_ArgVal)
{
	glutInit(apu32_ArgCount,apc_ArgVal);
	glutInitWindowPosition(WINDOW_POSY,WINDOW_POSX);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(WINDOW_NAME);

	glutDisplayFunc(DrawFrameCallback);
	glutMouseFunc(	MouseButtonCallback);
	glutMotionFunc(	MouseMotionCallback);
	glutTimerFunc(FRAME_DURATION,FrameExpireCallback,1);
	glutKeyboardFunc(KeyboardCallback);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(67.5f,(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,0.1,100.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void InitScene()
{
	Cube* po_Cube = new Cube();
	Matrix4 CubeTrans;

	po_Cube->SetTexture("Resources/Cube_Texture.bmp");
	CubeTrans.SetTranslationData(Vector3(-1,0,-1));
	po_Cube->SetTransformation(CubeTrans);
	gtpo_SceneList.push_back(po_Cube);

	po_Cube = new Cube();
	CubeTrans.MakeIdentity();

	po_Cube->SetTexture("Resources/Cube_Texture.bmp");
	CubeTrans.SetTranslationData(Vector3(1.5,0,0.5));
	CubeTrans.RotateAroundYDeg(25);
	po_Cube->SetTransformation(CubeTrans);
	gtpo_SceneList.push_back(po_Cube);

	po_Cube = new Cube();
	CubeTrans.MakeIdentity();

	po_Cube->SetTexture("Resources/Cube_Texture.bmp");
	CubeTrans.SetTranslationData(Vector3(0.5,2,0.15));
	CubeTrans.RotateAroundYDeg(35);
	po_Cube->SetTransformation(CubeTrans);
	gtpo_SceneList.push_back(po_Cube);

	Firefly* po_Firefly = new Firefly(	"Resources/Particle1_Texture.bmp",
										"Resources/Particle_Reflection.bmp", 
										"Resources/cercle.sp");

	po_Firefly->SetPathType(CurveFactory::Type_Jump);
	po_Firefly->SetSpeed(0.05f);
	po_Firefly->SetTrailWidth(0.20f);
	po_Firefly->SetReflectionColor(ColorRGBA(250/255.0f,200/255.0f,150/255.0f,1.0f));
	gtpo_Fireflies.push_back(po_Firefly);


	po_Firefly =		new Firefly(	"Resources/Particle2_Texture.bmp",
										"Resources/Particle_Reflection.bmp", 
										"Resources/carre.sp");

	po_Firefly->SetPathType(CurveFactory::Type_Jump);
	po_Firefly->SetSpeed(0.15f);
	po_Firefly->SetTrailWidth(0.5f);
	po_Firefly->SetReflectionColor(ColorRGBA(90/255.0f,200/255.0f,90/255.0f,1.0f));
	gtpo_Fireflies.push_back(po_Firefly);


	po_Firefly =		new Firefly(	"Resources/Particle2_Texture.bmp",
										"Resources/Particle_Reflection.bmp", 
										"Resources/cercle2.sp");

	po_Firefly->SetPathType(CurveFactory::Type_Jump);
	po_Firefly->SetSpeed(0.20f);
	po_Firefly->SetTrailWidth(0.5f);
	po_Firefly->SetReflectionColor(ColorRGBA(90/255.0f,200/255.0f,90/255.0f,1.0f));
	gtpo_Fireflies.push_back(po_Firefly);


	po_Firefly =		new Firefly(	"Resources/Particle1_Texture.bmp",
										"Resources/Particle_Reflection.bmp", 
										"Resources/trapeze.sp");

	po_Firefly->SetPathType(CurveFactory::Type_Jump);
	po_Firefly->SetSpeed(0.10f);
	po_Firefly->SetTrailWidth(0.2f);
	po_Firefly->SetReflectionColor(ColorRGBA(250/255.0f,200/255.0f,150/255.0f,1.0f));
	gtpo_Fireflies.push_back(po_Firefly);	
}

void DrawFrameCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	go_MouseCam.RefreshCamera(0);
	
	float tf_LightPos[] = {-5,5,5,1};
	glLightfv(GL_LIGHT0,GL_POSITION,tf_LightPos);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,180.0f);

	for(unsigned int i = 0; i < gtpo_SceneList.size(); ++i)
	{
		gtpo_SceneList[i]->Render(1/FPS);
	}

	for(unsigned int i = 0; i < gtpo_Fireflies.size(); ++i)
	{
		gtpo_Fireflies[i]->Render(1/FPS);
	}

	glutSwapBuffers();
}

void MouseMotionCallback(int as32_X, int as32_Y)
{
	go_MouseCam.RefreshPosition(as32_X,as32_Y);
}

void MouseButtonCallback(int as32_Button, int as32_State, int as32_X, int as32_Y)
{
	go_MouseCam.RefreshState(as32_Button,as32_State,as32_X,as32_Y);
}

void FrameExpireCallback(int as32_Value)
{
	glutTimerFunc(FRAME_DURATION,FrameExpireCallback,1);
	glutPostRedisplay();
}

void KeyboardCallback(unsigned char ac_Key,int as32_X, int as32_Y)
{
	switch(ac_Key)
	{
	case '1' :
		for(unsigned int i = 0; i < gtpo_Fireflies.size(); ++i)
		{
			gtpo_Fireflies[i]->SetPathType(CurveFactory::Type_Jump);
		}
		break;

	case '2' :
		for(unsigned int i = 0; i < gtpo_Fireflies.size(); ++i)
		{
			gtpo_Fireflies[i]->SetPathType(CurveFactory::Type_Linear);
		}
		break;

	case '3' :
		for(unsigned int i = 0; i < gtpo_Fireflies.size(); ++i)
		{
			gtpo_Fireflies[i]->SetPathType(CurveFactory::Type_CatmullRom);
		}
		break;

	case '4' :
		for(unsigned int i = 0; i < gtpo_Fireflies.size(); ++i)
		{
			gtpo_Fireflies[i]->SetPathType(CurveFactory::Type_CatmullRomWReparam);
		}
		break;

	case 'q' :
		for(unsigned int i = 0; i < gtpo_Fireflies.size(); ++i)
		{
			delete gtpo_Fireflies[i];
		}

		for(unsigned int i = 0; i < gtpo_SceneList.size(); ++i)
		{
			delete gtpo_SceneList[i];
		}

		exit(0);
		break;
	}
}
