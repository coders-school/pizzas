#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/DummyTimer.hpp"
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

TEST(PizzeriaTestMain, shouldCalculateOrderLikeInMainFunction){
    // Given
    constexpr double mockFirstPrice = 20.0;
    constexpr double mockSecondPrice = 25.0;
    constexpr char mockFirstName[] = "Pizza mock first";
    constexpr char mockSecondName[] = "Pizza mock second";
    constexpr minutes mockFirstBakingTime{10};
    constexpr minutes mockSecondBakingTime{5};

    StrictMock<TimeMock> tm;
    Pizzeria bravo("Bravo Pizza", tm);
    StrictMock<PizzaMock> pm1;
    NiceMock<PizzaMock> pm2;
    Pizzas pizzas = {new PizzaStub{"stub"}, &pm1, &pm2};

    EXPECT_CALL(pm1, getPrice()).WillOnce(Return(mockFirstPrice));
    EXPECT_CALL(pm1, getName()).WillOnce(Return(mockFirstName));
    EXPECT_CALL(pm1, getBakingTime()).WillOnce(Return(mockFirstBakingTime));
    EXPECT_CALL(pm2, getPrice()).WillOnce(Return(mockSecondPrice));
    EXPECT_CALL(pm2, getName()).WillOnce(Return(mockSecondName));
    EXPECT_CALL(pm2, getBakingTime()).WillOnce(Return(mockSecondBakingTime));
    EXPECT_CALL(tm, sleep_for).Times(3);

    // When
    auto orderId = bravo.makeOrder(pizzas);
    auto price = bravo.calculatePrice(orderId);
    bravo.bakePizzas(orderId);
    bravo.completeOrder(orderId);

    // Then
    ASSERT_EQ(price, mockFirstPrice + mockSecondPrice);
}
