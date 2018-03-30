#include "fsdialog.h"
#include "ui_fsdialog.h"

#include <QDir>
#include <QSettings>
#include <QDesktopWidget>

FsDialog::FsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FsDialog) {
    ui->setupUi(this);

    initializeSystem();
    initializeWidget();
}

FsDialog::~FsDialog() {
    delete ui;
}

/**
 * @brief FsDialog::showView
 * @param id
 * @param concStr
 * @param unitStr
 */
void FsDialog::showView(int id, QString concStr, QString unitStr) {
    m_rowId = id;
    ui->concDoubleSpinBox->setValue( concStr.toDouble() );
    int itmeId = ui->unitComboBox->findText( unitStr );
    if (itmeId != -1) {
        ui->unitComboBox->setCurrentIndex( itmeId );
    }

    show();

    QDesktopWidget *deskdop = QApplication::desktop();
    QPoint centerPoint = deskdop->rect().center() - rect().center();
    move( centerPoint );
}

/**
 * @brief FsDialog::unitStr
 * @return
 */
QString FsDialog::unitStr() {
    return ui->unitComboBox->currentText();
}

/**
 * @brief FsDialog::concStr
 * @return
 */
QString FsDialog::concStr() {
    return QString::number( ui->concDoubleSpinBox->value() );
}

/**
 * @brief FsDialog::hideView
 */
void FsDialog::hideView() {
    if (ui->okPBtn == this->sender()) {
        emit settingOk( m_rowId );
    }
    hide();
}

/**
 * @brief FsDialog::initializeSystem
 */
void FsDialog::initializeSystem() {
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    QStringList unitStrList = configIniReader->value( "/FittingView/Unit" ).toStringList();
    for(int i = 0; i < unitStrList.size(); i ++) {
        ui->unitComboBox->addItem( QIcon( ":/icons/uint.png" ), unitStrList.at( i ) );
    }

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief FsDialog::initializeWidget
 */
void FsDialog::initializeWidget() {

    setModal( true );
    connect(ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideView()));
    connect(ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideView()));
}


