#include "tests.h"

void TestConstuctor() {
  {
    matrix<int> m(TShape(0, 0));
    ASSERT_EQUAL(m.shape(), TShape(0,0));
    ASSERT_EQUAL(m.size(), 0); 
  }

  {
    matrix<int> m({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}});
    ASSERT_EQUAL(m.shape(), TShape(3,3));
    ASSERT_EQUAL(m.size(), 9); 
  }

  {
    matrix<int> m({{}});
    ASSERT_EQUAL(m.shape(), TShape(1,0));
    ASSERT_EQUAL(m.size(), 0); 
  }
  
}

void TestOperators() {
  {
    matrix<int> m({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}});
    matrix<int> l({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}});
    ASSERT_EQUAL(m, l);
    ASSERT(!(m+1 == l));                   
  }
  {
    matrix<int> m({{1, 2, 3},
                   {4, 5, 6}});
    matrix<int> l({{2, 4, 6},
                   {8, 10, 12}});
    ASSERT_EQUAL(m*2, l);
    ASSERT_EQUAL(m + m, l);
  }

  {
    matrix<int> m({{1, 1, 1},
                   {1, 1, 1}});
    matrix<int> l({{1, 1, 1},
                   {2, 2, 2}});
    m[1] *= 2;
    ASSERT_EQUAL(m, l);
  }
}

void TestIndex() {
  {
    matrix<int> m({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}});
    m[0][0] = 0;
    ASSERT_EQUAL(m[0][0], 0);

    std::string messege;
    try {
      m[-1];
    }
    catch(std::out_of_range& e) {
      messege = e.what();
    }
    ASSERT(messege == "Index out of range.");

    try {
      m[5];
    }
    catch(std::out_of_range& e) {
      messege = e.what();
    }
    ASSERT(messege == "Index out of range.");

    try {
      m[1][-1];
    }
    catch(std::out_of_range& e) {
      messege = e.what();
    }
    ASSERT(messege == "Index out of range.");

    try {
      m[1][10];
    }
    catch(std::out_of_range& e) {
      messege = e.what();
    }
    ASSERT(messege == "Index out of range.");
  }
}