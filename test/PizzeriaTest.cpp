#include <gtest/gtest.h>
#include <string>
#include "mocks/PizzaMock.hpp"
#include "mocks/TimerMock.hpp"
#include "Pizzeria.hpp"
#include "Margherita.hpp"
#include "Funghi.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test
{
public:
    StrictMock<TimerMock> timerMock{};
    Pizzeria pizzeria = Pizzeria("dummyName", timerMock); 
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
    EXPECT_CALL(timerMock, sleep_for(minutes(0))).Times(1);
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(timerMock, sleep_for(minutes(1))).Times(1);
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{   
    // Given
    PizzaMock mock{};
    Pizzas pizzas = {&mock};
    EXPECT_CALL(mock, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(mock, getName()).WillOnce(Return(""));
    EXPECT_CALL(mock, getBakingTime()).WillOnce(Return(minutes(0)));
    EXPECT_CALL(timerMock, sleep_for(minutes(0))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);

}

TEST_F(PizzeriaTest, calculatePriceFor3PizzasOrder)
{   
    // Give
    StrictMock<PizzaMock> funghiMock{};
    NiceMock<PizzaMock> margheritaMock{};
    Pizzas pizzas = {new PizzaStub{"STUB"},  &funghiMock, &margheritaMock};

    EXPECT_CALL(funghiMock, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(funghiMock, getName()).WillOnce(Return("Funghi"));
    EXPECT_CALL(funghiMock, getBakingTime()).WillOnce(Return(minutes(5)));
    EXPECT_CALL(margheritaMock, getPrice()).WillOnce(Return(25.0));
    EXPECT_CALL(margheritaMock, getName()).WillOnce(Return("Margherita"));
    EXPECT_CALL(margheritaMock, getBakingTime()).WillOnce(Return(minutes(9))); 
    EXPECT_CALL(timerMock, sleep_for(minutes(1))).Times(1);
    EXPECT_CALL(timerMock, sleep_for(minutes(5))).Times(1);
    EXPECT_CALL(timerMock, sleep_for(minutes(9))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then
    ASSERT_EQ(75, price);
}
