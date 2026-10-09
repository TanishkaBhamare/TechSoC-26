//
// Created by TANISHKA on 29-09-2026.
//
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
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
    };
    Move moves[4];

    Bender():hp(0),attack(0),defense(0),speed(0), moves{} {}

    Bender(std::string name1, std::string element1, unsigned int hp1, unsigned int attack1, unsigned int defence1, unsigned int speed1, Move moves1[4]) {
        name = name1;
        element = element1;
        hp = hp1;
        attack = attack1;
        defense = defence1;
        speed = speed1;
        for (int i = 0; i < 4; i++) {
            moves[i] = moves1[i];
        }
    }

    void display_stats() {
        std::cout << name <<"("<<element<<") - HP: "<< hp << ", Attack: "<<attack<<", Defense: "<<defense<<", Speed: "<<speed<<std::endl;
        std::cout<<"Moves: "<<moves[0].mname<<"("<<moves[0].power<<"), ";
        std::cout<<"Moves: "<<moves[1].mname<<"("<<moves[1].power<<"), ";
        std::cout<<"Moves: "<<moves[2].mname<<"("<<moves[2].power<<"), ";
        std::cout<<"Moves: "<<moves[3].mname<<"("<<moves[3].power<<")"<<std::endl;
    }

    double attackenemy(Bender& defender, int move) {
        int damage = std::round(static_cast<double>(attack * moves[move].power) / defender.defense);
        defender.hp=defender.hp-damage;
        return damage;
    }

    bool is_fainted() {
        return hp <= 0;
    }

};


int main() {
    Bender::Move MiraMove[4]={
        {"Water Whip", 35},
        {"Tide Push", 25},
        {"Mist Veil", 0},
        {"Tidal Wave", 60}
    };

    Bender::Move KaelMove[4]={
        {"Ember Slash",40},
        {"Quick Jab",30},
        {"Focus",0},
        {"Flame Surge",70}
    };

    Bender::Move ZephyrMove[4]={
        {"Gust",0},
        {"Wind Slap",12},
        {"Tumble",12},
        {"Cyclone",22}
    };

    Bender::Move DoranMove[4]={
        {"Boulder Throw",75},
        {"Rock Fist",42},
        {"Tremor",48},
        {"Mountain Crush",85}
    };

    Bender attacker;
    Bender defender;
    std::vector<Bender> Players;
    Players.push_back({"Kael", "Fire", 100, 58, 38, 88,KaelMove});
    Players.push_back({"Mira", "Water", 92, 50, 45, 60,MiraMove});
    Players.push_back({"Zephyr", "Air", 28, 12, 50, 95,ZephyrMove});
    Players.push_back({"Doran", "Earth", 145, 80, 75, 40,DoranMove});

    std::cout<<"Players:\n1->Kael\n2->Mira\n3->Zephyr\n4->Doran\n Enter Respective Number to Choose Players"<<std::endl;
    std::cout<<"Enter Number to choose PLAYER1:";
    int player1;
    std::cin>>player1;
    std::cout<<"Enter Number to choose PLAYER2:";
    int player2;
    std::cin>>player2;
    if (player1<1 || player2<1 || player1>4 || player2>4 || player1==player2) {
        std::cout<<"ERROR! Players must be between 1 and 4 and also Not the Same Number"<<std::endl;
        return 1;
    }
    if (Players[player1-1].speed > Players[player2-1].speed) {
        attacker = Players[player1-1];
        defender = Players[player2-1];
    }
    else {
        attacker = Players[player2-1];
        defender = Players[player1-1];
    }
    attacker.display_stats();
    defender.display_stats();

    std::cout<<"Moves for "<<attacker.name<<std::endl;
    for (int i=0;i<4;i++) {
        std::cout<<i+1<<": "<<attacker.moves[i].mname<<std::endl;
    }
    std::cout<<"Enter Number to choose Move for Attacker : ";
    int move;
    std::cin>>move;

    std::cout<<attacker.name<<" used "<<attacker.moves[move-1].mname<<std::endl;
    std::cout<<defender.name<<" took "<<attacker.attackenemy(defender, move-1)<<" damage! "<<std::endl;

    if (defender.is_fainted()) {
        defender.hp=0;
    }
    defender.display_stats();
    std::cout<<std::boolalpha;
    std::cout<<defender.name<<" fainted: "<<defender.is_fainted()<<std::endl;
}