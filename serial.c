#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	double pi;
	double sum=0;
	int nom=1;
	int i;
	if (argc<2) //If arguments are not enough show usage.
	{
		printf("Usage: ./serial numberOfIterations\n");
		return 0;
	}
	int iteration=atoi(argv[1]);
	double denominator=1;
	
	for(i=0;i<iteration;i++)
	{
		sum+=pow((-1),i)*(nom/denominator); // Calculate Leibniz formula
		denominator+=2; // Increment denominator by 2 each step
 	}
	
	pi=sum*4; // To figure out final result of pi multiply by 4
	printf("%1.51f\n",pi);	
}