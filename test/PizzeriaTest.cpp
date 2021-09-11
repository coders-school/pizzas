#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/PizzaMock.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test {
public:
    Pizzeria pizzeria = Pizzeria("dummyName");
};

TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55) {
    // Given
    Pizzas pizzas = {std::make_shared<Margherita>(25.0), std::make_shared<Funghi>(30.0)};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza) {
    // Given
    Pizzas pizzas = {std::make_shared<PizzaDummy>()};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {std::make_shared<PizzaStub>("STUB")};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock) {
    // Given
    std::shared_ptr<PizzaMock> mock = std::make_shared<PizzaMock>();
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(40.0));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);
}
