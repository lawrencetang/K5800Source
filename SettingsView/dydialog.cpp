#include "dydialog.h"
#include "ui_dydialog.h"

#include <QDebug>

DyDialog::DyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DyDialog) {
    ui->setupUi(this);

    setModal( true );
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    //ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
}

DyDialog::~DyDialog() {
    delete ui;
}

/**
 * @brief DyDialog::defaultInfo
 */
void DyDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief DyDialog::showDialog
 * @param paramStr
 */
void DyDialog::showDialog(QString paramStr, QString watchStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    if (!watchStr.isEmpty()) {
        initializeWatchs( watchStr );
    }
    show();
}

/**
 * @brief DyDialog::hideDialog
 */
void DyDialog::hideDialog() {
    QObject *object = this->sender();
    if (ui->okPBtn == object) {
        saveData();
        emit okBtnClicked();
    }
    hide();
}

/**
 * @brief DyDialog::wathLabelEnable
 * @param ok
 */
void DyDialog::wathLabelEnable(bool ok) {

    QCheckBox *checkBox = static_cast<QCheckBox *>(sender());
    if (checkBox == ui->tvCheckBox) {
        ui->tvDoubleSpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl2CheckBox) {
        ui->wl2SpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl3CheckBox) {
        ui->wl3SpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl4CheckBox) {
        ui->wl4SpinBox->setEnabled( ok );
    } else if (checkBox == ui->wl5CheckBox) {
        ui->wl5SpinBox->setEnabled( ok );
    }
}

/**
 * @brief DyDialog::saveData
 */
void DyDialog::saveData() {

    m_paramStr.clear();
    m_paramStr.append( "type=Dynamic" );
    m_paramStr.append( "," );
    m_paramStr.append( "wave=" + QString::number( ui->wl1SpinBox->value() ) );
    m_paramStr.append( "," );
    if (ui->tvCheckBox->isChecked()) {
        m_paramStr.append( "target=" + QString::number( ui->tvDoubleSpinBox->value() ) );
    } else {
        m_paramStr.append( "target=NULL" );
    }

    m_paramStr.append( "," );
    m_paramStr.append( "times=" + QString::number( ui->mtSpinBox->value() ));

    m_watchStr.clear();
    m_watchStr.append( "A" + QString::number( ui->wl1SpinBox->value() ) );

    m_watchStr.append( "," );
    if (ui->wl2CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl2SpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    if (ui->wl3CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl3SpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    if (ui->wl4CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl4SpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
    }

    m_watchStr.append( "," );
    if (ui->wl5CheckBox->isChecked()) {
        m_watchStr.append( "A" + QString::number( ui->wl5SpinBox->value() ) );
    } else {
        m_watchStr.append( "NULL" );
    }
}

/**
 * @brief DyDialog::initializeDialog
 * @param paramStr
 */
void DyDialog::initializeDialog(QString paramStr) {

    QMap<QString, QString> paramMap;
    QStringList paramList = paramStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < paramList.size(); i ++) {

        QString itemStr = paramList.at( i );
        QStringList itemList = itemStr.split( "=",  QString::SkipEmptyParts );
        if (itemList.isEmpty()) {
            continue;
        }
        paramMap.insert( itemList.first(), itemList.last() );
    }

    ui->wl1SpinBox->setValue( paramMap.value( "wave" ).toInt() );
    ui->mtSpinBox->setValue( paramMap.value( "times" ).toInt() );
    QString targetStr = paramMap.value( "target" );
    bool ok;
    if ( targetStr == "NULL" ) {
        ok = false;
        targetStr = "200";
    } else {
        ok = true;
        targetStr = targetStr.replace( "A", "" );
    }
    ui->tvCheckBox->setChecked( ok );
    ui->tvDoubleSpinBox->setValue( targetStr.toDouble() );
    ui->tvDoubleSpinBox->setEnabled( ok );
}

void DyDialog::initializeWatchs(QString watchStr) {

    QStringList watchList = watchStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < watchList.size(); i ++) {
        QString itemStr = watchList.at( i );
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
            ui->wl1SpinBox->setValue( itemStr.toInt() );
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
 * @brief DyDialog::initializeSystem
 */
void DyDialog::initializeSystem() {

}

/**
 * @brief DyDialog::initializeWidget
 */
void DyDialog::initializeWidget() {
    ui->tvDoubleSpinBox->setEnabled( false );
    ui->wl2SpinBox->setEnabled( false );
    ui->wl3SpinBox->setEnabled( false );
    ui->wl4SpinBox->setEnabled( false );
    ui->wl5SpinBox->setEnabled( false );

    connect( ui->tvCheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl2CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl3CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl4CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));
    connect( ui->wl5CheckBox, SIGNAL(clicked(bool)), this, SLOT(wathLabelEnable(bool)));

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
}
