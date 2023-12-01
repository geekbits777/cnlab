#include <iostream>
#include <string>
using namespace std;

string xor1(string a, string b)
{
     string result = "";
     int n = b.length();
     for (int i = 1; i < n; i++)
     {
          if (a[i] == b[i])
               result += "0";
          else
               result += "1";
     }
     return result;
}

string mod2div(string dividend, string divisor)
{
     int pick = divisor.length();
     string tmp = dividend.substr(0, pick);
     int n = dividend.length();
     while (pick < n)
     {
          if (tmp[0] == '1')
               tmp = xor1(divisor, tmp) + dividend[pick];
          else
               tmp = xor1(string(pick, '0'), tmp) + dividend[pick];
          pick++;
     }
     if (tmp[0] == '1')
          tmp = xor1(divisor, tmp);
     else
          tmp = xor1(string(pick, '0'), tmp);
     return tmp;
}

string sender(string data, string key)
{
     int k = key.length();
     string appended_data = data + string(k - 1, '0');
     string remainder = mod2div(appended_data, key);
     string sent_string = data + remainder;
     return sent_string;
}

void receiver(string sent_string, string key)
{
     string received_data = sent_string.substr(0, sent_string.length() - key.length() + 1);
     string received_remainder = mod2div(sent_string, key);
     int k = key.length();
     if (received_remainder == string(k - 1, '0'))
          cout << "Received Data: " << received_data << endl
               << "No errors detected." << endl;
     else
          cout << "Received Data: " << received_data << endl
               << "Errors detected." << endl;
}

int main()
{
     string data, key;
     cout << "Enter the data: ";
     cin >> data;
     cout << "Enter the key: ";
     cin >> key;
     string sent_string = sender(data, key);
     cout << "Sent String: " << sent_string << endl;
     receiver(sent_string, key);
     
     return 0;
}