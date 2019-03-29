
#include "parentheses.h"

void Parentheses::parseP()
{
    typedef boost::tokenizer< boost::char_separator<char> > Tok;
    boost::char_separator<char> conn("", "&&||;#()");
    Tok connector(fullStr, conn);

    for (Tok::iterator tok_iter = connector.begin(); tok_iter != connector.end(); tok_iter++)
    {
	if (tok_iter == connector.end())
	    break;
	for (int a=0; a<2; a++)
	{
	    if (*tok_iter == "&")
	    {
		a++;
		if (tok_iter!= connector.end())
		{
		    tok_iter++;
		    if (*tok_iter == "&")
		    {
			parsedContainer.push_back("&&");
			a++;
		    }
		 }
	    }
	}
	for (int b=0; b<2; b++)
	{
	    if (*tok_iter == "|")
	    {
		b++;
		if (tok_iter != connector.end())
		{
		    tok_iter++;
		    if (*tok_iter == "|")
		    {
			parsedContainer.push_back("||");
			b++;
		    }
		}
	    }
	}
	if(*tok_iter != "(" && *tok_iter != ")" && *tok_iter != "&" && *tok_iter != "|" && *tok_iter != " ")
	    parsedContainer.push_back(*tok_iter);
    }
};
