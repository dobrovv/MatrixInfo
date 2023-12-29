#ifndef QMATRIXWIDGET_H
#define QMATRIXWIDGET_H

#include <QWidget>
#include "CMatrix.h"
#include <QGridLayout>
#include <QLineEdit>

#include "QMatrixWidgetElement.h"

class QMatrixWidget : public QWidget
{
    Q_OBJECT

    CMatrix mx;

    QWidget *leftBracket;
    QWidget *rightBracket;
    QWidget *wgtMatrix;

public:
    explicit QMatrixWidget(int M=0, int N=0, QWidget *parent = 0);

    CMatrix getMatrix() {return mx;}
    void setMatrix(const CMatrix& matrix);

signals:
    void elementChanged(CNumber val, int row, int column);

private slots:
    void onElementChanged(CNumber val, int row, int column);

private:
    void resizeEvent(QResizeEvent *event);
};

#endif // QMATRIXWIDGET_H
