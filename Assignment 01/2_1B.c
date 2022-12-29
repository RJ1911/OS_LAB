
/*
     Group : A1
     Team Number : 2
     Date : 28 July , 2022

         Name               Roll
     --------------------------------
     1. Rimil Murmu          039
     2. Rafson Jani          008
     3. Rajan Kumar          041
     4. Pallabi Soren        010
*/

/*
    Assignment Details:  Program to set and get environment variables using system calls

    Program to GET and SET the Environment variables and to know use of getenv and setenv system calls.

    Display the following environment variables using getenv call:
    - USER
    - HOME
    - HOST
    - ARCH
    - DISPLAY
    - PRINTER
    - PATH

    Now, set two environment variables and display them

    Input Description: No input from command line

    Output Description:
    - Displays the values of the environment variables using getenv()
    - Displays the newly created environment variables created using setenv()
*/

/*
    Compilation Command:
    gcc 2_1B.c -o 2_1B

    Execution Sequence:
    ./2_1B

*/

/*
    Sample Input:
    <No Input>


    Sample Output:

    USER: rj
    HOME: /home/rj
    HOST: (null)
    ARCH: (null)
    DISPLAY: :0
    PRINTER: (null)
    PATH: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/VMware/VMware Player/bin/:/mnt/  c/Program Files/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt  /c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/dotnet/:/mnt/c/Program Files/Cloudflare/Cloudflare WARP/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Program Files/nodejs/:  /mnt/c/Program Files/Git/cmd:/mnt/c/Users/RAFSON/AppData/Local/Programs/Python/Python310/Scripts/:/mnt/c/Users/RAFSON/AppData/Local/Programs/Python/Python310/:/mnt/c/Prog  ram Files/MySQL/MySQL Shell 8.0/bin/:/mnt/c/Users/RAFSON/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/RAFSON/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Progr  am Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin:/mnt/c/Program Files/JetBrains/IntelliJ IDEA Community Edition 2021.3.2/bin:/mnt/c/Program Files (x  86)/SSH Communications Security/SSH Secure Shell:/mnt/c/Program Files/JetBrains/PyCharm Community Edition 2021.3.3/bin:/mnt/c/Users/RAFSON/AppData/Local/Programs/oh-my-po  sh/bin:/mnt/c/Program Files/nodejs/node_modules/npm/bin:/mnt/c/Users/RAFSON/AppData/Roaming/npm:/snap/bin

    VAR1 Created successfully!
    VAR1: val1

    VAR2 Created successfully!
    VAR2: val2

    VAR2 Overwritten successfully!
    VAR2: val3

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{

    /* Using getenv() */

    /* Storing value of getenv() in character pointers */

    char *user = getenv("USER");
    char *home = getenv("HOME");
    char *host = getenv("HOST");
    char *arch = getenv("ARCH");
    char *display = getenv("DISPLAY");
    char *printer = getenv("PRINTER");
    char *path = getenv("PATH");

    /* Printing values of getenv() */

    printf("USER: %s\n", user);
    printf("HOME: %s\n", home);
    printf("HOST: %s\n", host);
    printf("ARCH: %s\n", arch);
    printf("DISPLAY: %s\n", display);
    printf("PRINTER: %s\n", printer);
    printf("PATH: %s\n", path);
    

    /* Using setenv() */

    /* Using setenv() to create VAR1 variable with value val1 */

    if (setenv("VAR1", "val1", 0) == 0)
    {
        printf("\nVAR1 Created successfully!\n");
        printf("VAR1: %s\n", getenv("VAR1"));
    }
    else
    {
        perror("\nVAR1 could not be created\n");
    }


    /* Using setenv() to create VAR2 variable with value val2 */

    if (setenv("VAR2", "val2", 5) == 0)
    {
        printf("\nVAR2 Created successfully!\n");
        printf("VAR2: %s\n", getenv("VAR2"));
    }
    else
    {
	perror("\nVAR2 could not be created\n");
    }
    

    /* Overwritting value of VAR2 variable with vlaue val3 */
    
    if (setenv("VAR2", "val3", 10) == 0)
    {
        printf("\nVAR2 Overwritten successfully!\n");
        printf("VAR2: %s\n", getenv("VAR2"));
    }
    else
    {	    
        perror("\nVAR2 could not be overwritten\n");
    }

    return 0;
}
