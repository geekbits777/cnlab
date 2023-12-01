#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>

using namespace std;

const int WINDOW_SIZE = 4; // Size of the sending and receiving windows

// Function to simulate random errors
bool simulateError()
{
     // Generate a random number between 0 and 9
     int randomNum = rand() % 10;

     // Simulate an error if the random number is less than 2 (20% probability)
     return randomNum < 2;
}

// Sender side function
void sender(int dataBits)
{
     int base = 0;       // The base of the sending window
     int nextSeqNum = 0; // The next sequence number to be sent

     // Vector to represent the status of each frame in the window (0 - not sent, 1 - sent, -1 - acknowledged)
     vector<int> frameStatus(WINDOW_SIZE, 0);

     while (base < dataBits)
     {
          // Send frames in the window
          for (int i = base; i < min(base + WINDOW_SIZE, dataBits); ++i)
          {
               // Skip frames that have been sent and not yet acknowledged
               if (frameStatus[i % WINDOW_SIZE] == 0)
               {
                    // Simulate an error (frame lost)
                    if (simulateError())
                    {
                         cout << "Sender: Error - Frame " << i << " lost!" << endl;
                    }
                    else
                    {
                         // Simulate a delay in transmission
                         sleep(1);

                         // Receiver side processing
                         cout << "Sender: Frame " << i << " sent." << endl;
                    }
                    frameStatus[i % WINDOW_SIZE] = 1; // Mark frame as sent
               }
          }

          // Simulate an error (ACK lost)
          if (simulateError())
          {
               cout << "Sender: Error - ACK lost!" << endl;
          }
          else
          {
               // Simulate a delay in receiving the ACK
               sleep(1);

               // Receiver side processing
               cout << "Sender: Waiting for ACK..." << endl;

               // Update the base based on the acknowledged frames
               while (frameStatus[base % WINDOW_SIZE] == 1)
               {
                    cout << "Sender: ACK received for frame " << base << endl;
                    frameStatus[base % WINDOW_SIZE] = 0; // Mark frame as acknowledged
                    ++base;
               }
          }
     }

     cout << "Sender: All data sent successfully." << endl;
}

// Receiver side function
void receiver() {
    int expectedSeqNum = 0;  // Expected sequence number at the receiver

    while (true) {
        // Simulate a delay in receiving the frame
        sleep(1);

        // Simulate an error (frame received in error)
        if (simulateError()) {
            int errorFrame = rand() % WINDOW_SIZE;  // Randomly mark one frame as received in error
            cout << "Receiver: Error - Frame " << expectedSeqNum + errorFrame << " received in error!" << endl;
        } else {
            // Process the frame
            cout << "Receiver: Frame " << expectedSeqNum << " received." << endl;

            // Send ACK for the received frame
            cout << "Receiver: Sending ACK for frame " << expectedSeqNum << endl;

            // Simulate a delay in transmitting the ACK
            sleep(1);

            // Update the expected sequence number
            expectedSeqNum = (expectedSeqNum + 1) % (2 * WINDOW_SIZE);
        }
    }
}

int main()
{
     srand(time(0)); // Seed for random number generation

     int dataBits;
     cout << "Enter the number of bits to be transferred: ";
     cin >> dataBits;

     cout << "Simulating Go-Back-N Sliding Window Protocol..." << endl;

     // Start sender and receiver in separate threads (for simplicity, using sleep instead of actual threads)
     sender(dataBits);
     receiver();

     return 0;
}