#pragma once

#include <QObject>
#include <QVector>
#include <QtTest/QtTest>

// This is the based class for all unit testing suites
class QTestSuite : public QObject
{
    Q_OBJECT
public:
    explicit QTestSuite()
        : QObject()
    {
        AllSuites().push_back(this);
    }

public:
    static QVector<QObject*>& AllSuites()
    {
        static QVector<QObject*> testSuites;
        return testSuites;
    }

    static int RunAllTests()
    {
        int failedSuitesCount = 0;
        for(auto suite : AllSuites()) {
            if(QTest::qExec(suite)) {
                ++failedSuitesCount;
            }
        }
        return failedSuitesCount;
    }
};

