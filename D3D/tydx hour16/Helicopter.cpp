// Helicopter.cpp: implementation of the CHelicopter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#define D3D_OVERLOADS
#include <ddraw.h>
#include <d3d.h>
#include <d3dtypes.h>
#include "d3dmath.h"
#include "d3dutil.h"
#include "Helicopter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////v///////////////////////////////////

#define bladeVert(x,y,z) D3DLVERTEX(D3DVECTOR(x,y,z),0x00333333,0x00888888,0.0f,0.0f);

CHelicopter::CHelicopter(D3DVECTOR pos,D3DVECTOR ang,CD3DFile *lpMesh)
{
	// save the mesh pointer

	meshPtr=lpMesh;

	// set current position and rotation

	cur_pos=pos;
	cur_ang=ang;

	// clear velocities

	vel_pos=vel_ang=D3DVECTOR(0.0f,0.0f,0.0f);

	// clear controls

	steer=lift=pitch=0.0f;
}

CHelicopter::~CHelicopter()
{

}

void CHelicopter::set_lift(float val)
{
	// apply throttle/breaking

	lift+=val;
	if (lift>10.0f)
		lift=10.0f;
	else if (lift<-10.0f)
		lift=-10.0f;
}

void CHelicopter::set_steer(float val)
{
	// apply rotation

	steer+=val;
	if (steer>10.0f)
		steer=10.0f;
	else if (steer<-10.0f)
		steer=-10.0f;
}

void CHelicopter::set_pitch(float val)
{
	// apply pitch

	pitch=val;
	if (pitch>0.3f)
		pitch=0.3f;
	else if (pitch<-0.9f)
		pitch=-0.9f;
}

extern LPDIRECT3DDEVICE7 lpDevice;

D3DMATRIX CHelicopter::calc_move(float delt)
{
	cur_ang.x=-pitch*4.5f;
	cur_ang.y+=steer*delt*0.05f;
	cur_ang.z=-steer*0.01f;

	cur_pos.y+=lift*delt*12.0f;
	cur_pos.x+=sin(cur_ang.y)*cur_ang.x*625.0f*delt;
	cur_pos.z+=cos(cur_ang.y)*cur_ang.x*625.0f*delt;

	// calculate a decay factor based on time

	float decay=1.0f-delt*0.2f;

	// decay the speed and control positions gradually back towards zero

	lift*=decay;
	pitch*=decay;
	steer*=decay;

	// settle towards clear and level flight

	cur_ang.x*=decay;
	cur_ang.z*=decay;

	// set up rotations and combine into view transform matrix

	D3DMATRIX matTrans,matRotateY,matRotateZ,matRotateX,view;
	
	D3DUtil_SetTranslateMatrix(matTrans,cur_pos.x,cur_pos.y,cur_pos.z);
	
	D3DUtil_SetRotateXMatrix( matRotateX,cur_ang.x);
	D3DUtil_SetRotateYMatrix( matRotateY,cur_ang.y);
	D3DUtil_SetRotateZMatrix( matRotateZ,cur_ang.z);

    D3DMath_MatrixMultiply(view,matRotateY,matTrans);
	D3DMath_MatrixMultiply(view,matRotateZ,view);
	D3DMath_MatrixMultiply(view,matRotateX,view);

	// set the view transform for the 3D display

//	lpDevice->SetTransform(D3DTRANSFORMSTATE_VIEW,&view);

	// return view matrix

	return view;
}

void CHelicopter::draw(LPDIRECT3DDEVICE7 dev,float delt)
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

	D3DMATRIX world;
	static float delay=0.0f;
	delay+=delt;
	if (delay>1.2f) {
		int num=rand();
		if ((num&0x08)==1&&cur_pos.y<1000) {
			set_lift(10.0f);
		} else if ((num&0x08)==2&&cur_pos.y>600) {
			set_lift(-10.0f);
		} else if ((num&0x08)==3) {
			set_steer(-10.0f);
		} else if ((num&0x08)==4) {
			set_steer(10.0f);
		} else if ((num&0x08)==5) {
			set_pitch(-10.0f);
		} else if ((num&0x08)==6) {
			set_pitch(10.0f);
		}
		delay=0.0f;
	}
	set_pitch(0.1f);
	set_steer(0.1f);
//	set_lift(0.1f);
	if (meshPtr) {
		world=calc_move(delt);
		lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,&world);
		lpDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
		meshPtr->Render(lpDevice);
		D3DUtil_SetIdentityMatrix(world);
		lpDevice->SetTransform(D3DTRANSFORMSTATE_WORLD,&world);
		lpDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,FALSE);
	}
}
