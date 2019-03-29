//semi class
#ifndef SEMI_H
#define SEMI_H

#include <iostream>
#include <string>
#include <vector>
#include "shell.h"

using namespace std;

class Semi: public Shell
{
    private:
        Shell* semiCommand;
	    char** arg;

    public:
        Semi(Shell* com)
        {
	        fail = 0;
            semiCommand = com;
        };

        void print()
        {
	    cout << "Semi Command: " << semiCommand << endl;
        };
	string getStr() { return "s";};
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
