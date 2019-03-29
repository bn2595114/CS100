#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "shell.h"

using namespace std;

class Test: public Shell
{
    protected:
        bool noTest;
        string testString;
        vector<string> testVector;

    public:
        Test(string passedString)
        {
            testVector = parseTest(passedString);
        };

        char** get(){}; // returns value of whatever
        string getStr(){};
        bool getEsc(){};
        int getFail(){};
        void setFail(int){};
        void execute(){};
		void convert() {};
        void print(){}; //testing object inputs

        vector<string> parseTest(string passString)
        {
	    /*This parser will find the symbolic version of test if it exists*/
            vector<string> parsed;

            typedef boost::tokenizer< boost::char_separator<char> > Tok;
            boost::char_separator<char> conn(" ","[]");
            Tok connector(passString, conn);

            for (Tok::iterator tok_iter = connector.begin(); tok_iter != connector.end(); tok_iter++) 
			//Iterate through the passed command string and check for symbolic version of test.
            {
                if(tok_iter == connector.end())
                    break;

                else if(*tok_iter != " ")
                    parsed.push_back(*tok_iter);
            }

            return parsed; 
        };

        int testResult()
        {
            struct stat sb;
            string flag;
            string path;
            int i = 0;

            /*Assign parameters for test*/

            if(testVector[i] == "test" && (i + 1) < testVector.size())
            {
                if(testVector[i + 1] == "-e" || testVector[i + 1] == "-d" || testVector[i + 1] == "-f") //If we find a flag.
                {
                    flag = testVector[i + 1]; //Assign flag.
                    if((i + 2) < testVector.size())
                    {
                        path = testVector[i + 2]; //Assign path, which is presumably next to flag.
                    }

                    if((i + 2) >= testVector.size())
                    {
                        cout << "NO PATH" << endl; // Else we will error that there is no path.
                        return -1;
                    }

                    // cout << "flag: " << flag << endl;
                    // cout << "path: " << path << endl;
                    return testCommand(flag, path); // We call the testCommand method with the flag and path and return it.
                }


                else if(testVector[i + 1] != "-e" || testVector[i + 1] != "-d" || testVector[i + 1] != "-f") // If we do not find a flag.
                {
                    flag = "-e"; //Flag is defaulted to -e.
                    path = testVector[i + 1];
                    return testCommand(flag, path);
                }
            }

            else if (testVector[i] != "test" && (i + 1) < testVector.size()) //Logic for the symbolic version of test. Works similarly.
            {
                //cout << "Symbolic version" << endl;

                if(testVector[i + 1] == "-e" || testVector[i + 1] == "-d" || testVector[i + 1] == "-f")
                {
                    flag = testVector[i + 1]; 
                    if((i + 2) < testVector.size())
                    {
                        path = testVector[i + 2];
                    }

                    if((i + 2) >= testVector.size() || testVector[i] == "]")
                    {
                        cout << "NO PATH" << endl;
                        return -1;
                    }

                    // cout << "flag: " << flag << endl;
                    // cout << "path: " << path << endl;
                    return testCommand(flag, path);
                }


                else if(testVector[i + 1] != "-e" || testVector[i + 1] != "-d" || testVector[i + 1] != "-f")
                {
                    flag = "-e";
                    if(testVector[i + 1] == "]")
                    {
                        cout << "NO PATH" << endl;
                        return -1;
                    }
                    path = testVector[i + 1];
                    // cout << "flag: " << flag << endl;
                    // cout << "path: " << path << endl;
                    return testCommand(flag, path);
                }
            }
        };

        bool testCommand(string passedFlag, string passedPath)
        {
            struct stat sb;
            string flag = passedFlag;
            string path = passedPath;

            //PRIMING STAT WITH PATH.
            int statValue = stat(path.c_str(), &sb);
            /*-e checks if the file/directory exists*/
            if(flag == "-e")
            {
                if(statValue == 0) //if the path exists.
                {
                    return 1; //(True)
                }
                else
                {
                    return 0; //(False)
                }
            }

            /*-f checks if the file/directory exists and is a regular file*/
            if(flag == "-f")
            {
                if(S_ISREG(sb.st_mode)) //If the path is a file
                {
                    return 1; //(True)
                }

                else
                {
                    return 0; //(False)
                }
            }

            /*-d checks if the file/directory exists and is a directory*/
            if(flag == "-d")
            {
                if(S_ISDIR(sb.st_mode)) //If path is a directory.
                {
                    return 1; //(True)
                }

                else
                {
                    return 0; //(False)
                }
            }
        };

};

#endif
