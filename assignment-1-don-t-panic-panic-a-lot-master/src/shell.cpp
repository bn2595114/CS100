//Definition file for shell

#include <iostream>
#include "shell.h"
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;
using namespace boost;

Shell::Shell(){};

// string Shell::userPrompt()
// {
//     char hostName[1024];
//     gethostname(hostName, 1023);
//     if (!hostName)
//     {
//         perror("gethostname error");
//     }
//
//     char userName[1024];
//     getlogin_r(userName, 1023);
//     if (!userName)
//     {
//         perror("getusername error");
//     }
//
//     cout << userName << "@" << hostName << "$ ";
//
//     getline(cin, userInput);
//
//     return userInput;
// };

vector<string> Shell::parsing(string toParse)
{
    vector<string> parsed;

    typedef boost::tokenizer< boost::char_separator<char> > Tok;
    boost::char_separator<char> conn(" ","#[]()");
    Tok connector(toParse, conn);

    for (Tok::iterator tok_iter = connector.begin(); tok_iter != connector.end(); tok_iter++)
    {
	if(tok_iter == connector.end())
	    break;

	else if(*tok_iter != " ")
	    parsed.push_back(*tok_iter);
    }
    return parsed;
};
/*
vector<string> Shell::parsing(string toParse)
{
    vector<string> parsed;
    typedef boost::tokenizer< boost::char_separator<char> > Tok;
    boost::char_separator<char> conn(" ","#[]()");
    Tok connector(toParse, conn);
    for(Tok::iterator tok_iter = connector.begin(); tok_iter != connector.end(); tok_iter++)
    {
	if(tok_iter == connector.end())
	    break;
	else if(*tok_iter != " " && *tok_iter != ")" && *tok_iter != "(")
	    parsed.push_back(*tok_iter);
    }
    
    return parsed;

};
*/

