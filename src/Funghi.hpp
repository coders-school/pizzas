#pragma once
#include "Pizza.hpp"

class Funghi : public Pizza
{
public:
    Funghi() = delete;
    Funghi(double price);
    virtual double getPrice() const override;
};
