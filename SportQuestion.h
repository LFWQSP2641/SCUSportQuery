#ifndef SPORTQUESTION_H
#define SPORTQUESTION_H

#include <QMetaObject>
#include <QString>

class SportQuestion
{
    Q_GADGET
    friend QDebug operator<<(QDebug debug, const SportQuestion &question);

public:
    SportQuestion();
    SportQuestion(const QString &issue, const QString &choice, const QString &answer)
        : m_issue{ issue }, m_choice{ choice }, m_answer{ answer }
    {
    }

    QString issue() const;
    void setIssue(const QString &newIssue);

    QString choice() const;
    void setChoice(const QString &newChoice);

    QString answer() const;
    void setAnswer(const QString &newAnswer);

protected:
    QString m_issue;
    QString m_choice;
    QString m_answer;

private:
    Q_PROPERTY(QString issue READ issue WRITE setIssue)
    Q_PROPERTY(QString choice READ choice WRITE setChoice)
    Q_PROPERTY(QString answer READ answer WRITE setAnswer)
};

QDebug operator<<(QDebug debug, const SportQuestion &question);

#endif // SPORTQUESTION_H
