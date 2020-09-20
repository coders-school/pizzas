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
    StrictMock<TimeMock> mt;
    Pizzeria pizzeria = Pizzeria("dummyName", mt);
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
    EXPECT_CALL(mt, sleep_for(minutes(0))).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(mt, sleep_for(minutes(1))).Times(1);

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

TEST_F(PizzeriaTest, calculateOrderLikeInMainForStubPizzaAndTwoMockPizza) {
    // Given
    PizzaStub stubPizza{"stubPizza"};
    StrictMock<PizzaMock> strictMockPizza{};
    NiceMock<PizzaMock> niceMockPizza{};

    Pizzas pizzas = {&stubPizza, &strictMockPizza, &niceMockPizza};

    constexpr double nicePizzaPrice = 18.0;
    constexpr double strictPizzaPrice = 12.5;
    constexpr char nicePizzaName[] = "nicePizza";
    constexpr char strictPizzaName[] = "StrictPizza";
    constexpr minutes niceBakingTime{2};
    constexpr minutes strictBakingTime{3};

    EXPECT_CALL(mt, sleep_for(minutes(1))).Times(1);
    EXPECT_CALL(mt, sleep_for(minutes(2))).Times(1);
    EXPECT_CALL(mt, sleep_for(minutes(3))).Times(1);

    EXPECT_CALL(niceMockPizza, getName()).WillOnce(Return(nicePizzaName));
    EXPECT_CALL(niceMockPizza, getPrice()).WillOnce(Return(nicePizzaPrice));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillOnce(Return(niceBakingTime));

    EXPECT_CALL(strictMockPizza, getName()).WillOnce(Return(strictPizzaName));
    EXPECT_CALL(strictMockPizza, getPrice()).WillOnce(Return(strictPizzaPrice));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillOnce(Return(strictBakingTime));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then
    ASSERT_EQ(nicePizzaPrice + strictPizzaPrice, price);
}
