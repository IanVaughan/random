// Helicopter.h: interface for the CHelicopter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELICOPTER_H__82B11CE1_2DCC_11D3_A7AF_00400537F880__INCLUDED_)
#define AFX_HELICOPTER_H__82B11CE1_2DCC_11D3_A7AF_00400537F880__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "d3dfile.h"

class CHelicopter  
{
public:
	void draw(LPDIRECT3DDEVICE7 dev,float delt);
	float lift;
	float pitch;
	float steer;
	CD3DFile *meshPtr;
	D3DMATRIX calc_move(float delt);
	void set_pitch(float val);
	void set_steer(float val);
	void set_lift(float val);
	
	D3DVECTOR cur_ang;		// current rotational angle
	D3DVECTOR vel_ang;		// velocity of rotation

	D3DVECTOR cur_pos;		// current position
	D3DVECTOR vel_pos;		// current velocity

	CHelicopter(D3DVECTOR pos,D3DVECTOR ang,CD3DFile *lpMesh);
	virtual ~CHelicopter();
};

#endif // !defined(AFX_HELICOPTER_H__82B11CE1_2DCC_11D3_A7AF_00400537F880__INCLUDED_)
