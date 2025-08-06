#ifndef PRINTWIDGET_H
#define PRINTWIDGET_H

#include <QWidget>

class PrintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrintWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // PRINTWIDGET_H
