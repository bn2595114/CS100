

#include "piping.h"


void Piping::execute() 
{
    int i, end, status;
    int fd[2];
    pid_t cpid, ppid;


    for (i=0; i<arg.size()-1; i++)
    {
        pipe(fd);
	cpid = fork();
        if (cpid == 0)
        {
            if (end != 0)
            {
                dup2(end, 0);
		close(end);
            }
            if (fd[1] != 1)
            {
                fail = dup2(fd[1], 1);
                close(fd[1]);
            }

	    fail = execvp(*arg[i], arg[i]);
	    if (fail < 0)
		perror("Child execution failed");

        }
	else if (cpid == -1)
	{
	    perror("Forking error");
	    exit(EXIT_FAILURE);
	}
	else
	{
	    ppid = wait(&status);
	    if (status < 0)
		perror("Abnornmal exit of program");
	}
	close(fd[1]);
	end = fd[0];
    }


    cpid = fork();
    if (cpid == 0)
    {
        if(fd[0] != 0)
            fail = dup2(fd[0], 0);
        if (fail == -1)
        {
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        fail = execvp(*arg[i], arg[i]);
	if (fail == -1)
	    perror("Child execution failed");
	else
	    fail = 1;

        }
    else if (cpid > 0)
    {
        ppid = wait(&status);
        if (ppid < 0)
	    perror("Abnormal exit of program");
    }
    else
	perror("Forking error");

};
