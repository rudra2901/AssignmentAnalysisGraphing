#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

#define FILEIO freopen("input.txt", "r", stdin); freopen("outputmm.txt", "w", stdout);

using namespace std;
using namespace std::chrono;

// Function to generate arrays randomnly
void arrayGenerator(vector<vector<int> > &a, int n, int m) {

    for(int i = 0; i < n; i++) 
        for(int j = 0; j < m; j++) 
            a[i][j] = (rand()%5 + 1);
            
}

int matrixMultiplication(const vector<vector<int> > &a, const vector<vector<int> > &b, vector<vector<int> > &c, int n) {
    int steps = 0;

    for(int i = 0; i < n; i++) {
        steps++;
        for(int j = 0; j < n; j++) {
            steps++;
            int x = 0;
            steps++;
            for(int k = 0; k < n; k++) {
                steps++;
                x += a[i][k] * b[k][j];
                steps++;
            } steps++;

            c[i][j] = x;
            steps++;

        } steps++;
    } steps++;

    steps++;
    //((2n + 4)n + 2)n + 2
    return steps;
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

void printMatrix(const vector<vector<int> > &a, const vector<vector<int> > &b, const vector<vector<int> > &c, int n) {

    cout<<"\t  A\t\t\t\t   B\t\t\t  Result\n";
    for(int i = 0; i < n; i++) {
        
        for(int j = 0; j < n; j++) {
            if(j == 0) 
                cout<<"[ "<<a[i][j]<<" | ";
            else if(j == n-1) {
                cout<<a[i][j]<<" ] ";
            }
            else
                cout<<a[i][j]<<" | ";
        }

        if(i == n/2) {
            cout<<" X ";
        }
        for(int j = 0; j < n; j++) {
            if(j == 0) {
                if(i == n/2)
                    cout<<"[ "<<b[i][j]<<" | ";
                else
                    cout<<"\t [ "<<b[i][j]<<" | ";
            }
            else if(j == n-1) {
                cout<<b[i][j]<<" ] ";
            }
            else
                cout<<b[i][j]<<" | ";
        }

        if(i == n/2) {
            cout<<" = ";
        }
        for(int j = 0; j < n; j++) {
            if(c[i][j] > 9){
                if(j == 0) {
                    if(i == n/2)
                        cout<<"[ "<<c[i][j]<<" | ";
                    else
                        cout<<"\t  [ "<<c[i][j]<<" | ";
                }
                else if(j == n-1) {
                    cout<<c[i][j]<<" ] ";
                }
                else
                    cout<<c[i][j]<<" | ";
            }
            else {
                if(j == 0) {
                    if(i == n/2)
                        cout<<"[  "<<c[i][j]<<" | ";
                    else
                        cout<<"\t  [  "<<c[i][j]<<" | ";
                }
                else if(j == n-1) {
                    cout<<" "<<c[i][j]<<" ] ";
                }
                else
                    cout<<c[i][j]<<"  | ";
            }
        }
        cout<<"\n";
    }
}

//Driver Function
int main() {

    srand((unsigned)time(0));
    FILEIO
    fstream tf, sf, cf;
    sf.open("sizesmm.txt", ios::out);
    tf.open("timemm.txt", ios::out);
    cf.open("countmm.txt", ios::out);

    vector<vector<int> > a(3, vector<int> (3, 1));

    vector<vector<int> > b(3, vector<int> (3, 2));

    vector<vector<int> > res(3, vector<int> (3, 0));

    arrayGenerator(a, 3, 3);
    //Generating first array
    arrayGenerator(b, 3, 3);

    auto start = high_resolution_clock::now();
    long long steps = matrixMultiplication(a, b, res, 3);
    auto end = high_resolution_clock::now();
            
    auto duration = duration_cast<microseconds>(end - start);
    long long timeCount = duration.count();
    long double timeD= timeCount/1000.00;

    // Saving data into file to provide it to script for plotting
    sf<<3<<endl;
    cf<<steps<<endl;
    tf<<timeD<<endl;

    cout<<"\n\t\t\t Matrix Multiplication\n\n";

    printMatrix(a, b, res, 3);
    
    cout<<"\n\n\t Complexity Table\n\n";
    cout<<"Input |  Time\t  |  Steps \n";
    for(int i = 10; i <= 1000; i += 20) {

        if(i == 90)
            i += 10;

        vector<vector<int> > temp1(i, vector<int> (i)), temp2(i, vector<int> (i));
        vector<vector<int> > result(i, vector<int> (i, 0));
        arrayGenerator(temp1, i, i);
        arrayGenerator(temp2, i, i);

        auto start = high_resolution_clock::now();
        steps = matrixMultiplication(temp1, temp2, result, i);
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
