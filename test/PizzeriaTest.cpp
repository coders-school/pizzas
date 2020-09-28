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
    StrictMock<TimerMock> timerMock;
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
    EXPECT_CALL(timerMock, sleep_for(_)).Times(1);
    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(timerMock, sleep_for(_)).Times(1);
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
    const std::string stubPizzaName{"hawaii"};
    constexpr double stubPrice = 10.0;
    constexpr minutes stubBakingTime = minutes(5);

    const std::string strictPizzaName{"americana"};
    constexpr double strictPrice = 30.0;
    constexpr minutes strictBakingTime = minutes(10);

    const std::string nicePizzaName{"inferno"};
    constexpr double nicePrice = 50.0;
    constexpr minutes niceBakingTime = minutes(20);

    StrictMock<PizzaMock> strict;
    NiceMock<PizzaMock> nice;
    PizzaStub stub{stubPizzaName};

    EXPECT_CALL(strict, getName()).WillRepeatedly(Return(strictPizzaName));
    EXPECT_CALL(strict, getPrice()).WillRepeatedly(Return(strictPrice));
    EXPECT_CALL(strict, getBakingTime()).WillRepeatedly(Return(strictBakingTime));

    EXPECT_CALL(nice, getName()).WillRepeatedly(Return(nicePizzaName));
    EXPECT_CALL(nice, getPrice()).WillRepeatedly(Return(nicePrice));
    EXPECT_CALL(nice, getBakingTime()).WillRepeatedly(Return(niceBakingTime));

    EXPECT_CALL(timerMock, sleep_for(strictBakingTime));
    EXPECT_CALL(timerMock, sleep_for(niceBakingTime));
    EXPECT_CALL(timerMock, sleep_for(stubBakingTime));

    Pizzas pizzas{&stub, &strict, &nice};
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    constexpr double expectedPrice = strictPrice + nicePrice + stubPrice;

    EXPECT_EQ(price, expectedPrice);
}
