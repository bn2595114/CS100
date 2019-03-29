/* This is our Shell base class, the only thing the user will interact with*/

#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>
using namespace std;

class Shell
{
    protected:
        string userInput;
        char* argLeft[50]; //Let left be used for semi colon also
        char* argRight[50]; // Right argument
    	bool esc; // checj for escape
    	bool comment; // check for comment tag
    	int fail; // -1 fail, 0 nothing, 1 success
        bool testResult;

    public:
        /*Constructor*/
        Shell();

        // string userPrompt();

        // string getString()
        // {
        //     return userInput;
        // }
        vector<string> parsing(string); // parsing into own vectors
	vector<string> parsing(vector<string>);
    	virtual char** get() = 0; // returns value of whatever
    	virtual string getStr() = 0;
    	virtual bool getEsc() = 0;
    	virtual int getFail() = 0;
    	virtual void setFail(int) = 0;
        virtual void execute() = 0;
    	virtual void print() = 0; //testing object inputs
	virtual void convert() = 0;
};

#endif
