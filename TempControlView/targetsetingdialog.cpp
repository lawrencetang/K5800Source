#include "targetsetingdialog.h"
#include "ui_targetsetingdialog.h"

TargetSetingDialog::TargetSetingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetSetingDialog) {
    ui->setupUi(this);

    connect(ui->startpBtn, SIGNAL(clicked(bool)), this, SLOT(okBtnClicked()));
    connect(ui->cancelpBtn, SIGNAL(clicked(bool)), this, SLOT(hide()));
}

TargetSetingDialog::~TargetSetingDialog() {
    delete ui;
}

/**
 * @brief TargetSetingDialog::okBtnClicked 点击按钮
 */
void TargetSetingDialog::okBtnClicked() {
    double temperture = ui->doubleSpinBox->value();
    emit targetChanged( temperture );
    hide();
}
