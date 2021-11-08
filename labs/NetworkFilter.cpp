#include "NetworkFilter.h"


bool searchByInRepair(const Pipe& p, bool underRepair)
{
    return p.inRepair == underRepair;
}


bool searchByName(Compressor_station& item, std::string& param)
{
    return item.name == param;
}


bool searchByPercentDisabledWorkshops(Compressor_station& cs, forDisabledWorkshopsFilter & operatorStruct)
{
    double countWorkshops = cs.getcountWorkshops();
    double countDisabledWorkshops = countWorkshops - cs.getCountWorkedWorkshops();
    
    double csPercentDisabledWorkshops = countDisabledWorkshops / countWorkshops * 100;

    return (compareOperators.count(operatorStruct.op) && compareOperators[operatorStruct.op](csPercentDisabledWorkshops, operatorStruct.number));
}

void initFilter()
{
    // https://stackoverflow.com/questions/24716453/convert-string-to-operator 
    compareOperators["less"] = std::less<double>();
    compareOperators["greather"] = std::greater<double>();
    compareOperators["equal"] = std::equal_to<double>();
    compareOperators["not equal"] = std::not_equal_to<double>();
    compareOperators["greather equal"] = std::greater_equal<double>();
    compareOperators["less equal"] = std::less_equal<double>();

}


void getAvailableCompareOperators(std::vector<std::string>& ops)
{
    for (auto i : compareOperators)
        ops.push_back(i.first);
}