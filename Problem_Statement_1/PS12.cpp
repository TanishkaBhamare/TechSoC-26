//
// Created by TANISHKA on 27-08-2026.
//
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << "Enter Mode:\n1-->Toroidal\n2-->Classify\n3-->Metrics" << std::endl;
    int mode;
    std::cin >> mode;

    std::cout << "Enter Number of Rows\n";
    int r; //no. of rows
    std::cin >> r;
    std::cout << "Enter Number of Columns\n";
    int c; //no. of columns
    std::cin >> c;

    int g; //no. of Generations
    int bw=0;  //bounding width
    int bh=0;  //bounding height
    double sumr=0;  //sum of alive row no.
    double sumc=0;  //sum of alive col no.
    int period = 1;


    int counter = 0; //to count no. of alive cells
    int ip = 0; //Initial Population
    std::vector<std::string> arr; //vector to store row strings
    std::string row;
    for (int i = 0; i < r; i++) {
        std::cout << "Enter Row " << i + 1 << ": ";
        std::cin >> row;
        arr.push_back(row);
        if (arr[i].length() != c) {
            std::cout << "ERROR!";
            return 0;
        } else {
            for (int j = 0; j < c; j++) {
                if (arr[i].at(j) == '#') {
                    ip++;
                }
            }
        }
    }

    std::vector<std::string> newarr;
    std::vector<std::string> initialarr = arr;

    switch (mode) {
        case 1:
            std::cout << "Enter Number of Generations\n";
            std::cin >> g;
            std::cout << "Mode: Toroidal" << std::endl;
            std::cout << "Initial Population: " << ip << std::endl;
            if (g == 0) {
                for (int i = 0; i < r; i++) {
                    std::cout << arr[i] << std::endl;
                }
            }

            for (int k = 1; k <= g; k++) {
                //Calculating Final Population
                newarr = arr;
                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        if (i == 0) {
                            if (j == 0) {
                                if (arr[r - 1].at(0) == '#')
                                    counter++;
                                if (arr[r - 1].at(1) == '#')
                                    counter++;
                                if (arr[0].at(c - 1) == '#')
                                    counter++;
                                if (arr[1].at(c - 1) == '#')
                                    counter++;
                                if (arr[r - 1].at(c - 1) == '#')
                                    counter++;
                            }
                            if (j == c - 1) {
                                if (arr[0].at(0) == '#')
                                    counter++;
                                if (arr[1].at(0) == '#')
                                    counter++;
                                if (arr[r - 1].at(0) == '#')
                                    counter++;
                                if (arr[r - 1].at(c - 2) == '#')
                                    counter++;
                                if (arr[r - 1].at(c - 1) == '#')
                                    counter++;
                            }
                            if (j > 0 && j < c - 1) {
                                if (arr[r - 1].at(j - 1) == '#')
                                    counter++;
                                if (arr[r - 1].at(j) == '#')
                                    counter++;
                                if (arr[r - 1].at(j + 1) == '#')
                                    counter++;
                            }
                        }

                        if (i > 0 && i < r - 1) {
                            if (j == 0) {
                                if (arr[i - 1].at(c - 1) == '#')
                                    counter++;
                                if (arr[i].at(c - 1) == '#')
                                    counter++;
                                if (arr[i + 1].at(c - 1) == '#')
                                    counter++;
                            }
                            if (j == c - 1) {
                                if (arr[i - 1].at(0) == '#')
                                    counter++;
                                if (arr[i].at(0) == '#')
                                    counter++;
                                if (arr[i + 1].at(0) == '#')
                                    counter++;
                            }
                        }

                        if (i == r - 1) {
                            if (j == 0) {
                                if (arr[0].at(0) == '#')
                                    counter++;
                                if (arr[0].at(1) == '#')
                                    counter++;
                                if (arr[0].at(c - 1) == '#')
                                    counter++;
                                if (arr[r - 2].at(c - 1) == '#')
                                    counter++;
                                if (arr[r - 1].at(c - 1) == '#')
                                    counter++;
                            }
                            if (j == c - 1) {
                                if (arr[0].at(0) == '#')
                                    counter++;
                                if (arr[0].at(c - 2) == '#')
                                    counter++;
                                if (arr[0].at(c - 1) == '#')
                                    counter++;
                                if (arr[r - 2].at(0) == '#')
                                    counter++;
                                if (arr[r - 1].at(0) == '#')
                                    counter++;
                            }
                            if (j > 0 && j < c - 1) {
                                if (arr[0].at(j - 1) == '#')
                                    counter++;
                                if (arr[0].at(j) == '#')
                                    counter++;
                                if (arr[0].at(j + 1) == '#')
                                    counter++;
                            }
                        }


                        if (j < c - 1 && arr[i].at(j + 1) == '#') //right side of cell
                            counter++;
                        if (j > 0 && arr[i].at(j - 1) == '#') //left side of cell
                            counter++;
                        if (i < r - 1 && arr[i + 1].at(j) == '#') //below cell
                            counter++;
                        if (i > 0 && arr[i - 1].at(j) == '#') //above cell
                            counter++;
                        if (j < c - 1 && i < r - 1 && arr[i + 1].at(j + 1) == '#') //down right diag
                            counter++;
                        if (i < r - 1 && j > 0 && arr[i + 1].at(j - 1) == '#') //up right diag
                            counter++;
                        if (i > 0 && j > 0 && arr[i - 1].at(j - 1) == '#') //down left diag
                            counter++;
                        if (i > 0 && j < c - 1 && arr[i - 1].at(j + 1) == '#') //up left diag
                            counter++;

                        if (counter == 0 || counter == 1 || counter > 3 && arr[i].at(j) == '#') {
                            newarr[i].at(j) = '.';
                        }

                        if (arr[i].at(j) == '#' && counter == 2 || counter == 3) {
                            newarr[i].at(j) = '#';
                        }
                        if (arr[i].at(j) == '.' && counter == 3) {
                            newarr[i].at(j) = '#';
                        }
                        counter = 0;
                    }
                }

                int newpop = 0; //population of new grid
                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        if (newarr[i].at(j) == '#') {
                            newpop++;
                        }
                    }
                }

                if (k == g) {
                    std::cout << "Final Population: " << newpop << std::endl;
                }
                arr.clear();
                arr = newarr;
                newarr.clear();
            }

            std::cout << "Final Grid: \n";
            for (int i = 0; i < r; i++) {
                std::cout << newarr[i] << std::endl;
            }
            break;

        case 2:
            std::cout << "Mode: Classifier\n";
            std::cout << "Enter k value: " << std::endl;
            int k;
            std::cin >> k;

            if (k == 1) {
                std::cout << "Classification: Active\n";
                std::cout << "Reason: No repeat or extinction detected within K = 1 steps\n";
                std::cout << "Final Population: " << ip << std::endl;
            }
            while (k > 1 && period <= k) {
                int counter = 0; //to count no. of alive cells

                //Calculating Final Population
                newarr = arr;
                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        if (j < c - 1 && arr[i].at(j + 1) == '#') //right side of cell
                            counter++;
                        if (j > 0 && arr[i].at(j - 1) == '#') //left side of cell
                            counter++;
                        if (i < r - 1 && arr[i + 1].at(j) == '#') //below cell
                            counter++;
                        if (i > 0 && arr[i - 1].at(j) == '#') //above cell
                            counter++;
                        if (j < c - 1 && i < r - 1 && arr[i + 1].at(j + 1) == '#') //down right diag
                            counter++;
                        if (i < r - 1 && j > 0 && arr[i + 1].at(j - 1) == '#') //up right diag
                            counter++;
                        if (i > 0 && j > 0 && arr[i - 1].at(j - 1) == '#') //down left diag
                            counter++;
                        if (i > 0 && j < c - 1 && arr[i - 1].at(j + 1) == '#') //up left diag
                            counter++;

                        if (counter == 0 || counter == 1 || counter > 3 && arr[i].at(j) == '#') {
                            newarr[i].at(j) = '.';
                        }

                        if (arr[i].at(j) == '#' && counter == 2 || counter == 3) {
                            newarr[i].at(j) = '#';
                        }
                        if (arr[i].at(j) == '.' && counter == 3) {
                            newarr[i].at(j) = '#';
                        }
                        counter = 0;
                    }
                }

                int newpop = 0; //population of new grid
                for (int i = 0; i < r; i++) {
                    for (int j = 0; j < c; j++) {
                        if (newarr[i].at(j) == '#') {
                            newpop++;
                        }
                    }
                }
                if (newpop == 0) {
                    std::cout << "Classification: Extinct\nExtinction Step: " << period<<std::endl;
                    std::cout << "Final Population: " << newpop << std::endl;
                    break;
                }
                if (initialarr == newarr) {
                    if (period == 1) {
                        std::cout << "Classification: Still Life\nStable at Step: 0\nPeriod: 1\n";
                        std::cout << "Final Population: " << newpop << std::endl;
                        break;
                    }
                    if (period == 2) {
                        std::cout << "Classification: Oscillator\nPeriod: 2\nFirst Repeat Step: 2(Matches Step 0)\n";
                        std::cout << "Final Population: " << newpop << std::endl;
                        break;
                    }
                }
                if (initialarr != newarr && period == k) {
                    std::cout << "Classification: Active";
                    std::cout << "Final Population at end of " << k << " Generations: " << newpop << std::endl;
                    break;
                }
                arr.clear();
                arr = newarr;
                newarr.clear();
                period++;
            }
            break;

        case 3:
            std::cout<<"Live Cells: "<<ip<<std::endl;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (arr[i].at(j) == '#') {
                        sumr+=i;
                        sumc+=j;
                        if (j>=bw) {
                            bw=j;
                        }
                        if (i>=bh) {
                            bh=i;
                        }
                        counter++;
                    }
                }
            }
            std::cout<<"Bounding Box: "<<bw+1<<" x "<<bh+1<<" (Rows 0-"<<bw<<", Cols 0-"<<bh<<")"<<std::endl;
            if (ip>0) {
                std::cout<<"Centre of Mass: ("<<sumr/ip<<", "<<sumc/ip<<")"<<std::endl;
            }
            if (ip==0) {
                std::cout<<"Centre of Mass: N/A";
            }
            break;
    }
}
