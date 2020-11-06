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
        pizzeria("dummyName", std::move(m_timerMock_ptr)) {}

  std::unique_ptr< StrictMock<TimerMock> > m_timerMock_ptr = nullptr;
  TimerMock *m_timerMock_rawPtr = nullptr;
  Pizzeria pizzeria;
};


TEST_F(PizzeriaTest, priceForMargherita25AndFunghi30ShouldBe55)
{
    // Given
    Pizzas pizzas = {new Margherita{25.0}, new Funghi{30.0}};

    // When

    EXPECT_CALL(*m_timerMock_rawPtr , now());
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
    EXPECT_CALL(*m_timerMock_rawPtr , now());
    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(_));

    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
}

TEST_F(PizzeriaTest, completeOrderWithStubPizza)
{
    // Given
    Pizzas pizzas = {new PizzaStub{"STUB"}};

    // When
    EXPECT_CALL(*m_timerMock_rawPtr , now());
    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(_));
    auto orderId = pizzeria.makeOrder(pizzas);
    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);
}

TEST_F(PizzeriaTest, calculatePriceForPizzaMock)
{
    // Given
    constexpr double mockPizzaPrice = 40.0;
    PizzaMock* mock = new PizzaMock{};
    Pizzas pizzas = {mock};

    EXPECT_CALL(*m_timerMock_rawPtr , now());
    EXPECT_CALL(*mock, getPrice()).WillOnce(Return(mockPizzaPrice));

    // When
    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);

    // Then
    ASSERT_EQ(mockPizzaPrice, price);

    delete mock;
}

TEST_F(PizzeriaTest, completeOrderWith3Pizzas)
{
    constexpr double margeritaPrice = 11.11;
    constexpr double fungiPrice = 22.22;
    constexpr minutes margeritaTime(10);
    constexpr minutes fungiTime(20);

    PizzaStub* pizzaStub = new PizzaStub{"STUB"};

    double totalPrice = margeritaPrice + fungiPrice + pizzaStub->getPrice();

    PizzaMock* mockMargerita = new StrictMock<PizzaMock>{};
    ON_CALL(*mockMargerita, getPrice()).WillByDefault(Return(margeritaPrice));
    ON_CALL(*mockMargerita, getBakingTime()).WillByDefault(Return(margeritaTime));
    ON_CALL(*mockMargerita, getName()).WillByDefault(Return("Margerita"));

    PizzaMock* mockFungi = new NiceMock<PizzaMock>{};
    ON_CALL(*mockFungi, getPrice()).WillByDefault(Return(fungiPrice));
    ON_CALL(*mockFungi, getBakingTime()).WillByDefault(Return(fungiTime));

    Pizzas pizzas = {mockFungi,mockMargerita,pizzaStub};

    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(margeritaTime)).Times(1);
    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(fungiTime)).Times(1);
    EXPECT_CALL(*m_timerMock_rawPtr , sleep_for(pizzaStub->getBakingTime())).Times(1);
    EXPECT_CALL(*m_timerMock_rawPtr , now());

    EXPECT_CALL(*mockMargerita, getPrice()).WillOnce(Return(margeritaPrice));
    EXPECT_CALL(*mockMargerita, getName()).WillOnce(Return("Margerita"));
    EXPECT_CALL(*mockMargerita, getBakingTime()).WillOnce(Return(margeritaTime));

    EXPECT_CALL(*mockFungi, getPrice()).WillOnce(Return(fungiPrice));
    EXPECT_CALL(*mockFungi, getBakingTime()).WillOnce(Return(fungiTime));

    auto orderId = pizzeria.makeOrder(pizzas);
    auto price = pizzeria.calculatePrice(orderId);
    EXPECT_EQ(totalPrice, price);

    pizzeria.bakePizzas(orderId);
    pizzeria.completeOrder(orderId);

    delete mockMargerita;
    delete mockFungi;
    delete pizzaStub;
}



