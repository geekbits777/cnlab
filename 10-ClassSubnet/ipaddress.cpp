#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Function to determine the class of the IP address in Classful notation
char findClass(const string &ipAddress)
{
     int firstOctet = stoi(ipAddress.substr(0, ipAddress.find('.')));
     if (firstOctet >= 1 && firstOctet <= 126)
     {
          return 'A';
     }
     else if (firstOctet >= 128 && firstOctet <= 191)
     {
          return 'B';
     }
     else if (firstOctet >= 192 && firstOctet <= 223)
     {
          return 'C';
     }
     else if (firstOctet >= 224 && firstOctet <= 239)
     {
          return 'D';
     }
     else if (firstOctet >= 240 && firstOctet <= 255)
     {
          return 'E';
     }
     else
     {
          return 'U'; // Unknown class
     }
}

// Function to calculate the subnet mask based on CIDR notation
string calculateSubnetMask(int cidr)
{
     int fullOctets = cidr / 8;
     int remainderBits = cidr % 8;

     string subnetMask = "";
     for (int i = 0; i < fullOctets; ++i)
     {
          subnetMask += "255.";
     }

     int lastOctet = 0;
     for (int i = 0; i < remainderBits; ++i)
     {
          lastOctet |= (1 << (7 - i));
     }
     subnetMask += to_string(lastOctet);

     return subnetMask;
}

int main()
{
     string ipAddress;
     cout << "Enter an IP address (e.g., 192.168.1.1): ";
     cin >> ipAddress;

     cout << "Choose notation type: \n";
     cout << "1. Classful Notation\n";
     cout << "2. CIDR Notation\n";
     int choice;
     cout << "Enter your choice (1 or 2): ";
     cin >> choice;

     if (choice == 1)
     {
          // Classful Notation
          char ipClass = findClass(ipAddress);
          cout << "Class: " << ipClass << endl;

          // Determine subnet mask based on class
          string subnetMask;
          if (ipClass == 'A')
          {
               subnetMask = "255.0.0.0";
          }
          else if (ipClass == 'B')
          {
               subnetMask = "255.255.0.0";
          }
          else if (ipClass == 'C')
          {
               subnetMask = "255.255.255.0";
          }
          else
          {
               cout << "Subnetting not applicable for Class " << ipClass << endl;
               return 0;
          }
          cout << "Subnet Mask: " << subnetMask << endl;

          // Determine subnet IP address range
          // Assume the first IP in the subnet is the network ID, and the last IP is the broadcast ID
          string networkID = ipAddress;
          networkID = networkID.substr(0, networkID.rfind('.') + 1) + "0";

          string broadcastID = ipAddress;
          broadcastID = broadcastID.substr(0, broadcastID.rfind('.') + 1) + "255";

          cout << "Subnet IP Address Range:\n";
          cout << "Network ID: " << networkID << endl;
          cout << "Broadcast ID: " << broadcastID << endl;
          cout << "Host IP Range: " << networkID.substr(0, networkID.size() - 1) + "1"
               << " to "
               << broadcastID.substr(0, broadcastID.size() - 1) + "254" << endl;
     }
     else if (choice == 2)
     {
          // CIDR Notation
          int cidr;
          cout << "Enter CIDR notation (e.g., 24 for /24): ";
          cin >> cidr;

          // Determine class based on CIDR notation
          char ipClass;
          if (cidr >= 1 && cidr <= 7)
          {
               ipClass = 'A';
          }
          else if (cidr >= 8 && cidr <= 15)
          {
               ipClass = 'B';
          }
          else if (cidr >= 16 && cidr <= 23)
          {
               ipClass = 'C';
          }
          else
          {
               cout << "CIDR notation not applicable for Class " << ipClass << endl;
               return 0;
          }
          cout << "Class: " << ipClass << endl;

          // Determine subnet mask based on CIDR notation
          string subnetMask = calculateSubnetMask(cidr);
          cout << "Subnet Mask: " << subnetMask << endl;

          // Determine subnet IP address range
          string networkID = ipAddress;
          networkID = networkID.substr(0, networkID.rfind('.') + 1) + "0";

          string broadcastID = ipAddress;
          broadcastID = broadcastID.substr(0, broadcastID.rfind('.') + 1) + "255";

          cout << "Subnet IP Address Range:\n";
          cout << "Network ID: " << networkID << endl;
          cout << "Broadcast ID: " << broadcastID << endl;
          cout << "Host IP Range: " << networkID.substr(0, networkID.size() - 1) + "1"
               << " to "
               << broadcastID.substr(0, broadcastID.size() - 1) + "254" << endl;
     }
     else
     {
          cout << "Invalid choice. Please choose 1 or 2.\n";
     }

     return 0;
}
