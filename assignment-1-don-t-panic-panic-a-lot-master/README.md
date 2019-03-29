# Creating a basic shell
We are creating a basic shell program in C++ that essentially what BASH does. The program should simply do 3 things. 
1. Print "username@hostname$ " to prompt the user that we are in the shell.
2. Parse the input.
3. Execute the input accordingly.

Simple right? Here's the breakdown of what we did to accomplish this.

## Shell Class
This class is the base class that the client interacts with. 
It has one attribute/component and that is:
```
string userInput
string userInput;
char* argLeft[50]; //Let left be used for semi colon also
char* argRight[50]; // Right argument
bool esc; // checj for escape
bool comment; // check for comment tag
int fail; // -1 fail, 0 nothing, 1 success
bool testResult;
```
Shell then contains the following functions.
```
Shell(); // Constructor
vector<string> parsing(string); // parsing into own vectors
virtual char** get() = 0; // returns value of whatever
virtual string getStr() = 0; // Function that allows us to grab the current string at any point in our program.
virtual bool getEsc() = 0; // Function that checks for exit.
virtual int getFail() = 0; // Function that checks if there has been an execution failure
virtual void setFail(int) = 0;
virtual void execute() = 0;
virtual void print() = 0; //testing object inputs

```
## Command Class
The command class is essentially in charge of parsing the vector further so we can pass the command as well as the arguments to the appropriate connector or if it's just a single command, the end class which handles single commands.

## Connector Classes

### SemiColon
Processes commands involving semicolons.

### And
Processes commands involving ampersands.

### Or
Processes commands involving ||.

### End
This class processes the command if the user enters a single command and no connectors.

## Executor Class
The composite class is also our execution class, while also being our composite class. It contains a vector of Shell pointers and creates a tree that we traverse when we execute.

## Test Command
This is the testCommand object that is called when the program sees the keyword for the command “Test”, when this object is created, we will simply execute the command along with the flag and path, and whatever is returned we will replace what is inside the original vector of strings to either testPass, testFail, or testError depending on what was returned. The connector classes are programmed so that it will recognize these strings execute those strings accordingly.

## Parentheses Class
The Parentheses Class allows us to utilize order of operations to our code. The Parentheses constructor deals with much of the work, since it parses the vector of strings that is sent to it. 
parseP() further parses the vector, by parsing spaces and the parentheses themselves. Though it may not be fully utilized such as (echo x) does not work, we believed that it was not the most important to deal with and went to complete more important tasks. The getV() method parses the things inside the parentheses such as &&, ||, and ;. After parsing like so, we are able to parse it given some logic to the executor class so the order of operations are being followed.

## Piping Class
The piping class allows us to utilize pipes to our shell script. The constructor contains all the basic necessities for the program to continue looping. It also contains the get() function of the command class to parse and convert the command strings into char** in order to execute in the execute function. The main code went to our execute function, using pipe(), fork(), execvp(), wait(), dup2(), and perror(). We were able to make piping work by using two child processes and continually piping to the directed output and input. We implemented a vector to hold multiple pipe commands in case the user wants to use multiple pipes and it works as desired. For the rest, it contains many methods declared in the abstract parent class that are not utilized.

## Redirection Classes
The redirection classes allow us to redirect input and output to different commands. For a practical application of the redirections, we could for example redirect the output of a file to a text file which could act as an error log.

### Input Redirection '<'
This function allows us to take any argument and redirect it into a command. 

### Output Redirection '>'
This function allows us to redirect the output of a command, into another location for example a txt file. Using the open function we open the file, and assign it to a file descriptor. Once we have that we input the file descriptor in the dup2 function which will redirect the standard output stream to the file.

### Output Redirection '>>'
This function is essentially the same thing as the single output redirection, but the only difference is that we append to the file instead of overwrite it. This may be useful if we’re trying to look for the history of errors or something of that nature.

## List of known bugs / to do list

* Comments don't work as intended
* Test command only works with one flag and specific syntax.
* Test command still needs to return value for connectors to know if pass or fail.
* Sometimes exit has to be entered multiple times for the program to exit.
* ( echo x) does not work. Singular commands in parentheses without the semicolon does not work, everything else does
* Some things output twice when the test command is involved
* Redirection commands only work in single instances. Does not work with connectors or pipes.

