//
// Created by TANISHKA on 29-09-2026.
//
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

//I did not Make Duel class as didn't feel a need to make so and I couldn't understand the use of it


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

    Bender(std::string name, std::string element, unsigned int hp, unsigned int attack, unsigned int defence, unsigned int speed, Move moves[4]) {
        this->name = name;
        this->element = element;
        this->hp = hp;
        this->attack = attack;
        this->defense = defence;
        this->speed = speed;
        for (int i = 0; i < 4; i++) {
            this->moves[i] = moves[i];
        }
    }

    void display_stats(std::vector<int> iniHP, int i) {
        std::cout << name <<"("<<element<<", HP: "<< hp << "/"<<iniHP[i]<<std::endl;
    }

    double critical_chance=0.10;
    double critical_multiplier=1.0;
    bool isCriticalHit(){ //I Googled this.
        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::bernoulli_distribution dis(critical_chance);

        return dis(gen);
    }
    double attackenemy(Bender& attacker, Bender& defender, int move, int &ch, int &seh) {
        double base_damage = std::round(static_cast<double>(attack * moves[move].power) / defender.defense);
        double type_multiplier=1.0;
        if ((attacker.element == "Water" && defender.element == "Fire") || (attacker.element=="Fire" && defender.element == "Air") || (attacker.element=="Air" && defender.element == "Earth")
            || (attacker.element=="Earth" && defender.element == "Water")) {
            type_multiplier=2.0;
            std::cout<<"Super Effective! "<<std::endl;
            seh++;
        }
        else if (attacker.element=="Fire" && defender.element == "Water" || attacker.element=="Air" && defender.element == "Fire" || attacker.element=="Earth" && defender.element == "Air"
            || attacker.element=="Water" && defender.element == "Earth") {
            type_multiplier=0.5;
            std::cout<<"Not Very Effective... "<<std::endl;
        }


        if (isCriticalHit()) {
            critical_multiplier=2.0;
            std::cout<<"Critical Hit! "<<std::endl;
            ch++;
        }
        double final_damage= base_damage * type_multiplier * critical_multiplier;
        final_damage= std::max(1.0,std::round(final_damage));
        defender.hp=defender.hp-final_damage;
        return final_damage;
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

    Bender::Move NadiaMove[4]={
        {"Wave Crash",35},
        {"Splash Kick",25},
        {"Guard",0},
        {"Riptide",50}
    };

    Bender::Move TalonMove[4]={
        {"Gale Strike",38},
        {"Wind Cutter",28},
        {"Updraft",0},
        {"Cyclone Blast", 48}
    };

    Bender current_bender;
    Bender target_bender;
    std::vector<Bender> Players;
    Players.push_back({"Kael", "Fire", 100, 58, 38, 88,KaelMove});
    Players.push_back({"Mira", "Water", 92, 50, 45, 60,MiraMove});
    Players.push_back({"Zephyr", "Air", 28, 12, 50, 95,ZephyrMove});
    Players.push_back({"Doran", "Earth", 145, 80, 75, 40,DoranMove});
    Players.push_back({"Nadia", "Water", 85, 48, 60, 72,NadiaMove});
    Players.push_back({"Talon", "Air", 90, 52, 55, 72,TalonMove});

    std::vector<int> iniHP;
    iniHP.push_back(100);
    iniHP.push_back(92);
    iniHP.push_back(28);
    iniHP.push_back(145);
    iniHP.push_back(85);
    iniHP.push_back(90);

    std::cout<<"Players:\n1->Kael\n2->Mira\n3->Zephyr\n4->Doran\n5->Nadia\n6->Talon Enter Respective Number to Choose Players"<<std::endl;
    std::cout<<"Enter Number to choose PLAYER1:";
    int player1;
    std::cin>>player1;
    std::cout<<"Enter Number to choose PLAYER2:";
    int player2;
    std::cin>>player2;
    if (player1<1 || player2<1 || player1>6 || player2>6 || player1==player2) {
        std::cout<<"ERROR! Players must be between 1 and 6 and also Not the Same Number"<<std::endl;
        return 1;
    }
    int n1;
    int n2;


    if (Players[player1-1].speed > Players[player2-1].speed) {
        current_bender = Players[player1-1];
        target_bender = Players[player2-1];
    }
    else if (Players[player1-1].speed < Players[player2-1].speed) {
        current_bender = Players[player2-1];
        target_bender = Players[player1-1];
    }
    else if (Players[player1-1].speed == Players[player2-1].speed) {
        std::random_device rd;  //I googled this idk if other function exists.
        std::mt19937 gen(rd());
        std::bernoulli_distribution coin_flip(0.5);
        current_bender = coin_flip(gen)?Players[player1-1]:Players[player2-1];

        std::cout<<"===DUEL BEGINS!==="<<std::endl;

        if (current_bender.name == Players[player1-1].name) {
            target_bender = Players[player2-1];
            n1=player1-1;
            n2=player2-1;
        }
        else {
            target_bender = Players[player1-1];
            n1=player2-1;
            n2=player1-1;
        }
        current_bender.display_stats(iniHP, n1);
        std::cout<<" VS ";
        target_bender.display_stats(iniHP, n2);
        std::cout<<std::endl;
    }


    std::cout<<"Moves for "<<current_bender.name<<std::endl;
    for (int i=0;i<4;i++) {
        std::cout<<i+1<<": "<<current_bender.moves[i].mname<<std::endl;
    }

    std::cout<<"Moves for "<<target_bender.name<<std::endl;
    for (int i=0;i<4;i++) {
        std::cout<<i+1<<": "<<target_bender.moves[i].mname<<std::endl;
    }

    int ch=0;
    int seh=0;
    int turn=1;
    while (current_bender.hp>=0 && target_bender.hp>=0) {
        std::cout<<"Turn "<<turn<<": ";
        if (Players[player1-1].speed == Players[player2-1].speed && turn==1) {
            std::cout<<"Speed Tie! "<<current_bender.name<<" Goes First! (Speed: "<<current_bender.speed<<" VS "<<target_bender.speed<<std::endl;
        }
        else if (turn%2==0) {
            std::cout<<current_bender.name<<" Strikes Back!"<<std::endl;
        }
        else {
            std::cout<<current_bender.name<<" Goes First!!"<<std::endl;
        }
        std::cout<<"Enter Number to choose Move for Attacker : ";
        int move;
        std::cin>>move;
        std::cout<<current_bender.name<<" used "<<current_bender.moves[move-1].mname<<std::endl;
        double damage = current_bender.attackenemy(current_bender,target_bender, move-1, ch, seh);

        std::cout<<target_bender.name<<" took "<< damage <<" damage! "<<std::endl;
        if (target_bender.hp<=0) {
            std::cout<<target_bender.name<<" HP: 0/"<<iniHP[n2]<<std::endl;
            std::cout<<target_bender.name<<" Fainted! \n🏆 "<<current_bender.name<<" Wins The Duel! "<<std::endl;
            break;
        }
        std::cout<<target_bender.name<<" HP: "<<target_bender.hp<<"/"<<iniHP[n2]<<std::endl;
        std::swap(current_bender, target_bender);
        turn++;
        std::cout<<std::endl<<std::endl;
    }

    std::cout<<"\n\nDuel Summary:"<<std::endl;
    std::cout<<"-Winner: "<<current_bender.name<<std::endl;
    std::cout<<"-Turns: "<<turn<<std::endl;
    std::cout<<"-Critical Hits: "<<ch<<std::endl;
    std::cout<<"-Super Effective Hits: "<<seh<<std::endl;

}