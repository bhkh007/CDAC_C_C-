
#include <cstdio>

class Employee{
public :  
    void GetData(){
        printf("This is GetData member functiond.");
    }
};

int main(){

    Employee emp;
    emp.GetData();
}