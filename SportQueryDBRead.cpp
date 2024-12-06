#include "SportQueryDBRead.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

SportQueryDBRead::SportQueryDBRead(QObject *parent)
    : QThread{ parent }
{
}

SportQueryDBRead::~SportQueryDBRead()
{
    exit(1);
    wait();
}

void SportQueryDBRead::search(const QString &issue)
{
    qDebug() << Q_FUNC_INFO;
    m_searchIssue = issue;
    start();
}

QList<SportQuestion> SportQueryDBRead::searchSync(const QString &issue, bool signal)
{
    qDebug() << "搜索问题：" << issue;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
#ifdef Q_OS_WINDOWS
    const QString dbPath = QCoreApplication::applicationDirPath().append(QStringLiteral("/data/question.db"));
#else
    const QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append(QStringLiteral("/question.db"));
#endif
    db.setDatabaseName(dbPath);

    if (!db.open())
    {
        qWarning() << "无法打开数据库：" << db.lastError();
    }

    QSqlQuery query;
    query.setForwardOnly(true);
    // QString queryStr = QStringLiteral("SELECT * FROM QUESTIONS WHERE ISSUE LIKE '%")
    //                        .append(issue)
    //                        .append(QStringLiteral("%'"));
    query.prepare("SELECT * FROM QUESTIONS WHERE ISSUE LIKE :issue");
    query.bindValue(":issue", QStringLiteral("%").append(issue).append(QStringLiteral("%")));
    QList<SportQuestion> questions;
    if (query.exec())
    {
        while (query.next())
        {
            QString column1 = query.value(0).toString();
            QString column2 = query.value(1).toString();
            QString column3 = query.value(2).toString();
            questions.append(SportQuestion{ column1, column2, column3 });
        }
    }
    else
    {
        qDebug() << "查询失败：" << query.lastError();
    }
    qDebug() << "搜索完成" << questions.size() << "个问题";
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    if (signal)
    {
        qDebug() << "发射信号";
        emit searchResult(questions);
    }
    return questions;
}

void SportQueryDBRead::run()
{
    qDebug() << Q_FUNC_INFO;
    searchSync(m_searchIssue, true);
}
