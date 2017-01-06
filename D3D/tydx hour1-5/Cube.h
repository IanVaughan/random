// Cube.h: interface for the CCube class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBE_H__0DF83AE1_0299_11D3_A7AF_00400537F880__INCLUDED_)
#define AFX_CUBE_H__0DF83AE1_0299_11D3_A7AF_00400537F880__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCube  
{
public:
	void draw(LPDIRECT3DDEVICE7 device);
	D3DVERTEX *verts;
	CCube(D3DVECTOR origin,D3DVECTOR size,float R,float G,float B);
	virtual ~CCube();
};

#endif // !defined(AFX_CUBE_H__0DF83AE1_0299_11D3_A7AF_00400537F880__INCLUDED_)
