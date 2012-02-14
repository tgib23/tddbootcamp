//--- LRU Cache for CppUnit

#include <iostream>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "LRUCache.hpp"

class Test : public CPPUNIT_NS::TestCase
{
  LRUCache * a;
  CPPUNIT_TEST_SUITE(Test);
// init size
  CPPUNIT_TEST(testLRUCacheInit);
// put one
  CPPUNIT_TEST(testLRUCachePut);
// get one
  CPPUNIT_TEST(testLRUCacheGet);
// put many - LRU check
  CPPUNIT_TEST(testLRUCachePutMult);
// get many - LRU check
  CPPUNIT_TEST(testLRUCacheGetMult);
  CPPUNIT_TEST(testLRUCacheIncreaseMaxSize);
  CPPUNIT_TEST(testLRUCacheDecreaseMaxSize);
// change max size

// final test
//  CPPUNIT_TEST(testLRUCache);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(void) {}
  void tearDown(void) {} 

protected:
  void testLRUCacheInit(void);
  void testLRUCachePut(void);
  void testLRUCacheGet(void);
  void testLRUCachePutMult(void);
  void testLRUCacheGetMult(void);
  void testLRUCacheIncreaseMaxSize(void);
  void testLRUCacheDecreaseMaxSize(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main( int ac, char **av )
{
  //--- Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  //--- Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  //--- Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  //--- Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  return result.wasSuccessful() ? 0 : 1;
}

void Test::testLRUCacheInit()
{
	LRUCache a;
	CPPUNIT_ASSERT_EQUAL(0,a.getsize());
}

void Test::testLRUCachePut()
{
	LRUCache a;
        std::string key("a");
        std::string value("dataA");
	CPPUNIT_ASSERT(a.put(key, value));
	CPPUNIT_ASSERT_EQUAL(1,a.getsize());
}

void Test::testLRUCacheGet()
{
	LRUCache a;
        std::string key("a");
        std::string value("dataA");
	CPPUNIT_ASSERT(a.put(key, value));
	CPPUNIT_ASSERT_EQUAL(value, a.get(key));
}

void Test::testLRUCachePutMult()
{
  	LRUCache a;
        std::string key1("a");
        std::string value1("dataA");
        std::string key2("b");
        std::string value2("dataB");
        std::string key3("c");
        std::string value3("dataC");

	CPPUNIT_ASSERT(a.put(key1, value1));
	CPPUNIT_ASSERT(a.put(key2, value2));
	CPPUNIT_ASSERT(a.put(key3, value3));

	CPPUNIT_ASSERT_EQUAL(2,a.getsize());
	CPPUNIT_ASSERT_EQUAL(std::string(""), a.get(key1));
	CPPUNIT_ASSERT_EQUAL(value2, a.get(key2));
	CPPUNIT_ASSERT_EQUAL(value3, a.get(key3));
}


void Test::testLRUCacheGetMult()
{
  	LRUCache a;
        std::string key1("a");
        std::string value1("dataA");
        std::string key2("b");
        std::string value2("dataB");
        std::string key3("c");
        std::string value3("dataC");

	CPPUNIT_ASSERT(a.put(key1, value1));
	CPPUNIT_ASSERT(a.put(key2, value2));
	a.get(key1);
	CPPUNIT_ASSERT(a.put(key3, value3));
	

	CPPUNIT_ASSERT_EQUAL(2,a.getsize());
	CPPUNIT_ASSERT_EQUAL(value1, a.get(key1));
	CPPUNIT_ASSERT_EQUAL(std::string(""), a.get(key2));
	CPPUNIT_ASSERT_EQUAL(value3, a.get(key3));
}


void Test::testLRUCacheIncreaseMaxSize()
{
  	LRUCache a;
        std::string key1("a");
        std::string value1("dataA");
        std::string key2("b");
        std::string value2("dataB");
        std::string key3("c");
        std::string value3("dataC");

	CPPUNIT_ASSERT(a.put(key1, value1));
	CPPUNIT_ASSERT(a.put(key2, value2));
	CPPUNIT_ASSERT(a.put(key3, value3));
	

	CPPUNIT_ASSERT_EQUAL(2,a.getsize());
	CPPUNIT_ASSERT_EQUAL(std::string(""), a.get(key1));
	CPPUNIT_ASSERT_EQUAL(value2, a.get(key2));
	CPPUNIT_ASSERT_EQUAL(value3, a.get(key3));

// サイズ変更
	a.change_maxsize(3);
	CPPUNIT_ASSERT(a.put(key1, value1));

	CPPUNIT_ASSERT_EQUAL(3,a.getsize());
	CPPUNIT_ASSERT_EQUAL(value1, a.get(key1));
	CPPUNIT_ASSERT_EQUAL(value2, a.get(key2));
	CPPUNIT_ASSERT_EQUAL(value3, a.get(key3));
}


void Test::testLRUCacheDecreaseMaxSize()
{
  	LRUCache a;
        std::string key1("a");
        std::string value1("dataA");
        std::string key2("b");
        std::string value2("dataB");
        std::string key3("c");
        std::string value3("dataC");

	CPPUNIT_ASSERT(a.put(key1, value1));
	CPPUNIT_ASSERT(a.put(key2, value2));
	a.get(key1);
	CPPUNIT_ASSERT(a.put(key3, value3));
	

	CPPUNIT_ASSERT_EQUAL(2,a.getsize());
	CPPUNIT_ASSERT_EQUAL(value1, a.get(key1));
	CPPUNIT_ASSERT_EQUAL(std::string(""), a.get(key2));
	CPPUNIT_ASSERT_EQUAL(value3, a.get(key3));

	a.change_maxsize(1);

	CPPUNIT_ASSERT_EQUAL(1,a.getsize());
	CPPUNIT_ASSERT_EQUAL(std::string(""), a.get(key1));
	CPPUNIT_ASSERT_EQUAL(std::string(""), a.get(key2));
	CPPUNIT_ASSERT_EQUAL(value3, a.get(key3));
}


