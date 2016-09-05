#include <iostream>
#include "CEventGenClient.h"
#include<string>
using namespace std;
int main()
{
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	char* dt = ctime(&now);
	cout << "The local date and time is: " << dt << endl;

	string s("Hello World!!!!!");
	CEventGenClient client("localhost", 30000);
	try
	{
		if(client.send(s))
			cout<<"Message Sent successfully";
	}
	catch(CSocketException &e)
	{
		cout<<e.description()<<"\n Exiting ...\n";
	}
	return 0;
}
