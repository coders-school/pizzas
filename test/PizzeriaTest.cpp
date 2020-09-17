#include <gtest/gtest.h>
#include <string>

#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"

#include "mocks/PizzaMock.hpp"
#include "mocks/TimerMock.hpp"

using namespace std;
using namespace ::testing;

constexpr double niceMockPizzaPrice = 35.0;
constexpr int niceMockPizzaBakingTime = 5;
constexpr double strictMockPizzaPrice = 25.0;
constexpr int strictMockPizzaBakingTime = 8;

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<TimerMock> dt;
    Pizzeria pizzeria = Pizzeria("dummyName", dt);
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
    EXPECT_CALL(dt, sleep_for(_));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(dt, sleep_for(_));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock) {
    // Given
    NiceMock<PizzaMock> mock{};
    Pizzas pizzas = {&mock};
    EXPECT_CALL(mock, getPrice()).WillOnce(Return(40.0));
    EXPECT_CALL(dt, sleep_for(_));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(40, price);
}

TEST_F(PizzeriaTest, orderingDifferentPizzasMainSimulator) {
    //Given
    std::shared_ptr<PizzaStub> stubPizza = std::make_shared<PizzaStub>("DeliciouStubPizza");
    NiceMock<PizzaMock> niceMockPizza{};
    StrictMock<PizzaMock> strictMockPizza{};

    Pizzas pizzas = {stubPizza.get(), &niceMockPizza, &strictMockPizza};

    EXPECT_CALL(niceMockPizza, getPrice()).WillRepeatedly(Return(niceMockPizzaPrice));
    EXPECT_CALL(niceMockPizza, getName()).WillRepeatedly(Return("TastyNiceMockPizza"));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillRepeatedly(Return(minutes(niceMockPizzaBakingTime)));

    EXPECT_CALL(strictMockPizza, getPrice()).WillRepeatedly(Return(strictMockPizzaPrice));
    EXPECT_CALL(strictMockPizza, getName()).WillRepeatedly(Return("YummyStrictMockPizza"));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillRepeatedly(Return(minutes(strictMockPizzaBakingTime)));

    EXPECT_CALL(dt, sleep_for(stubPizza->getBakingTime()));
    EXPECT_CALL(dt, sleep_for(minutes(niceMockPizzaBakingTime)));
    EXPECT_CALL(dt, sleep_for(minutes(strictMockPizzaBakingTime)));

    //When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    //Then
    ASSERT_EQ(70, price);
}
