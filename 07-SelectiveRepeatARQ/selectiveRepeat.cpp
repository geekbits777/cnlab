#include <bits/stdc++.h>
using namespace std;

struct Frame
{
     int seqNumber;
     bool isAcked;
     bool isSent;
};

// Sender Function
void sender(int numFrames, vector<Frame> &senderFrames, vector<Frame> &receiverFrames)
{
     for (int i = 0; i < numFrames; i++)
     {
          senderFrames[i].seqNumber = i;
          senderFrames[i].isAcked = false;
          senderFrames[i].isSent = false;

          if (rand() % 2 == 0)
          {
               senderFrames[i].isSent = true;
               cout << "Sender: Frame " << i << " sent." << endl;
          }
     }

     for (int i = 0; i < numFrames; i++)
     {
          if (senderFrames[i].isSent)
          {
               if (rand() % 2 == 0)
               {
                    receiverFrames[i] = senderFrames[i];
                    cout << "Receiver: Frame " << i << " received." << endl;
               }
               else
               {
                    cout << "Receiver: Frame " << i << " discarded." << endl;
               }
          }
     }
}

// Receiver Function
void receiver(int numFrames, vector<Frame> &receiverFrames)
{
     for (int i = 0; i < numFrames; i++)
     {
          if (receiverFrames[i].isSent)
          {
               if (rand() % 2 == 0)
               {
                    receiverFrames[i].isAcked = true;
                    cout << "Receiver: Acknowledgment for Frame " << i << " sent." << endl;
               }
          }
     }
}

// Error Function
void introduceErrors(int numFrames, vector<Frame> &receiverFrames)
{
     for (int i = 0; i < numFrames; i++)
     {
          if (receiverFrames[i].isSent)
          {
               if (rand() % 2 == 0)
               {
                    cout << "Receiver: Frame " << i << " marked as received in error." << endl;
               }
          }
     }
}

int main()
{
     srand(time(0));

     int numFrames;
     cout << "Enter the number of frames: ";
     cin >> numFrames;

     vector<Frame> senderFrames(numFrames);
     vector<Frame> receiverFrames(numFrames);

     // Sender Function Call
     sender(numFrames, senderFrames, receiverFrames);

     // Error Function Call
     introduceErrors(numFrames, receiverFrames);

     // Receiver Function Call
     receiver(numFrames, receiverFrames);

     cout << "Sender: Resending unacknowledged frames..." << endl;
     for (int i = 0; i < numFrames; i++)
     {
          if (senderFrames[i].isSent && !receiverFrames[i].isAcked)
          {
               cout << "Sender: Frame " << i << " resent." << endl;
          }
     }

     return 0;
}