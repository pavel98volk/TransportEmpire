#pragma once

#include <QObject>
#include <QVector>
#include <QtTest/QtTest>

// This is the based class for all unit testing suites
class QTestSuite : public QObject
{
    Q_OBJECT

protected:
    int argc;
    char** argv;

public:
    explicit QTestSuite()
        : QObject()
    {
        AllSuites().push_back(this);
    }
    virtual ~QTestSuite()
    {
    }

public:
    void SetConsoleArgs(int _argc, char* _argv[])
    {
        argc = _argc;
        argv = _argv;
    }

public:
    static QVector<QObject*>& AllSuites()
    {
        static QVector<QObject*> testSuites;
        return testSuites;
    }

    static int RunAllTests(int _argc, char* _argv[])
    {
        int failedSuitesCount = 0;
        for(auto suite : AllSuites())
        {
            dynamic_cast<QTestSuite*>(suite)->SetConsoleArgs(_argc, _argv);
            if(QTest::qExec(suite)) {
                ++failedSuitesCount;
            }
        }
        return failedSuitesCount;
    }
};

