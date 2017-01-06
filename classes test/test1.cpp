#include <iostream.h>

class A
{
protected:
	virtual bool dumb() = 0 ;
public:
    A();
};

A::A()
{
}

class B : public A
{
public:
    B();
    bool dumb();
};



B::B() : A()
{
}

bool B::dumb()
{
    return false ;
}





class Z
{
protected:

public:
    Z();
	virtual bool dumb() ;
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
    return false ;
}

Y::Y() : Z()
{
}


bool Y::dumb()
{
    return false ;
}


void main()
{
	B* b = new B ;
	cout << "b is:" << b->dumb() << endl ;//? "true" : "false" << endl;
	
	Z* z = new Z ;
	cout << "z is:" << z->dumb();// ? "true" : "false";
}


