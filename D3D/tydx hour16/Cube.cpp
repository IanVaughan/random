// Cube.cpp: implementation of the CCube class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#define D3D_OVERLOADS
#include "d3d.h"
#include "Cube.h"

WORD cube_index[36]={	0,1,2,
				  		2,1,3,
						2,3,4,
						4,3,5,
						4,5,6,
						6,5,7,
						6,7,0,
						0,7,1,
						1,7,3,
						3,7,5,
						0,2,6,
						2,4,6
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCube::CCube(D3DVECTOR origin,D3DVECTOR size,float R,float G,float B,
			 LPDIRECTDRAWSURFACE7 text_ptr)
{
	// save the texture pointer

	texture=text_ptr;

	// allocate the vertex array

	verts=new D3DLVERTEX[8];

	// calculate far corner of the cube

	D3DVECTOR extent=origin+size;

	// calculate highlight, midtone, and shadow colors

	D3DCOLOR clr[8];
	float luma[8]={0.7f,1.0f,0.5f,0.8f,0.15f,0.45f,0.35f,0.65f};
	for (int i=0;i<8;i++) 
		clr[i]=D3DRGB(R*luma[i],G*luma[i],B*luma[i]);

	// set up the 8 corners of the cube

	verts[0]=D3DLVERTEX(D3DVECTOR(origin.x,origin.y,origin.z),clr[0],0,0.0f,0.0f);
	verts[1]=D3DLVERTEX(D3DVECTOR(origin.x,extent.y,origin.z),clr[1],0,0.0f,2.0f);
	verts[2]=D3DLVERTEX(D3DVECTOR(extent.x,origin.y,origin.z),clr[2],0,1.0f,0.0f);
	verts[3]=D3DLVERTEX(D3DVECTOR(extent.x,extent.y,origin.z),clr[3],0,1.0f,2.0f);
	verts[4]=D3DLVERTEX(D3DVECTOR(extent.x,origin.y,extent.z),clr[4],0,2.0f,0.0f);
	verts[5]=D3DLVERTEX(D3DVECTOR(extent.x,extent.y,extent.z),clr[5],0,2.0f,2.0f);
	verts[6]=D3DLVERTEX(D3DVECTOR(origin.x,origin.y,extent.z),clr[6],0,1.0f,0.0f);
	verts[7]=D3DLVERTEX(D3DVECTOR(origin.x,extent.y,extent.z),clr[7],0,1.0f,2.0f);
}

#define SafeDelete(x) if (x) {delete x;x=NULL;}

CCube::~CCube()
{
	// de-allocate the vertex array

	SafeDelete(verts);
}

void CCube::draw(LPDIRECT3DDEVICE7 device)
{
//	if (texture)
		device->SetTexture( 0, texture );
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,
								 verts,8,
								 cube_index,36,
								 0);
}
