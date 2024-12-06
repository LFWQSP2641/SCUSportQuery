#include "SportQuestion.h"

#include <QDebug>

SportQuestion::SportQuestion()
{
}

QString SportQuestion::issue() const
{
    return m_issue;
}

void SportQuestion::setIssue(const QString &newIssue)
{
    m_issue = newIssue;
}

QString SportQuestion::choice() const
{
    return m_choice;
}

void SportQuestion::setChoice(const QString &newChoice)
{
    m_choice = newChoice;
}

QString SportQuestion::answer() const
{
    return m_answer;
}

void SportQuestion::setAnswer(const QString &newAnswer)
{
    m_answer = newAnswer;
}

QDebug operator<<(QDebug debug, const SportQuestion &question)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "SportQuestion(" << question.m_issue << ", " << question.m_choice << ", " << question.m_answer << ")";
    return debug;
}
