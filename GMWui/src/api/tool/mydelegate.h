#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QStyledItemDelegate>

class MyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyDelegate(QObject* parent = nullptr);
    virtual QWidget* createEditor(QWidget* parent,
                                  const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const override;
    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    virtual QSize sizeHint(const QStyleOptionViewItem& option,
                           const QModelIndex& index) const override;

};

#endif // MYDELEGATE_H
