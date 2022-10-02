#include <iostream>

using namespace std;

int main()
{
    int lengthOfArray;
    cin >> lengthOfArray;
    if (lengthOfArray < 4) lengthOfArray = 4;

    int* randomArray = new int[lengthOfArray];

    for (int i=0; i<lengthOfArray; i++) {
        randomArray[i] = i; // = rand();
    }

    int max1 = NULL;
    int max2 = NULL;
    int max3 = NULL;
    int max4 = NULL;
    for (int i=0; i<lengthOfArray; i++) {
        if (max1 == NULL || randomArray[i] > max1) {
            max4 = max3;
            max3 = max2;
            max2 = max1;
            max1 = randomArray[i];

        }
        else {
            if (max2 == NULL || randomArray[i] > max2) {
                max4 = max3;
                max3 = max2;
                max2 = randomArray[i];
            }
            else {
                if (max3 == NULL || randomArray[i] > max3) {
                    max4 = max3;
                    max3 = randomArray[i];
                }
                else {
                    if (max4 == NULL || randomArray[i] > max4) {
                        max4 = randomArray[i];
                    }
                }
            }
        }
    }

    cout << max1 << " " << max2 << " " << max3 << " " << max4 << endl;

    return 0;
}
