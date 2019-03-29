
#ifndef PARENTHESES_H
#define PARENTHESES_H

#include "shell.h"
#include "and.h"
#include "semi.h"
#include "or.h"
#include "end.h"
#include "command.h"
using namespace std;
using namespace boost;

class Parentheses : public Shell
{
    private:
	string fullStr; // Converts container into one long string
        vector<string> container;
	vector<string> parsedContainer;
	vector<Shell*> shellContainer;
	bool ex;
	
    public:
        Parentheses(vector<string> p)
        {
	    fullStr = "";
	    ex = false;
	    esc = false;
	    fail = 0;
            container = p;
	    for (int i=0; i<container.size(); i++)
	    {
		fullStr += container[i];
	    }
	    //container.pop_back();
	

	    
	    parseP();
        };
	void parseP(); //parses parentheses
	void convert() {};
	char** get() {};
	void getV() 
	{
	    for (int i=0; i<parsedContainer.size(); i++)
	    {
		if (parsedContainer[i] == ";")
		{
		    Command* child = new Command(parsedContainer[i-1]);
		    Semi* tree = new Semi(child);
		    shellContainer.push_back(tree);
		}
		else if (parsedContainer[i] == "&&")
		{
		    Command* leftChild = new Command(parsedContainer[i-1]);
		    Command* rightChild = new Command(parsedContainer[i+1]);
		    And* tree = new And(leftChild, rightChild);
		    shellContainer.push_back(tree);
		}
		else if (parsedContainer[i] == "||")
		{
		    Command* leftChild = new Command(parsedContainer[i-1]);
		    Command* rightChild = new Command(parsedContainer[i+1]);
		    Or* tree = new Or(leftChild, rightChild);
		    shellContainer.push_back(tree);
		}
		else if ( i == parsedContainer.size()-1 && parsedContainer[i] != ";" && parsedContainer[i] !=
			  "&&" && parsedContainer[i] != "||" && i>0 && parsedContainer[i-1] != "&&" && 
			  parsedContainer[i-1] != "||")
		{
		    Command* child = new Command(parsedContainer[i]);
		    End* tree = new End(child);
		    shellContainer.push_back(tree);
		}
/*		else if (parsedContainer.size() == 1)
		{
		    cout << "Single end () found\n";
		    Command* child = new Command(parsedContainer[i]);
		    End* tree = new End(child);
		    shellContainer.push_back(tree);
		}
*/
		
	    }
	      
	};
	string getStr() { return "p"; };
	bool getEsc() {return ex;};
	int getFail() {return fail;};
	void setFail(int f) { fail = f;};
	void execute()
	{
	    this->getV();
	    for (int i=0; i<shellContainer.size(); i++)
	    {
		if (i>0)
		    shellContainer[i]->setFail(shellContainer[i-1]->getFail());
		shellContainer[i]->execute();
		
		if (shellContainer[shellContainer.size()-1]->getFail() == -1)
		    this->fail = -1;
		if(shellContainer[shellContainer.size()-1]->getFail() == 1)
		    this->fail = 1;
		if (shellContainer[i]->getEsc() == true)
		{
		    ex = true;
		    return;
		}
	    }  
	};
	void print() {};
};

#endif
