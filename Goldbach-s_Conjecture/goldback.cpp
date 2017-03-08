#include<iostream>
using namespace std;

int main()
{
	int i,j,k;
	int a[101];
	cout<< "Primes:\n";
	cout<<endl;
	if (i>10)
			cout<<"  ";
	for(i=1;i<=100;i++)
	{
		a[i]=i;
	}
	a[1]=0;
	for(i=2;i<=100;i++)
	{
		if(i!=0)
		{
			for(j=2;j<=(100/i);j++){
				a[i*j]=0;
			}
		}
	}
	for(i=1;i<=100;i++)
	{
		if(a[i]!=0)
			cout<<i<<" ";
		else
			cout<<".  ";
		if(i%10==0)cout<<endl;

	}
	cout<<endl;
	cout<< "Test of Goldbach's Conjecture:\n";
	cout<<endl;
	for(i=4;i<=100;i=i+2)
	{
		cout<<i<<":\t";
		for(j=i-1,k=1;j>=k;j--,k++)
		{
			if(a[j]+a[k]==i)
				cout<<k<<" "<<j<<endl<<"\t";
		}
		cout<<endl;
	}
	return 0;
}
