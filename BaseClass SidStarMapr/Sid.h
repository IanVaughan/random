//---------------------------------------------------------------------------
#ifndef SidH
#define SidH

#include "BaseSidStarMapr.h"
//---------------------------------------------------------------------------
class Sid : public TBaseSidStarMapr 
{
private:
public:
    __fastcall Sid(TComponent* Owner);
    bool Execute();
};


#endif
 