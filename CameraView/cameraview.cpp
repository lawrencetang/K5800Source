#include "cameraview.h"
#include "ui_cameraview.h"

#include <QDebug>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QCamera>
#include <QDateTime>
#include <QCameraInfo>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

#define FREQUENCE 33

CameraView::CameraView(QString systemPath, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CameraView) {
    ui->setupUi(this);

    m_systemPath = QDir::currentPath() + "/" + systemPath;
    initializeSystem();
    initalizeWidgets();
}

CameraView::~CameraView() {
    if (m_isOpen) {
        cvReleaseCapture( &m_pCamera );
        m_pTimer->stop();
    }
    delete ui;
}

/**
 * @brief CameraView::autoCheck
 * @return
 */
bool CameraView::autoCheck() {
    // open
    if (!m_isOpen) {
        m_pCamera = cvCreateCameraCapture( 0 );
        if (m_pCamera == NULL) {
            showMessage( tr( "No Signal!" ) );
            return false;
        }
        m_isOpen = true;
        m_pTimer->start( FREQUENCE );
        ui->openBtn->setText( tr( "Close" ) );
    }
    // check

    // close
    m_isOpen = false;
    cvReleaseCapture( &m_pCamera );
    m_pTimer->stop();
    ui->openBtn->setText( tr( "Open" ) );
    showMessage( tr( "Camera is closed!" ) );

    return true;
}

/**
 * @brief CameraView::upDateImage
 */
void CameraView::upDateImage(QString fileName) {

    QFileInfo fileInfo( fileName );
    QListWidgetItem *item = NULL;
    item = new QListWidgetItem( QIcon( fileInfo.absoluteFilePath() ), fileInfo.fileName() );
    ui->listWidget->addItem( item );
}

/**
 * @brief CameraView::openCamera
 */
void CameraView::openCamera() {
    if (ui->openBtn->text() == tr( "Open" )) {
        if (m_pCamera != NULL) {
            return;
        }

        m_pCamera = cvCreateCameraCapture( 0 );
        if (m_pCamera == NULL) {
            showMessage( tr( "No Signal!" ) );
            return;
        }
        m_isOpen = true;
        m_pTimer->start( FREQUENCE );
        ui->openBtn->setText( tr( "Close" ) );
    } else {
        if (m_pCamera == NULL) {
            return;
        }

        m_isOpen = false;
        cvReleaseCapture( &m_pCamera );
        m_pTimer->stop();
        ui->openBtn->setText( tr( "Open" ) );
        showMessage( tr( "Camera is closed!" ) );
    }
}

/**
 * @brief CameraView::readFrame
 */
void CameraView::readFrame() {
    if (m_isOpen) {
        IplImage *frame = cvQueryFrame( m_pCamera );
        QImage image = toImage( frame );
        QPixmap pixmap = QPixmap::fromImage( image );
        pixmap = pixmap.scaled( ui->cameraLabel->width(), ui->cameraLabel->height() );
        ui->cameraLabel->setPixmap( pixmap );
    }
}

/**
 * @brief CameraView::showCamera
 */
void CameraView::showCamera() {
    if (ui->cameraBtn->text() == tr( "Camera" )) {
        ui->stackedWidget->setCurrentIndex( 0 );
        ui->cameraBtn->setText( tr( "Image" ) );
    } else {
        ui->stackedWidget->setCurrentIndex( 1 );
        ui->cameraBtn->setText( tr( "Camera" ) );

        if (ui->listWidget->count() > 0) {
            showSelectedImage( ui->listWidget->item( 0 ) );
        }
    }
}

/**
 * @brief CameraView::remove
 */
void CameraView::remove() {

    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if (selectedItems.size() == 0) {
        return;
    }

    for (int i = 0; i < selectedItems.size(); i ++) {
        QListWidgetItem *item = selectedItems.at( i );
        QString filename = m_systemPath + "/" + item->text();
        bool ok = QFile::remove( filename );
        if (!ok) {
            QMessageBox::warning(this, tr("Warnning"),
                                 tr("Delete file error!"), QMessageBox::Ok);
            return;
        }
        ui->listWidget->removeItemWidget( item );
        delete item;
    }

    int count = ui->listWidget->count();
    if (count > 0) {
        QListWidgetItem *item = ui->listWidget->item( 0 );
        showSelectedImage( item );
    } else {
        if (ui->listWidget->count() == 0) {
            ui->imageLabel->clear();
            ui->titleLabel->clear();
        }
    }
}

/**
 * @brief CameraView::saveAs
 */
void CameraView::saveAs() {
    // 获取选中的item
    QListWidget *t_pListWidget = ui->listWidget;
    QList<QListWidgetItem *> selectedItems = t_pListWidget->selectedItems();

    if (selectedItems.isEmpty()) {
        return;
    }

    QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode));
    // 获取目录路径
    QString path;
    QString filepath = m_systemPath + "/";
    for (int i = 0; i < selectedItems.size(); i ++) {
        if (path.isEmpty()) {
            path = QDir::currentPath();
        }
        QString newName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                       path, tr("File (*.png)"));
        if (newName.isEmpty()) {
            continue;
        }
        QFileInfo fileInfo( newName );
        path = fileInfo.path();
        // 复制文件到指定目录下
        QListWidgetItem *item = selectedItems.at( i );
        QString filename = filepath + item->text();
        bool ok = QFile::copy( filename, newName );
        if (!ok) {
            QMessageBox::warning(this, tr( "Warnning" ),
                                 tr( "Copy file error!" ), QMessageBox::Ok);
            continue;
        }
    }
}

