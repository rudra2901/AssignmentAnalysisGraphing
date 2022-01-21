#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <algorithm>

#define FILEIO freopen("input.txt", "r", stdin); freopen("outputmt.txt", "w", stdout);

using namespace std;
using namespace std::chrono;

// Function to generate arrays randomnly
void arrayGenerator(vector<vector<int> > &a, int n, int m) {

    for(int i = 0; i < n; i++) 
        for(int j = 0; j < m; j++) 
            a[i][j] = (rand()%5 + 1);
            
}

int matrixTranspose(vector<vector<int> > &b, int n) {
    int steps = 0;

    for(int i = 0; i < n; i++) {
        steps++;
        for(int j = 0; j < n; j++) {
            steps++;

            swap(b[i][j], b[j][i]);

            steps++;
        } steps++;
    } steps++;

    steps++;
    //((2n + 4)n + 2)
    return steps;
}

//Driver Function
int main() {

    srand((unsigned)time(0));
    FILEIO
    fstream tf, sf, cf;
    sf.open("sizesmt.txt", ios::out);
    tf.open("timemt.txt", ios::out);
    cf.open("countmt.txt", ios::out);

    vector<vector<int> > a(3, vector<int> (3, 1));

    vector<vector<int> > b;

    arrayGenerator(a, 3, 3);
    b = a;

    auto start = high_resolution_clock::now();
    long long steps = matrixTranspose(b, 3);
    auto end = high_resolution_clock::now();
            
    auto duration = duration_cast<microseconds>(end - start);
    long long timeCount = duration.count();
    long double timeD= timeCount/1000.00;

    // Saving data into file to provide it to script for plotting
    sf<<3<<endl;
    cf<<steps<<endl;
    tf<<timeD<<endl;

    cout<<"\n\t Matrix Transpose";
    
    cout<<"\n\t Complexity Table\n\n";
    cout<<"Input |  Time\t  |  Steps \n";
    for(int i = 10; i <= 1000; i += 20) {

        if(i == 90)
            i += 10;

        vector<vector<int> > temp1(i, vector<int> (i)), temp2(i, vector<int> (i));
        vector<vector<int> > result(i, vector<int> (i, 0));
        arrayGenerator(temp1, i, i);

        auto start = high_resolution_clock::now();
        steps = matrixTranspose(temp1, i);
        auto end = high_resolution_clock::now();
            
        auto duration = duration_cast<microseconds>(end - start);
        timeCount = duration.count();
        timeD= timeCount/1000.00;

        sf<<i<<endl;
        cf<<steps<<endl;
        tf<<timeD<<endl;

        if(i == 50 || i % 100 == 0) {
            // Print input
            if(i < 100)
                cout<<i<<"\t  | ";
            else if(i < 1000)
                cout<<i<<"\t  | ";
            else
                cout<<i<<"  | ";

            timeCount /= 1000;
            // Print time taken
            if(timeCount < 10) 
                cout<<"  "<<timeCount<<"\t\t  | ";
            else if(timeCount < 100)
                cout<<"  "<<timeCount<<"\t  | ";
            else if(timeCount < 1000)
                cout<<" "<<timeCount<<"\t  | ";
            else if(timeCount < 10000)
                cout<<" "<<timeCount<<"     | ";
            else if(timeCount < 100000) 
                cout<<" "<<timeCount<<"    | ";
            else
                cout<<" "<<timeCount<<"   | ";

            // Print Program steps
            cout<<" "<<steps<<endl;
        }
    }
    
    cout<<"\n";
    
    return 0;
}
