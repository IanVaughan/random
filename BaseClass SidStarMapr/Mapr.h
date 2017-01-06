//---------------------------------------------------------------------------
#ifndef MaprH
#define MaprH
//---------------------------------------------------------------------------
#include "BaseSidStarMapr.h"

class Mapr : public TBaseSidStarMapr
{
private:
public:
    __fastcall Mapr(TComponent* Owner);
    bool Execute();
};

#endif
