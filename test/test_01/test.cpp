#include "gtest/gtest.h"
#include "calc/calc.h"

namespace {

    TEST(Calc, TestCalc) {
        Calc calc;
        ASSERT_EQ (10, calc.valor);
    }
}
