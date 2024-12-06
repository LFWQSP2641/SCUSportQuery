#ifndef SPORTQUERYDBREAD_H
#define SPORTQUERYDBREAD_H

#include "SportQuestion.h"

#include <QSqlDatabase>
#include <QThread>

class SportQueryDBRead : public QThread
{
    Q_OBJECT

public:
    explicit SportQueryDBRead(QObject *parent = nullptr);
    ~SportQueryDBRead();

public slots:
    void search(const QString &issue);
    QList<SportQuestion> searchSync(const QString &issue, bool signal = false);

protected:
    void run() override;

protected:
    QString m_searchIssue;

signals:
    void searchResult(const QList<SportQuestion> &questions);
};

#endif // SPORTQUERYDBREAD_H
