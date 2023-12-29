#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QLabel *lbl1 = new QLabel("<i>A</i> is a ");
    QLabel *lbl2 = new QLabel("x");
    QLabel *lbl3 = new QLabel("Matrix");

    spbM = new QSpinBox;
    spbM->setValue(3);
    connect(spbM, SIGNAL(valueChanged(int)), SLOT(onSizeChanged()));

    spbN = new QSpinBox;
    spbN->setValue(3);
    connect(spbN, SIGNAL(valueChanged(int)), SLOT(onSizeChanged()));


    inputMatrix = new QMatrixWidget(spbM->value(),spbN->value());
    connect(inputMatrix, SIGNAL(elementChanged(CNumber,int,int)), SLOT(onElementChanged()));
    inverseMatrix = new QMatrixWidget;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lbl1, 0, 0);
    mainLayout->addWidget(spbM,0, 1);
    mainLayout->addWidget(lbl2,0, 2);
    mainLayout->addWidget(spbN,0, 3);
    mainLayout->addWidget(lbl3, 0, 4);
    mainLayout->addWidget(inputMatrix, 1, 0, 1, 5);
    mainLayout->addWidget(inverseMatrix, 2, 0, 1, 5);

    QWidget * mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

}

void MainWindow::onSizeChanged()
{
    inputMatrix->setMatrix(CMatrix(spbM->value(), spbN->value()));
}

void MainWindow::onElementChanged()
{
    CMatrix matrix = inputMatrix->getMatrix();
    inverseMatrix->setMatrix(matrix.echelonFormReduced());
}
