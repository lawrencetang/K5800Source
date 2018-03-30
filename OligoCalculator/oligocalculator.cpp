#include "oligocalculator.h"
#include "ui_oligocalculator.h"

OligoCalculator::OligoCalculator(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OligoCalculator) {
    ui->setupUi(this);
    connect(ui->inputTextEdit, SIGNAL(textChanged()), this, SLOT(calculate()));
}

OligoCalculator::~OligoCalculator() {
    delete ui;
}

/**
 * 函数名称: calculate
 * 函数用途: 计算引物的退火温度（Tm），分子量和1OD260相当于多少摩尔数
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void OligoCalculator::calculate() {

    QString text = ui->inputTextEdit->toPlainText();
    if (!text.isEmpty()) {
        QRegExp regExp("[^ACGT]");
        if (text.count(regExp)) {
            text.replace(regExp, "");
            ui->inputTextEdit->setPlainText(text);
        }
    }
    clear();

    int A = text.count("A");
    int C = text.count("C");
    int G = text.count("G");
    int T = text.count("T");

    int Number = A + C + G + T;
    if (0 == Number) {
        return;
    }
    int GC = (G + C)*100/Number;

    double Tm = 0;
    if (Number >= 14 && Number <= 20) {
        Tm = 4*(G+C)+2*(A+T);
    } else if (Number > 20) {
        Tm = 0.41*(double)GC- 675/(double)Number + 81.5;
    }

    int MW = (A*312)+(C*288)+(G*328)+(T*303)-61;

    int OD260 = 0;
    if (0 != MW) {
        OD260 = 33*1000000/MW;
    }

    ui->nbLineEdit->setText(QString::number(Number));
    ui->gcLineEdit->setText(QString::number(GC));
    ui->tmLineEdit->setText(QString::number(Tm, 'g'));
    ui->mwLineEdit->setText(QString::number(MW));
    ui->odLineEdit->setText(QString::number(OD260));
}

/**
 * 函数名称: clear
 * 函数用途: 清空计算结果
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void OligoCalculator::clear() {
    ui->nbLineEdit->clear();
    ui->gcLineEdit->clear();
    ui->tmLineEdit->clear();
    ui->mwLineEdit->clear();
    ui->odLineEdit->clear();
}
