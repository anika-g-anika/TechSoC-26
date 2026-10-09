#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <random>
using namespace std;
float multiplier;
bool iscrit;
bool someone_fainted = false;
void checkformultiplier(bender a, bender d, bool iscrit, float &multiplier)
{
    vector<vector<string>> elemlist = {{"water", "fire"}, {"fire", "air"}, {"air", "earth"}, {"earth", "water"}};
    for (int i = 0; i < 4; i++)
    {
        if (a.element == elemlist[i][0] && d.element == elemlist[i][1])
        {
            multiplier = 2;
        }
        else if (a.element == elemlist[i][1] && d.element == elemlist[i][0])
        {
            multiplier = 0.5;
        }
        else
        {
            multiplier = 1;
        }
    }
    if (iscrit)
    {
        multiplier *= 2;
    }
}
class bender{
    public:
    string name, element;
    int hp, attack, defense, speed;
    vector<tuple<string, int>> moves;
    int hpog;
    

public:
    void dispstat(bender n)
    {
        cout << n.name << '(' << n.element << "): " << n.hp << '/' << n.hpog << ", Attack: " << n.attack << ", Defense: " << n.defense << ", Speed: " << n.speed << endl;
        cout << "Moves: ";
        for (tuple<string, int> &move : n.moves)
        {
            cout << get<0>(move) << '(' << get<1>(move) << "), ";
        }
        cout << endl;
    }

public:
    void attackchar(bender &attacker, bender &defender, int index)
    {
        int damage = (round(static_cast<double>(attack) * (get<1>(moves[index])) / defender.defense))*multiplier;
        checkformultiplier(attacker,defender, iscrit, multiplier);
        cout << defender.name << " took " << damage << " damage!" << endl;
        defender.hp -= damage;
        if (defender.hp < 0)
        {
            defender.hp = 0;
        }
        cout << "\n";
        dispstat(defender);
    }

public:
    void checkiffainted(bender defender)
    {
        if (defender.hp == 0)
        {
            cout << defender.name << " has fainted! " << endl;
            someone_fainted=true;
        }
        else
        {
            cout << defender.name << " has not fainted! " << endl;
            someone_fainted=false;
        }
    }

public:
    void setattributes(string n, string e, int h, int a, int d, int s, vector<tuple<string, int>> m)
    {
        name = n;
        element = e;
        hp = h;
        attack = a;
        defense = d;
        speed = s;
        moves = m;
        hpog = hp;
    }
};

class duel{
    public:
        bender attacker, defender;
        int moveindex;
        float critchance = 0.10;       
        void critcheck(float critchance, bool & iscrit){
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<int> distrib(0,1);
            float rand=distrib(gen);
            iscrit = (rand < critchance);
        }
        
        void choose(bender char1, bender char2){
            if (char1.speed >= char2.speed){
                attacker = char1;
                defender = char2;
            }
            else if (char1.speed<=char2.speed){
                attacker = char2;
                defender = char1;
            }
            else{
                vector < bender > list = {char1,char2};
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> distrib(0, 1);                
                int index = distrib(gen);
                attacker = list[index];
                swap(list[index],list.back());
                list.pop_back();
                defender = list [0];
            }
        }
        void turn(bender attacker, bender defender){
            cout << attacker.name << " goes first" << endl;
            attacker.dispstat(attacker);
            cout << "Index of move you want: ";
            cin >> moveindex;
            attacker.attackchar(attacker, defender, moveindex);
        }
};

void input(bender &character)
{
    string n, e;
    int h, a, d, s;
    vector<tuple<string, int>> m;
    cout << " Bender Creation: " << endl;
    std::cout << "- name: ";
    std::cin >> n;

    std::cout << "- element (\"Water\", \"Fire\", \"Earth\", or \"Air\"): ";
    std::cin >> e;

    std::cout << "- hp (1-200): ";
    std::cin >> h;

    std::cout << "- attack (1-100): ";
    std::cin >> a;

    std::cout << "- defense (1-100): ";
    std::cin >> d;

    std::cout << "- speed (1-100): ";
    std::cin >> s;

    cout << "- moves: " << endl;
    for (int i = 0; i < 4; i++)
    {
        string n;
        int p;
        cout << "move name: ";
        cin >> n;
        cout << "attack power: ";
        cin >> p;
        tuple<string, int> move(n, p);
        m.push_back(move);
    }
    character.setattributes(n, e, h, a, d, s, m);
}

int main()
{
    bender character1;
    input(character1);
    bender character2;
    input(character2);
    
}
