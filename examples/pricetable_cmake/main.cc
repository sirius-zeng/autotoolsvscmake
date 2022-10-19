#include <iostream>
#include "PriceTable.h"

int main(int argc, char **argv)
{
    if (argc < 2){
        std::cout << "Usage: PriceTable basePrice" << std::endl;
        return 0;
    }

    double basePrice = atof(argv[1]);
    std::cout << "Base price is " << basePrice << std::endl;

    InitPriceTable();
    UpdatePriceTable(basePrice);
    PrintPriceTable();
    DestroyPriceTable();

    return 0;
}