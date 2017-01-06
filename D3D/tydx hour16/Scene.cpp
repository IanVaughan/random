// Scene.cpp: implementation of the CScene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#define D3D_OVERLOADS
#include <ddraw.h>
#include <d3d.h>
#include <d3dtypes.h>
#include "d3dmath.h"
#include "d3dutil.h"
#include "Scene.h"
#include "Helicopter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////v///////////////////////////////////

#define bladeVert(x,y,z) D3DLVERTEX(D3DVECTOR(x,y,z),0x00333333,0x00888888,0.0f,0.0f);

CScene::CScene(D3DVECTOR pos,D3DVECTOR ang)
{
	// set current position and rotation

	cur_pos=pos;
	cur_ang=ang;

	// clear velocities

	vel_pos=vel_ang=D3DVECTOR(0.0f,0.0f,0.0f);

	// clear controls

	steer=lift=pitch=0.0f;

	// generate the background plane

    background[0] = D3DTLVERTEX( D3DVECTOR( 0.0f, 381.0f, 0.9999f ), 0.5f,D3DRGB(0.1f,0.5f,0.8f), 0, 0.0f, 1.0f );
    background[1] = D3DTLVERTEX( D3DVECTOR( 0.0f, 0.0f, 0.9999f ), 0.5f, D3DRGB(0.2f,0.6f,0.6f), 0, 0.0f, 0.0f );
    background[2] = D3DTLVERTEX( D3DVECTOR( 640.0f, 381.0f, 0.9999f ), 0.5f, D3DRGB(0.23f,0.6f,0.8f), 0, 1.0f, 1.0f );
    background[3] = D3DTLVERTEX( D3DVECTOR( 640.0f, 0.0f, 0.9999f ), 0.5f, D3DRGB(0.15f,0.6f,0.76f), 0, 1.0f, 0.0f );
	background[0].color=background[1].color=
	background[2].color=background[3].color=D3DRGB(0.2f,0.6f,0.6f);
}

CScene::~CScene()
{

}

void CScene::set_lift(float val)
{
	// apply throttle/breaking

	lift+=val;
	if (lift>10.0f)
		lift=10.0f;
	else if (lift<-10.0f)
		lift=-10.0f;
}

void CScene::set_steer(float val)
{
	// apply rotation

	steer+=val;
	if (steer>10.0f)
		steer=10.0f;
	else if (steer<-10.0f)
		steer=-10.0f;
}

void CScene::set_pitch(float val)
{
	// apply pitch

	pitch=val;
	if (pitch>0.3f)
		pitch=0.3f;
	else if (pitch<-0.9f)
		pitch=-0.9f;
}

extern LPDIRECT3DDEVICE7 lpDevice;

D3DMATRIX CScene::calc_move(float delt)
{
	cur_ang.x+=pitch*delt*0.5f;
	cur_ang.y+=steer*delt*0.2f;
	cur_ang.z-=steer*delt*0.1f;

	cur_pos.y+=lift*delt*12.0f;
	cur_pos.x+=sin(cur_ang.y)*cur_ang.x*625.0f*delt;
	cur_pos.z-=cos(cur_ang.y)*cur_ang.x*625.0f*delt;

	// calculate a decay factor based on time

	float decay=1.0f-delt;

	// decay the speed and control positions gradually back towards zero

	lift*=decay;
	pitch*=decay;
	steer*=decay;

	// settle towards clear and level flight

	cur_ang.x*=decay;
	cur_ang.z*=decay;

	// set up rotations and combine into view transform matrix

	D3DMATRIX matTrans,matRotateY,matRotateZ,matRotateX,view;
	
	D3DUtil_SetTranslateMatrix(matTrans,-cur_pos.x,-cur_pos.y,-cur_pos.z);
	
	D3DUtil_SetRotateXMatrix( matRotateX,cur_ang.x);
	D3DUtil_SetRotateYMatrix( matRotateY,cur_ang.y);
	D3DUtil_SetRotateZMatrix( matRotateZ,cur_ang.z);

    D3DMath_MatrixMultiply(view,matTrans,matRotateY);
	D3DMath_MatrixMultiply(view,view,matRotateZ);
	D3DMath_MatrixMultiply(view,view,matRotateX);

	// set the view transform for the 3D display

	lpDevice->SetTransform(D3DTRANSFORMSTATE_VIEW,&view);

	// return view matrix

	return view;
}

void CScene::draw(LPDIRECT3DDEVICE7 dev)
{
// set up matrix for the world transformation of the blades
/*	
	D3DMATRIX matTrans,matRotateY,matRotateZ,matRotateX,world;
	
	D3DUtil_SetTranslateMatrix(matTrans,cur_pos.x,cur_pos.y,cur_pos.z);
	D3DUtil_SetRotateXMatrix( matRotateX,cur_ang.x);
	D3DUtil_SetRotateZMatrix( matRotateZ,cur_ang.z);

	// set the view transform for the 3D display

	lpDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_NONE);
	
//	for (int i=0;i<blade_count;i++) {
//		blade_pos+=blade_speed;
//		D3DUtil_SetRotateYMatrix( matRotateY,blade_pos);
		D3DMath_MatrixMultiply(world,matRotateX,matTrans);
		D3DMath_MatrixMultiply(world,matRotateZ,world);
		D3DMath_MatrixMultiply(world,matRotateY,world);
		lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,&world);
		dev->DrawPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,
								 blades,24,
								 0);
	}
	lpDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_CCW);

	// clear the world matrix

	D3DUtil_SetIdentityMatrix(world);
	lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,&world);*/
}
