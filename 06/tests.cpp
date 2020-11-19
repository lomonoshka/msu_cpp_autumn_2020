#include "test_runner.h"
#include "format.h"

void test_format() {

    ASSERT_EQUAL(format("{0} + {0} = {1}", "one", 2), "one + one = 2");

    ASSERT_EQUAL(format("{0}hello{1}", "hey", 5), "heyhello5");

    ASSERT_EQUAL(format("oooo{0}oooo", "000"), "oooo000oooo");

    bool error = false;
    try {
        auto t = format("{", 1);
    } catch (const std::logic_error &e) {
        error = true;
    }
    
    ASSERT(error);
    error = false;
    try {
        auto t = format("{asdas}sdfsd{1}", 1, 2);
    } catch (const std::logic_error &e) {
        error = true;
    }

    ASSERT(error);

}