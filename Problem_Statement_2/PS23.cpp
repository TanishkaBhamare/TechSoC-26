//
// Created by TANISHKA on 29-09-2026.
//





//I could not complete the code (T-T) also the logic was unclear and how to use AI analysis and damage function 😭
//-->This is incomplete code with a lot of errors below was my attempt 😭😭😭😭





/*Here are My Assumptions/My add on's:
* easy leve=choose any move
*medium level=choose move with highest base damage calculated as in PS21
*hard level=move chosen by AI
*I also added healing effect in bender called:  i assume the healing effect to
*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

class Bender {
public:
    std::string name;
    std::string element;
    int hp;
    unsigned int attack;
    unsigned int defense;
    unsigned int speed;
    struct Move {
        std::string mname;  //movename
        int power;
        std::string status_effect;
        int status_duration;
    };
    Move moves[4];

    Bender():hp(0),attack(0),defense(0),speed(0), moves{} {}

    Bender(std::string name, std::string element, unsigned int hp, unsigned int attack, unsigned int defence, unsigned int speed, Move moves[4]) {
        this->name = name;
        this->element = element;
        this->hp = hp;
        this->attack = attack;
        this->defense = defence;
        this->speed = speed;
        for (int i = 0; i < 4; i++) {
            this->moves[i] = moves[i];
            this->moves[i].status_effect= "none";
            this->moves[i].status_duration= 0;
        }
    }

    void display_stats(std::vector<int> iniHP, int i) {
        std::cout << name <<"("<<element<<", HP: "<< hp << "/"<<iniHP[i]<<")";
    }

    double AI_attack(Bender defender,int move, int &ch, int &seh, int &rh, int &status_duration, std::string difficulty) {
        if (difficulty=="easy") {
            int damage = std::round(static_cast<double>(attack * moves[move].power) / defender.defense);
            defender.hp=defender.hp-damage;
            return damage;
        }
        else if (difficulty=="medium") {

        }
        else if (difficulty=="hard") {

        }
        else {
            std::cout<<"INVALID INPUT"<<std::endl;
        }
    }

    double base_attack(Bender defender, Move move, int &status_duration, std::string status_effect, int iniHP) {
        if (status_duration>0) {
            if (status_effect=="Burn") {
                status_duration--;
                defender.hp=defender.hp-0.1*iniHP;
                return defender.hp;
            }
            else if (status_effect=="Frozen") {
                status_duration--;
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> distrib(0, 1);
                return distrib(gen)*(defender.hp-move.power);
            }
            else if (status_effect=="Buried") {
                status_duration--;
                return defender.hp;
            }
        }
    }
};

class AIDuel {
public:
    void start_tournament(std::vector<Bender> participants, std::string difficulty) {

    }

    Bender start_duel(Bender a, Bender b, std::string difficulty) {

        do {
            if (will_bender_a_attack(a, b)) {
                a.attack(b);
            } else {

            }
        } while (a.hp>0 && b.hp>0);

    }

private:
    static bool will_bender_a_attack(const Bender &attacker, const Bender &defender) {
        return attacker.speed > defender.speed;
    }

};

int main() {
    Bender::Move SableMove[4]={
        {"Arctic Gust", 0, "frozen"},
        {"Wind Blade", 52},
        {"Tailwind", 0},
        {"Cyclone Fang", 58}
    };

    Bender::Move BoranMove[4]={
        {"Rockslide", 55},
        {"Quicksand Trap", 0, "buried"},
        {"Stone Wall", 0},
        {"Seismic Slam", 70}
    };

    Bender::Move IgnisMove[4]={
        {"Inferno Slash", 60},
        {"Flame Dash", 38},
        {"Ember Guard", 0},
        {"Volcanic Burst", 80}
    };

    Bender::Move KestraMove[4]={
        {"Tidal Crush", 65},
        {"Ice Shard", 45},
        {"Mist Shield", 0},
        {"Maelstrom", 85}
    };

    Bender::Move TerrakMove[4]={
        {"Stone Avalanche", 70},
        {"Quake Punch", 48},
        {"Bulwark", 0},
        {"Mountain's Wrath", 88}
    };

    Bender::Move SquallMove[4]={
        {"Thunder Gale", 58},
        {"Razor Wind", 35},
        {"Updraft", 0, "frozen"},
        {"Tempest Strike", 72}
    };

    Bender attacker;
    Bender defender;
    std::vector<Bender> Players;
    Players.push_back({"Sable", "Air", 95, 60, 58, 85,SableMove});
    Players.push_back({"Boran", "Earth", 110, 68, 62, 50,BoranMove});
    Players.push_back({"Ignis", "Fire", 120, 82, 70, 95,IgnisMove});
    Players.push_back({"Kestra", "Water", 128, 78, 85, 68,KestraMove});
    Players.push_back({"Terrak", "Earth", 135, 88, 90, 45,TerrakMove});
    Players.push_back({"Squall", "Air", 105, 65, 55, 100,SquallMove});

    std::vector<int> iniHP;
    iniHP.push_back(95);
    iniHP.push_back(110);
    iniHP.push_back(120);
    iniHP.push_back(128);
    iniHP.push_back(135);
    iniHP.push_back(105);

    std::cout<<"Enter 1 for AI DUEL or 2 for ELEMENTAL ARENA CHAMPIONSHIP";
    int choice;
    std::cin>>choice;

    std::cout<<"Enter difficulty level: "<<std::endl;
    std::string difficulty;
    std::cin>>difficulty;

    std::cout<<"Players:\n1->Kael\n2->Mira\n3->Zephyr\n4->Doran\n Enter Respective Number to Choose Players"<<std::endl;
    int ch=0;
    int seh=0;
    int rh=0;
    int turn=1;
    int se=0;
    int status_duration=0;

    if(choice == 1) {

    }
    else if(choice == 2) {

    }
    else {
        std::cout<<"Invalid choice"<<std::endl;
        return 1;
    }

    std::cout<<"\n\n=== TOURNAMENT STATISTICS ==="<<std::endl;
    std::cout<<"-Winner: "<<attacker.name<<std::endl;
    std::cout<<"-Total Turns: "<<turn<<std::endl;
    std::cout<<"-Critical Hits: "<<ch<<std::endl;
    std::cout<<"-Super Effective Hits: "<<seh<<std::endl;
    std::cout<<"-Status Effect: "<<se<<std::endl;

    return 0;
}