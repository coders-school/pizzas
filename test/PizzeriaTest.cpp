#include <gtest/gtest.h>
#include <string>

#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"

#include "mocks/PizzaMock.hpp"
#include "mocks/TimerMock.hpp"

using namespace std;
using namespace ::testing;
using ::testing::Return;

struct PizzeriaTest : public ::testing::Test {
   public:
    StrictMock<TimerMock> mock;
    Pizzeria pizzeria = Pizzeria("dummyName", mock);
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
    EXPECT_CALL(mock, sleep_for(_)).Times(1);
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(mock, sleep_for(_)).Times(1);
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

TEST_F(PizzeriaTest, completeOrderWithStubPizzaAndTwoMockPizzas) {
    StrictMock<PizzaMock> strict;
    NiceMock<PizzaMock> nice;
    PizzaStub stub{"hawaii"};
    EXPECT_CALL(strict, getName())
        .WillOnce(Return("americana"));
    EXPECT_CALL(strict, getPrice())
        .WillOnce(Return(30));
    EXPECT_CALL(strict, getBakingTime())
        .WillOnce(Return(minutes(10)));
    EXPECT_CALL(nice, getName())
        .WillOnce(Return("inferno"));
    EXPECT_CALL(nice, getPrice())
        .WillOnce(Return(50));
    EXPECT_CALL(nice, getBakingTime())
        .WillOnce(Return(minutes(20)));
    EXPECT_CALL(mock, sleep_for(_))
        .Times(3);
    Pizzas pizzas{&stub, &strict, &nice};
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, BrokenTest) {
    EXPECT_EQ(1, 0);
}
