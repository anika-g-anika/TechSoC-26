#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;
class bender{
    string name, element;
    int hp, attack, defense, speed;
    vector <tuple<string ,int>> moves;
    int hpog;
    public:
    void dispstat(bender n){
        cout << n.name << '(' << n.element << "): " << n.hp << '/' << n.hpog << ", Attack: " << n.attack << ", Defense: " << n.defense << ", Speed: " << n.speed << endl;
        cout << "Moves: ";
        for (tuple < string, int > & move : n.moves){
            cout << get<0> (move) << '(' << get <1> (move) << "), " ; 
        }
        cout << endl;
    }
    
    public:
    void attackchar(bender &defender, int index){
        int damage = round(static_cast<double>(attack) * (get<1>(moves[index])) / defender.defense);
        cout << defender.name << " took " << damage << " damage!" << endl;
        defender.hp-=damage;
        if (defender.hp<0){
            defender.hp = 0;
        }
        cout << "\n" ;
        dispstat(defender);
    }
    public:
    void checkiffainted(bender defender){
        if (defender.hp == 0){
            cout << defender.name << " has fainted! " << endl;
        }
        else {
            cout << defender.name << " has not fainted! " << endl;
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

void input(bender & character){
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

    cout << "- moves: "<< endl;
    for (int i = 0; i< 4; i++){
        string n ;
        int p;
        cout << "move name: ";
        cin >> n;
        cout << "attack power: ";
        cin >> p;
        tuple<string, int> move (n,p);
        m.push_back(move);
    }
    character.setattributes(n,e,h,a,d,s,m);
}

int main(){
    bender character1;
    input(character1);
    bender character2;
    input(character2);
    character1.dispstat(character1);
    character2.dispstat(character2);
    character1.attackchar(character2,0);
    character2.checkiffainted(character2);
    return 0;
}
