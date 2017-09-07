#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flush_stdin();
long long getLeastCommonMultiple(long long wheelPeriodicities[], int numberOfWheels);

const int PERIODICITY_STRING_LENGTH = 100;

int main() {
   
    int numberOfMachines = 0;
    scanf("%d", &numberOfMachines);
    //printf("%d machines.\n", numberOfMachines);
    
    long long answers[numberOfMachines];
    
    for (int i = 0; i < numberOfMachines; i++) {
        int numberOfWheels = 0;
        scanf("%d", &numberOfWheels);
        // printf("%d wheels for machine %i.\n", numberOfWheels, (i + 1));
        flush_stdin();
        
        long long wheelPeriodicities[numberOfWheels];
        char periodicity[PERIODICITY_STRING_LENGTH];
        scanf( "%99[^\n]", periodicity);
        
        // Get all the wheel periodicities.
        int startIndex = 0;
        int wheelIndex = 0;
        for (int i = 0; i < PERIODICITY_STRING_LENGTH &&
                        wheelIndex < numberOfWheels; i++) {
            if (periodicity[i] == ' ' ||
                periodicity[i] == '\0') {
                // printf("Found blank space at %d, creating a buffer of size %d.", i, bufferSize);
                int bufferSize = i - startIndex;
                char buffer[bufferSize + 1];
                buffer[bufferSize] = '\0';
                memcpy(buffer, &periodicity[startIndex], bufferSize);
                wheelPeriodicities[wheelIndex] = atoll(buffer);
                
                startIndex = i + 1;
                wheelIndex++;
            }
        }
        
        long long leastCommonMultiple = getLeastCommonMultiple(wheelPeriodicities,
                                                               numberOfWheels);
        answers[i] = leastCommonMultiple;
    }

    for (int i = 0; i < numberOfMachines; i++) {
        if (answers[i] != 0) {
            printf("%lld", answers[i]);
        }
        else {
            printf("More than a billion.");
        }
        if (i == numberOfMachines - 1)
            break;
        printf("\n");
    }

    
    return 0;
}

long long getGreatestCommonDivisor(long long a, long long b) {
    if (b == 0) // We are done
        return a;
    return getGreatestCommonDivisor(b, a%b);
}

long long getLeastCommonMultiple(long long wheelPeriodicities[], int numberOfWheels) {
    long long res = 1;
    for (int i = 0; i < numberOfWheels; i++) {
        res = res * wheelPeriodicities[i] / getGreatestCommonDivisor(res, wheelPeriodicities[i]);
        if (res > 10000000000)
            return 0;
    }
    return res;
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}