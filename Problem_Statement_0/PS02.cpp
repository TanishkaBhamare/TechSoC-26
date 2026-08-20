//
// Created by TANISHKA on 18-08-2026.
//
#include <iostream>
# include <fstream>
using namespace std;

void sorting(double arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (arr[j]>arr[j+1]) {
                swap(arr[j],arr[j+1]);
            }
        }
    }

    cout<<"Conatiners in Sorted Order "<<endl;
    for (int i = 0; i < n; i++) {
        cout<<i+1<<". "<<arr[i]<<endl;
    }
    cout<<endl;
}

void multi() {
    cout<<"Enter Number of Containers: ";
    int n;  //number of Containers
    cin>>n;
    double arr[n];  //array to store weight of each container
    double total=0.0;

    for (int i = 0; i < n; i++) {
        cout<<"Enter Weight of Container "<<i+1<<": ";
        double w;
        cin>>w;
        arr[i]=w;
        total+=w;
    }
    cout<<"Total Shipment Weight: "<<total<<endl;
    if (total>=200) {
        cout<<"Classification:Heavy"<<endl;
    }
    else {
        cout<<"Classification:Light"<<endl;
    }

}

int binarysearch(double arr[],int w,int n) {
    int start=0;
    int end=n-1;
    while (start<=end) {
        int mid = start+(end-start)/2;
        if (w>arr[mid]) {
            start=mid+1;
        }
        else if (w<arr[mid]) {
            end=mid-1;
        }
        else {
           return mid+1;
        }
    }
    return -1;
}

void generateReport(double total,double arr[],int n) {
    cout<<"Do you Want to Save Report? ";
    string c;  //choice
    cin>>c;
    if (c=="yes") {
        ofstream file("shipment_report.txt");
        file<<"Total Shipment Weight: "<<total<<endl;
        file<<"Average Container Weight: "<<total/n<<endl;
        file<<"Heaviest Container Weight: "<<arr[n-1]<<endl;
        file<<"Lightest Container Weight: "<<arr[0]<<endl;
        if (total>=200) {
            file<<"Classification:Heavy"<<endl;
        }
        else {
            file<<"Classification:Light"<<endl;
        }
        file.close();
    }
    cout<<endl;
}

void readReport() {
    ifstream file("containers.txt");
    double total=0.0;
    double hc;
    double lc;
    int n;
    file>>n;
    double arr3[n];
    for (int i=0; i<n; i++) {
        file>>arr3[i];
        total+=arr3[i];
        if (i==0) {
            lc=arr3[i];
            hc=arr3[i];
        }

        if (arr3[i]>=hc) {
            hc=arr3[i];
        }
        else if (arr3[i]<=lc) {
            lc=arr3[i];
        }
    }
    double avg=total/n;
    cout<<"Loaded "<<n<<" containers from containers.txt"<<endl;
    cout<<"Weights: ";
    for (int i=0; i<n; i++) {
        cout<<arr3[i]<<", ";
    }
    cout<<endl;
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
    file.close();
}

int main() {
    cout<<"Enter Number of Containers: ";
    int n;  //number of Containers
    cin>>n;
    double arr[n];  //array to store weight of each container
    double total=0.0;

    for (int i = 0; i < n; i++) {
        cout<<"Enter Weight of Container "<<i+1<<": ";
        double w;
        cin>>w;
        arr[i]=w;
        total+=w;
    }

    //Bubble Sorting
    sorting(arr,n);

    cout<<"Total Shipment Weight: "<<total<<endl;
    if (total>=200) {
        cout<<"Classification:Heavy"<<endl;
    }
    else {
        cout<<"Classification:Light"<<endl;
    }
    cout<<endl;


    cout<<"Container Bar Chart: "<<endl;
    for (int i=0; i<n; i++) {
        cout<<"Conatiner "<<i+1<<"("<<arr[i]<<"): ";
        for (int j=arr[i]; j>0; j-=5) {
            cout<<"*";
        }
        cout<<endl;
    }
    cout<<endl;


    generateReport(total,arr,n);
    readReport();


    //Binary Search
    cout<<"Enter Weight to Find Container: "<<endl;
    double tar;  //Target to find
    cin>>tar;
    if (binarysearch(arr,tar,n)!=-1) {
        cout<<"Container Found! "<<endl;
        cout<<"Container "<<binarysearch(arr,tar,n)<<" has weight "<<tar<<endl;
    }
    else if (binarysearch(arr,tar,n)==-1) {
        cout<<"No Container Found with weight "<<tar<<endl;
    }

    //Kth Heaviest
    cout<<"Enter Number X to find Weight of Xth Heaviest Container: "<<endl;
    int x;
    cin>>x;
    if (x>n) {
        cout<<"Invalid Input: Only "<<n<<" Containers exist."<<endl;
    }
    else if (x<1){
        cout<<"Invalid Input: X MUST be ATLEAST 1 "<<endl;
    }
    else {
        cout<<x<<"th Heaviest Container has Weight: "<<arr[x-1]<<endl;
    }

    //Multi-Ship Processing
    int k=1;  //Number of ships Processed
    string choice;
    cout<<"Continue?";
    cin>>choice;
    while (choice=="yes") {
        multi();
        cout<<"Continue? "<<endl;
        cin>>choice;
        k++;
    }
    cout<<"Total Ships Processed: "<<k<<endl;

}