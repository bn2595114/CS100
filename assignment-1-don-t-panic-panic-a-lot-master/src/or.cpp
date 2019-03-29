#include <iostream>
#include <vector>
#include "or.h"

using namespace std;

void Or::convert()
{
    argLeft = orLeft->get();
    argRight = orRight->get();
};

void Or::execute()
{
    string checkL = orLeft->getStr();
    string checkR = orRight->getStr();

    if (checkL == "exit " || checkL == "exit" || checkL == " exit" || checkL == " exit ")
    {
        esc = true;
        return;
    }

    else if (checkL == "testPass") //Checks if left child test command passed. Command was still executable.
    {
        cout << "(True)" << endl;
        fail = 1;
    }

    else if (checkL == "testFail") //Checks if left child test command failed. Command still executable.
    {
        cout << "(False)" << endl;
        fail = 1;
    }

    else if(checkL == "error") //Checks if left child test command errored. Command was not executable.
    {
        fail = -1;
    }
    //Or execution logic
    int status;
    pid_t childID, parentID;

    this->convert();


    if (fail == 0)
    {
        childID = fork();
        if (childID < 0)
        {
            perror("Forking error");
	    exit(EXIT_FAILURE);
        }
        if (childID == 0)
        {
	    fail = execvp(*argLeft, argLeft);
	    if (fail < 0)
	        perror("Child execution failed");
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

    else if (fail == 1 && checkR == "testPass") //Checks if left Child was executable and checks if right child test command passed.
    {
        cout << "(True)" << endl;
    }

    else if (fail == 1 && checkR == "testFail") //Checks if left Child was executable and checks if right child test command failed.
    {
        cout << "(False)" << endl;
    }

    else if (fail == -1 && checkR == "error") //Checks if left Child was executable and checks if right child is an error.
    {
        fail = -1;
    }



    if (fail == -1)
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
		perror("Child execution failed");
	}

	parentID = wait(&status);
	if (parentID < 0)
	    perror("Abnormal exit of program");
    }

    if (fail != -1)
        fail = 1;
};
