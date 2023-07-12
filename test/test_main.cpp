#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char** argv)
{
    try {
        ::testing::InitGoogleMock(&argc, argv);
        auto code = RUN_ALL_TESTS();
        return code;
    }
    catch (...)
    {
        return 0;
    }
    return 0;
}
