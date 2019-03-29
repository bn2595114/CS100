#include <iostream>
#include "and.h"
#include <vector>

using namespace std;

void And::convert()
{
    argLeft = andLeft->get();
    argRight = andRight->get();
};


void And::execute()
{

    string checkL = andLeft->getStr();
    string checkR = andRight->getStr();

    if (checkL == "exit " || checkL == "exit" || checkL == " exit" || checkL == " exit ")
    {
	    esc = true;
        return;
    }

     if (checkL == "testPass") //Checks if left child passed. Test was executable.
    {
        cout << "(True)" << endl;
        fail = 1;
    }

    if (checkL == "testFail") //Checks if left child failed. Test was executable.
    {
        cout << "(False)" << endl;
        fail = 1;
    }

    if (checkL == "error") //Checks if left child errored. Test was not executable.
    {
        fail = -1;
    }

    else
    //And execution logic
    this->convert();

    int status;
    pid_t childID, parentID;

    if (fail == 0)
    {
        childID = fork(); // for child and parent
        if (childID < 0)
        {
            perror("Forking error");
            exit(EXIT_FAILURE);
        }
        if (childID == 0)
        {
            fail = execvp(*argLeft, argLeft);
            if (fail < 0)
                perror("Child execution failed"); //if child failed to execute
        }

        parentID = wait(&status);
        if (status < 0)
            perror("Abnormal exit of program");
    }

    if (fail != -1 && (checkR == "exit " || checkR == "exit" || checkR == " exit" || checkR == " exit "))
    {
    	esc = true;
    	return;
    }

    if (fail == 1 && checkR == "testPass") //Checks if left child  was executable. Checks Right Child for test command pass.
    {
        cout << "(True)" << endl;
    }

    if (fail == 1 && checkR == "testFail") //Checks if left child  was executable. Checks Right Child for test command fail.
    {
        cout << "(False)" << endl;
    }

    if (fail == -1 && checkR == "error") //Checks if left child  was executable. Checks Right Child for error.
    {
        fail = -1;
    }


    if (fail != -1)
    {
        childID = fork();
        if (childID < 0)
        {
    	    perror("Forking error");
    	    exit(EXIT_FAILURE);
        }
            if (childID == 0)
        {
    	    fail = execvp(*argRight, argRight);
    	    if (fail < 0)
    		perror("Child executino failed");
        }

    	parentID = wait(&status);
    	if (parentID < 0)
    	perror("Abnormal exit of program");
    }

    if (fail != -1)
        fail = 1;
};
