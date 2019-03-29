#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "shell.h"
using namespace std;

class Command: public Shell
{
    private:
        string command;
    	char** arg;
    	vector<string> parsed;

    protected:
        bool testResult;
    public:
        Command(string c)
        {
    	    esc = false; // exit command
    	    comment = false; // # connector
	        fail =  0;  // to prevent repeats of && and ||
    	    command = c;
        }
	void convert() {};
	void print()
	{
	    cout << "Command: " << command << endl;
	}
        char** get(){
	    parsed = this->parsing(command);

	    arg = new char *[parsed.size()+1];

	    for (int i=0; i<parsed.size(); i++)
	    {
		if (parsed[i] == "#")
		    arg[i] = NULL;

        else if (parsed[i] == "testPass")
        {
            arg[i] = NULL;
            return arg;
        }

        else if (parsed[i] == "testFail")
        {
            arg[i] = NULL;
            return arg;
        }

        else if (parsed[i] == "error")
        {
            arg[i] = NULL;
            return arg;
        }
        else
	        arg[i] = const_cast <char*> ((parsed[i]).c_str());
	    }

	    arg[parsed.size()] = NULL;
	    return arg;
	}
	string getStr()
	{
	    return this->command;
	}
    void execute() {};
    bool getEsc() {};
    int getFail() {};
    void setFail(int) {};
};

#endif
