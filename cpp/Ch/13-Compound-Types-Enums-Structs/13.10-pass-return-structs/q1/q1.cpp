#include <iostream>

struct Advertising
{
    int adsShown {};
    double clickedPercentage {};
    double averageEarningsPerClick {};
};

Advertising getAdvertising()
{
    Advertising temp {};
    std::cout << "How many ads were shown today? ";
    std::cin >> temp.adsShown;
    std::cout << "What percentage of users clicked on an ad? ";
    std::cin >> temp.clickedPercentage;
    std::cout << "What was the average earnings per clicked ad? ";
    std::cin >> temp.averageEarningsPerClick;

    return temp;
}

void printAdvertising(const Advertising& ad)
{
    std::cout << "Number of ads shown: " << ad.adsShown << '\n';
    std::cout << "Click through rate: " << ad.clickedPercentage << '\n';
    std::cout << "Average earnings per click: $" << ad.averageEarningsPerClick << '\n';

    std::cout << "Total Earnings: $" <<
        (ad.adsShown * ad.clickedPercentage / 100 * ad.averageEarningsPerClick) << '\n';
}

int main()
{
    Advertising ad{ getAdvertising() };
    printAdvertising(ad);

    return 0;
}
