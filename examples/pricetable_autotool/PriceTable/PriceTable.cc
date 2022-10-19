#include <iostream>
#include "config.h"

typedef struct PriceTable{
    const char* strRatio;
    double ratio;
} PriceTable;

PriceTable table[] = {
    {"1%", 0.01},
    {"2%", 0.02},
    {"3%", 0.03},
    {"4%", 0.04},
    {"5%", 0.05},
    {"6%", 0.06},
    {"7%", 0.07},
    {"8%", 0.08},
    {"9%", 0.09},
    {"10%", 0.10},
    {"20%", 0.20},
    {"30%", 0.30},
    {"40%", 0.40},
    {"50%", 0.50},
    {"60%", 0.60},
    {"70%", 0.70},
    {"80%", 0.80}
};

static const int TABLESIZE = sizeof(table)/sizeof(PriceTable);
double pValueTable[TABLESIZE];
double nValueTable[TABLESIZE];

void InitPriceTable()
{
    for(int i=0; i<TABLESIZE; i++){
        pValueTable[i] = 0;
        nValueTable[i] = 0;
    }
}

void DestroyPriceTable()
{
    InitPriceTable();
}

void UpdatePriceTable(double price)
{
    for(int i=0; i<TABLESIZE; i++){
        pValueTable[i] = price * (1+table[i].ratio);
        nValueTable[i] = price * (1-table[i].ratio);
    }
}


void PrintPriceTable()
{
    std::cout << "Price Up:" << std::endl;
    std::cout << "************************" << std::endl;
    for(int i=0; i<TABLESIZE; i++){
        std::cout << table[i].strRatio << " : " << pValueTable[i] << std::endl;
    }
    std::cout << "************************" << std::endl;

#ifdef PRINT_NEGATIVE_TABLE
    std::cout << "Price Down:" << std::endl;
    std::cout << "************************" << std::endl;
    for(int i=0; i<TABLESIZE; i++){
        std::cout << "-" << table[i].strRatio << " : " << nValueTable[i] << std::endl;
    }
    std::cout << "************************" << std::endl;
#endif
}