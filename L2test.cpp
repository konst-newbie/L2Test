#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define IMSI 3
#define RXBYTES 9
#define END 1

using namespace std;

int getNumOfUe(string filename){
    int numOfUe = 0;

    ifstream in(filename);
    vector<double> statsArray;
    string line;
    double tmp;

    getline(in, line);
    while(getline(in, line)){
        stringstream lineStream(line);
        
        while(lineStream >> tmp){
            statsArray.push_back(tmp);;
        }
        
        if(statsArray[IMSI] > numOfUe)
            numOfUe = statsArray[IMSI];
        
        statsArray.clear();
    }

    in.close();

    return numOfUe;
}

void calculateThroughput(string filename){
    ifstream in(filename);

    int numOfUe = getNumOfUe(filename);
    double throughput[numOfUe];
    double tmp, start, endTime = 0;
    string line, header;
    vector <double> statsArray;
    
    getline(in, header);
    while(getline(in, line)){
        stringstream lineStream(line);
        
        while(lineStream >> tmp){
            statsArray.push_back(tmp);
        }
        
        throughput[int(statsArray[IMSI] - 1)] += statsArray[RXBYTES];
        endTime = statsArray[END];
        statsArray.clear();
    }

    for (int i =0; i < numOfUe; i++)
    {
        throughput[i] = throughput[i] * 8 / 1024 / 1024 / (endTime - start);
        cout << "Throughput for IMSI = " << i + 1 << " is: " << throughput[i] << " Mbps" << endl;
    }
            
    in.close();

    return;
}

int main(int argc, char* argv[]){
    string name = "scratch/L2Test/L2testStats/UlRlcStats.txt"; //comment this if you run with IDE
    //string name = "L2testStats/UlRlcStats.txt";   //uncomment this if you run with IDE 
    cout << "for Ul: " << endl;
    calculateThroughput(name);
    
    name = "scratch/L2Test/L2testStats/DlRlcStats.txt";    //comment this if you run with IDE
    //name = "L2testStats/DlRlcStats.txt";    //uncomment this if you run with IDE
    cout << "for Dl: " << endl;
    calculateThroughput(name);

    return 0;
}
