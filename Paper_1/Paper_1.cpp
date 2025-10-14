#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

// Using long long int for large inputs


long long int euclid(long long int m, long long int n, long long int &divCount) {
    divCount = 0;

    while (n != 0) {
        divCount ++;                  // counting modulo
        long long int r = m % n;      //r is the remainder
        m = n;
        n = r;
    }
    return m;
}

long long int decremental(long long int m, long long int n, long long int &divCount) {
    divCount = 0;

    long long int result;

    if (m < n) {
        result = m;
    }
    else {
        result = n;
    }

    while (result > 0) {
        // One modulo operation for each m and n
        divCount = divCount + 2;
        
        // Checking if m and n are divisible by the result
        if (m % result == 0 && n % result == 0) {
            break;
        } 
        // Decrement result
        result --;
    }

    return result;

}

/*
Helper function for pollRho
computing x^2 % n
*/
long long int modPow(long long base, long long int exp, long long int mod, long long &divCount) {
    // initialize result
    long long int result = 1;

    while(exp > 0){
        // if y is odd, multiply the base with result
        if (exp % 2 == 1) {
            result = (result * base) % mod;
            divCount++;
        }

        exp = exp / 2;

        base = (base * base) % mod;         // square base
        divCount++;
    }
    return result;
}


/*
Helper function for pollRhoFactorize
Checking if n is a prime number
*/
bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }
    if (n % 2 == 0 && n != 2) {
        return false;
    }
    // Checking for divisibility from 3 up to the square root of n,
    // increment by 2 to only check odd numbers
    for(long long int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

long long int pollRho(long long int n, long long int &divCount){
    if (n % 2 == 0) {
        divCount++;
        return 2;       // even number means one of the divisor is 2
    }

    // Picking from the range [2, N)
    long long int x = (rand () % (n-2)) + 2;
    long long int y = x;
    // Rerun with a different c if it throws failure for a composite
    long long int c = (rand() % (n - 1)) + 1;
    long long d = 1;

    // Keep going until a nontrivial factor is found
    while (d == 1) {
        /* 
            x = (x^2 + c) % n
           Tortoise move:  x(i + 1) = f(x(i))*/
        x = (modPow(x, 2, n, divCount) + c + n) % n;
        divCount++;

        /*
             y = f(f(y))
             Hare move: y(i + 1) = f(f(y(i)))
        */
        y = (modPow(y, 2, n, divCount) + c + n) % n;
        divCount++;
        y = (modPow(y, 2, n, divCount) + c + n) % n;
        divCount++;

        long long euclidDivCount = 0;
        d = euclid(abs(x - y), n, euclidDivCount);
        divCount += euclidDivCount;
    }

    // Try again if the algorithm fails to find prime facto with x and c 
    if (d == n) {
        return pollRho(n, divCount);
    }

    return d;
}

vector<long long> pollRhoFactorize(long long n, long long &divCount) {
    vector<long long> factors;

    if (n == 1) {
        return factors;
    }

    // Base case
    if(isPrime(n)) {
        factors.push_back(n);
        return factors;
    }

    long long factor = pollRho(n, divCount);

    // Recursively factor both parts
    vector<long long> factor1 = pollRhoFactorize(factor, divCount);
    vector<long long> factor2 = pollRhoFactorize(n / factor, divCount);

    // merging results
    factors.insert(factors.end(), factor1.begin(), factor1.end());
    factors.insert(factors.end(), factor2.begin(), factor2.end());

    return factors;
}

/*
compute GCD- Prime Factorization
*/

long long gcdFactorization(long long m, long long n, long long &divCount) {
    vector<long long> mFactors = pollRhoFactorize(m, divCount);
    vector<long long> nFactors = pollRhoFactorize(n, divCount);

    // sort the lists
    sort(mFactors.begin(), mFactors.end());
    sort(nFactors.begin(), nFactors.end());

    // Find common primes
    long long gcd = 1;
    size_t i = 0, j = 0;
    
    while (i < mFactors.size() && j < nFactors.size()) {
        if(mFactors[i] == nFactors[j]) {
            gcd *= mFactors[i];
            i++;
            j++;
        }
        else if (mFactors[i] < nFactors[j]) {
            i++;
        }
        else {
            j++;
        }
    }

    return gcd;
}

void getUserInput() {
    long long int m, n;

    cout << " " << endl;
    cout << "           Please enter m and n integer values" << endl;
    cout << " " << endl;

    // Input m and n
    cout << "Enter m: " << endl;
    while (!(cin >> m)) {
        cout << "Invalid input. Please enter an integer for m: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "You entered: " << m << " as m \n" << endl;

    cout << "Now, enter n: " << endl;
    while (!(cin >> n)) {
        cout << "Invalid input. Please enter an integer for n: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "You entered: GCD (" << m << ", " << n << ")" << endl;

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

    return;
}