#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/MockTimer.hpp"
#include "mocks/PizzaMock.hpp"

using namespace std;
using namespace ::testing;

constexpr int sleepForOneMinute = 1;

constexpr int calledOneTime = 1;
constexpr int calledTwoTimes = 2;
constexpr int calledThreeTimes = 3;

constexpr minutes funghiBakingTime = minutes(4);
constexpr minutes margheritaBakingTime = minutes(3);

constexpr double margheritaPrice = 25;
constexpr double funghiPrice = 30;

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<MockTimer> mockTimer;
    Pizzeria pizzeria = Pizzeria("dummyName", mockTimer);
};

TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55)
{
    constexpr double expectedPrice = margheritaPrice + funghiPrice;

    // Given
    Pizzas pizzas = {new Margherita{margheritaPrice}, new Funghi{funghiPrice}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(expectedPrice, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza)
{
    // Given
    Pizzas pizzas = {new PizzaDummy{}};
    EXPECT_CALL(mockTimer, sleep_for).Times(calledOneTime);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(mockTimer, sleep_for).Times(calledOneTime);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{
    constexpr double fourtyPounds = 40;
    constexpr double expectedPrice = fourtyPounds;

    // Given
    PizzaMock* mock = new PizzaMock{};
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(fourtyPounds));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(expectedPrice, price);

    delete mock;
}

TEST_F(PizzeriaTest, shouldDuplicateMain)
{
    constexpr double pizzaStubPrice = 10;
    constexpr double cheaperPizza = 10.99;
    constexpr double moreExpensivePizza = 250.0;

    constexpr double expectedPrice = cheaperPizza + moreExpensivePizza + 3 * pizzaStubPrice;

    NiceMock<PizzaMock> niceMockPizza{};
    StrictMock<PizzaMock> strictMockPizza{};

    Pizzeria bravo("Bravo Pizza", mockTimer);
    Pizzas pizzas = {new PizzaStub("Stub"), new PizzaStub("Stub2"), new PizzaStub("Stub3"), &niceMockPizza, &strictMockPizza};

    EXPECT_CALL(mockTimer, sleep_for(minutes(sleepForOneMinute))).Times(calledThreeTimes);

    EXPECT_CALL(niceMockPizza, getPrice()).WillOnce(Return(cheaperPizza));
    EXPECT_CALL(niceMockPizza, getName()).WillOnce(Return("Special Margherita With More Cheese"));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillOnce(Return(margheritaBakingTime));
    EXPECT_CALL(mockTimer, sleep_for(margheritaBakingTime)).Times(calledOneTime);

    EXPECT_CALL(strictMockPizza, getPrice()).WillOnce(Return(moreExpensivePizza));
    EXPECT_CALL(strictMockPizza, getName()).WillOnce(Return("Special Funghi With Olives"));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillOnce(Return(funghiBakingTime));
    EXPECT_CALL(mockTimer, sleep_for(funghiBakingTime)).Times(calledOneTime);

    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    ASSERT_EQ(expectedPrice, price);
}
