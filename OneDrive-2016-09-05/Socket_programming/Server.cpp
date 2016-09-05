#include "CEventGenServer.h"
#include "CSocketException.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{

try
{

    CEventGenServer server(30000);

    while(true)
    {
	CEventGenServer new_sock;

        server.accept(new_sock);

        string fileName;

        try
        {
		new_sock.recieve(fileName);
		// current date/time based on current system
		time_t now = time(0);
		// convert now to string form
		char* dt = ctime(&now);
		cout << "The local date and time is: " << dt << endl; 
		cout<<"The Returned String is: "<<fileName<<endl;
        }
        catch(CSocketException &e)
        {
            cout<<e.description()<<"\n";
        }
    }

}
catch(CSocketException &e)
{
    cout<<e.description()<<"\n Exiting ...\n";
} 
    return 0;
}
