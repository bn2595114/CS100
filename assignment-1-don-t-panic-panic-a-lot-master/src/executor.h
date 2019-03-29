

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include "shell.h"

class Executor : public Shell
{
    private:
    vector<Shell*> toExecute;
	bool ex; //exit

    public:
        Executor() { ex = false; };
        void add(Shell* leaf)
        {
            toExecute.push_back(leaf);
        }
	void convert() {};
        void print()
        {
            for(int i=0; i<toExecute.size(); i++)
	    {
    		cout << "Executor commands: ";
    		toExecute[i]->print();
	    }
        }
    	string getStr() {};
    	char** get() {};
    	int getFail() {};
    	void setFail(int) {};
        void execute()
    	{
    	    for(int i=0; i<toExecute.size(); i++)
    	    {

        		if (i > 0)
        		{
        		    toExecute[i]->setFail(toExecute[i-1]->getFail());

                    if (toExecute[i-1]->getStr() == "o" && toExecute[i]->getStr() == "p")
        		    {

                        if (toExecute[i-1]->getFail() == 1)
                        {
                            break;
                        }
            			else
            			    toExecute[i]->execute();

        		    }

                    else if (toExecute[i-1]->getStr() == "a" && toExecute[i]->getStr() == "p")
        		    {
            			if(toExecute[i-1]->getFail() == -1) {;}

                        else
            			toExecute[i]->execute();
        		    }

                    else if (toExecute[i-1]->getStr() == "p" && toExecute[i]->getStr() == "p")
        		    {

        		    }
        		    // else
                    // cout << "2" << endl;
        			// toExecute[i]->execute();

        		}

        		else
        		    toExecute[i]->execute();


                	if (toExecute[i]->getEsc() == true)
                	{
            		    ex = true;
            		    return;
                	}
            	}
    	}
    	bool getEsc()
        {
    	       return ex;
	    };

};

#endif
