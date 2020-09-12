#include <gtest/gtest.h>
#include <string>
//#include "mocks/DummyTimer.hpp"
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
    //DummyTimer dt;
    //Pizzeria pizzeria = Pizzeria("dummyName", dt);
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
