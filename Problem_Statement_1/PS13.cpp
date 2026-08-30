//
// Created by TANISHKA on 30-08-2026.
//
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
int main () {
    std::cout<<"Enter Number of Rows\n";
    int r;   //no. of rows
    std::cin>>r;
    std::cout<<"Enter Number of Columns\n";
    int c;   //no. of columns
    std::cin>>c;
    std::cout<<"Enter Number of Generations\n";
    int g;   //no. of Generations
    std::cin>>g;
    int ip=0;  //Initial Population
    int peakpop=ip;  //Storing peak Population
    std::vector<std::string> arr; //vector to store row strings
    std::string row;
    for (int i = 0; i<r;i++) {
        std::cout<<"Enter Row "<<i+1<<": ";
        std::cin>>row;
        arr.push_back(row);
        if (arr[i].length()!=c) {
            std::cout<<"ERROR!";
            return 0;
        }
        else {
            for(int j=0;j<c;j++) {
                if (arr[i].at(j)=='#') {
                    ip++;
                }
            }
        }
    }
    std::cout<<"Initial Population: "<<ip<<std::endl;
    if (g==0) {
        for (int i = 0; i<r;i++) {
            std::cout<<arr[i]<<std::endl;
        }
    }
    else if (g>0) {
        int counter=0;   //to count no. of alive cells
        std::vector<std::string> newarr;
        for (int k=1;k<=g;k++) {
            //Calculating Final Population
            newarr=arr;
            for(int i=0;i<r;i++) {
                for(int j=0;j<c;j++) {
                    if (j<c-1 && arr[i].at(j+1)=='#')  //right side of cell
                        counter++;
                    if (j>0 && arr[i].at(j-1)=='#')  //left side of cell
                        counter++;
                    if (i<r-1 && arr[i+1].at(j)=='#')   //below cell
                        counter++;
                    if (i>0 && arr[i-1].at(j)=='#')   //above cell
                        counter++;
                    if (j<c-1 && i<r-1 && arr[i+1].at(j+1)=='#')  //down right diag
                        counter++;
                    if (i<r-1 && j>0 && arr[i+1].at(j-1)=='#')   //up right diag
                        counter++;
                    if (i>0 && j>0 && arr[i-1].at(j-1)=='#')   //down left diag
                        counter++;
                    if (i>0 && j<c-1 && arr[i-1].at(j+1)=='#')   //up left diag
                        counter++;

                    if (counter==0 || counter==1 || counter>3 && arr[i].at(j)=='#') {
                        newarr[i].at(j)='.';
                    }

                    if (arr[i].at(j)=='#' && counter==2 || counter==3) {
                        newarr[i].at(j)='#';
                    }
                    if ( arr[i].at(j)=='.' && counter==3) {
                        newarr[i].at(j)='#';
                    }
                    counter=0;
                }
            }

            for (int i = 0; i<r;i++) {
                    std::cout<<newarr[i]<<std::endl;
            }
            std::cout<<"\n\n";
            arr.clear();
            arr=newarr;
            newarr.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::system("clear");
        }
    }
}