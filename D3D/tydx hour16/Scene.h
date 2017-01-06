// Scene.h: interface for the CScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__5EFF4E86_331B_11D3_A7AF_00400537F880__INCLUDED_)
#define AFX_SCENE_H__5EFF4E86_331B_11D3_A7AF_00400537F880__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScene  
{
public:
	CScene(D3DVECTOR pos,D3DVECTOR ang);
	virtual ~CScene();
	void draw(LPDIRECT3DDEVICE7 dev);
	D3DTLVERTEX background[4];
	float lift;
	float pitch;
	float steer;
	D3DMATRIX calc_move(float delt);
	void set_pitch(float val);
	void set_steer(float val);
	void set_lift(float val);
	
	D3DVECTOR cur_ang;		// current rotational angle
	D3DVECTOR vel_ang;		// velocity of rotation

	D3DVECTOR cur_pos;		// current position
	D3DVECTOR vel_pos;		// current velocity
};

#endif // !defined(AFX_SCENE_H__5EFF4E86_331B_11D3_A7AF_00400537F880__INCLUDED_)
