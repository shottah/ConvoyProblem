#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define I 9999
int capacity, items;
int convoy(int*,int*,int*,int*);
void printArray(int*, int);

int main()
{
    // Declare & Initialize Variables
    ifstream fin;
    fin.open("input.txt");
	ofstream fout;
	
    // Verify input file
    if (!fin.is_open())
    {
        printf("Could not open file.");
        exit(1);
    } else {
    	// Process Inputs
	    fin >> capacity;
	    fin >> items;
	
	    // Store from 1 to N+1
	    int *weight = new int[items + 1];
	    int *load = new int[items + 1];
	    int *trucks = new int[items + 1];
	    int *truckLoad = new int[items + 1];
	
	    // Read weight[i] for item[i] up to N
	    for (int i = 1; i < items + 1; i++)
	    {
	        fin >> weight[i];
	    }
	
	    // Close input file
	    fin.close();
	
	    // Processing function
	    int spare = convoy(weight, load, trucks, truckLoad);
	    
	    // Open output file
	    fout.open("output.txt");
	    if (!fout.is_open()) {
	    	printf("Could not open output file... printing to console.");
	    	printf("%d\n", load[items]);
	    	printArray(truckLoad, trucks[items]);
	    	printf("%d", trucks[items]);
	    } else {
	    	// Save output data
	    	fout << trucks[items] << "\n";
	    	for (int i = 1; i <= trucks[items]; i++)
	    		fout << truckLoad[i] << " ";
	    	fout << "\n" << spare; 
	    	fout.close();
	    }
    }

    system("PAUSE");
    return 1;
}

/**
 * This function accepts the array of item weights, load of each truch, number of trucks,
 * and the number of items on each truck.
 * 
 * truck [i] = Number of trucks needed to load i items
 *
 *
 * @return void
 */		
int convoy(int *weight, int *L, int *T, int *TL)
{

    int i, currMinLF;
    L[0] = 0;
    T[0] = 0;
    TL[0] = 0;

    for (int i = 1; i < items + 1; i++)
    {
        int k = i;
        // Consider the weight of item i
        int lastItem = weight[i];
        T[i] = T[i - 1] + 1;
        // Number of items on truck[i] = 1
        TL[T[i]] = 1;
        currMinLF = I;

        while (lastItem <= capacity && k > 0)
        {
            // Load truck[i] till capacity met or all items loaded
            int currLF = (capacity - lastItem) * (capacity - lastItem) + L[k - 1];

            // Minimum load for all items till i
            if (currLF < currMinLF)
            {
                currMinLF = currLF;
                T[i] = T[k - 1] + 1;
                TL[T[i]] = i - k +1;
            }
            // Add item to new truck
            lastItem += weight[--k];
        }

        // Store solution
        L[i] = currMinLF;
    }

    return currMinLF;
}

void printArray(int * a, int n)
{
    for (int i = 1; i < n+1; i++)
        printf("%d ", a[i]);
    printf("\n");
}
