//This is just to test as we go along.

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "command.h"
#include "semi.h"
#include "and.h"
#include "or.h"
#include "shell.h"
#include "executor.h"
#include "end.h"
#include "parentheses.h"
#include "test.h"
#include "piping.h"
#include "inRed.h"
#include "singleOutRed.h"
#include "doubleOutRed.h"
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_iterator.hpp>

using namespace std;
using namespace boost;

string userPrompt()
{
    string userInput;

    char hostName[1024];
    gethostname(hostName, 1023);
    if (!hostName)
    {
        perror("gethostname error");
    }

    char userName[1024];
    getlogin_r(userName, 1023);
    if (!userName)
    {
        perror("getusername error");
    }

    cout << userName << "@" << hostName << "$ ";

    getline(cin, userInput);

    return userInput;
};

vector<string> parser(string passedInput)
{
    vector<string> parsedVector;

    string userInput = passedInput;

    typedef boost::tokenizer<boost::char_separator<char>> Tok;
    boost::char_separator<char> conn("", ";&&||()><");
    Tok connector(userInput, conn);

    for (Tok::iterator tok_iter = connector.begin(); tok_iter != connector.end(); tok_iter++)
    {
        if (tok_iter == connector.end())
        {
            return parsedVector;
        }

        if (*tok_iter == " ")
        {
            tok_iter++;
        }

        for (int a = 0; a < 2; a++)
        {
            if (*tok_iter == "&")
            {
                a++;
                if (tok_iter != connector.end())
                {
                    tok_iter++;
                    if (*tok_iter == "&")
                    {
                        parsedVector.push_back("&&");
                        a++;
                    }
                }
            }
        }

        for (int b = 0; b < 2; b++)
        {
            if (*tok_iter == "|")
            {
                b++;
                if (tok_iter != connector.end())
                {
                    tok_iter++;
                    if (*tok_iter == "|")
                    {
                        parsedVector.push_back("||");
                        b++;
                    }
		    else // testing this for piping
                    {
                        parsedVector.push_back("|");
                        b++;
                    }
                }
            }
        }

        for (int c = 0; c < 2; c++)
        {
            if (*tok_iter == ">")
            {
                c++;
                if (tok_iter != connector.end())
                {
                    tok_iter++;
                    if (*tok_iter == ">")
                    {
                        parsedVector.push_back(">>");
                        c++;
                    }
                    else
                    parsedVector.push_back(">");
                    break;
                }
            }
        }

        if (*tok_iter != "|" && *tok_iter != "&" && *tok_iter != ">")
        {
            parsedVector.push_back(*tok_iter);
        }

    }

    return parsedVector;
};

bool checkTest(string toCheck)
{
    string isTest = toCheck;
    vector<string> testVector;

    typedef boost::tokenizer< boost::char_separator<char> > Tok;
    boost::char_separator<char> conn(" ","#[]");
    Tok connector(isTest, conn);

    for (Tok::iterator tok_iter = connector.begin(); tok_iter != connector.end(); tok_iter++)
    {
    if(tok_iter == connector.end())
        break;

    else if(*tok_iter != " ")
        testVector.push_back(*tok_iter);
    }
    //for(int i=0; i<testVector.size(); i++)
    //cout << "vector: " << testVector[i] << endl;
    //cout << "Now checking for test.." << endl;

    for(int i = 0; i < testVector.size(); i++)
    {
        if (testVector[i] == "test")
        {
            //cout << "Found keyword" << endl;
            return true;
        }

        if (testVector[i] == "[")
        {
            for(int x = i; x < testVector.size(); x++)
            {
                if(testVector[x] == "]")
                {
                    return true;
                }
            }
            return false;
        }

        else
        //cout << "No test keyword found" << endl;
        return false;
    }
};