/**
 * @brief CameraView::showSelectedImage
 * @param item
 */
void CameraView::showSelectedImage(QListWidgetItem *item) {

    if (ui->stackedWidget->currentIndex() != 1) {
        ui->stackedWidget->setCurrentIndex( 1 );
        ui->cameraBtn->setText( tr( "Camera" ) );
    }

    QString filename = m_systemPath + "/" + item->text();
    QPixmap pixmap = QPixmap(filename);
    ui->imageLabel->setPixmap( pixmap );

    QString title = item->text();
    ui->titleLabel->setText( title );
}

/**
 * @brief CameraView::showPageChanged
 * @param id
 */
void CameraView::showPageChanged(int id) {
    if (id == 1) {
        ui->openBtn->setEnabled( false );
    } else {
        ui->openBtn->setEnabled( true );
    }
}

/**
 * @brief CameraView::mouseDoubleClickEvent
 * @param event
 */
void CameraView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (ui->stackedWidget->currentIndex() == 0) {
            capture();
        }
    }
    QFrame::mouseDoubleClickEvent( event );
}

/**
 * @brief CameraView::showMessage
 * @param text
 */
void CameraView::showMessage(QString text) {

    ui->cameraLabel->clear();
    ui->cameraLabel->setText( text );
}

/**
 * @brief CameraView::insert
 * @param pixmap
 */
void CameraView::insert(QPixmap pixmap) {

    if (ui->stackedWidget->currentIndex() != 1) {
        ui->stackedWidget->setCurrentIndex( 1 );
        ui->cameraBtn->setText( tr( "Camera" ) );
    }

    pixmap = pixmap.scaled( ui->imageLabel->width(), ui->imageLabel->height() );
    int row = ui->listWidget->count();
    QString text = QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss") + ".png";
    QListWidgetItem *item = new QListWidgetItem( text );
    item->setIcon( pixmap );
    ui->listWidget->insertItem( row, item );

    QString filename = m_systemPath + "/" + text;
    pixmap.save(filename);
    showSelectedImage( item );
}

/**
 * @brief CameraView::capture
 */
void CameraView::capture() {
    QPixmap pixmap;
    if (m_isOpen) {
        IplImage *frame = cvQueryFrame( m_pCamera );
        QImage image = toImage( frame );

        pixmap = QPixmap::fromImage( image );
        insert( pixmap );
    }
}
/**
 * @brief CameraView::toImage
 * @param iplImg
 * @return
 */
QImage CameraView::toImage(IplImage *iplImg) {
    QImage image;
    int nChannel=iplImg->nChannels;
    if(nChannel == 3) {
        cvConvertImage( iplImg, iplImg, CV_CVTIMG_SWAP_RB );
        image = QImage( (const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_RGB888);
    } else if(nChannel == 4 || nChannel == 1) {
        image = QImage( (const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_ARGB32);
    }
    return image;

}

/**
 * 函数名称: initializeSystem
 * 函数用途: 初始化文件系统
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void CameraView::initializeSystem() {

    // 检查系统文件目录是否存在,如果不存在则创建系统文件目录
    QDir dir(m_systemPath);
    if(!dir.exists()) {
        bool ok = dir.mkdir(m_systemPath);
        if (!ok) {
            QMessageBox::warning(this, tr("Warnning"),
                                 tr("Create dir error!"), QMessageBox::Ok);
            return;
        }
    }

    // 清空listWidget
    ui->listWidget->clear();

    // 加载该目录下所有以.png结尾的所有文件
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i ++) {

        QFileInfo fileinfo = list.at(i);
        if (fileinfo.fileName().endsWith( ".png" )) {
            QListWidgetItem *item = NULL;
            item = new QListWidgetItem( QIcon( fileinfo.absoluteFilePath()), fileinfo.fileName() );
            ui->listWidget->addItem( item );
        }
    }
}

/**
 * 函数名称: initializeWidget
 * 函数用途: 初始化窗体
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void CameraView::initalizeWidgets() {

    m_isOpen = true;
    m_pCamera = NULL;
    m_pTimer = new QTimer( this );

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(readFrame()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(showSelectedImage(QListWidgetItem *)));
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(showPageChanged(int)));
    connect(ui->openBtn, SIGNAL(clicked(bool)), this, SLOT(openCamera()));
    connect(ui->cameraBtn, SIGNAL(clicked(bool)), this, SLOT(showCamera()));
    connect(ui->removeBtn, SIGNAL(clicked(bool)), this, SLOT(remove()));
    connect(ui->moveToBtn, SIGNAL(clicked(bool)), this, SLOT(saveAs()));
}
