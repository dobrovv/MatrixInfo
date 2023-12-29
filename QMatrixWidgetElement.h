#ifndef QMATRIXWIDGETELEMENT_H
#define QMATRIXWIDGETELEMENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "CNumber.h"

class QMatrixWidgetElement : public QWidget
{
    Q_OBJECT

    QLabel *lbl;
    QLineEdit *lne;

    CNumber val;
    int i_pos, j_pos;


public:
    QMatrixWidgetElement(CNumber value=0.0, int row=-1, int column=-1, QWidget *parent=0);

protected:
    void focusInEvent(QFocusEvent * event);
    void resizeEvent(QResizeEvent * event);


signals:
    void elementChanged(CNumber value, int row, int column);

private slots:
    void editingFinished();


};

QFont fontToFitBound (QFont font, QSize bound, QString string);


#endif // QMATRIXWIDGETELEMENT_H
