#include <stdio.h>
#include <stdlib.h>

int Ackerman(long long int m, long long int n)
{
    long long int r;
    if (m < 0 || n < 0) r = -1;
    else if (m == 0) r = n + 1;
    else if (n == 0) r = Ackerman(m-1,1);
    else r = Ackerman(m-1,Ackerman(m,n-1));

    return r;
    
}

int main()
{
    
    printf ("%lld", Ackerman(3,0));

}
