//---------------------------------------------------------------------------
#ifndef ErrorH
#define ErrorH

#include "d3d.h"
//---------------------------------------------------------------------------
class TD3DError
{
public:
    TD3DError();

    void Display(HRESULT);
};
#endif
