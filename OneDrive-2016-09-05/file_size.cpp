#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<vector>
#include<stdio.h>
#include<sys/stat.h>
using namespace std;

void fileStat(char *);
void fileSeekStatSeek(FILE *);
int main(int argc,char *argv[])
{
	argv[1]="temp.txt";
	FILE *file = fopen(argv[1], "r");
	fileStat(argv[1]);
	fileSeekStatSeek(file);
	return 0;
}	
void fileStat(char *ptr)
{
	//filsestat is faster	
	cout<<"\nIn FileStat";
	struct stat st;
	for(int i=0;i<1000000;i++)
	{
		stat(ptr, &st);
	}
	cout<<"\nFile Size using stat is: "<<st.st_size;
}
void fileSeekStatSeek(FILE *file)
{	
	int size;
	cout<<"\nfileSeekStatSeek";
	for(int i=0;i<1000000;i++)
        {
		fseek(file, 0, SEEK_END);
		size=ftell(file);
		fseek(file,0,SEEK_SET);
	}	
	cout<<"\nFile Size using ftell and fseek is: "<<size;
}

