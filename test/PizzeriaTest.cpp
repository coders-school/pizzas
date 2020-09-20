#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
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
    EXPECT_CALL(timerMock, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(timerMock, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock) {
    PizzaMock mock{};
    Pizzas pizzas = {&mock};
    constexpr double mockPizzaPrice = 40.0;
    EXPECT_CALL(mock, getPrice()).WillOnce(Return(mockPizzaPrice));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(mockPizzaPrice, price);
}

TEST_F(PizzeriaTest, orderTwoPizzaMockAndOnePizzaStub) {
    // Given
    constexpr double strictPizzaPrice = 15.0;
    constexpr double nicePizzaPrice = 20.0;
    constexpr char strictPizzaName[] = "strictPizza";
    constexpr char nicePizzaName[] = "nicePizza";
    constexpr minutes strictPizzaTime{12};
    constexpr minutes nicePizzaTime{14};
    PizzaStub stubPizza{"stub"};
    StrictMock<PizzaMock> strictMockPizza{};
    NiceMock<PizzaMock> niceMockPizza{};
    Pizzas pizzas = {&stubPizza, &strictMockPizza, &niceMockPizza};

    EXPECT_CALL(strictMockPizza, getName()).WillOnce(Return(strictPizzaName));
    EXPECT_CALL(strictMockPizza, getPrice()).WillOnce(Return(strictPizzaPrice));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillOnce(Return(strictPizzaTime));

    EXPECT_CALL(niceMockPizza, getName()).WillOnce(Return(nicePizzaName));
    EXPECT_CALL(niceMockPizza, getPrice()).WillOnce(Return(nicePizzaPrice));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillOnce(Return(nicePizzaTime));

    EXPECT_CALL(timerMock, sleep_for(strictPizzaTime)).Times(1);
    EXPECT_CALL(timerMock, sleep_for(nicePizzaTime)).Times(1);
    EXPECT_CALL(timerMock, sleep_for(stubPizza.getBakingTime())).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then
    ASSERT_EQ(strictPizzaPrice + nicePizzaPrice, price);
}
