/*
Consider reigon of memory of size 2048KB.

Further, consider that it can be divided into size of 2^N chunks, where N varies from 4 to 8.

Lets say that memory requirement of K different process (P1,P2,P3,....,PK) can be modelled as 2^(1+j+N) KB for process Pj.

If k varies from 4 to 9 for each value of N. Write a program to determine if processes for a selected K can be assigned to memory of size 2048KB.

Determine how much memory is free, if any at the end in each case and how many contiguous chunks of memory are allocated to each process.

For example -
K=4 your program should give an answer for N=4,5,6,7,8.

*/

#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
    // Consider reigon of memory of size 2048KB.
    int memory_size = 2048;
    vector<int> memory(memory_size, 0);

    // Input k number of processes
    int k = 4;
    cout << "Enter k (between 4 and 8): ";
    cin >> k;

    for (int N = 4; N <= 8; N++) { // N varies from 4 to 8
        cout << endl;

        // Consider that it can be divided into size of 2^N chunks, where N varies from 4 to 8.
        int chunk_size = pow(2, N);            // for N=4, chunk_size = 2^4
        int chunks = memory_size / chunk_size; // for N=4, chunks = 2048/2^4 = 2048/16 = 128= 2^7

        cout << "N = " << N << ", chunk_size = " << chunk_size << "KB, Number of chunks = " << chunks << ", memory size = " << memory_size << "KB" << endl;

        vector<int> chunkAlloted(chunks, 0); // chunkAlloted[i] = process number to which chunk i is alloted

        // Lets say that memory requirement of K different process (P1,P2,P3,....,PK) can be modelled as 2^(1+j+N) KB for process Pj.
        vector<int> process_size(k); // Size of process number i
        for (int i = 0; i < k; i++) {
            process_size[i] = pow(2, 1 + (i + 1) + N); // Define process size for each process
        }
        // for k=4 and N=4, process_size = {2^6, 2^7, 2^8, 2^9}

        cout << "Process size -> ";
        for (int i = 0; i < k; i++) {
            // cout<<"Process "<<i+1<<" size = "<<process_size[i]<<" ";
            cout << "P1 = " << process_size[i] << "KB | ";
        }
        cout << endl;

        // If k varies from 4 to 9 for each value of N. Write a program to determine if processes for a selected K can be assigned to memory of size 2048KB.

        vector<int> pages(k); // Number of pages required for process number i
        for (int i = 0; i < k; i++) {
            if (process_size[i] > chunk_size) {
                pages[i] = process_size[i] / chunk_size; // Number of pages required for process number i
            } else {
                pages[i] = 1;
            } // If process is smaller than chunk then assign 1 page
        }     // for k=4 and N=4, pages = {2^6/2^4, 2^7/2^4, 2^8/2^4, 2^9/2^4} = {2^2, 2^3, 2^4, 2^5}

        cout << "Pages needed = ";
        for (int i = 0; i < k; i++) {
            // cout<<"Process "<<i+1<<" pages = "<<pages[i]<<" ";
            cout << "P1 = " << pages[i] << " | ";
        }
        cout << endl;

        // Here 1 page size == 1 chunk size (Concept of Paging)

        int chunksNeeded = 0; // Number of chunks needed for all the processes
        for (int i = 0; i < k; i++) {
            chunksNeeded += pages[i];
        }

        vector<int> processAllocatedMemory(k, 0); // If process is allocated memory then processAllocatedMemory[i] = 1
        for (int i = 0; i < k; i++) {
            if (pages[i] == 1) {
                processAllocatedMemory[i] = 1;
            }
        }

        if (chunksNeeded > chunks) {
            cout << "Processes cannot be alloted to memory!" << endl;
            // cout << "Chunks needed = " << chunksNeeded << ", Number of chunks = " << chunks << endl;
            cout << "Memory needed = " << chunksNeeded * chunk_size << "KB, Memory available = " << memory_size << "KB" << endl;
            continue;
        }
        // Assign all the chunks with process
        int chunk = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < pages[i]; j++) {
                chunkAlloted[chunk] = i + 1;
                chunk++;
            }
        }

        for (int i = 0; i < chunks; i++) {
            // cout<<"Chunk "<<i+1<<" alloted to process "<<chunkAlloted[i]<<endl;
            cout << chunkAlloted[i] << " ";
        }
        cout << endl;

        // Determine how much memory is free
        int free_memory = 0;
        for (int i = 0; i < chunks; i++) {
            if (chunkAlloted[i] == 0) {    // If chunk is free
                free_memory += chunk_size; // Add chunk size to free memory
            }
        }
        // cout << "-- STATISTICS --" << endl;
        cout << "Free memory = " << free_memory << "KB" << endl;

        vector<int> countOfChunksAllocated(k, 0); // Number of chunks allocated to process number i
        for (int i = 0; i < chunks; i++) {
            if (chunkAlloted[i] != 0) {
                countOfChunksAllocated[chunkAlloted[i] - 1]++;
            }
        }

        cout << "Chunks allocated ->";
        for (int i = 0; i < k; i++) {
            // cout << "Process " << i + 1 << " allocated " << countOfChunksAllocated[i] << " chunks" << endl;
            cout << "P" << i + 1 << " = " << countOfChunksAllocated[i] << " | ";
        }
        cout << endl;
        cout << "Total Chunks allocated = " << chunksNeeded << endl;

        cout << endl;
    }
}