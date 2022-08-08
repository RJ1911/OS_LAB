
/*
     Group : A1
     Team Number : 02
     Date : 3rd August , 2022

         Name               Roll
     --------------------------------
     1. Rimil Murmu          039
     2. Rafson Jani          008
     3. Rajan Kumar          041
     4. Pallabi Soren        010
*/

/*
    Assignment : 2-A . SIGNAL HANDLING

    Details:  Catch the signal "SIGINT" and display “Ha Ha, Not Stopping”. Use "signal"
    system call. Always use “perror” to check the return status of a library/system
    call.

    Input Description:
    After executing the program.
    Press (Ctrl + C) to send signal SIGINT

    Output Description:
    -Display "Ha,Ha,Not Stopping"  .


*/

/*
    Compilation Command:
    gcc 02_2A.c -o 02_2A

    Execution Sequence:
    ./02_2A

*/

/*
    Sample Input :
    <Ctrl + C > (for sending signal)

    <Ctrl + \ > (for exiting the program)

    Sample Output :
    ^C
    Ha Ha , Not Stopping
    ^C
    Ha Ha , Not Stopping
    ^C
    Ha Ha , Not Stopping
    ^\Quit


*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Signal Handler function */

void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        /* Printing string when SIGINT signal is caught */
        printf("\nHa Ha , Not Stopping\n");
    }
}

int main(void)
{
    /* Calling signal() function  to handle SIGINT signal and registering our sig_handler function to kernel */

    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        perror("\nUnable to catch SIGINT\n");
    }

    /* A long long wait so that we can easily issue a signal to this process */

    while (1)
    {
        /* Using sleep() function so that while loop executes after some time(i.e 1 second in this case) , to prevent while        loop from running infinitely which may consume most of the CPU */

        sleep(1);
    }

    return 0;
}
