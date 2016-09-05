#include<iostream>
#include<signal.h>
#include<stdio.h>
#include <string.h>
using namespace std;
/*
1. Signal Handling is used to modify the behaviour of the Program if any Interrupt(Signal) is given by User.
2. A Structure needs to be defined this structure calls the function that needs to be executed once signal is received (sa_handler field is usually used)
3. You Can't modify the behaviour of process when it receives SIGKILL ()
4. The Map of Signals vs Kill is in Basic C++ Programs folder
5. The Signal is caught immediately irrespective of where you have done the signal handling
6. When the function defined in structure is being executed no other signal can be caught so make sure that you write real small functions for the same and do other handlings else where (Eg:- Function to switch ON Debugs in WL Decommisioning)
7.  Use function signal if you want to overcome the restriction mentioned above
*/

int sighandling1();
int sighandling2();

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	//To Show that "When the function defined in structure is being executed no other signal can be caught so make sure that you write real small functions for the same and do other handlings else where (Eg:- Function to switch ON Debugs in WL Decommisioning)"
	//siginfo_t gives additional info on the type of signal caught
	cout<<"\n======================================="<<endl;
	cout<<"sig is "<<sig;
	cout<<"\nsig Tells you which kill command was executed";
	cout<<"\n======================================="<<endl;
		
	static int no=0;
	no++;
	printf ("\nSending PID: %ld, UID: %ld\n",
			(long)siginfo->si_pid, (long)siginfo->si_uid);
	cout<<"\nHave Been Called "<<no<<" times"<<endl;
	sleep(10);
}
 
void hdl2 (int sig)
{
	cout<<"\nIn hdl2"<<endl;
	cout<<"\n======================================="<<endl;
        cout<<"sig is "<<sig;
        cout<<"\nsig Tells you which kill command was executed";
        cout<<"\n======================================="<<endl;

}


int main (int argc, char *argv[])
{
	//This function needs to be initialized once then onwards it catches the irrespective of it is called or not
	sighandling1();
	sighandling2();
	while(1)
		sleep(20);
	return 0;
}	

int sighandling1()
{	
	struct sigaction act;
 	//MemSet is used to clear any objject
	memset (&act, '\0', sizeof(act));
 
	/* Use the sa_sigaction field because the handles has two additional parameters */
	act.sa_sigaction = &hdl;

	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGTERM, &act, NULL) < 0) 
	{
		perror ("sigaction");
		return 1;
	}
	return 0;
}

int sighandling2()
{
        struct sigaction act1;
        //MemSet is used to clear any objject
        memset (&act1, '\0', sizeof(act1));
	
	//If I use sa_handler then I can only create a function with sig as a parameter 
        
	act1.sa_handler = hdl2;

        //if (sigaction(SIGTERM, &act, NULL) < 0) In case more than 1 sigaction is used for same signal Only one gets executed 
        //PLEASE NEVER DO SUCH A THING AS THE BEHAVIOUR IS UNEXPECTED
	if (sigaction(SIGUSR1, &act1, NULL) < 0) 
        {
                perror ("sigaction");
                return 1;
        }
        return 0;
}

