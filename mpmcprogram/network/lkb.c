#include <stdio.h>   // Standard input-output functions

int main() {
    int i, n;                  // i → loop variable, n → number of inputs
    int bucket_size;           // Maximum capacity of bucket
    int outgoing_rate;         // Fixed rate at which packets leave
    int packet_size;           // Size of incoming packet
    int storage = 0;           // Current amount of data in bucket (initially empty)

    // Get number of packets
    printf("Enter the number of inputs: ");
    scanf("%d", &n);

    // Get bucket capacity
    printf("Enter the bucket size: ");
    scanf("%d", &bucket_size);

    // Get outgoing rate
    printf("Enter the outgoing rate: ");
    scanf("%d", &outgoing_rate);

    // Loop for each incoming packet
    for (i = 0; i < n; i++) {

        // Input packet size
        printf("\nEnter the incoming packet size: ");
        scanf("%d", &packet_size);

        // Calculate remaining space in bucket
        int size_left = bucket_size - storage;

        // Case 1: Packet fits in bucket
        if (packet_size <= size_left) {
            storage += packet_size;   // Add packet to bucket
        }
        // Case 2: Packet does NOT fit → overflow
        else {
            // Drop extra packets
            printf("Dropped %d packets\n", packet_size - size_left);

            // Fill bucket to maximum
            storage = bucket_size;
        }

        // Show current buffer status
        printf("Buffer size: %d out of %d\n", storage, bucket_size);

        // Simulate outgoing packets (leaking)
        if (storage < outgoing_rate)
            storage = 0;              // If less data, empty bucket
        else
            storage -= outgoing_rate; // Remove outgoing packets

        // Display remaining packets
        printf("After outgoing %d packets, %d packets left in buffer\n",
               outgoing_rate, storage);
    }

    return 0;   // End of program
}