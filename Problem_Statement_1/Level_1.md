#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct base{
    int r,c,g;
};
base input(){
    int r,c,g;
    cout << "rows (>=1): ";
    cin >> r;
    cout << "columns(<=100): ";
    cin >> c;
    cout << "generations(0 to 1000): ";
    cin >> g;
    return {r,c,g};
}

void createarray(vector < vector <int>> & mat, int r, int c){
    for (int i=0; i < r; i++ ){
        string line;
        cin >> line;
        int j = 0;
        for (char io: line){
            if (io=='.'){
                mat [i][j] = 0;
            }
            else if (io == '#'){
                mat [i][j] = 1;
            }
            j++;
        }
    }
}
//
void padding(vector<vector<int>> &mat, int &r, int &c){
    for (vector <int> & row: mat){
        row.insert(row.begin(),0);
        row.push_back(0);
    }
    c+=2;
    vector<int> zerorow(c,0);
    mat.insert(mat.begin(),zerorow);
    mat.push_back(zerorow);
    r+=2;
}

void updatevalue(vector<vector<int>> &main, int i, int j, int con){
    if (main[i][j]==1){
        if (con < 2)
        {
            main[i][j] = 0;
        }
        else if (con > 3)
        {
            main[i][j] = 0;
        }
    }
    else if (main[i][j]==0){
        if (con == 3){
            main[i][j] = 1;
        }
    }
   
}

int track(vector<vector<int>> &main){
    int tc=0;
    for (vector<int> row : main){
        for (int ele:row){
            if (ele == 1){
                tc += 1;
            }
        }
    }
return tc;
}

void check(const vector<vector<int>> &buf, vector<vector<int>> &main, int r, int c, vector <int> &treck)
{
    for (int i = 1; i < r-1 ; i++){
        for (int j = 1; j < c - 1; j++)
        {
            int count = 0;
            int k = i - 1;
            for (k; k <= i + 1; k++)
            {
                int l = j - 1;
                for (l; l <= j + 1; l++)
                {
                    if (k == i && l == j)
                    {
                        continue;
                    }
                    else
                    {
                        if (buf[k][l] == 1)
                        {
                            count++;
                        }
                    }
                }
            }
            updatevalue(main, i, j, count);
        }
    }
    int trackin = track(main);
    treck.push_back(trackin);
}

void printfinal(vector<vector<int>>&main, int r, int c){
    for (int i = 1; i<r-1; i++ ){
        for (int j = 1; j< c-1; j++){
            int val = main [i] [j];
            if (val==0){
                cout<<'.';
            }
            else if (val==1){
                cout << '#';
            }
        }
        cout << endl;
    }
}

int main(){
    auto [r,c,g]=input();
    vector < vector <int> > mat(r, vector <int> (c,0));
    createarray(mat,r,c);
    padding (mat, r, c);
    vector <int> population;
    for (int i = 0; i<g; i++){
        vector<vector<int>> matbuf = mat;
        check(matbuf,mat,r,c,population);
    }
    cout << "\n" << "Final matrix is:" << endl;
    printfinal(mat, r, c);
    int trackin = track(mat);
    population.push_back(trackin);
    int in= population[0];
    int fin = population.back();
    int max = 0;
    for (int pop: population){
        if (pop>max){
            max= pop;
        }
    }
    cout << "Initial population is : "<< in << endl;
    cout << "Final population is : " << fin << endl;
    cout << "Maximum population is : " << max;
return 0;
}
