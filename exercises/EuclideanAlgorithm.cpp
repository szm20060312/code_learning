#include<iostream>
using namespace std;

// Euclidean algorithm to find GCD of two numbers
int EuclideanAlgorithm(int a,int b){
    int r=a%b;
    if(b==0){
        return a;
    }
    return EuclideanAlgorithm(b,r);
}
// Driver code
int main(){
    int a,b;
    cout << "Please enter two integers: "<<endl;
    cin >> a >> b;
    cout<<EuclideanAlgorithm(a,b)<<endl;
    return 0;
}