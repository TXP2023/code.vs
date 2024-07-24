#include<iostream>
#define elif else if
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    if (n == 5)
    {
        cout << "JMcat Win";
    }elif(n % 2 == 0)
    {
        cout << "JMcat Win";
    }
    else
    {
        cout << "PZ Win";
    }      
    return 0;
}