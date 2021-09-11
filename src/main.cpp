#include <memory>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"

int main() {
    Pizzeria bravo("Bravo Pizza");
    Pizzas pizzas = {std::make_shared<Margherita>(25.0), std::make_shared<Funghi>(30.0)};

    auto orderId = bravo.makeOrder(pizzas);
    [[maybe_unused]] auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    return 0;
}
