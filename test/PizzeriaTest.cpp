#include <gtest/gtest.h>
#include <string>
#include "Funghi.hpp"
#include "Margherita.hpp"
#include "Pizzeria.hpp"
#include "gmock/gmock.h"
#include "mocks/PizzaMock.hpp"
#include "mocks/TimerMock.hpp"

using namespace std;
using namespace ::testing;

namespace PizzasConstValues {
const std::string strictMockPizzaName = "strictMockPizzaName";
const std::string niceMockPizzaName = "niceMockPizzaName";
const minutes strictMockPizzaBakingTime = minutes(29);
const minutes niceMockPizzaBakingTime = minutes(2);
const double strictMockPizzaPrice = 23.2;
const double niceMockPizzaPrice = 33.1;
}  // namespace PizzasConstValues

struct PizzeriaTest : public ::testing::Test {
public:
    StrictMock<TimerMock> timerMock;
    Pizzeria pizzeria = Pizzeria("dummyName", timerMock);
};

TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55) {
    // Given
    std::unique_ptr<Margherita> margherita = std::make_unique<Margherita>(25.0);
    std::unique_ptr<Funghi> funghi = std::make_unique<Funghi>(30.0);
    Pizzas pizzas = {margherita.get(), funghi.get()};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza) {
    // Given
    std::unique_ptr<PizzaDummy> pizzaDummy = std::make_unique<PizzaDummy>();
    Pizzas pizzas = {pizzaDummy.get()};
    EXPECT_CALL(timerMock, sleepFor(_));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    std::unique_ptr<PizzaStub> pizzaStub = std::make_unique<PizzaStub>("STUB");
    Pizzas pizzas = {pizzaStub.get()};
    EXPECT_CALL(timerMock, sleepFor(_));

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

TEST_F(PizzeriaTest, orderTwoPizzaMockAndOnePizzaStub) {
    std::unique_ptr<PizzaStub> stubPizza = std::make_unique<PizzaStub>("StubPizza");
    StrictMock<PizzaMock> strictMockPizza{};
    NiceMock<PizzaMock> niceMockPizza{};

    Pizzas pizzas = {stubPizza.get(), &strictMockPizza, &niceMockPizza};

    EXPECT_CALL(strictMockPizza, getName()).WillRepeatedly(Return(PizzasConstValues::strictMockPizzaName));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillRepeatedly(Return(PizzasConstValues::strictMockPizzaBakingTime));
    EXPECT_CALL(strictMockPizza, getPrice()).WillRepeatedly(Return(PizzasConstValues::strictMockPizzaPrice));
    EXPECT_CALL(niceMockPizza, getName()).WillRepeatedly(Return(PizzasConstValues::niceMockPizzaName));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillRepeatedly(Return(PizzasConstValues::niceMockPizzaBakingTime));
    EXPECT_CALL(niceMockPizza, getPrice()).WillRepeatedly(Return(PizzasConstValues::strictMockPizzaPrice));
    EXPECT_CALL(timerMock, sleepFor(stubPizza->getBakingTime()));
    EXPECT_CALL(timerMock, sleepFor(PizzasConstValues::strictMockPizzaBakingTime));
    EXPECT_CALL(timerMock, sleepFor(PizzasConstValues::niceMockPizzaBakingTime));

    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    auto price = pizzeria.calculatePrice(orderId);

    ASSERT_EQ(66.3, PizzasConstValues::strictMockPizzaPrice +
                        PizzasConstValues::niceMockPizzaPrice +
                        stubPizza->getPrice());
}