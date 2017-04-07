#pragma once

#include "Test/test_suite.h"

// Data Access Object unit testing suite
class TestDAO : public QTestSuite
{
    Q_OBJECT
private slots:
    void CitiesTableTest();
    void BusesTableTest();
    void RoutesTableTest();
};
