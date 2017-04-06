#pragma once

#include "Test/test_suite.h"

// Data Access Object unit testing suite
class TestDAO : public QTestSuite
{
    Q_OBJECT
private slots:
    void Test1();
    void Test2();
    void Test3();
};
