//Shailee Patel (shailee2)
//Introduction: We used Pascal's Triangle to determine a nth row determined by the user. We then utilized for loops and if statements to print out a singular row with n values. We used a loop for i to determine the row we were in, and another for loop to choose the amount of spaces between our rows. We used another for loop to print out the individual numbers within the rows, choosing whether to just print 1 or to use the math equation to print out the value.

#include <stdio.h>
#include <stdlib.h>
 
int main()
{
  unsigned long int row;
 
  printf("Enter a row index: ");
  scanf("%lu",&row);
  row = row +1;
 
  int i;
  int j;
  int space;
  unsigned long int value;
  for (i=1; i<=row; i++)
  {
      for (space = 1; space <= (row-i); space++)
      {
          if (i==row)
          printf(" ");
      }
      for (j=1; j<=i; j++)
      {
          if (i==1 || j==1)
          {
              value = 1;
          }
          else
          {
              value = value*(i-j+1)/(j-1);
          }
          if (i==row)
          printf("%4ld", value);
      }
      if (i==row)
      printf("\n");
  }
}
