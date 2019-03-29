#ifndef DOUBLERED_H
#define DOUBLERED_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "shell.h"

using namespace std;

class DoubleRed: public Shell
{
    protected:
    Shell* left;
    Shell* right;
    string commandString;
    char** arg;

    public:
    DoubleRed(Shell* passLeft, Shell* passRight)
    {
        esc = false;
        fail = 0;
        left = passLeft;
        right = passRight;
    }

    void print() {};
    void convert()
    {
        arg = left->get();
        commandString = right->getStr();

        //Removes white spaces so that we don't have an error when opening the
        //string.
        for (int i = 0; i < commandString.size(); i++)
        {
            if (commandString[i] == ' ')
            {
                commandString.erase(i, 1);
            }
        }
    };

    void execute()
    {
        this->convert();
        int fs;

        //Opening the file and assigning to file descriptor with flags
        //Create if does not exist, write only, and append instead of overwrite.
        fs = open(commandString.c_str(), O_CREAT | O_WRONLY | O_APPEND);

        if(fs < 0)
        {
            perror("open Error");
            exit(1);
        }

        //Execution logic for output redirection wtih appending.
        int status;
        pid_t childID, parentID;

        childID = fork();
        if (childID < 0)
        {
            perror("Forking error");
            exit(EXIT_FAILURE);
        }
        if (childID == 0)
        {
            //changing the out stream to be whatever file we opened.
            int dupReturn = dup2(fs, 1);

            if(dupReturn < 0)
            {
                perror("dup2 Error");
                exit(1);
            }

            fail = execvp(*arg, arg);
            if (fail < 0)
            perror("Child execution failed");
        }

        parentID = wait(&status);
        if (status < 0)
        {
            perror("Abnormal exit of program");
            fail = 0;
        }

    };

    char** get() {};
    bool getEsc()
    {
        return esc;
    };
    int getFail()
    {
        return fail;
    };
    void setFail(int f)
    {
        fail = f;
    };
    string getStr()
    {
        return "doubleOutRed";
    };
};

#endif
