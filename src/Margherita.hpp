#pragma once
#include "Pizza.hpp"

class Margherita : public Pizza
{
public:
    Margherita() = delete;
    Margherita(double price);
};
