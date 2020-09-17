#include <gtest/gtest.h>

#include <string>

#include "Funghi.hpp"
#include "Margherita.hpp"
#include "mocks/DummyTimer.hpp"
#include "mocks/PizzaMock.hpp"
#include "mocks/TimeMock.hpp"
#include "Pizzeria.hpp"




using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test
{
public:
    StrictMock<TimeMock> dt;
    Pizzeria pizzeria = Pizzeria("dummyName", dt); 
};


TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55)
{
    // Given
    Pizza* pm = new Margherita{25.0};
    Pizza* pf = new Funghi{30.0};
    Pizzas pizzas = {pm,pf};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);

    delete pm;
    delete pf;
}

TEST_F(PizzeriaTest, bakeDummyPizza)
{
    // Given
    Pizza* pd = new PizzaDummy{};
    Pizzas pizzas = {pd};
    EXPECT_CALL(dt, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);

    delete pd;
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizza* ps = new PizzaStub{"stub"};
    Pizzas pizzas = {ps};
    EXPECT_CALL(dt, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    delete ps;
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{   
    // Given
    PizzaMock mock{};
    Pizzas pizzas = {&mock};
    EXPECT_CALL(mock, getPrice()).WillOnce(Return(40.0));
    
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);

}

TEST(PizzeriaTestMain, shouldCalculateOrderLikeInMain)
{
    // Given
    const double mock1Price = 35.99;
    const string mock1Name = "PizzaM-1";
    const minutes mock1BakingTime{20};

    const double mock2Price = 40.99;
    const string mock2Name= "PizzaM-2";
    const minutes mock2BakingTime{15};

    StrictMock<TimeMock> tm;
    Pizzeria domino("Średnia hawajska dla każdego", tm);
    StrictMock<PizzaMock> pm1;
    NiceMock<PizzaMock> pm2;

    Pizza* ps = new PizzaStub{"stub"};
    Pizzas pizzas = {ps, &pm1, &pm2};

    EXPECT_CALL(pm1, getPrice()).WillOnce(Return(mock1Price));
    EXPECT_CALL(pm1, getName()).WillOnce(Return(mock1Name));
    EXPECT_CALL(pm1, getBakingTime()).WillOnce(Return(mock1BakingTime));

    EXPECT_CALL(pm2, getPrice()).WillOnce(Return(mock2Price));
    EXPECT_CALL(pm2, getName()).WillOnce(Return(mock2Name));
    EXPECT_CALL(pm2, getBakingTime()).WillOnce(Return(mock2BakingTime));

    EXPECT_CALL(tm, sleep_for).Times(3);

    // When
    auto orderId = domino.makeOrder(pizzas);
    auto price = domino.calculatePrice(orderId);
    domino.bakePizzas(orderId);
    domino.completeOrder(orderId);

    // Then
    ASSERT_EQ(price, mock1Price + mock2Price);

    delete ps;
}