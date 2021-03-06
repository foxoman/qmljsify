#include <QQmlApplicationEngine>
#include <QTest>
#include <Automator>
#include <QtShell>
#include "tests.h"
#include "qmljsify.h"

using namespace QtShell;

void printException(QJSValue value)
{
    if (value.isError()) {
        QString message = QString("%1:%2: %3: %4")
                          .arg(value.property("fileName").toString())
                          .arg(value.property("lineNumber").toString())
                          .arg(value.property("name").toString())
                          .arg(value.property("message").toString());
        qWarning() << message;
    }
}

Tests::Tests(QObject *parent) : QObject(parent)
{
    auto ref = [=]() {
        QTest::qExec(this, 0, 0); // Autotest detect available test cases of a QObject by looking for "QTest::qExec" in source code
    };
    Q_UNUSED(ref);
}

void Tests::test_prepare()
{
    Qmljsify jsify;

    QString buildFolder = realpath_strip(pwd(), "build");
    jsify.setBuildFolder(buildFolder);
    jsify.setPackage("lodash");

    jsify.prepare();

    QString index = realpath_strip(buildFolder, "index.js");
    QString webpack = realpath_strip(buildFolder, "webpack.config.js");

    QVERIFY(QFile::exists(index));
    QVERIFY(QFile::exists(webpack));

    QString content = cat(index);
    QVERIFY(content.indexOf("lodash") >= 0);
}

void Tests::test_create()
{
    Qmljsify jsify;

    QString buildFolder = realpath_strip(pwd(), "build");
    QString outputFolder = pwd();

    QString origJs = realpath_strip(pwd() , "sprintf.orig.js");

    QString package = "sprintf";
    jsify.setMinifyEnabled(true);
    jsify.setOutputFolder(outputFolder);

    jsify.setBuildFolder(buildFolder);
    jsify.setPackage(package);

    jsify.prepare();

    jsify.fetch();

    jsify.build();

    jsify.create();

    QVERIFY(QFile::exists(origJs));
    QVERIFY(cat(origJs).size() > 0);
}


