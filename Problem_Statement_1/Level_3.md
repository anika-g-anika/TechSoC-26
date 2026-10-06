#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <windows.h>
using namespace std;
struct base
{
    int r, c, g;
};
base input()
{
    int r, c, g;
    cout << "rows (>=1): ";
    cin >> r;
    cout << "columns(<=100): ";
    cin >> c;
    cout << "generations(0 to 1000): ";
    cin >> g;
    return {r, c, g};
}

void classify(const vector<vector<vector<int>>> &images, const vector <int> population){
    vector<vector<vector<int>>> copy = images;
    int i1,i2;
    i1 = 0;
    int flag = 0;
    for (const vector<vector<int>> &stages : images){
        for (int i = 1; i< copy.size(); i++){
            if (stages == copy[i]){
                i2 = i;
                flag = 1;
                break;
            }
        }
        if (flag == 1){
            break;
        }
        else {
            i1++;
        }
    }
    if (flag == 1){
        int step = i2 - i1;
        for (int j = 0; j < population.size(); j++)
        {
            if (population[j] == 0)
            {
                cout << "Classification: Extinct" << endl;
                cout << "Extinction step: " << j;
                return;
            }
        }
        if (step == 1)
        {
            cout << "Classification: Still life" << endl;
            cout << "Stable at step: " << i1 << endl;
            cout << "Period: 1";
        }
        else if (step >= 2){
            cout << "Classification: Oscillator" << endl;
            cout << "Period: " << step << endl;
            cout << "First repeat step: " << i2 << "(matches step " << i1 << ")";
        }
    }
    else {
        cout << "Classification: Active" << endl;
    }
}

void createarray(vector<vector<int>> &mat, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        string line;
        cin >> line;
        int j = 0;
        for (char io : line)
        {
            if (io == '.')
            {
                mat[i][j] = 0;
            }
            else if (io == '#')
            {
                mat[i][j] = 1;
            }
            j++;
        }
    }
}

void updatevalue(vector<vector<int>> &main, int i, int j, int con)
{
    if (main[i][j] == 1)
    {
        if (con < 2)
        {
            main[i][j] = 0;
        }
        else if (con > 3)
        {
            main[i][j] = 0;
        }
    }
    else if (main[i][j] == 0)
    {
        if (con == 3)
        {
            main[i][j] = 1;
        }
    }
}

int track(vector<vector<int>> &main)
{
    int tc = 0;
    for (vector<int> row : main)
    {
        for (int ele : row)
        {
            if (ele == 1)
            {
                tc += 1;
            }
        }
    }
    return tc;
}

void printfinal(vector<vector<int>> &main, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int val = main[i][j];
            if (val == 0)
            {
                cout << '.';
            }
            else if (val == 1)
            {
                cout << '#';
            }
        }
        cout << endl;
    }
}

void check(const vector<vector<int>> &buf, vector<vector<int>> &main, vector<vector<vector<int>>> &images, int r, int c, vector<int> &treck){
    for (int i = 0; i < r ; i++)
    {
        for (int j = 0; j < c ; j++)
        {
            int count = 0;
            int k = i - 1;
            for (k; k <= i + 1; k++){
                int nk = (k+r) %r;  
                int l = j - 1;
                for (l; l <= j + 1; l++)
                {                    
                    int nl = (l+c)%c;
                    if (k == i && l == j)
                    {
                        continue;
                    }
                    else
                    {
                        if (buf[nk][nl] == 1)
                        {
                            count++;
                        }
                    }
                }
            }
            updatevalue(main, i, j, count);
        }
    }
    images.push_back(main);
    system("cls");
    printfinal(main,r,c);
    Sleep(500);
    int trackin = track(main);
    treck.push_back(trackin);
}



void bdd(vector<vector<int>> &main, int r, int c, vector <int> population){
    int rmin, rmax, cmin, cmax;
    rmin = rmax = cmin = cmax = 0;
    int flag = 0;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (main[i][j] !=0){
                rmin = i;
                flag = 1;
                break;
            }
        }
        if (flag == 1){break;}
    }
    for (int i = r-1; i >= 0; i--){
        for (int j = 0; j < c; j++)
        {
            if (main[i][j] != 0)
            {
                rmax = i;
                flag = 2;
                break;
            }
        }
        if (flag == 2){break;}
    }
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if (main[j][i] != 0)
            {
                cmin = i;
                flag = 3;
                break;
            }
        }
        if (flag == 3){break;}
    }
    for (int i = c - 1; i >= 0 ; i--)
    {
        for (int j = 0; j < r; j++)
        {
            if (main[j][i] != 0)
            {
                cmax = i;
                flag = 4;
                break;
            }
        }
        if (flag == 4){break;}
    }
    if (flag == 4){
        cout << "Bounding Box: " << rmax - rmin + 1 << "x" << cmax - cmin + 1 << endl;
    }
    else{
        cout << "Bounding Box: 0 x 0" << endl;
    }
    
}

void com(vector<vector<int>> &main, int r, int c, vector<int> population){
    vector <int> activer;
    vector <int> activec;
    int popf = population.back();
    for (int i = 0; i < r; i++){
        for (int j = 0 ; j < c ; j++){
            if (main[i][j]==1){
                activer.push_back(i);
                activec.push_back(j);
            }
        }
    }
    if (popf == 0){
        cout << "Live cells: 0"<< endl;
        cout << "Center of mass: N/A";
    }
    else {
        int sumr = 0;
        int sumc = 0;
        for (int el : activec){sumc+=el;}
        for (int el : activer){sumr+=el;}
        cout << "Center of mass: " << double(sumr)/popf << ',' << double(sumc)/popf << endl;
    }
}

int main()
{
    auto [r, c, g] = input();
    vector<vector<int>> mat(r, vector<int>(c, 0));
    createarray(mat, r, c);
    vector<int> population;
    int trackin = track(mat);
    population.push_back(trackin);
    vector <vector< vector <int>>> images;
    images.push_back(mat);
    for (int i = 0; i < g; i++)
    {
        vector<vector<int>> matbuf = mat;
        check(matbuf, mat, images, r, c, population);
    }
    cout << "\n"
         << "Final matrix is:" << endl;
    printfinal(mat, r, c);
    int in = population[0];
    int fin = population.back();
    int max = 0;
    for (int pop : population)
    {
        if (pop > max)
        {
            max = pop;
        }
    }
    cout << "Initial population is : " << in << endl;
    cout << "Final population is : " << fin << endl;
    cout << "Maximum population is : " << max << endl;
    classify(images, population);
    bdd(mat,r,c,population);
    com(mat, r, c, population);
    return 0;
}
