#include "SportQueryDBRead.h"
#include "SportQuestionListModel.h"

#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
    // 将assets:/question.db拷贝到数据目录
    QFile dbFile(QStringLiteral("assets:/question.db"));
    if (!dbFile.copy(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append(QStringLiteral("/question.db"))))
    {
        qWarning() << "无法拷贝数据库：" << dbFile.errorString();
    }
#endif

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
