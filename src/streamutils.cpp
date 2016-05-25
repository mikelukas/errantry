#include "streamutils.h"

void getIdLine(istream& is, set<int>& ids)
{
	int id;
	while(is.peek() != '\n')
	{
		is>>id;
		ids.insert(id);
	}
	is.get();//throwout newline char
}

void getIdLine(istream& is, vector<int>& ids)
{
	int id;
	while(is.peek() != '\n')
	{
		is>>id;
		ids.push_back(id);
	}
	is.get();//throwout newline char
}
