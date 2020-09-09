#include <gtest/gtest.h>
#include <string>
#include "mocks/PizzaMock.hpp"
#include "mocks/TimeMock.hpp"
#include "Pizzeria.hpp"
#include "Margherita.hpp"
#include "Funghi.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test
{
public:
    StrictMock<TimeMock> timer;
    Pizzeria pizzeria = Pizzeria("dummyName", timer); 
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
    EXPECT_CALL(timer, sleep_for(minutes(0))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(timer, sleep_for(minutes(1))).Times(1);

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

TEST_F(PizzeriaTest, completeOrderWithStubPizzaAndTwoDifferentMockPizzas)
{
    // Given
    PizzaStub stubPizza{"STUB"};
    StrictMock<PizzaMock> mockPizza1{};
    NiceMock<PizzaMock> mockPizza2{};
    Pizzas pizzas = {&stubPizza, &mockPizza1, &mockPizza2};
    
    //stubPizza excepts
    EXPECT_CALL(timer, sleep_for(minutes(1))).Times(1);

    //mockPizza1 excepts
    EXPECT_CALL(mockPizza1, getPrice()).WillOnce(Return(666));
    EXPECT_CALL(mockPizza1, getName()).WillOnce(Return("FirstMock"));
    EXPECT_CALL(mockPizza1, getBakingTime()).WillOnce(Return(minutes(2)));
    EXPECT_CALL(timer, sleep_for(minutes(2))).Times(1);

    //mockPizza2 excepts
    EXPECT_CALL(mockPizza2, getPrice()).WillOnce(Return(333));
    EXPECT_CALL(mockPizza2, getName()).WillOnce(Return("SecondMock"));
    EXPECT_CALL(mockPizza2, getBakingTime()).WillOnce(Return(minutes(0)));
    EXPECT_CALL(timer, sleep_for(minutes(0))).Times(1);
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    ASSERT_GE(price, 999);
}
