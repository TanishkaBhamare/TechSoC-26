//
// Created by TANISHKA on 18-08-2026.
//
#include <iostream>
using namespace std;
int main() {
    cout<<"Enter Storage Capacity: ";
    int c;  // capacity
    cin>>c;
    cout<<"Enter Number of Containers: ";
    int n;  //number of Containers
    cin>>n;
    double total=0.0;  //storing total shipment weight
    double hc;  //hc=weight of heaviest container
    double lc;  //lc=weight of lightest container

    for (int i = 0; i < n; i++) {
        cout<<"Enter Weight of Container "<<i+1<<": ";
        double w;
        cin>>w;
        total+=w;

        if (i==0) {
            lc=w;
            hc=w;
        }

        if (w>=hc) {
            hc=w;
        }
        else if (w<=lc) {
            lc=w;
        }
    }

    double avg=total/n; //Storing average shipment weight

    cout<<"Total Shipment Weight: "<<total<<endl;
    cout<<"Average Shipment Weight: "<<avg<<endl;
    cout<<"Heaviest Container: "<<hc<<endl;
    cout<<"Lightest Container: "<<lc<<endl;

    if(total>=200) {
        cout<<"Classification:Heavy"<<endl;
    }
    else {
        cout<<"Classification:Light"<<endl;
    }

    cout<<"Port Capacity: "<<c<<endl;

    if (total<=c) {
        cout<<"Status: Shipment can be unloaded "<<endl;
    }
    else {
        cout<<"Status: Shipment exceeds port capacity "<<endl;
    }

}