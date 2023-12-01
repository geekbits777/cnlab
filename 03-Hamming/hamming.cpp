#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to calculate the number of redundant bits needed
int calculateRedundantBits(int dataSize)
{
     int r = 1;
     while ((1 << r) < (dataSize + r + 1))
     {
          r++;
     }
     return r;
}

// Function to perform XOR operation
int xorOperation(const vector<int> &data, int start, int end)
{
     int result = data[start];
     for (int i = start + 1; i <= end; i++)
     {
          result ^= data[i];
     }
     return result;
}

// Function to generate the Hamming Code for a given input data
vector<int> generateHammingCode(const vector<int> &inputData)
{
     int dataSize = inputData.size();
     int redundantBits = calculateRedundantBits(dataSize);

     vector<int> hammingCode(dataSize + redundantBits, 0);

     // Fill in the data bits
     int dataIndex = 0;
     for (int i = 1; i <= hammingCode.size(); i++)
     {
          if (!((i & (i - 1)) == 0))
          {
               // If the position is not a power of 2
               hammingCode[i - 1] = inputData[dataIndex++];
          }
     }

     // Fill in the redundant bits
     for (int i = 0; i < redundantBits; i++)
     {
          int position = (1 << i) - 1; // 2^i-1
          hammingCode[position] = xorOperation(hammingCode, position + 1, hammingCode.size() - 1);
     }

     return hammingCode;
}

// Function to introduce errors in the received data
void introduceError(vector<int> &data)
{
     srand(time(0));
     int errorIndex = rand() % data.size();
     data[errorIndex] = (data[errorIndex] == 0) ? 1 : 0;
}

// Function to correct errors in the received data
void correctErrors(vector<int> &receivedData)
{
     int redundantBits = calculateRedundantBits(receivedData.size() - 1);

     int errorPosition = 0;
     for (int i = 0; i < redundantBits; i++)
     {
          errorPosition += receivedData[(1 << i) - 1] << i;
     }

     if (errorPosition != 0)
     {
          cout << "Error detected at bit: " << errorPosition << endl;
          receivedData[errorPosition - 1] = (receivedData[errorPosition - 1] == 0) ? 1 : 0;
          cout << "Error corrected." << endl;
     }
     else
     {
          cout << "No errors detected." << endl;
     }
}

// Function to receive and check data using Hamming Code
void receiveData(const vector<int> &receivedData)
{
     cout << "Received data string: ";
     for (int bit : receivedData)
     {
          cout << bit;
     }
     cout << endl;

     correctErrors(const_cast<vector<int> &>(receivedData));
}

int main()
{
     string inputData;

     // Sender side
     cout << "Enter input data string (0s and 1s): ";
     cin >> inputData;

     // Convert input string to vector of integers
     vector<int> inputBits;
     for (char bit : inputData)
     {
          inputBits.push_back(bit - '0');
     }

     vector<int> sentData = generateHammingCode(inputBits);
     cout << "Sent data string: ";
     for (int bit : sentData)
     {
          cout << bit;
     }
     cout << endl;

     // Receiver side
     vector<int> receivedData = sentData;
     introduceError(receivedData);

     receiveData(receivedData);

     return 0;
}