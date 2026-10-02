#include <iostream>
#include <fstream>
using namespace std;
void sort(int array1[], int n){
    for (int i = 0; i < n ; i++){
        int j = i;
        int min = array1[0];
        int minindex;
        for (j; j < n ; j++){
            if (array1[j] <= min ){
                min = array1[j];
                minindex = j;
            }
        }
        int placeholder = array1 [i];
        array1[i]= array1[minindex];
        array1[minindex]= placeholder;
    }

}
void writeto(int tot, int avg, int he, int li, string cls){
    ofstream f("containers.txt");
    f << tot << avg << he << li << cls;
    f.close();
}

void readfrom(string filename){
    string cls;
    int tot, avg, he, li;
    ifstream f(filename);
    while (f >> tot >> avg >> he >> li >> cls){
        cout << tot << avg << he << li << cls;
    }
    f.close();
}

void kth(){

}

void search(string filename, int wt){
    string cls;
    int tot, avg, he, li;
    ifstream f(filename);
    while (f >> tot >> avg >> he >> li >> cls)
    {;
    }
    f.close();
}

int main(){
    bool choice = true;
    do{
        int maxstr;
        cin >> maxstr;
        int noofcont;
        cin >> noofcont;
        int array1[noofcont];
        for (int i = 0; i < noofcont; i++)
        {
            int n;
            cin >> n;
            array1[i] = n;
        }
        int sum = 0;
        sort(array1,noofcont);
        for ( int qty : array1){
            sum += qty;
        }
        int min = array1[0];
        int max = array1[noofcont-1];
        cout << "Total shipment weight" << sum;
        int avg = (float)sum / noofcont;
        cout << avg;
        string stat;
        if (sum >= 200)
        {
            cout << "Heavy";
            stat = "Heavy";
        }
        else {cout << "Light"; stat = "Light";};
    char ch2;
    cout << "Wish to write to file? y/n ";
    cin >> ch2;
    if (ch2 == 'y'){
        writeto(sum, avg, max, min, stat);
    };
    char ch;
    cout << "Wish to continue? y/n";
    cin >> ch;
    if (ch == 'n'){
        choice = false;
    }
    } while (choice == true);
return 0;
}
