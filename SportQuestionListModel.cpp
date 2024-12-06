#include "SportQuestionListModel.h"

SportQuestionListModel::SportQuestionListModel()
{
}

int SportQuestionListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_questions.size();
}

QVariant SportQuestionListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= m_questions.size() || index.row() < 0)
    {
        return QVariant();
    }

    const SportQuestion &question = m_questions.at(index.row());
    switch (role)
    {
    case IssueRole:
        return question.issue();
    case ChoiceRole:
        return question.choice();
    case AnswerRole:
        return question.answer();
    }

    return QVariant();
}

QVariant SportQuestionListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QStringLiteral("问题");
        case 1:
            return QStringLiteral("选项");
        case 2:
            return QStringLiteral("答案");
        default:
            break;
        }
    }

    return QVariant();
}

void SportQuestionListModel::receiveSearchResult(const QList<SportQuestion> &questions)
{
    qDebug() << Q_FUNC_INFO << questions.size();
    beginResetModel();
    m_questions = questions;
    endResetModel();
}

QHash<int, QByteArray> SportQuestionListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IssueRole] = "issue";
    roles[ChoiceRole] = "choice";
    roles[AnswerRole] = "answer";
    return roles;
}
