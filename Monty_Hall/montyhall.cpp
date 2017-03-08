#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int genRandChoice(){

	int choice;
	choice = rand() % 3 + 1;

	return choice;
}
int main()
{
	int cardoor, choice_1, montychoice, sum, choice_2, i, num, win1=0,win2=0;
	srand (time(NULL));
	cout <<"   "<<"#"<<"  "<<"   Car"<<"  "<<"   First"<<"  "<<"  Opened"<<"  "<<"  Second"<<"  "<<"    Win"<<"  "<<"     Win"<< endl;
	cout <<"        "<<"Here"<<"    "<<"Choice"<<"  "<<"    Door"<<"    "<<"Choice"<<"    "<<"First"<<"    "<<"Second"<< endl<< endl;
	for(i=0;i<100;i++)
		{
		num =num+1;
		if (num<10)
		cout<<"  ";
		else if(num<100)
			cout<<" ";
	cardoor = genRandChoice();
	choice_1 = genRandChoice();
	sum = cardoor+choice_1;
	montychoice = 6-sum;
	if (cardoor==choice_1)
	{
		do{
			montychoice = genRandChoice();
		}while(montychoice==choice_1);
	}
	do{
		choice_2 = genRandChoice();
	}while(choice_2==choice_1||choice_2==montychoice);
	cout <<" "<<num<<"      "<<cardoor<<"       "<<choice_1<<"          "<<montychoice<<"        "<<choice_2;
	if (choice_2==cardoor)
	{
		cout<<"           "<<"       yes";
		win2++;
	}
	else {cout <<"       yes"<<"            ";
	win1++;
	}
	cout<< endl;
}
	cout<<"\n"<< win1<<" wins if stay with the first choice" << endl;
	cout<<win2<<" wins if switch to the second choice"<< endl<<endl;
	cout<<"Win ratio of switch over stay: "<<(float)win2/(float)win1;
}

