#include "uvdialog.h"
#include "ui_uvdialog.h"

UvDialog::UvDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UvDialog) {
    ui->setupUi(this);

    setModal( true );
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    //ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
}

UvDialog::~UvDialog() {
    delete ui;
}

void UvDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief UvDialog::showDialog
 * @param paramStr
 */
void UvDialog::showDialog(QString paramStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    show();
}

/**
 * @brief UvDialog::hideDialog
 */
void UvDialog::hideDialog() {
    QObject *object = this->sender();
    if (ui->okPBtn == object) {
        saveData();
        emit okBtnClicked();
    }
    hide();
}

/**
 * @brief UvDialog::wathLabelEnable
 * @param ok
 */
void UvDialog::wathLabelEnable(bool ok) {

    QCheckBox *checkBox = static_cast<QCheckBox *>(sender());
    if (checkBox == ui->wl1CheckBox) {
        ui->wl1SpinBox->setEnabled( ok );
        ui->cf1DoubleSpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl2CheckBox) {
        ui->wl2SpinBox->setEnabled( ok );
        ui->cf2DoubleSpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl3CheckBox) {
        ui->wl3SpinBox->setEnabled( ok );
        ui->cf3DoubleSpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl4CheckBox) {
        ui->wl4SpinBox->setEnabled( ok );
        ui->cf4DoubleSpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl5CheckBox) {
        ui->wl5SpinBox->setEnabled( ok );
        ui->cf5DoubleSpinBox->setEnabled( ok );
    }
}

/**
 * @brief UvDialog::saveData
 */
void UvDialog::saveData() {

    m_watchStr.clear();
    m_paramStr.clear();
    if (ui->wl1CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl1SpinBox->value() ) );
        m_paramStr.append( "Coef1=" + QString::number( ui->cf1DoubleSpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
        m_paramStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    m_paramStr.append( "," );
    if (ui->wl2CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl2SpinBox->value() ) );
        m_paramStr.append( "Coef2=" + QString::number( ui->cf2DoubleSpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
        m_paramStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    m_paramStr.append( "," );
    if (ui->wl3CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl3SpinBox->value() ) );
        m_paramStr.append( "Coef3=" + QString::number( ui->cf3DoubleSpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
        m_paramStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    m_paramStr.append( "," );
    if (ui->wl4CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl4SpinBox->value() ) );
        m_paramStr.append( "Coef4=" + QString::number( ui->cf4DoubleSpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
        m_paramStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    m_paramStr.append( "," );
    if (ui->wl5CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl5SpinBox->value() ) );
        m_paramStr.append( "Coef5=" + QString::number( ui->cf5DoubleSpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
        m_paramStr.append( "NULL" );
    }
}

/**
 * @brief UvDialog::initializeDialog
 * @param paramStr
 */
void UvDialog::initializeDialog(QString paramStr) {

    QStringList paramList = paramStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < paramList.size(); i ++) {
        QString itemStr = paramList.at( i );
        bool ok = false;
        if (itemStr == "NULL") {
            ok = false;
            itemStr = "200";
        } else {
            ok = true;
            itemStr = itemStr.replace( "A", "" );
        }

        switch( i ) {
        case 0:
            ui->wl1CheckBox->setChecked( ok );
            ui->wl1SpinBox->setValue( itemStr.toInt() );
            ui->wl1SpinBox->setEnabled( ok );
            break;
        case 1:
            ui->wl2CheckBox->setChecked( ok );
            ui->wl2SpinBox->setValue( itemStr.toInt() );
            ui->wl2SpinBox->setEnabled( ok );
            break;
        case 2:
            ui->wl3CheckBox->setChecked( ok );
            ui->wl3SpinBox->setValue( itemStr.toInt() );
            ui->wl3SpinBox->setEnabled( ok );
            break;
        case 3:
            ui->wl4CheckBox->setChecked( ok );
            ui->wl4SpinBox->setValue( itemStr.toInt() );
            ui->wl4SpinBox->setEnabled( ok );
            break;
        case 4:
            ui->wl5CheckBox->setChecked( ok );
            ui->wl5SpinBox->setValue( itemStr.toInt() );
            ui->wl5SpinBox->setEnabled( ok );
            break;
        }
    }
}

/**
 * @brief UvDialog::initializeSystem
 */
void UvDialog::initializeSystem() {

}

/**
 * @brief UvDialog::initializeWidget
 */
void UvDialog::initializeWidget() {

    ui->wl2SpinBox->setEnabled( false );
    ui->wl3SpinBox->setEnabled( false );
    ui->wl4SpinBox->setEnabled( false );
    ui->wl5SpinBox->setEnabled( false );
    ui->cf2DoubleSpinBox->setEnabled( false );
    ui->cf3DoubleSpinBox->setEnabled( false );
    ui->cf4DoubleSpinBox->setEnabled( false );
    ui->cf5DoubleSpinBox->setEnabled( false );

    connect( ui->wl1CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl2CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl3CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl4CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl5CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
}
