#include "toolsview.h"
#include "ui_toolsview.h"

#include <QDir>
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

const QSize tvSize = QSize(400, 300);

ToolsView::ToolsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolsView) {
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setModal(Qt::ApplicationModal);

    m_isShow = false;
    initializeWidget();
    resize(tvSize);
}

ToolsView::~ToolsView() {
    delete ui;
}

/**
 * @brief ToolsView::showDirView
 */
void ToolsView::showDirView() {
    m_pCurToolButton = ui->datatBtn;
    m_pCurToolButton->setChecked( true );
}

/**
 * @brief ToolsView::showRecordView
 */
void ToolsView::showRecordView() {
    m_pCurToolButton = ui->recordtBtn;
    m_pCurToolButton->setChecked( true );
}

/**
 * @brief ToolsView::hideDirView
 */
void ToolsView::hideDirView() {
    m_pCurToolButton = ui->datatBtn;
    m_pCurToolButton->setChecked( false );
    finishOption();
}

/**
 * @brief ToolsView::hideRecordView
 */
void ToolsView::hideRecordView() {
    m_pCurToolButton = ui->recordtBtn;
    m_pCurToolButton->setChecked( false );
    finishOption();
}

/**
 * @brief ToolsView::setCameraEnable
 * @param ok
 */
void ToolsView::setCameraEnable(bool ok) {
    m_cameraEnable = ok;
    ui->cameratBtn->setEnabled( ok );
}

/**
 * 函数名称: showDialog
 * 函数用途: 显示窗体
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void ToolsView::showDialog() {

    if (!m_isShow) {
        m_isShow = true;
        show();
        QPropertyAnimation *animation = new QPropertyAnimation( this, "size" );
        animation->setDuration( 500 );
        animation->setStartValue( QSize(0,0) );
        animation->setEndValue( tvSize );
        animation->start();
    } else {
        hideDialog();
    }

}

/**
 * 函数名称: hideDialog
 * 函数用途: 隐藏窗体
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void ToolsView::hideDialog() {
    if (m_isShow) {
        m_isShow = false;
        m_pCurToolButton = static_cast<QToolButton *>( this->sender() );

        QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
        animation->setDuration(500);
        animation->setStartValue(tvSize);
        animation->setEndValue(QSize(0, 0));
        animation->start();

        connect(animation, SIGNAL(finished()), this, SLOT(hide()));
        connect(animation, SIGNAL(finished()), this, SLOT(finishOption()));
    }
}

/**
 * 函数名称: onToolBtnClicked
 * 函数用途: 相应点击事件
 * 输入参数:
 *          ok = true/false
 * 输出参数:
 *          无
 */
void ToolsView::finishOption() {
    if (NULL == m_pCurToolButton) {
        return;
    }
    bool ok = m_pCurToolButton->isChecked();
    if (m_pCurToolButton == ui->datatBtn) {
        ui->oligotBtn->setEnabled( !ok );
        if (m_cameraEnable) {
            ui->cameratBtn->setEnabled( !ok );
        }
        emit triggered(1, ok);
    } else if (m_pCurToolButton == ui->recordtBtn) {
        ui->oligotBtn->setEnabled( !ok );
        if (m_cameraEnable) {
            ui->cameratBtn->setEnabled( !ok );
        }
        emit triggered(2, ok);
    } else if (m_pCurToolButton == ui->oligotBtn) {
        ui->datatBtn->setEnabled( !ok );
        ui->printtBtn->setEnabled( !ok );
        if (m_cameraEnable) {
            ui->cameratBtn->setEnabled( !ok );
        }
        ui->recordtBtn->setEnabled( !ok );
        ui->picturetBtn->setEnabled( !ok );
        emit triggered(3, ok);
    } else if (m_pCurToolButton == ui->cameratBtn) {
        ui->datatBtn->setEnabled( !ok );
        ui->printtBtn->setEnabled( !ok );
        ui->oligotBtn->setEnabled( !ok );
        ui->recordtBtn->setEnabled( !ok );
        ui->picturetBtn->setEnabled( !ok );
        emit triggered(4, ok);
    } else if (m_pCurToolButton == ui->printtBtn) {
        emit triggered(5, ok);
    } else if (m_pCurToolButton == ui->picturetBtn) {
        emit triggered(6, ok);
    } else if (m_pCurToolButton == ui->helptBtn) {
        emit triggered(7, ok);
    } else if (m_pCurToolButton == ui->mergetBtn) {
        emit triggered(8, ok);
    }
}

/**
 * 函数名称: initializeWidget
 * 函数用途: 初始化
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void ToolsView::initializeWidget() {
    QString toolsIconsPath = QDir::currentPath() + "/images/tools/";

    ui->oligotBtn->setIcon(QIcon(toolsIconsPath + "Oligo.png"));
    connect(ui->oligotBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->cameratBtn->setIcon(QIcon(toolsIconsPath + "Camera.png"));
    connect(ui->cameratBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->picturetBtn->setIcon(QIcon(toolsIconsPath + "Picture.png"));
    connect(ui->picturetBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->printtBtn->setIcon(QIcon(toolsIconsPath + "Print.png"));
    connect(ui->printtBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->datatBtn->setIcon(QIcon(toolsIconsPath + "Data.png"));
    connect(ui->datatBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->recordtBtn->setIcon(QIcon(toolsIconsPath + "Record.png"));
    connect(ui->recordtBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->helptBtn->setIcon(QIcon(toolsIconsPath + "Help.png"));
    connect(ui->helptBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));

    ui->mergetBtn->setIcon(QIcon(toolsIconsPath + "Merge.png"));
    connect(ui->mergetBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
}
