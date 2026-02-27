#include <iostream>
#include <iomanip>
#include <cstdlib>  // atof
using namespace std;

int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    int sum = 0;

    for (int i = 1; i < argc; i++) {
        sum += atof(argv[i]);   // แปลง string เป็น double
    }

    int average = sum / (argc - 1);

    cout << "---------------------------------" << endl;
    cout << "Average of " << (argc - 1) << " numbers = "
         << fixed << setprecision(3) << average << endl;
    cout << "---------------------------------" << endl;

    return 0;
}