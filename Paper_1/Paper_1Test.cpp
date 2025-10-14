#include "Paper_1.h"
#include <fstream>
#include <iomanip>

void runTest() {
        srand(time(NULL));
        vector<pair<int, int>> scales = {
        {100, 200},         // 10^2
        {1000, 2000},       // 10^3
        {10000, 20000}      // 10^4
    };

    // Creating and opening file
    ofstream fileOut("results.csv");
    if (!fileOut) {
        cerr << "Error: Could not open results.csv for writing" << endl;
        return;
    }
    fileOut << "Scale, m, n, Algorithm, GCD, Divisions, Time_ns" << endl;

    cout << "Testing Starts" << endl;
        for (auto [low, high] : scales) {
        string scaleLabel = "[" + to_string(low) + "-" + to_string(high) + "]";
        cout << "========================================================" << endl; 
        cout << "Testing range: m in " << scaleLabel << ", n smaller than m" << endl;
        cout << "========================================================" << endl; 

        for (int i = 1; i <= 5; i++) {
            long long m = (rand() % (high - low + 1)) + low;
            long long n = rand() % m; // ensure n < m

            cout << fixed << setprecision(0);
            cout << "\nTest " << i << ": m = " << m << ", n = " << n << endl;

            //Euclid
            long long int EuclidDivCount = 0;       // For counting division
            auto start1 = chrono::high_resolution_clock::now();
            int result1 = euclid(m, n, EuclidDivCount);
            auto stop1 = chrono::high_resolution_clock::now();

            //Duration in nano second
            auto duration1 = chrono::duration_cast<chrono::nanoseconds>(stop1-start1);

            cout << "Euclid:" << endl;
            cout << "   GCD (" << m << ", " << n << ") = " << result1 << endl;
            cout << "   Number of divisions performed: " << EuclidDivCount << endl;
            cout << "   Execution time: " << duration1.count() << " nanoseconds" << endl;
            cout << "========================================================" << endl; 
            fileOut << scaleLabel << "," << m << "," << n << ",Euclid," << result1 << "," << EuclidDivCount << "," << duration1.count() << "\n";

            // Decremental
            long long int DecDivCount = 0;       // For counting division
            auto start2 = chrono::high_resolution_clock::now();
            int result2 = decremental(m, n, DecDivCount);
            auto stop2 = chrono::high_resolution_clock::now();

            //Duration in nano second
            auto duration2 = chrono::duration_cast<chrono::nanoseconds>(stop2-start2);

            cout << "Decremental:" << endl;
            cout << "   GCD (" << m << ", " << n << ") = " << result2 << endl;
            cout << "   Number of divisions performed: " << DecDivCount << endl;
            cout << "   Execution time: " << duration2.count() << " nanoseconds" << endl;
            cout << "========================================================" << endl;
            fileOut << scaleLabel << "," << m << "," << n << ",Decremental," << result2 << "," << DecDivCount << "," << duration2.count() << "\n";

            // Pollard Rho Prime Factorization
            long long int RhoDivCount = 0;       // For counting division
            auto start3 = chrono::high_resolution_clock::now();
            long long int result3 = gcdFactorization(m, n, RhoDivCount);
            auto stop3 = chrono::high_resolution_clock::now();

            //Duration in nano second
            auto duration3 = chrono::duration_cast<chrono::nanoseconds>(stop3-start3);

            cout << "Pollard Rho Prime Factorization:" << endl;
            cout << "   GCD (" << m << ", " << n << ") = " << result3 << endl;
            cout << "   Number of divisions performed: " << RhoDivCount << endl;
            cout << "   Execution time: " << duration3.count() << " nanoseconds" << endl;
            cout << "==========================================================" << endl;
            fileOut << scaleLabel << "," << m << "," << n << ",Pollard Rho Prime Fact," << result3 << "," << RhoDivCount << "," << duration3.count() << "\n";
        }
    }
}

int main() {
    runTest();
}

