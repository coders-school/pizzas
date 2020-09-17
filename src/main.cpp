#include "Margherita.hpp"
#include "Funghi.hpp"
#include "Pizzeria.hpp"
#include "ThreadTimer.hpp"

int main()
{
    ThreadTimer tt;
    Pizzeria bravo("Bravo Pizza", tt);

    Pizza* pm = new Margherita{25.0};
    Pizza* pf = new Funghi{30.0};
    Pizzas pizzas = {pm, pf};

    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    delete pm;
    delete pf;

    return 0;
}
