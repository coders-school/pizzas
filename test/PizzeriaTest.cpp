#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/DummyTimer.hpp"
#include "mocks/PizzaMock.hpp"
#include "mocks/TimeMock.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<TimeMock> tm;
    Pizzeria pizzeria = Pizzeria("dummyName", tm);
};

TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55) {
    // Given
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza) {
    // Given
    Pizzas pizzas = {new PizzaDummy{}};
    EXPECT_CALL(tm, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(tm, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock) {
    // Given
    PizzaMock* mock = new PizzaMock{};
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(40.0));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);

    delete mock;
}

TEST_F(PizzeriaTest, shouldCalculateOrderLikeInMainFunction) {
    // Given
    constexpr double niceMockPizzaPrice = 20.0;
    constexpr int niceMockPizaaBakingTime = 5;

    constexpr double strictMockPizzaPrice = 22.0;
    constexpr int strictMockPizaaBakingTime = 7;

    std::shared_ptr<PizzaStub> pizzaStub = std::make_shared<PizzaStub>("StubPizza");
    StrictMock<PizzaMock> strictPizza{};
    NiceMock<PizzaMock> nicePizza{};
    Pizzas pizzas = {pizzaStub.get(), &nicePizza, &strictPizza};

    EXPECT_CALL(nicePizza, getPrice()).WillRepeatedly(Return(niceMockPizzaPrice));
    EXPECT_CALL(nicePizza, getName()).WillRepeatedly(Return("NiceMockPizza"));
    EXPECT_CALL(nicePizza, getBakingTime()).WillRepeatedly(Return(minutes(niceMockPizaaBakingTime)));

    EXPECT_CALL(strictPizza, getPrice()).WillRepeatedly(Return(strictMockPizzaPrice));
    EXPECT_CALL(strictPizza, getName()).WillRepeatedly(Return("StrictMockPizza"));
    EXPECT_CALL(strictPizza, getBakingTime()).WillRepeatedly(Return(minutes(strictMockPizaaBakingTime)));

    EXPECT_CALL(tm, sleep_for(pizzaStub->getBakingTime()));
    EXPECT_CALL(tm, sleep_for(minutes(niceMockPizaaBakingTime)));
    EXPECT_CALL(tm, sleep_for(minutes(strictMockPizaaBakingTime)));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then
    ASSERT_EQ(price, strictMockPizzaPrice + niceMockPizzaPrice + pizzaStub->getPrice());
}
