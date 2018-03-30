#ifndef OLIGOCALCULATOR_H
#define OLIGOCALCULATOR_H

#include <QFrame>

namespace Ui {
class OligoCalculator;
}

class OligoCalculator : public QFrame
{
    Q_OBJECT

public:
    explicit OligoCalculator(QWidget *parent = 0);
    ~OligoCalculator();

public slots:
    void calculate();

private:
    Ui::OligoCalculator *ui;
    void clear();
};

#endif // OLIGOCALCULATOR_H
