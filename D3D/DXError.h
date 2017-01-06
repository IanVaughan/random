// Copyright (C) Micro Nav Limited
//---------------------------------------------------------------------------
// Current Revision $Revision: 1.1 $
//
// Revision Date    $Date: Mon Nov 13 15:31:02 2000 $
//
// Revised by       $Author: IanVaughan $
//---------------------------------------------------------------------------
/*
$Log20: I:\Projects\MapEditor\Source\Tower3DDLL\D3DError.i $
//  
//    
//  
//  Revision 1.1  by: IanVaughan  Rev date: Mon Nov 13 15:31:02 2000
//    forgot to include the micronav/qvcs header
//  
//  Revision 1.0  by: IanVaughan  Rev date: Mon Nov 13 15:09:20 2000
//    Initial revision.
//  
//  $Endlog$
*/


//---------------------------------------------------------------------------
#ifndef ErrorH
#define ErrorH

#include "d3d.h"
//---------------------------------------------------------------------------
class DXError
{
public:
    DXError();

    //displays the DirectX err msg
    void Display(HRESULT);

    //displays the last windows message
    void Display();
};
#endif
