#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flush_stdin();
unsigned int getLeastCommonMultiple(int wheelPeriodicities[], int numberOfWheels);

const int PERIODICITY_STRING_LENGTH = 100;

int main() {
    
    int numberOfMachines = 0;
    scanf("%d", &numberOfMachines);
    //printf("%d machines.\n", numberOfMachines);
    
    for (int i = 0; i < numberOfMachines; i++) {
        int numberOfWheels = 0;
        scanf("%d", &numberOfWheels);
        // printf("%d wheels for machine %i.\n", numberOfWheels, (i + 1));
        flush_stdin();
        
        int wheelPeriodicities[numberOfWheels];
        char periodicity[PERIODICITY_STRING_LENGTH];
        scanf( "%99[^\n]", periodicity);
        
        // Get all the wheel periodicities.
        int startIndex = 0;
        int wheelIndex = 0;
        for (int i = 0; i < PERIODICITY_STRING_LENGTH &&
                        wheelIndex < numberOfWheels; i++) {
            if (periodicity[i] == ' ' ||
                periodicity[i] == '\0') {
                int bufferSize = i - startIndex;
                printf("Found blank space at %d, creating a buffer of size %d.", i, bufferSize);
                char buffer[bufferSize + 1];
                buffer[bufferSize + 1] = '\0';
                memcpy(buffer, &periodicity[startIndex], bufferSize);
                wheelPeriodicities[wheelIndex] = atoi(buffer);
                printf("\nInteger value %d.\n", wheelPeriodicities[wheelIndex]);
                startIndex = i + 1;
                wheelIndex++;
            }
        }
        
        unsigned int leastCommonMultiple = getLeastCommonMultiple(wheelPeriodicities, numberOfWheels);
        if (leastCommonMultiple != -1) {
            printf("%d", leastCommonMultiple);
        }
        else {
            printf("More than a billion.");
        }
        
    }
    
    return 0;
}

unsigned int getHighestValueInArray(int integerArray[], int numberOfItems) {
    int highestValue = integerArray[0];
    for (int i = 0; i < numberOfItems; i++) {
        if (integerArray[i] > highestValue) {
            highestValue = integerArray[i];
        }
    }
    return highestValue;
}

unsigned int getLeastCommonMultiple(int wheelPeriodicities[], int numberOfItems) {
    unsigned int highestValue = getHighestValueInArray(wheelPeriodicities, numberOfItems);
    unsigned int checkedValue = highestValue;
    int commonMultipleFound = 0;
    while (!commonMultipleFound) { // Loop until found
        commonMultipleFound = 1;
        for (int i = 0; i < numberOfItems; i++) {
            if (checkedValue % wheelPeriodicities[i] != 0) {
                commonMultipleFound = 0;
                break;
            }
        }
        if (!commonMultipleFound) {
            checkedValue += highestValue;
            //printf("%u\n", checkedValue);
        }
        if (checkedValue > 10000000000) {
            return -1;
        }
    }
    
    return checkedValue;
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}