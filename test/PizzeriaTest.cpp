#include <gtest/gtest.h>
#include <string>
#include "mocks/MockTimer.hpp"
#include "mocks/PizzaMock.hpp"
#include "Pizzeria.hpp"
#include "Margherita.hpp"
#include "Funghi.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test
{
public:
    StrictMock<MockTimer> mockTimer {};
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
    EXPECT_CALL(mockTimer, sleep_for(minutes(0))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(mockTimer, sleep_for(minutes(1))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{   
    // Given
    NiceMock<PizzaMock> mock{};
    Pizzas pizzas = {&mock};
    EXPECT_CALL(mock, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(mock, getName()).WillOnce(Return(""));
    EXPECT_CALL(mock, getBakingTime()).WillOnce(Return(minutes(0)));
    EXPECT_CALL(mockTimer, sleep_for(minutes(0))).Times(1);
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then
    ASSERT_EQ(40, price);
}

TEST_F(PizzeriaTest, completeOrderForOneStubAndTwoMockPizzas) {
    // Given
    PizzaStub StubPizza{"STUB"};
    StrictMock<PizzaMock> funghiMockPizza;
    NiceMock<PizzaMock> margheritaMockPizza;
    Pizzas pizzas{&StubPizza, &funghiMockPizza, &margheritaMockPizza};

    EXPECT_CALL(funghiMockPizza, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(funghiMockPizza, getName()).WillOnce(Return("Funghi"));
    EXPECT_CALL(funghiMockPizza, getBakingTime()).WillOnce(Return(minutes(5)));
    EXPECT_CALL(margheritaMockPizza, getPrice()).WillOnce(Return(25.0));
    EXPECT_CALL(margheritaMockPizza, getName()).WillOnce(Return("Margherita"));
    EXPECT_CALL(margheritaMockPizza, getBakingTime()).WillOnce(Return(minutes(9))); 
    EXPECT_CALL(mockTimer, sleep_for(minutes(1))).Times(1);
    EXPECT_CALL(mockTimer, sleep_for(minutes(5))).Times(1);
    EXPECT_CALL(mockTimer, sleep_for(minutes(9))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then
    ASSERT_EQ(75, price);
}
