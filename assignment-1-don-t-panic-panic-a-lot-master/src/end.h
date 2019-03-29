
#ifndef END_H
#define END_H

#include "shell.h"

using namespace std;

class End : public Shell
{
    private:
	Shell* command;
	char** arg;
    public:
        End(Shell* c)
	{
	    fail = 0;
	    command = c;
	};
	void print() {};
	void convert();
	void execute();
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
	string getStr() { return "e";};
};

#endif
