#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/MockTimer.hpp"
#include "mocks/PizzaMock.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<MockTimer> mockTimer;
    Pizzeria pizzeria = Pizzeria("dummyName", mockTimer);
};

struct PizzeriaTestMain : public ::testing::Test {
    StrictMock<MockTimer> mockTimer;
};

TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55)
{
    // Given
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza)
{
    // Given
    Pizzas pizzas = {new PizzaDummy{}};
    EXPECT_CALL(mockTimer, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(mockTimer, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{
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

TEST_F(PizzeriaTestMain, shouldDuplicateMain)
{
    constexpr minutes funghiBakingTime = minutes(4);
    constexpr minutes margheritaBakingTime = minutes(3);

    constexpr double cheaperPizza = 10.99;
    constexpr double moreExpensivePizza = 250.0;

    NiceMock<PizzaMock> niceMockPizza{};
    StrictMock<PizzaMock> strictMockPizza{};

    Pizzeria bravo("Bravo Pizza", mockTimer);
    Pizzas pizzas = {new PizzaStub("Stub"), new PizzaStub("Stub2"), new PizzaStub("Stub3"), &niceMockPizza, &strictMockPizza};

    EXPECT_CALL(mockTimer, sleep_for(minutes(1))).Times(3);
    
    EXPECT_CALL(niceMockPizza, getPrice()).WillOnce(Return(cheaperPizza));
    EXPECT_CALL(niceMockPizza, getName()).WillOnce(Return("Special Margherita With More Cheese"));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillOnce(Return(margheritaBakingTime));
    EXPECT_CALL(mockTimer, sleep_for(margheritaBakingTime)).Times(1);

    EXPECT_CALL(strictMockPizza, getPrice()).WillOnce(Return(moreExpensivePizza));
    EXPECT_CALL(strictMockPizza, getName()).WillOnce(Return("Special Funghi With Olives"));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillOnce(Return(funghiBakingTime));
    EXPECT_CALL(mockTimer, sleep_for(funghiBakingTime)).Times(1);


    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);
}
