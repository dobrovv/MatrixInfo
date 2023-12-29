#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include "QMatrixWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSpinBox *spbM;
    QSpinBox *spbN;

    QMatrixWidget *inputMatrix;
    QMatrixWidget *inverseMatrix;

public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

private slots:
    void onSizeChanged();
    void onElementChanged();
};

#endif // MAINWINDOW_H
