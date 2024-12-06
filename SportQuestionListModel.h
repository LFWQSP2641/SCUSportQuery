#ifndef SPORTQUESTIONLISTMODEL_H
#define SPORTQUESTIONLISTMODEL_H

#include "SportQuestion.h"

#include <QAbstractListModel>

class SportQuestionListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SportQuestionListModel();

    enum DataRoles
    {
        IssueRole = Qt::UserRole + 1,
        ChoiceRole,
        AnswerRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

public slots:
    // 接收搜索结果
    void receiveSearchResult(const QList<SportQuestion> &questions);

private:
    QList<SportQuestion> m_questions;

protected:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // SPORTQUESTIONLISTMODEL_H
