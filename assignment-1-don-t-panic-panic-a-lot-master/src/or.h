//or class
#ifndef OR_H
#define OR_H

#include <iostream>
#include <string>
#include <vector>
#include "shell.h"

using namespace std;

class Or: public Shell
{
    private:
        Shell* orLeft;
        Shell* orRight;
    	char** argLeft;
    	char** argRight;

    public:
        Or(Shell* leftChild, Shell* rightChild)
        {
	        fail = 0;
            orLeft = leftChild;
            orRight = rightChild;
        }

        void print()
        {
            cout << "Left Child = ";
	        orLeft->print();
            cout << "Right Child = ";
	        orRight->print();
        }
	string getStr() { return "o"; };
	char** get() {};
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
	void convert();
        void execute();
};

#endif
