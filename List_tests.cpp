// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_default_dtor) {

    List<int> empty_list;
    empty_list.push_front(15);
    ASSERT_FALSE(empty_list.empty());
    empty_list.pop_front();
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_back(35);
    empty_list.push_front(45);
    empty_list.push_front(55);
    empty_list.pop_front();
    empty_list.pop_back();
    empty_list.pop_front();
    ASSERT_TRUE(empty_list.empty());

    List<int> empty_list2;
    empty_list2.push_front(55);
    empty_list2.clear();
    ASSERT_TRUE(
        empty_list2.empty());
}

TEST(test_list_empty) {
    List<int> empty_list;
    ASSERT_EQUAL(
        empty_list.empty(),
        true);
    empty_list.push_back(55);
    ASSERT_EQUAL(
        empty_list.front()
            == empty_list.back(),
        true);
    empty_list.pop_front();
    ASSERT_EQUAL(
        empty_list.size(),
        0);

    empty_list.push_back(26);
    empty_list.clear();
    ASSERT_EQUAL(
        empty_list.size(),
        0);
}

TEST(test_size) {

    List<int> empty_list;
    empty_list.push_front(15);
    empty_list.pop_front();
    empty_list.push_back(35);
    empty_list.push_front(45);
    empty_list.push_front(55);
    empty_list.pop_front();
    ASSERT_EQUAL(empty_list.size(), 
        2);

    List<int> empty_list2;
    empty_list2.push_front(55);
    empty_list2.clear();
    ASSERT_EQUAL(empty_list2.size(),
        0);

    List<int> empty_list3;
    ASSERT_EQUAL(empty_list3.size(),
        0);
    empty_list3.push_front(55);
    ASSERT_EQUAL(empty_list3.size(),
        1);
}


TEST(test_front_back) {

    List<int> empty_list;
    empty_list.push_front(10);
    ASSERT_EQUAL(empty_list.front()
        , 10);
    ASSERT_EQUAL(empty_list.back()
        , 10);
    empty_list.push_back(35);
    empty_list.push_front(45);
    empty_list.push_back(55);
    ASSERT_EQUAL(empty_list.front()
        , 45);
    ASSERT_EQUAL(empty_list.back()
        , 55);
}

TEST(test_push_pop) {

    List<int> empty_list;
    empty_list.push_front(10);
    empty_list.pop_back();
    empty_list.push_back(35);
    empty_list.push_front(45);
    empty_list.push_back(55);
    empty_list.pop_back();
    ASSERT_EQUAL(empty_list.
        back()
        , 35);
    empty_list.pop_front();
    ASSERT_EQUAL(empty_list.
        front()
        , 35);
}


TEST(test_clear) {

    List<int> empty_list;
    empty_list.push_front(10);
    empty_list.push_back(36);
    empty_list.push_front(2);
    empty_list.push_back(5);
    empty_list.clear();
    ASSERT_EQUAL(empty_list.
        empty()
        , true);

    List<int> empty_list2;
    empty_list2.push_front(11);
    empty_list2.clear();
    ASSERT_EQUAL(empty_list2.
        empty()
        , true);

    List<int> empty_list3;
    empty_list3.push_back(11);
    empty_list3.clear();
    ASSERT_EQUAL(empty_list3.
        empty()
        , true);

}


TEST(test_copy) {

    List<int> empty_list;

    empty_list.push_front(10);
    empty_list.push_back(36);
    empty_list.push_front(2);
    empty_list.push_back(5);

    List<int> empty_list2(
        empty_list);

    ASSERT_EQUAL(empty_list.
        front()
        , empty_list2.
        front());

    ASSERT_EQUAL(empty_list.
        back()
        , empty_list2.
        back());
}


TEST(test_iterator_1) {

    List<int> empty_list;

    empty_list.push_front(1);
    empty_list.push_back(2);
    empty_list.push_front(3);
    empty_list.push_back(4);
    empty_list.push_front(5);

    List<int>::Iterator iter = 
        empty_list.begin();
    empty_list.insert(iter, 30);
    ASSERT_EQUAL(empty_list.
        front()
        , 30);
    iter = empty_list.begin();
    empty_list.erase(iter);
    iter = empty_list.begin();
    ASSERT_EQUAL(empty_list.
        front()
        , 5);

    List<int> empty_list2(
        empty_list);

    empty_list2 = empty_list;

    List<int>::Iterator iter2
        = empty_list2.begin();

    empty_list2.insert(iter2, 30);
    ASSERT_EQUAL(iter2 == iter
        , false);
}

TEST(test_iterator_2) {
    List<int> empty_list;

    empty_list.push_front(1);
    empty_list.push_front(2);
    empty_list.push_front(3);

    List<int> empty_list2(
        empty_list);

    List<int>::Iterator iter =
        empty_list.begin();
    ASSERT_EQUAL(*iter,
        3);

    List<int>::Iterator iter2 =
        empty_list2.begin();
    ASSERT_EQUAL(*iter2,
        3);

    ++iter;
    ASSERT_EQUAL(*iter,
        2);
    ++iter2;
    ASSERT_EQUAL(*++--iter,
        *--++iter2);

    List<int> empty_list3;

    empty_list3.push_front(1);
    List<int>::Iterator iter3 =
        empty_list3.begin();
    ASSERT_EQUAL(*iter3,
        1);
}


TEST(test_insert_erase) {
    List<int> empty_list;
    empty_list.push_front(1);
    empty_list.insert(
        empty_list.begin(), 3);
    empty_list.erase(
        empty_list.begin());
    ASSERT_EQUAL(
        empty_list.front(), 1);

    List<int> empty_list2;
    empty_list2.push_back(1);
    empty_list2.push_back(2);
    empty_list2.push_back(3);
    List<int>::Iterator iter2 =
        empty_list2.begin();
    empty_list2.insert(
        empty_list2.begin(), 10);
    ++iter2;
    empty_list2.erase(iter2);

    iter2 =
        empty_list2.begin();

    ASSERT_EQUAL(
        *iter2,
        10);
    ++iter2;
    ASSERT_EQUAL(
        *iter2,
        1); 
    ++iter2;
    ASSERT_EQUAL(
        *iter2,
        3);
}

TEST(test_overload_operators) {
    List<int> empty_list;

    empty_list.push_front(1);
    empty_list.push_front(2);
    empty_list.push_front(3);

    List<int> empty_list2;

    empty_list2 = empty_list;

    ASSERT_EQUAL(
        empty_list2.back(), 
        empty_list.back());

    ASSERT_EQUAL(
        empty_list2.front(), 
        empty_list.front());

    List<int>::Iterator iter = 
        empty_list.begin();
    ++iter;
    ASSERT_FALSE(iter 
        == empty_list.begin());
    
    ASSERT_TRUE(iter
        != empty_list.begin());

}

TEST(test_template){
    List<string> str1;
    str1.push_back("280");
    str1.push_front("EECS");
    ASSERT_EQUAL(
        str1.front(),
        "EECS");
}

TEST(test_empty_insert){
    List<int> int1;
    int1.insert(
        int1.begin(),4);
    int1.insert(
        int1.begin(),3);
    int1.insert(
        int1.begin(),2);
    int1.insert(
        int1.begin(),-1);

    ASSERT_EQUAL(
        int1.front(), -1);
    ASSERT_EQUAL(
        int1.back(), 4);

    int1.erase(int1.begin());
    int1.erase(int1.begin());
    int1.erase(int1.begin());
    int1.erase(int1.begin());

    ASSERT_EQUAL(
        int1.empty(), true);
    
}

TEST_MAIN()
