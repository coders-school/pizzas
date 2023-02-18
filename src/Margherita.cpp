#include "Margherita.hpp"

Margherita::Margherita(double price)
    : Pizza("Margherita", price, minutes(3))
{}


double Margherita::getPrice() const
{
    return 25.0;
}