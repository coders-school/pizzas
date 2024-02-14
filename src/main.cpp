#include "Margherita.hpp"
#include "Funghi.hpp"
#include "Pizzeria.hpp"

#include <iostream>

int main()
{
    Pizzeria bravo("Bravo Pizza");
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    std::cout << "Price: " << price << std::endl;

    return 0;
}
