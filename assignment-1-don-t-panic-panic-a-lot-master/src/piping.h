
#ifndef PIPING_H
#define PIPING_H

#include "shell.h"

using namespace std;


// piping : [0] for reading  | [1] for writing

class Piping : public Shell
{
    private:
        bool isPiped;
        Shell* pipeLeft;
        Shell* pipeRight;
	char** argLeft;
	char** argRight;
        vector<Shell*> pC; // pipe container
	vector<char**> arg;
    public:
        Piping(vector<Shell*> p)
        {
	    esc = false;
            fail = 0;
	    for (int i=0; i<p.size(); i++)
	    {
		arg.push_back(p[i]->get());
	    }
        };
        void print()
        {
            cout << "Left Child = ";
            pipeLeft->print();
            cout << "Right Child = ";
            pipeRight->print();
        };

        string getStr() { return "pipe"; };
        char** get() {};
        bool getEsc() { return esc; };
        int getFail() { return fail; };
        void setFail(int f) { fail = f;};
        void execute(); // executing pipes
        void convert() {};

};



#endif
