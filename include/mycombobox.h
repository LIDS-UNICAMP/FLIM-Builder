#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include "common.h"
#include <QComboBox>

class MyComboBox: public QComboBox
{
    Q_OBJECT

public:
    explicit MyComboBox(QWidget *parent = nullptr);
    ~MyComboBox() override;

signals:
    void itemClicked(int index);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;
};

#endif // MYCOMBOBOX_H
