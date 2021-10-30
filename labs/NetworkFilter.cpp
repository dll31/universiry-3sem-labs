#include "NetworkFilter.h"


bool NetworkFilter::searchByInRepair(const Pipe& p, bool underRepair)
{
    return p.inRepair == underRepair;
}


bool NetworkFilter::searchByPercentDisabledWorkshops(Compressor_station& cs, double percent)
{
    double countWorkshops = cs.getcountWorkshops();
    double countDisabledWorkshops = countWorkshops - cs.getCountWorkedWorkshops();
    
    double csPercentDisabledWorkshops = countDisabledWorkshops / countWorkshops * 100;

    return csPercentDisabledWorkshops >= percent;
}