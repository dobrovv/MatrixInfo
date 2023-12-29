#include <QApplication>
#include <QDebug>
#include <time.h>

#include "MainWindow.h"

#define evalDebug(arg1, op, arg2) \
    (qDebug() << arg1 << #op << arg2 << "=" << (arg1 op arg2))

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    srand(time(0));
    CMatrix m(2,2);
    CMatrix m2(2,3);

    for(int i=0; i < m.M()*m.N(); ++i)
        m[i / m.N()][i % m.N()] = CNumber(rand()%10, rand()%9+1);

    for(int i=0; i < m2.M()*m2.N(); ++i)
        m2[i / m2.N()][i % m2.N()] = CNumber(rand()%10, rand()%9+1);

    qDebug() << m << endl;
    qDebug() << m.adj() << " " << m.det() << endl;
    qDebug() << m.adj() * (1/m.det()) << endl;
    qDebug() << m.inverse() << endl;

    qDebug() << m.toString();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->inputMatrix->setMatrix(m);
    mainWindow->show();

    return app.exec();
}
