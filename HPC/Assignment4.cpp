// Addition of Vectors

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 10;  // Size of vectors for demonstration

int main() {
    // Create and initialize vectors
    vector<int> a(N), b(N), c(N);

    srand(time(nullptr));
    cout << "Vector A: ";
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100;
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "Vector B: ";
    for (int i = 0; i < N; ++i) {
        b[i] = rand() % 100;
        cout << b[i] << " ";
    }
    cout << endl;

    // Perform vector addition
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Output result
    cout << "Result Vector C (A + B): ";
    for (int i = 0; i < N; ++i) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}






// Matrix Multiplication

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int N = 3;  // Size of matrix for demonstration

int main() {
    // Create and initialize matrices
    vector<vector<int>> a(N, vector<int>(N)), b(N, vector<int>(N)), c(N, vector<int>(N));

    srand(time(nullptr));
    cout << "Matrix A:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = rand() % 100;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix B:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            b[i][j] = rand() % 100;
            cout << b[i][j] << " ";
        }
        cout << endl;
    }

    // Perform matrix multiplication
    cout << "Matrix C (A * B):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
