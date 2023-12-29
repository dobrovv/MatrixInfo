#include "QMatrixWidgetElement.h"

#include <QFocusEvent>
#include <QResizeEvent>
#include <QFontMetricsF>

QMatrixWidgetElement::QMatrixWidgetElement(CNumber value, int row, int column,QWidget *parent)
    : QWidget(parent), val(value), i_pos(row), j_pos(column)
{
    QString valString = val.toString();
    if (val.rational() && val.denominator() != 1) {
        valString = "<sup>" + valString.replace("/","</sup>/<sub>") + "</sub>";
    }

    lbl = new QLabel(valString,this);
    lne = new QLineEdit(val.toString(),this);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setMargin(0);
    lbl->setIndent(0);

    setFocusPolicy(Qt::StrongFocus);
    lne->setFocusPolicy(Qt::NoFocus);

    connect(lne, &QLineEdit::editingFinished, this, &QMatrixWidgetElement::editingFinished);

    lne->hide();
    lbl->show();
}

void QMatrixWidgetElement::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
    lbl->hide();
    lne->show();
    lne->setFocus();
    lne->selectAll();
}

void QMatrixWidgetElement::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QFont font = fontToFitBound(lbl->font(), lbl->contentsRect().size(), val.toString());
    lbl->setFont(font);
    lne->setFont(font);


    lne->resize(event->size());
    lbl->resize(event->size());
    updateGeometry();
}

void QMatrixWidgetElement::editingFinished()
{
    CNumber value = CNumber::fromString(lne->text());

    if (val == value){
        lne->hide();
        lbl->show();
        return;
    }

    val = value;

    QString valString = val.toString();
    if (val.rational() && val.denominator() != 1) {
        valString = "<sup>" + valString.replace("/","</sup>/<sub>") + "</sub>";
    }

    lbl->setText(valString);
    emit elementChanged(value, i_pos, j_pos);

    QFont font = fontToFitBound(lbl->font(), lbl->contentsRect().size(), val.toString());
    lbl->setFont(font);
    lne->setFont(font);

    updateGeometry();

    lne->hide();
    lbl->show();
}

QFont fontToFitBound (QFont font, QSize bound, QString string) {

    int fontSize = 15;
    while( true )
    {
        QFont f(font);
        f.setPixelSize( fontSize );
        QRect r = QFontMetrics(f).boundingRect( string );
        if (r.height() < bound.height() && r.width() < bound.width() )
            fontSize++;
        else
            break;
    }

    font.setPixelSize(fontSize);
    return font;
}
