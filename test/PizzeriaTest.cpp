#include <gtest/gtest.h>

#include <string>

#include "mocks/DummyTimer.hpp"
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
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

TEST(PizzeriaTestMain, shouldCalculateOrderLikeInMain){
    // Given
    constexpr double mock1Price = 5.0;
    constexpr double mock2Price = 4.0;
    constexpr char mock1Name[] = "Pizza mock 1";
    constexpr char mock2Name[] = "Pizza mock 2";
    constexpr minutes mock1BakingTime{10};
    constexpr minutes mock2BakingTime{5};

    StrictMock<TimeMock> tm;
    Pizzeria bravo("Bravo Pizza", tm);
    StrictMock<PizzaMock> pm1;
    NiceMock<PizzaMock> pm2;
    Pizzas pizzas = {new PizzaStub{"stub"}, &pm1, &pm2};

    EXPECT_CALL(pm1, getPrice()).WillOnce(Return(mock1Price));
    EXPECT_CALL(pm1, getName()).WillOnce(Return(mock1Name));
    EXPECT_CALL(pm1, getBakingTime()).WillOnce(Return(mock1BakingTime));
    EXPECT_CALL(pm2, getPrice()).WillOnce(Return(mock2Price));
    EXPECT_CALL(pm2, getName()).WillOnce(Return(mock2Name));
    EXPECT_CALL(pm2, getBakingTime()).WillOnce(Return(mock2BakingTime));
    EXPECT_CALL(tm, sleep_for).Times(3);

    // When
    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    // Then
    ASSERT_EQ(price, mock1Price + mock2Price);
}
