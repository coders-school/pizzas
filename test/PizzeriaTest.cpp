#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "mocks/PizzaMock.hpp"
#include "mocks/TimeMock.hpp"

using namespace std;
using namespace ::testing;

constexpr double niceMockPizzaPrice = 35.0;
constexpr int niceMockPizzaBakingTime = 5;
constexpr double strictMockPizzaPrice = 25.0;
constexpr int strictMockPizzaBakingTime = 8;

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
    EXPECT_CALL(tm, sleep_for(_));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(tm, sleep_for(_));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock) {
    // Given
    PizzaMock* mock = new PizzaMock{"mock", 10, minutes(0)};
    Pizzas pizzas = {mock};
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(40.0));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);

    delete mock;
}

TEST_F(PizzeriaTest, orderStubAndTwoMockPizzas) {
    // Given
    StrictMock<PizzaMock>* strict_mock = new StrictMock<PizzaMock>{"strict", 1, minutes(1)};
    NiceMock<PizzaMock>* nice_mock = new NiceMock<PizzaMock>{"nice", 2, minutes(3)};
    PizzaStub ps("STUB");
    Pizzas pizzas = {&ps, strict_mock, nice_mock};
    EXPECT_CALL(*strict_mock, getPrice()).WillRepeatedly(Return(strictMockPizzaPrice));
    EXPECT_CALL(*strict_mock, getName());
    EXPECT_CALL(*strict_mock, getBakingTime());
    EXPECT_CALL(*nice_mock, getPrice()).WillOnce(Return(niceMockPizzaPrice));
    EXPECT_CALL(tm, sleep_for(_)).Times(2);
    EXPECT_CALL(tm, sleep_for(ps.getBakingTime()));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    ASSERT_EQ(price, 30);

    delete strict_mock;
    delete nice_mock;
}
