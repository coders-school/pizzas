#include "Funghi.hpp"

Funghi::Funghi(double price)
    : Pizza("Funghi", price, minutes(4))
{}

double Funghi::getPrice() const
{
    return 30.0;
}
