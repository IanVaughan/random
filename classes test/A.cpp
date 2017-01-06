// A.cpp: implementation of the A class.
//
//////////////////////////////////////////////////////////////////////

#include "A.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

A::A()
{

}

A::~A()
{

}

class A
{
protected:
	virtual bool dumb() = 0 ;
public:
    A();
};

class B : public A
{
public:
    B();
    bool dumb();
};


B::B()
{
}

bool B::dumb()
{
    return false ;
}


class Z
{
protected:
	virtual bool dumb() ;
public:
    Z();
};

class Y : public Z
{
public:
    Y();
    bool dumb();
};

Z::Z()
{
}

bool Z::dumb()
{
    return true ;
}

Y::Y()
{
}

bool Y::dumb()
{
    return false ;
}