void checkConnectors(vector<string> passedVector, Executor* comp)
{
    vector<string> parsedVector = passedVector;
    vector<string> parenthVec;
    int lpCount = 0;
    int rpCount = 0;
    int breakCount=0;
    string lp = "(";
    string rp = ")";

    string inRedConnector = "<";
    string singleOutRed = ">";
    string doubleOutRed = ">>";

    string semiConnector = ";";
    string andConnector = "&&";
    string orConnector = "||";
    string exit = "exit";

    string pipeConnector = "|";

    for(int i = 0; i < parsedVector.size(); i++)
    {
        if (parsedVector[i] == "(")
	{
	    lpCount++;
	    while (lpCount != rpCount && breakCount != 50 && i< parsedVector.size())
	    {
		if (breakCount == 49)
		{
		    cout << "Cannot find parentheses" << endl;
		    parenthVec.clear();
		    break;
		}
		breakCount++;
		parenthVec.push_back(parsedVector[i]);
		i++;
		if (parsedVector[i] == "(")
		{
		    lpCount++;
		    //rsedVector[i] = parsedVector[i-1];
		}
		if (parsedVector[i] == ")")
		{
		    rpCount++;
		    //rsedVector[i] = parsedVector[i-1];
		}
	    }
	    comp->add(new Parentheses(parenthVec));
	    parenthVec.clear();
        }

/*
	if (parsedVector[i] == "(")
	{
	    while (parsedVector[i] != rp)
	    {
		if (i == parsedVector.size()-1)
		    break;
		parenthVec.push_back(parsedVector[i]);
		i++;
	    }
	    parenthVec.push_back(")");
	    for (int j=i+1; j < parsedVector.size(); j++)
	    {
		if (parsedVector[j] == rp)
		{
		    cout << "fault1 " << endl;
		    for (i++; i <= j; i++)
		    {
			cout << "fault2" << endl;
			parenthVec.push_back(parsedVector[i]);
		    }
		    cout << "fault3" << endl;
		    i++;
		}
	    }
	    for (int i=0; i< parenthVec.size(); i++)
		cout << parenthVec[i] << endl;
	    comp->add(new Parentheses(parenthVec));
	    parenthVec.clear();

	}
*/
        if (parsedVector[i] == inRedConnector)
        {
            Command* leftChild = new Command(parsedVector[i - 1]);
            Command* rightChild = new Command(parsedVector[i + 1]);

            InputRed* tree = new InputRed(leftChild, rightChild);
            comp->add(tree);

        }

        if (parsedVector[i] == singleOutRed)
        {
            Command* leftChild = new Command(parsedVector[i - 1]);
            Command* rightChild = new Command(parsedVector[i + 1]);

            SingleRed* tree = new SingleRed(leftChild, rightChild);
            comp->add(tree);
        }

        if (parsedVector[i] == doubleOutRed)
        {
            Command* leftChild = new Command(parsedVector[i - 1]);
            Command* rightChild = new Command(parsedVector[i + 1]);

            DoubleRed* tree = new DoubleRed(leftChild, rightChild);
            comp->add(tree);
        }

        if (parsedVector[i] == semiConnector)
        {
            //cout << "Found semicolon" << endl;

            string toPass = parsedVector[i - 1];
            bool foundTest = false;
            foundTest = checkTest(toPass);

            if (foundTest == true)
            {
                Test* test = new Test(parsedVector[i - 1]);
                int didTest;
                didTest = test->testResult();

                //cout << "Did test = " << didTest << endl;

                if (didTest == 1)
                {
                    parsedVector[i - 1] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i - 1] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i - 1] = "error";
                }

                Command* child = new Command(parsedVector[i -1]);
                Semi* tree = new Semi(child);
                comp->add(tree);
            }
	    else if (parsedVector.size() > 3)
		if (parsedVector[i-2] == "|")
		    comp->add(new Semi(new Command(" ")));

            else if (foundTest == false)
            {
                Command* child = new Command(parsedVector[i-1]);
                Semi* tree = new Semi(child);
    	        comp->add(tree);
            }
        }

        if (parsedVector[i] == pipeConnector)
        {
	    vector<Shell*>pipes;

	    pipes.push_back(new Command(parsedVector[i-1]));
	    i++;
	    int k = 0;
	    for (int j = i; j<parsedVector.size(); j++)
	    {
		if (parsedVector[j] == pipeConnector)
		    k = j;
            }
            for (i; i < (k+1); i++)
	    {

		if (parsedVector[i] != pipeConnector)
		    pipes.push_back(new Command(parsedVector[i]));
		if ( i == k )
		    pipes.push_back(new Command(parsedVector[i+1]));
	    }
	    if (k == 0)
		pipes.push_back(new Command(parsedVector[i]));
	    Piping* tree = new Piping(pipes);
            comp->add(tree);

        }

        if(parsedVector[i] == andConnector)
        {
	    if (parsedVector.size() > 4)
	    {
		if (parsedVector[i-2] == "|")
		    comp->add(new And(new Command(" "), new Command(parsedVector[i+1])));
	    }

	    else if (parsedVector[i-1] != ")" && parsedVector[i+1] != "(")
	    {
	        Command* leftChild = new Command(parsedVector[i-1]);
                Command* rightChild = new Command(parsedVector[i+1]);
                And* tree = new And(leftChild, rightChild);
	        comp->add(tree);
	    }

	    else if (parsedVector[i-1] == ")" && parsedVector[i+1] != "(")
	    {
		Command* leftChild = new Command(" ");
		Command* rightChild = new Command(parsedVector[i+1]);
		And* tree = new And(leftChild, rightChild);
		comp->add(tree);
	    }
	    else if (parsedVector[i+1] == "(" && parsedVector[i-1] != ")")
	    {
		Command* leftChild = new Command(parsedVector[i-1]);
		Command* rightChild = new Command(" ");
		And* tree = new And(leftChild, rightChild);
		comp->add(tree);
	    }
	    else if(parsedVector[i-1] == rp && parsedVector[i+1] == lp)
	    {
		Command* leftChild = new Command(" ");
		Command* rightChild = new Command(" ");
		And* tree = new And(leftChild, rightChild);
		comp->add(tree);
	    }


            /*Add tree to vector*/

            //cout << "Found and" << endl;
            string leftPass = parsedVector[i - 1];
            bool leftTest = false;
            leftTest = checkTest(leftPass);

            //cout << "left test" << leftTest << endl;

            string rightPass = parsedVector[i + 1];
            bool rightTest = false;
            rightTest = checkTest(rightPass);

            //cout << "Right test" << rightTest << endl;

            if (leftTest == true && rightTest == true)
            {
                Test* test = new Test(parsedVector[i - 1]);
                int didTest;
                didTest = test->testResult();

                if (didTest == 1)
                {
                    parsedVector[i - 1] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i - 1] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i - 1] = "error";
                }

                Command* leftChild = new Command(parsedVector[i - 1]);

                Test* secondTest = new Test(parsedVector[i + 1]);
                didTest = secondTest->testResult();

                if (didTest == 1)
                {
                    parsedVector[i + 1] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i + 1] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i + 1] = "error";
                }
                Command* rightChild = new Command(parsedVector[i + 1]);
                And* tree = new And(leftChild, rightChild);
                comp->add(tree);
            }

            else if (leftTest == false || rightTest == false)
            {
                if(leftTest == true)
                {
                    Test* test = new Test(parsedVector[i - 1]);
                    int didTest;
                    didTest = test->testResult();

                    if (didTest == 1)
                    {
                        parsedVector[i - 1] = "testPass";
                    }

                    if (didTest == 0)
                    {
                        parsedVector[i - 1] = "testFail";
                    }

                    if (didTest == -1)
                    {
                        parsedVector[i - 1] = "error";
                    }

                    Command* leftChild = new Command(parsedVector[i - 1]);
                    Command* rightChild = new Command(parsedVector[i + 1]);
                    And* tree = new And(leftChild, rightChild);
                    comp->add(tree);
                }

                if (rightTest == true)
                {
                    Test* secondTest = new Test(parsedVector[i + 1]);
                    int didTest;
                    didTest = secondTest->testResult();

                    if (didTest == 1)
                    {
                        parsedVector[i + 1] = "testPass";
                    }

                    if (didTest == 0)
                    {
                        parsedVector[i + 1] = "testFail";
                    }

                    if (didTest == -1)
                    {
                        parsedVector[i - 1] = "error";
                    }
                    Command* leftChild = new Command(parsedVector[i -1]);
                    Command* rightChild = new Command(parsedVector[i + 1]);
                    And* tree = new And(leftChild, rightChild);
                    comp->add(tree);
                }
            }

            if(leftTest == false && rightTest == false)
            {
                //cout << "HERE" << endl;
                Command* leftChild = new Command(parsedVector[i -1]);
                Command* rightChild = new Command(parsedVector[i + 1]);
                And* tree = new And(leftChild, rightChild);
                //comp->add(tree);
            }

        }

        if(parsedVector[i] == orConnector)
        {
	    if (parsedVector.size() > 4)
	    {
		if (parsedVector[i-2] == "|")
		    comp->add(new Or(new Command(" "), new Command(parsedVector[i+1])));
	    }
	    if (parsedVector[i-1] != ")" && parsedVector[i+1] != "(")
	    {
                Command* leftChild = new Command(parsedVector[i-1]);
                Command* rightChild = new Command(parsedVector[i+1]);
                Or* tree = new Or(leftChild, rightChild);
	        comp->add(tree);
	    }
	    else if (parsedVector[i-1] == ")" && parsedVector[i+1] != "(")
	    {
		Command* leftChild = new Command(" ");
		Command* rightChild = new Command(parsedVector[i+1]);
		Or* tree = new Or(leftChild, rightChild);
		comp->add(tree);
	    }
	    else if (parsedVector[i-1] != ")" && parsedVector[i+1] == "(")
	    {
		Command* leftChild = new Command(parsedVector[i-1]);
		Command* rightChild = new Command(" ");
		Or* tree = new Or(leftChild, rightChild);
		comp->add(tree);
	    }
	    else if(parsedVector[i-1] == rp && parsedVector[i+1] == lp)
	    {
		Command* leftChild = new Command(" ");
		Command* rightChild = new Command(" ");
		Or* tree = new Or(leftChild, rightChild);
		comp->add(tree);
	    }

            //cout << "Found or" << endl;

            string leftPass = parsedVector[i - 1];
            bool leftTest = false;
            leftTest = checkTest(leftPass);

            if(i + 1 > parsedVector.size())
            {
                perror("Out of range");
                exit;
            }

            string rightPass = parsedVector[i + 1];
            bool rightTest = false;
            rightTest = checkTest(rightPass);


            if (leftTest == true && rightTest == true)
            {
                Test* test = new Test(parsedVector[i - 1]);
                int didTest;
                didTest = test->testResult();

                if (didTest == 1)
                {
                    parsedVector[i - 1] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i - 1] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i - 1] = "error";
                }

                Command* leftChild = new Command(parsedVector[i - 1]);

                Test* secondTest = new Test(parsedVector[i + 1]);
                didTest = secondTest->testResult();

                if (didTest == 1)
                {
                    parsedVector[i + 1] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i + 1] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i + 1] = "error";
                }

                Command* rightChild = new Command(parsedVector[i + 1]);

                Or* tree = new Or(leftChild, rightChild);
                comp->add(tree);
            }

            else if (leftTest == false || rightTest == false)
            {
                if(leftTest == true)
                {
                    Test* test = new Test(parsedVector[i - 1]);
                    int didTest;
                    didTest = test->testResult();

                    if (didTest == 1)
                    {
                        parsedVector[i - 1] = "testPass";
                    }

                    if (didTest == 0)
                    {
                        parsedVector[i - 1] = "testFail";
                    }

                    if (didTest == -1)
                    {
                        parsedVector[i - 1] = "error";
                    }

                    Command* leftChild = new Command(parsedVector[i - 1]);
                    Command* rightChild = new Command(parsedVector[i + 1]);
                    Or* tree = new Or(leftChild, rightChild);
                    comp->add(tree);
                }

                if (rightTest == true)
                {
                    Test* secondTest = new Test(parsedVector[i + 1]);
                    int didTest;
                    didTest = secondTest->testResult();

                    if (didTest == 1)
                    {
                        parsedVector[i + 1] = "testPass";
                    }

                    if (didTest == 0)
                    {
                        parsedVector[i + 1] = "testFail";
                    }

                    if (didTest == -1)
                    {
                        parsedVector[i + 1] = "error";
                    }
                    Command* leftChild = new Command(parsedVector[i -1]);
                    Command* rightChild = new Command(parsedVector[i + 1]);
                    Or* tree = new Or(leftChild, rightChild);
                    comp->add(tree);
                }
            }

            if(leftTest == false && rightTest == false)
            {
                Command* leftChild = new Command(parsedVector[i-1]);
                Command* rightChild = new Command(parsedVector[i+1]);
                Or* tree = new Or(leftChild, rightChild);
    	        //comp->add(tree);
            }
        }

        if (i == parsedVector.size()-1 && parsedVector[i] != semiConnector && parsedVector[i] != andConnector
            && parsedVector[i] != orConnector && i > 0 && parsedVector[i-1] != andConnector &&
	    parsedVector[i-1] != orConnector && parsedVector[i] != "(" && parsedVector[i] != ")" && parsedVector[i]
            != pipeConnector && parsedVector[i-1] != pipeConnector)
        {

            //cout << "Found command" << endl;
            string toPass = parsedVector[i];

            Command* command = new Command(toPass);
	    End* tree = new End(command);
	    comp->add(tree);

            bool foundTest = false;
            foundTest = checkTest(toPass);

            if (foundTest == true)
            {
                Test* test = new Test(parsedVector[i]);
                int didTest;
                didTest = test->testResult();

                if (didTest == 1)
                {
                    parsedVector[i] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i] = "error";
                }

                Command* command = new Command(parsedVector[i]);
                End* tree = new End(command);
                comp->add(tree);

            }

            else if (foundTest == false)
            {
        	    Command* command = new Command(parsedVector[i]);
        	    End* tree = new End(command);
        	    comp->add(tree);
            }

            // string toPass = parsedVector[i];
            // Command* command = new Command(toPass);
	        // End* tree = new End(command);
	        // comp->add(tree);
        }

        if (parsedVector.size() == 1)
    	{
            string toPass = parsedVector[i];
            bool foundTest = false;
            foundTest = checkTest(toPass);

            if (foundTest == true)
            {
                Test* test = new Test(parsedVector[i]);
                int didTest;
                didTest = test->testResult();

                if (didTest == 1)
                {
                    parsedVector[i] = "testPass";
                }

                if (didTest == 0)
                {
                    parsedVector[i] = "testFail";
                }

                if (didTest == -1)
                {
                    parsedVector[i] = "error";
                }

                Command* command = new Command(parsedVector[i]);
                End* tree = new End(command);
                comp->add(tree);


            }

            else if (foundTest == false)
            {
        	    Command* command = new Command(parsedVector[i]);
        	    End* tree = new End(command);
        	    comp->add(tree);
            }
    	}
    }
};

void print(vector<string> passedVector)
{
    vector<string> parsedVector = passedVector;

    cout << "PARSED VECTOR: ";

    for(int i = 0; i < parsedVector.size(); i++)
    {
        cout << "Index: " << i  << " " << parsedVector[i] << " " << endl;
    }

    cout << "Vector size " << parsedVector.size() << endl;
};


int main()
{
    string userInput;
    vector<string> parsedVector;
    Executor* composite;

    do {
        composite = new Executor();

        userInput = userPrompt(); //Input line
        parsedVector = parser(userInput); //Parse line
        checkConnectors(parsedVector, composite);
        //composite->print();
	    composite->execute();
    }
    while (!composite->getEsc());

    cout << "Exiting...\n";
    return 0;
};
