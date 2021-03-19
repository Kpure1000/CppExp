#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string inStr;
    cin >> inStr;
    vector<char> outStr;
    vector<int> outNum;
    for (auto &ch : inStr)
    {
        if (ch == 'n' || ch == 'w')
        {
            outStr.push_back(ch);
        }
    }
    cout << "Size: " << outStr.size() << endl;
    for (int i = 0, len = outStr.size(); i < len; i += 9)
    {
        int newNum = 0;
        for (int j = 0; i + j < len && j < 9; j++)
        {
            newNum <<= 1;
            newNum += outStr[i + j] == 'n' ? 0 : 1;
        }
        outNum.push_back(newNum);
    }
    cout << "[";
    for (auto &it : outNum)
    {
        cout << "0x" << hex << it << ", ";
    }
    cout << "]\n";
}