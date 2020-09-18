#include <gtest/gtest.h>
#include <string>

#include "mocks/PizzaMock.hpp"
#include "../src/Pizzeria.hpp"
#include "../src/Margherita.hpp"
#include "../src/Funghi.hpp"
#include "mocks/DummyTimer.hpp"
#include "mocks/MockTimer.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test
{
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
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(*mock, getBakingTime).Times(1);
    EXPECT_CALL(mockTimer, sleepFor).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);

    delete mock;
}

TEST_F(PizzeriaTest, orderOneStubAndTwoMocks) {
    // Given
    PizzaStub* stubPizza = new PizzaStub{"stub"};
    StrictMock<PizzaMock>* strictMockPizza = new StrictMock<PizzaMock>{};
    NiceMock<PizzaMock>* niceMockPizza = new NiceMock<PizzaMock>{};

    Pizzas pizzas = {stubPizza, strictMockPizza, niceMockPizza};

    EXPECT_CALL(*strictMockPizza, getName()).WillOnce(Return("scrict_mock"));
    EXPECT_CALL(*strictMockPizza, getBakingTime()).WillOnce(Return(minutes(1)));
    EXPECT_CALL(*strictMockPizza, getPrice()).WillOnce(Return(30.0));

    EXPECT_CALL(*niceMockPizza, getName()).WillOnce(Return("nice_mock"));
    EXPECT_CALL(*niceMockPizza, getBakingTime()).WillOnce(Return(minutes(1)));
    EXPECT_CALL(*niceMockPizza, getPrice()).WillOnce(Return(35.0));

    EXPECT_CALL(mockTimer, sleepFor).Times(3);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(65, price);

    delete stubPizza;
    delete strictMockPizza;
    delete niceMockPizza;
}
