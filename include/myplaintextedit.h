#ifndef MYPLAINTEXTEDIT_H
#define MYPLAINTEXTEDIT_H

#include "common.h"

class MyPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit MyPlainTextEdit(QWidget *parent = nullptr);
    ~MyPlainTextEdit() override;

signals:
    void focusChanged();

protected:
    void focusOutEvent(QFocusEvent* event) override;
};

#endif // MYPLAINTEXTEDIT_H
