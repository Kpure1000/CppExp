#include <iostream>
#include <string>
#include <vector>

unsigned int code[10] = {
    0x06, 0x11, 0x09, 0x18, 0x05, 0x14, 0x0c, 0x03, 0x12, 0x0a};

const unsigned int Fuller = 0x1f;

enum WidthType
{
    FAT = 1,
    THIN = 2
};
enum FillType
{
    FILL = 3,
    VOID = 4
};

int main()
{
    std::string inStr;
    std::cin >> inStr;
    std::vector<int> outCode;
    //  starting code
    for (int i = 0; i < 4; i++)
        outCode.push_back(WidthType::THIN * (i % 2 == 0 ? FillType::FILL : FillType::VOID));
    int orgL, orgR;
    for (int i = 0; i + 1 < inStr.size(); i += 2)
    {
        orgL = code[inStr[i] - '0'];
        orgR = code[inStr[i + 1] - '0'];
        int cCode = 0x10;
        for (int j = 0; j < 5; j++)
        {
            outCode.push_back(((orgL & cCode) >> (4 - j) ? WidthType::FAT : WidthType::THIN) * FillType::FILL);
            outCode.push_back(((orgR & cCode) >> (4 - j) ? WidthType::FAT : WidthType::THIN) * FillType::VOID);
            cCode >>= 1;
        }
    }
    //  ending code
    outCode.push_back(WidthType::FAT * FillType::FILL);
    outCode.push_back(WidthType::THIN * FillType::VOID);
    outCode.push_back(WidthType::THIN * FillType::FILL);

    for (auto &it : outCode)
    {
        // std::cout << (it == (int)WidthType::FAT ? 1 : 0) << " ";
        std::cout << it << " ";
    }
    std::cout << "\nSize: " << outCode.size() << "\n";
}
