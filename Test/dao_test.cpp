#include "dao_test.h"

// Just an example
void TestDAO::Test1()
{
     QVERIFY(QString("hello").toUpper() == "HELLO");
}

// DAO test suite instatiation
static TestDAO dao_test_suite_instace;
