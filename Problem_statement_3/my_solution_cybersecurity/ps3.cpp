#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const string base64table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct rsareturnval{
    string numbered;
    vector <long long> encodedd;
};

string atob(long long int ascii)
{
    string binary;
    for (int i = 7; i >= 0; i--){
        binary += ((ascii >> i) & 1) ? '1' : '0';
    }
    return binary;
}

int btoa(string sixbit, int n){
    int dec = 0;
    for (int i = 0; i < n; i++){
        dec <<= 1;
        if (sixbit[i] == '1'){
            dec |= 1;
        }
    }
    return dec;
}

string base64(string msg){
    vector <int> ascii64;
    for (char c : msg){
        ascii64.push_back(int(c));
    }
    int padding = ascii64.size() % 3;
    string binaryeq;
    vector <string> binary64;
    for ( size_t i = 0; i < msg.size() ; i++){
        binaryeq = atob(ascii64[i]);
        binary64.push_back(binaryeq);
    }
    string finalbinary = "";
    for (string bin : binary64){
        finalbinary += bin;
    }
    while (finalbinary.length() % 6 != 0){
        finalbinary += '0';}
    const char* ptr = finalbinary.data();
    vector <string> sixbitarray;
    for (size_t i = 0; i < finalbinary.length(); i += 6){
        sixbitarray.push_back(finalbinary.substr(i,6));
    }
    vector <int> decencoded;
    for (string sixbit  : sixbitarray){
        int dec = btoa(sixbit,6);
        decencoded.push_back(dec);
    }
    string base64encoded = "";
    for (int dec : decencoded){
        base64encoded += base64table[dec];
    }
    if (padding==1){
        base64encoded+="==";
    }
    else if (padding == 2){
        base64encoded += "=";
    }
    return base64encoded;
}

long long modPow(long long m, long long e, long long n)
{
    long long result = 1;
    for (long long i = 0; i < e; i++)
    {
        result = (result * m) % n;
    }
    return result;
}

rsareturnval rsaenc(string msg, long long e, long long n){
    vector <int> ascii;
    rsareturnval k;
    for (char c : msg){
        ascii.push_back(int(c));
    }
    vector <long long> encoded;
    for (int charac : ascii){
        long long rsaval = modPow(charac, e, n);
        encoded.push_back(rsaval);
    }
    string rsaencoded = "";
    string rsacharactereds = "";
    for (int i = 0; i < encoded.size(); i++){
        if (i!=(encoded.size()-1)){
            rsaencoded += (to_string(encoded[i])) + '-';
        }
        else{
            rsaencoded += (to_string(encoded[i]));
        }
    }
    k.encodedd = encoded;
    k.numbered = rsaencoded;
    return (k);
}

string base64decode(string msg){
    vector <string> fourchars;
    string decoded;
    for (int i = 0 ; i < msg.size() ; i+=4){
        fourchars.push_back(msg.substr(i,4));
    } 
    
    for (string gp : fourchars){
        string bitarray = "";
        for (char c : gp){
            if (c=='='){
                bitarray+="000000";
            }
            else{
                bitarray+= atob(base64table.find(c)).substr(2,6);
            }
        }
        string eightbit = "";
        vector <int> eightbitarray;
        for (int i = 1; i <= bitarray.size(); i++){
            eightbit+=bitarray[i-1];
            if (i%8 == 0){
                eightbitarray.push_back(btoa(eightbit,8));
                eightbit = "";
            }
        }
        for (int dec : eightbitarray){
            decoded+= char(dec);
        }
    }
    return decoded;
}

string rsadecode(string msg, long long int d, long long int n){
    vector <int> nums;
    string decrypted;
    int i = 0;
    int flag = 0;
    while (true){
        size_t h = msg.find('-', i);
        int len = 0;
        string x = "";
        if (h != string::npos){
            len = h - i;
            x = msg.substr(i, len);
        }
        else{
            flag = 1;
            x = msg;
        }        
        if (flag == 0)
        {
            nums.push_back(stoi(x));
            msg.erase(i, len+1);
        }
        else{
            nums.push_back(stoi(x));
            break;
        }
    }
    for (int dec : nums){
        decrypted += char(modPow(dec,d,n));
    }
    return decrypted;
}



int main(){
    string msg;
    string functions;
    long long e,n;
    cout << "Input message, e and n: " << endl;
    cin >> msg >> e >> n;
    rsareturnval encrypted = rsaenc(msg,e,n);
    cout << "rsa encrypted: " << encrypted.numbered << endl;
    string encoded = base64(encrypted.numbered);
    cout << "base64 encoded: " << encoded << endl;
    string decoded = base64decode(encoded);
    cout << "base 64 decoded: " << decoded << endl;
    long long d;
    cout << "enter d: ";
    cin >> d;
    string decrypted = rsadecode(decoded,d,n);
    cout << "rsa decrypted: " << decrypted;
    return 0;
}