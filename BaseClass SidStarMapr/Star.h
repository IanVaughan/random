//---------------------------------------------------------------------------
#ifndef StarH
#define StarH
//---------------------------------------------------------------------------
#include "BaseSidStarMapr.h"

class Star : public TBaseSidStarMapr
{
private:
public:
    __fastcall Star(TComponent* Owner);
    bool Execute();
};



#endif

