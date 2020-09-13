#include <gtest/gtest.h>

#include <string>

#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/DummyTimer.hpp"
#include "mocks/PizzaMock.hpp"
#include "mocks/TimerMock.hpp"

using namespace std;
using namespace ::testing;

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<TimerMock> timerMock{};
    Pizzeria pizzeria = Pizzeria("dummyName", timerMock);
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
    EXPECT_CALL(timerMock, sleepFor(minutes(0))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(timerMock, sleepFor(minutes(1))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock) {
    // Given
    PizzaMock mock{};
    Pizzas pizzas = {&mock};
    EXPECT_CALL(mock, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(mock, getName()).WillOnce(Return(""));
    EXPECT_CALL(mock, getBakingTime()).WillOnce(Return(minutes(0)));
    EXPECT_CALL(timerMock, sleepFor(minutes(0))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);
}

TEST_F(PizzeriaTest, calculatePriceFor3PizzasStubAndMock) {
    // Given
    NiceMock<PizzaMock> capriciosaMock{};
    StrictMock<PizzaMock> hawaiiMock{};
    Pizzas pizzas = {new PizzaStub{"Stub"}, &capriciosaMock, &hawaiiMock};

    EXPECT_CALL(timerMock, sleepFor(minutes(1))).Times(1);
    EXPECT_CALL(capriciosaMock, getPrice()).WillOnce(Return(22.0));
    EXPECT_CALL(capriciosaMock, getName()).WillOnce(Return("Capriciosa"));
    EXPECT_CALL(capriciosaMock, getBakingTime()).WillOnce(Return(minutes(3)));
    EXPECT_CALL(timerMock, sleepFor(minutes(3))).Times(1);
    EXPECT_CALL(hawaiiMock, getPrice()).WillOnce(Return(20.0));
    EXPECT_CALL(hawaiiMock, getName()).WillOnce(Return("Hawaii"));
    EXPECT_CALL(hawaiiMock, getBakingTime()).WillOnce(Return(minutes(4)));
    EXPECT_CALL(timerMock, sleepFor(minutes(4))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(52, price);
}
