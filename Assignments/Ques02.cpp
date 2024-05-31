#include <iostream>
using namespace std;

int main(){

    int num1= 29;
    int num2= 30;

    int result  = num1+ num2;

    cout <<"Sum"<<endl;
    cout<< "The sum of 29 and 30 is " <<result<<endl;

    int input1,input2,temp;

    cout<<"Swap"<<endl;
    cout<<"Input 1st Number";
    cin>>input1;
    cout<<"Input 2nd Number";
    cin>>input2;

    temp=input1;
    input1 = input2;
    input2 = temp;

    cout<<"After swapping the first number is: "<<input1<<endl;
    cout<<"After swapping the second number is: "<<input2<<endl;

    return 0;
}