#include <gtest/gtest.h>
#include <string>

#include "../src/Funghi.hpp"
#include "../src/Margherita.hpp"
#include "../src/Pizzeria.hpp"
#include "mocks/MockTimer.hpp"
#include "mocks/PizzaMock.hpp"

using namespace std;
using namespace ::testing;

constexpr minutes mockBakingTime = minutes(10);
constexpr minutes strictBakingTime = minutes(12);
constexpr minutes niceBakingTime = minutes(16);

constexpr double mockPizzaPrice = 40;
constexpr double strictMockPizzaPrice = 30;
constexpr double niceMockPizzaPrice = 35;

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<MockTimer> mockTimer;
    Pizzeria pizzeria = Pizzeria("dummyName", mockTimer);
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

    // When
    EXPECT_CALL(mockTimer, sleepFor).Times(1);
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};

    // When
    EXPECT_CALL(mockTimer, sleepFor).Times(1);
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{   
    // Given
    NaggyMock<PizzaMock>* mock = new NaggyMock<PizzaMock>{};
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getName()).WillOnce(Return("naggy_mock"));
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(mockPizzaPrice));
    EXPECT_CALL(*mock, getBakingTime).WillOnce(Return(mockBakingTime));
    EXPECT_CALL(mockTimer, sleepFor(mockBakingTime)).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(mockPizzaPrice, price);

    delete mock;
}

TEST_F(PizzeriaTest, orderOneStubAndTwoMocks) {
    // Given
    PizzaStub* stubPizza = new PizzaStub{"stub"};
    StrictMock<PizzaMock>* strictMockPizza = new StrictMock<PizzaMock>{};
    NiceMock<PizzaMock>* niceMockPizza = new NiceMock<PizzaMock>{};

    Pizzas pizzas = {stubPizza, strictMockPizza, niceMockPizza};

    EXPECT_CALL(*strictMockPizza, getName()).WillOnce(Return("scrict_mock"));
    EXPECT_CALL(*strictMockPizza, getBakingTime()).WillOnce(Return(strictBakingTime));
    EXPECT_CALL(*strictMockPizza, getPrice()).WillOnce(Return(strictMockPizzaPrice));

    EXPECT_CALL(*niceMockPizza, getName()).WillOnce(Return("nice_mock"));
    EXPECT_CALL(*niceMockPizza, getBakingTime()).WillOnce(Return(niceBakingTime));
    EXPECT_CALL(*niceMockPizza, getPrice()).WillOnce(Return(niceMockPizzaPrice));

    EXPECT_CALL(mockTimer, sleepFor(stubPizza->getBakingTime())).Times(1);
    EXPECT_CALL(mockTimer, sleepFor(strictBakingTime)).Times(1);
    EXPECT_CALL(mockTimer, sleepFor(niceBakingTime)).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(strictMockPizzaPrice + niceMockPizzaPrice, price);

    delete stubPizza;
    delete strictMockPizza;
    delete niceMockPizza;
}
