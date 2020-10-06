#include <gtest/gtest.h>
#include <string>
#include "mocks/PizzaMock.hpp"
#include "mocks/TimerMock.hpp"
#include "Pizzeria.hpp"
#include "Margherita.hpp"
#include "Funghi.hpp"

using namespace std;
using namespace ::testing;

using ::testing::NiceMock;
using ::testing::NaggyMock;
using ::testing::StrictMock;
using ::testing::_;

struct PizzeriaTest : public ::testing::Test
{
public:
    PizzeriaTest() : 
        m_timerMock_ptr(new StrictMock<TimerMock>),
        m_timerMock_rawPtr(m_timerMock_ptr.get()),
        pizzeria("dummyNane", std::move(m_timerMock_ptr)) {}

  std::unique_ptr< StrictMock<TimerMock> > m_timerMock_ptr = nullptr;
  TimerMock *m_timerMock_rawPtr = nullptr;
  Pizzeria pizzeria;
};


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

    // When

    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(_));

    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};

    // When
    //
    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(_));
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

TEST_F(PizzeriaTest, completeOrderWith3Pizzas)
{
    PizzaMock* mockMargerita = new StrictMock<PizzaMock>{};
    ON_CALL(*mockMargerita, getPrice()).WillByDefault(Return(11.11));
    ON_CALL(*mockMargerita, getBakingTime()).WillByDefault(Return(minutes(10)));
    ON_CALL(*mockMargerita, getName()).WillByDefault(Return("Margerita"));

    PizzaMock* mockFungi = new NiceMock<PizzaMock>{};
    ON_CALL(*mockFungi, getPrice()).WillByDefault(Return(22.22));

    PizzaStub* pizzaStub = new PizzaStub{"STUB"};

    Pizzas pizzas = {mockFungi,mockMargerita,pizzaStub};

    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(_)).Times(3);

    EXPECT_CALL(*mockMargerita, getPrice()).WillOnce(Return(11.11));
    EXPECT_CALL(*mockMargerita, getName()).WillOnce(Return("Margerita"));
    EXPECT_CALL(*mockMargerita, getBakingTime()).WillOnce(Return(minutes(10)));

    auto orderId = pizzeria.makeOrder(pizzas);

    auto price = pizzeria.calculatePrice(orderId);
    ASSERT_EQ(43.33, price);

    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
    delete mockMargerita;
    delete mockFungi;
}



