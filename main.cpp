#include "SportQueryDBRead.h"
#include "SportQuestionListModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<SportQuestion>("SportQuestion");
    qmlRegisterType<SportQueryDBRead>("SCUSportQuery", 1, 0, "SportQueryDBRead");
    qmlRegisterType<SportQuestionListModel>("SCUSportQuery", 1, 0, "SportQuestionListModel");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SCUSportQuery", "Main");

    SportQueryDBRead sportQueryDBRead;

    return app.exec();
}
