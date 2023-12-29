#include "QMatrixWidget.h"

#include "QHBoxLayout"

QMatrixWidget::QMatrixWidget(int M, int N, QWidget *parent)
    : QWidget(parent), mx(M,N), wgtMatrix(0)
{
    setFocusPolicy(Qt::TabFocus);
    setMinimumSize(QSize(30,15));

    leftBracket = new QWidget;
    rightBracket = new QWidget;


    setMatrix(mx);
}

void QMatrixWidget::setMatrix(const CMatrix &matrix)
{
    if (wgtMatrix)
        wgtMatrix->deleteLater();

    wgtMatrix = new QWidget;

    if (this->layout())
        delete this->layout();

    QGridLayout * grid = new QGridLayout;
    grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);
    wgtMatrix->setLayout(grid);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);

    mainLayout->addWidget(leftBracket);
    if (mx.M() > 0 && mx.N() > 0)
        mainLayout->addWidget(wgtMatrix);
    mainLayout->addWidget(rightBracket);

    setLayout(mainLayout);

    mx = matrix;

    for (int i = 0; i < mx.M(); ++i){
        for (int j=0; j < mx.N(); ++j){
            QMatrixWidgetElement *mwe = new QMatrixWidgetElement(mx[i][j], i, j);
            mwe->setMinimumSize(QSize(25,25));
            mwe->setMaximumSize(QSize(200,200));
            grid->addWidget(mwe, i, j);

            connect(mwe, &QMatrixWidgetElement::elementChanged, this, &QMatrixWidget::onElementChanged);
        }
    }
}

void QMatrixWidget::onElementChanged(CNumber val, int row, int column)
{
    Q_ASSERT(row != -1 && column != -1);
    mx[row][column] = val;

    elementChanged(val, row, column);
}

void QMatrixWidget::resizeEvent(QResizeEvent *event)
{
    QString borderStyleLeft = QString("border: %1px solid #000; border-right: 0px;");
    QString borderStyleRight = QString("border: %1px solid #000; border-left: 0px;");

    int borderWidth = qMax(1, size().height() / 75);
    leftBracket->setStyleSheet(borderStyleLeft.arg(borderWidth));
    rightBracket->setStyleSheet(borderStyleRight.arg(borderWidth));

    leftBracket->setFixedWidth(borderWidth+size().width()/35);
    rightBracket->setFixedWidth(borderWidth+size().width()/35);

    QWidget::resizeEvent(event);
}

