#include <iostream>
using namespace std;
int main(){
    int maxstr;
    cin >> maxstr;
    int noofcont;
    cin >> noofcont;
    int array1[noofcont];
    for (int i=0; i < noofcont; i++){
        int n;
        cin >> n;
        array1[i]= n;
    }
    int sum = 0; 
    int min = array1 [0];
    int max = array1[0];
    for (int qty : array1){
        sum += qty;
        if (qty >= max){
            max = qty;
        }
        if (qty <= min ){
            min = qty;
        }
    }
    cout << "Total shipment weight" << sum;
    cout << (float)sum/noofcont;
    cout << max;
    cout << min;
    if (sum >= 200){
        cout << "Heavy";
    }
    cout << maxstr;
    if (sum <= maxstr){
        cout << "Shipment can be unloaded";
    } else {cout << "Shipment exceeds port capacity";}
return 0;
}
