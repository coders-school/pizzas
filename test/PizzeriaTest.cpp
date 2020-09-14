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
    StrictMock<TimerMock> mt;
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

    // When

    auto orderId = pizzeria.makeOrder(pizzas);
    EXPECT_CALL(mt, sleep_for(minutes(0))).Times(1);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza) {
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    EXPECT_CALL(mt, sleep_for(minutes(1))).Times(1);
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

TEST_F(PizzeriaTest, MainCppScenarioTest) {
    // There is no need to expect_call for NiceMock 
    StrictMock<PizzaMock> mockeritha{};
    NiceMock<PizzaMock> mockeroni{};
    
    auto stubbioni = new PizzaStub{"Stubbioni"};

    Pizzas pizzas = {&mockeritha, &mockeroni, stubbioni};

    EXPECT_CALL(mockeritha, getPrice()).WillOnce(Return(22.50));
    EXPECT_CALL(mockeroni, getPrice()).WillOnce(Return(25.00));
    EXPECT_CALL(mockeritha, getName()).WillOnce(Return("Mockeritha"));
    
    auto orderId = pizzeria.makeOrder(pizzas);
    auto calculatedPrice = pizzeria.calculatePrice(orderId);

    EXPECT_CALL(mockeritha, getBakingTime()).WillOnce(Return(minutes(10)));

    EXPECT_CALL(mt, sleep_for(minutes(0))).Times(1);
    EXPECT_CALL(mt, sleep_for(minutes(10))).Times(1);
    EXPECT_CALL(mt, sleep_for(minutes(1))).Times(1);

    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    ASSERT_EQ(calculatedPrice, 57.50);

    delete stubbioni;
}
