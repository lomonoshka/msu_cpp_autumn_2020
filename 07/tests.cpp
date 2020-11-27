#include "test_runner.h"
#include "vector.hpp"

void TestCtors() {
    {
        my::vector<int> v;
        ASSERT_EQUAL(v.size(), 0u)
        ASSERT_EQUAL(v.capacity(), 0u)
    }

    {
        my::vector<int> v(100, 100);
        ASSERT_EQUAL(v.size(), 100u)
        ASSERT_EQUAL(v.capacity(), 100u)
        for (const auto &val : v) {
            ASSERT_EQUAL(val, 100)
        }
    }

    {
        my::vector<int> v_source(10, 1);
        my::vector<int> v_dest(v_source);
        ASSERT_EQUAL(v_source.size(), v_dest.size())
        ASSERT_EQUAL(v_source.capacity(), v_dest.capacity())
        for (size_t i = 0; i < std::min(v_source.size(), v_dest.size()); ++i) {
            ASSERT_EQUAL(v_source[i], v_dest[i])
        }
    }

    {
        my::vector<int> v_source(10, 1);
        my::vector<int> v_source_copy(10, 1);
        my::vector<int> v_dest(std::move(v_source_copy));
        ASSERT_EQUAL(v_source.size(), v_dest.size())
        ASSERT_EQUAL(v_source.capacity(), v_dest.capacity())
        for (size_t i = 0; i < std::min(v_source.size(), v_dest.size()); ++i) {
            ASSERT_EQUAL(v_source[i], v_dest[i])
        }
        ASSERT_EQUAL(v_source_copy.size(), 0)
        ASSERT_EQUAL(v_source_copy.capacity(), 0)
    }

    {
        my::vector<int> v = {1, 2, 3, 4, 5};
        stringstream ss;
        ss << v;
        ASSERT_EQUAL(ss.str(), "1 2 3 4 5")
    }
}

void TestMethods() {
    {
        my::vector<int> v;
        v.push_back(1);
        ASSERT_EQUAL(v.back(), 1)
        ASSERT_EQUAL(v.size(), 1)
        ASSERT_EQUAL(v.capacity(), 1)
        v.push_back(2);
        ASSERT_EQUAL(v.back(), 2)
        ASSERT_EQUAL(v.size(), 2)
        ASSERT_EQUAL(v.capacity(), 2)
        v.push_back(3);
        ASSERT_EQUAL(v.back(), 3)
        ASSERT_EQUAL(v.size(), 3)
        ASSERT_EQUAL(v.capacity(), 4)
        v.pop_back();
        ASSERT_EQUAL(v.size(), 2)
        ASSERT_EQUAL(v.capacity(), 4)
        v.pop_back();
        ASSERT_EQUAL(v.size(), 1)
        ASSERT_EQUAL(v.capacity(), 4)
        v.pop_back();
        ASSERT(v.empty());
        ASSERT_EQUAL(v.size(), 0);
        ASSERT_EQUAL(v.capacity(), 4)
    }

    {
        my::vector<my::vector<int>> v;
        auto res = v.emplace_back(5, 1);
        ASSERT(res == my::vector<int>({1, 1, 1, 1, 1}))
    }

    {
        my::vector<int> v;
        v.reserve(10);
        ASSERT_EQUAL(v.capacity(), 10u)
        ASSERT_EQUAL(v.size(), 0u)

        v.resize(5);
        ASSERT_EQUAL(v.size(), 5u)

        v.resize(15);
        ASSERT_EQUAL(v.capacity(), 15u)
        ASSERT_EQUAL(v.size(), 15u)

        v.reserve(10);
        ASSERT_EQUAL(v.capacity(), 15u)
        ASSERT_EQUAL(v.size(), 15u)

        v.resize(3);
        ASSERT_EQUAL(v.capacity(), 15u)
        ASSERT_EQUAL(v.size(), 3u)
    }

    {
        my::vector<int> v = {1, 2, 3, 4, 5};
        my::vector<int> v_rev = {5, 4, 3, 2, 1};
        auto it1 = v.begin();
        auto it2 = v_rev.rbegin();
        for (; it1 != v.end() && it2 != v_rev.rend(); ++it1, ++it2) {
            ASSERT_EQUAL(*it1, *it2)
        }
    }
}