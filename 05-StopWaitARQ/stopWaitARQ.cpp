#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int FRAME_SIZE = 2; // Frame size in bits

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
     int sequenceNumber = 0;

     while (dataBits > 0)
     {
          // Prepare the frame
          cout << "Sender: Sending frame with sequence number " << sequenceNumber << endl;

          // Simulate an error (frame lost or ACK lost)
          if (simulateError())
          {
               cout << "Sender: Error - Frame lost!" << endl;
               sleep(1); // Wait for a while before retransmission
          }
          else
          {
               // Simulate a delay in transmission
               sleep(1);

               // Receiver side processing
               cout << "Sender: Waiting for ACK..." << endl;
               sleep(1);

               // Simulate an error (ACK lost)
               if (simulateError())
               {
                    cout << "Sender: Error - ACK lost!" << endl;
                    sleep(1); // Wait for a while before retransmission
               }
               else
               {
                    cout << "Sender: ACK received. Frame successfully sent." << endl;
                    sequenceNumber = 1 - sequenceNumber; // Toggle sequence number
                    dataBits -= FRAME_SIZE;
               }
          }
     }

     cout << "Sender: All data sent successfully." << endl;
}

// Receiver side function
void receiver()
{
     int expectedSequenceNumber = 0;

     while (true)
     {
          // Simulate a delay in receiving the frame
          sleep(1);

          // Simulate an error (frame lost)
          if (simulateError())
          {
               cout << "Receiver: Error - Frame lost!" << endl;
               continue; // Ignore the lost frame and wait for retransmission
          }

          // Process the frame
          cout << "Receiver: Frame received with sequence number " << expectedSequenceNumber << endl;

          // Simulate an error (ACK lost)
          if (simulateError())
          {
               cout << "Receiver: Error - ACK lost!" << endl;
               sleep(1); // Wait for a while before retransmission
          }
          else
          {
               // Send ACK
               cout << "Receiver: Sending ACK for sequence number " << expectedSequenceNumber << endl;
               expectedSequenceNumber = 1 - expectedSequenceNumber; // Toggle sequence number
          }
     }
}

int main()
{
     srand(time(0)); // Seed for random number generation

     int dataBits;
     cout << "Enter the number of bits to be transferred: ";
     cin >> dataBits;

     cout << "Simulating 1-bit Stop and Wait Protocol..." << endl;

     // Start sender and receiver in separate threads (for simplicity, using sleep instead of actual threads)
     sender(dataBits);
     receiver();

     return 0;
}