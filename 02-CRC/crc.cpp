/*
Program to implement error detection using CRC Algo

Sender side - user enters the input data and CRC polynomial, implement the process to find sent string
Receiver side - Received data is checked for errors. Ouput to show received data string and errors (if any)
Error function - Randomly one of the input bits will be changed
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>

using namespace std;

// Function to perform CRC encoding
string encodeData(string inputData, string crcPoly)
{
     int m = inputData.length();
     int n = crcPoly.length();

     // Appending zeros to the input data
     string appendedData = inputData;
     for (int i = 0; i < n - 1; i++)
     {
          appendedData += '0';
     }

     for (int i = 0; i <= m; i++)
     {
          if (appendedData[i] == '1')
          {
               for (int j = 0; j < n; j++)
               {
                    appendedData[i + j] = (appendedData[i + j] == crcPoly[j]) ? '0' : '1';
               }
          }
     }

     // Getting the sent string (input data + remainder)
     string sentString = inputData + appendedData.substr(m, n - 1);

     return sentString;
}

// Function to simulate errors in received data
void introduceError(string &data)
{
     srand(time(0));
     int errorIndex = rand() % data.length();
     data[errorIndex] = (data[errorIndex] == '0') ? '1' : '0';
}

// Function to perform CRC decoding and error checking
void receiveData(string receivedData, string crcPoly)
{
     int n = crcPoly.length();

     // Checking for errors
     string remainder = receivedData.substr(receivedData.length() - n + 1);
     string temp = receivedData;
     for (int i = 0; i <= receivedData.length() - n; i++)
     {
          if (temp[i] == '1')
          {
               for (int j = 0; j < n; j++)
               {
                    temp[i + j] = (temp[i + j] == crcPoly[j]) ? '0' : '1';
               }
          }
     }

     // If remainder is all zeros, no error
     if (temp.substr(receivedData.length() - n + 1) == string(n - 1, '0'))
     {
          cout << "Received data string: " << receivedData << endl;
          cout << "No errors detected." << endl;
     }
     else
     {
          cout << "Received data string: " << receivedData << endl;
          cout << "Errors detected." << endl;
     }
}

int main()
{
     string inputData, crcPoly;

     // Sender side
     cout << "Enter input data: ";
     cin >> inputData;
     cout << "Enter CRC polynomial: ";
     cin >> crcPoly;

     string sentString = encodeData(inputData, crcPoly);
     cout << "Sent data string: " << sentString << endl;

     // Receiver side
     string receivedData = sentString;

     introduceError(receivedData); // Simulating error

     receiveData(receivedData, crcPoly);

     return 0;
}

//SAMPLE OUTPUT
// Enter input data: 101010
// Enter CRC polynomial: 101
// Sent data string: 10101000
// Received data string: 10101100
// Errors detected.