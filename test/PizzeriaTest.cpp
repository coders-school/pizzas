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

struct PizzeriaTest : public ::testing::Test
{
public:
    StrictMock<TimeMock> tm;
    Pizzeria pizzeria = Pizzeria("dummyName", tm); };


TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55)
{
    // Given
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(55, price);
}

TEST_F(PizzeriaTest, bakeDummyPizza)
{
    // Given
    Pizzas pizzas = {new PizzaDummy{}};
    EXPECT_CALL(tm, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};
    EXPECT_CALL(tm, sleep_for).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{   
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

TEST_F(PizzeriaTest, cloneMainFunctionWithOneStubPizzaAndTwoMockPizza)
{   
    // Given
    PizzaStub* stubPizza = new PizzaStub{"STUB"};
    StrictMock<PizzaMock> strictMockPizza {};
    NiceMock<PizzaMock> niceMockPizza {};
    Pizzas pizzas = {stubPizza, & strictMockPizza, & niceMockPizza};
    std::string strictPizzaName = "Strikt";
    std::string nicePizzaName = "Najs";
    constexpr double strictPizzaPrice = 18.99;
    constexpr double nicePizzaPrice = 35.49;
    auto stubPizzaTime = stubPizza->getBakingTime();
    constexpr auto strictPizzaTime = minutes(4);
    constexpr auto nicePizzaTime = minutes(8);
    
    EXPECT_CALL(strictMockPizza, getName()).WillOnce(Return(strictPizzaName));
    EXPECT_CALL(strictMockPizza, getBakingTime()).WillOnce(Return(minutes(strictPizzaTime)));
    EXPECT_CALL(strictMockPizza, getPrice()).WillOnce(Return(strictPizzaPrice));

    EXPECT_CALL(niceMockPizza, getName()).WillOnce(Return(nicePizzaName));
    EXPECT_CALL(niceMockPizza, getBakingTime()).WillOnce(Return(minutes(nicePizzaTime)));
    EXPECT_CALL(niceMockPizza, getPrice()).WillOnce(Return(nicePizzaPrice));

    EXPECT_CALL(tm, sleep_for(stubPizzaTime)).Times(1);
    EXPECT_CALL(tm, sleep_for(strictPizzaTime)).Times(1);
    EXPECT_CALL(tm, sleep_for(nicePizzaTime)).Times(1);

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    // Then    
    ASSERT_EQ(strictPizzaPrice + nicePizzaPrice + stubPizza->getPrice(), price);

    delete stubPizza;
}
