//and class
#ifndef AND_H
#define AND_H

#include <iostream>
#include <string>
#include <vector>
#include "shell.h"

using namespace std;

class And: public Shell
{
    private:
        Shell* andLeft;
        Shell* andRight;
    	char** argLeft;
    	char** argRight;

    public:
        And(Shell* leftChild, Shell* rightChild)
        {
	    fail = 0;
            andLeft = leftChild;
            andRight = rightChild;
        }

        void print()
        {
            cout << "Left Child = ";
	    andLeft->print();
            cout << "Right Child = ";
	    andRight->print();
        }
	void convert(); //Convert to char**
        void execute();
	char** get() {};
	string getStr() { return "a"; };
	bool getEsc()
	{
	    return esc;
	}
	int getFail()
	{
	    return fail;
	}
	void setFail(int f)
	{
	    fail = f;
	}

};

#endif
