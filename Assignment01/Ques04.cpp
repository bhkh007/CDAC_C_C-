#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << "--------------------------------------------------" << endl;

   
    cout << "The maximum limit of int data type : " << numeric_limits<int>::max() << endl;
    cout << "The minimum limit of int data type : " << numeric_limits<int>::min() << endl;


    // long limits
    cout << "The maximum limit of long data type : " << numeric_limits<long>::max() << endl;
    cout << "The minimum limit of long data type : " << numeric_limits<long>::min() << endl;

    
    cout << "The maximum limit of long long data type : " << numeric_limits<long long>::max() << endl;
    cout << "The minimum limit of long long data type : " << numeric_limits<long long>::min() << endl;

    cout << "The maximum limit of char data type : " << static_cast<int>(numeric_limits<char>::max()) << endl;
    cout << "The minimum limit of char data type : " << static_cast<int>(numeric_limits<char>::min()) << endl;

    cout << "The maximum limit of float data type : " << numeric_limits<float>::max() << endl;
    cout << "The minimum limit of float data type : " << numeric_limits<float>::min() << endl;

    cout << "The maximum limit of double data type : " << numeric_limits<double>::max() << endl;
    cout << "The minimum limit of double data type : " << numeric_limits<double>::min() << endl;

    cout << "The maximum limit of long double data type : " << numeric_limits<long double>::max() << endl;
    cout << "The minimum limit of long double data type : " << numeric_limits<long double>::min() << endl;

    cout << "The maximum limit of bool data type : " << numeric_limits<bool>::max() << endl;
    cout << "The minimum limit of bool data type : " << numeric_limits<bool>::min() << endl;

    return 0;
}
