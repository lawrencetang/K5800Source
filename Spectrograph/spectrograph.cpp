#include "spectrograph.h"

#include "usbdriver.h"
#include "usbdata.h"

#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QElapsedTimer>
#include <QApplication>

Spectrograph::Spectrograph(QObject *parent)
    : QObject(parent) {

    initializeParameter();
    initializeDevice();
}

Spectrograph::~Spectrograph() {

    if (m_isOpened) {
        close();
    }
    delete m_pUsbData;
    delete m_pUsbDriver;
}

/**
 * @brief Spectrograph::reset 重置光谱仪
 */
void Spectrograph::reset() {

    if (m_isOpened) {
        close();
    }

    delete m_pUsbDriver;
    delete m_pUsbData;

    initializeParameter();
    initializeDevice();
}

/**
 * @brief Spectrograph::isOpened 获取光谱仪是否为打开状态
 * @return true-打开; false-关闭
 */
bool Spectrograph::isOpened() {
    return m_isOpened;
}

/**
 * @brief Spectrograph::setIntegrationTime 设置积分时间
 * @param time 积分时间(单位:ms)
 */
void Spectrograph::setIntegrationTime(int time) {
    m_integrationTime = time;
}

/**
 * @brief Spectrograph::open 打开光谱仪
 * @return 是否成功
 */
bool Spectrograph::open() {

    m_isOpened = true;
    int spectrometerNumber = m_pUsbDriver->Usb_openAllSpectrometers();
    if (1 != spectrometerNumber) {
        if (0 == spectrometerNumber) {
            emit error( spectrometerNumber, tr( "No Spectrometer!") );
        } else {
            emit error( spectrometerNumber, tr( "System Error!") );
        }
        m_isOpened = false;
    }

    return m_isOpened;
}

/**
 * @brief Spectrograph::close 关闭光谱仪
 */
void Spectrograph::close() {
    if (m_isOpened) {
        m_pUsbDriver->Usb_closeAllSpectrometers();
    }
    m_isOpened = false;
}

/**
 * @brief Spectrograph::measure 测量数据
 * @param waveLength 波长
 * @param spectrum 光谱数据
 * @return 读取的数据大小
 */
int Spectrograph::measure(QVector<int> &waveLength,
                          QVector<double> &spectrum, int count) {

    if (!m_isOpened) {
        return 0;
    }

    DOUBLEARRAY_T spectrumArray = NULL;
    DOUBLEARRAY_T wavelengthArray = NULL;

    spectrumArray = m_pUsbData->Usb_Create();//lt:光谱数据
    if (NULL == spectrumArray) {
        return 0;
    }
    wavelengthArray = m_pUsbData->Usb_Create();//lt:波长数组
    if (NULL == wavelengthArray) {
        m_pUsbData->Usb_Destroy( spectrumArray );//lt:未建立成功
        return 0;
    }

    /*
    * 1. 设置积分时间
    * 2. 开灯
    * 3. 获取波长
    * 4. 获取光强
    * 5. 关灯
    */
    m_pUsbDriver->Usb_setTimeout( 0, 500 );
    m_pUsbDriver->Usb_setIntegrationTime( 0, m_integrationTime );//lt:设置积分时间
    m_pUsbDriver->Usb_setStrobeEnable( 0, TRUE );//lt:开灯

    m_xSource.clear();
    m_ySource.clear();
    int c = 0, startCount = 2;
    for (int t = 0; t < count + startCount; t ++) {
        m_pUsbDriver->Usb_getWavelengths( 0, wavelengthArray ) ;
        m_pUsbDriver->Usb_getSpectrum( 0, spectrumArray );
        if (t < startCount) {
            continue;
        }//lt:开始两次不算?
        int size = m_pUsbData->Usb_getLength( spectrumArray );
        double sum = 0;
        for (int i = 0; i < size; i ++) {
            sum += m_pUsbData->Usb_getElementAt( spectrumArray, i );
            if (0 != sum) {
                break;
            }
        }//lt:得到值?
        if (sum == 0) {
            continue;
        }//lt:在整个数组长度内没有得到值，则进行下次count获取光谱和波长数组
        if (m_xSource.isEmpty()) {
            for (int i = 0; i < size; i ++) {
                m_xSource.append( m_pUsbData->Usb_getElementAt( wavelengthArray, i ) );
                m_ySource.append( m_pUsbData->Usb_getElementAt( spectrumArray, i ) );
            }//lt:把第一次得到的数据放到m_xsource和m_ysource中
        } else {
            double xValue;
            double yValue;
            for (int i = 0; i < size; i ++) {
                xValue = (m_xSource.at( i )*c + m_pUsbData->Usb_getElementAt( wavelengthArray, i ))/(c + 1);
                yValue = (m_ySource.at( i )*c + m_pUsbData->Usb_getElementAt( spectrumArray, i ))/(c + 1);

                m_xSource.replace( i, xValue );
                m_ySource.replace( i, yValue );//lt:(将之前的值*c+现在值)/(c+1)放到qvector中(取平均)
            }//lt:是什么算法?m_xsource不会变,m_ysource会变
        }
        c ++;
    }

    m_pUsbDriver->Usb_setStrobeEnable( 0, FALSE );//lt:关灯
    m_pUsbDriver->Usb_getSpectrum( 0, spectrumArray );

    // 释放空间
    m_pUsbData->Usb_Destroy( wavelengthArray );
    m_pUsbData->Usb_Destroy( spectrumArray );

    m_yFilter.clear();
    //avgSlidingFilter( m_smoothingWidth, m_yFilter );
    integerProcess( waveLength, spectrum );//lt:整形化,在该函数中取继续处理m_xsource和m_ysource
    //waitting(500);
    return waveLength.size();
}

/**
 * @brief Spectrograph::serialNumber 获取光谱仪序列号
 * @return 序列号
 */
QString Spectrograph::serialNumber() {
    QString snStr;
    if (m_isOpened) {
        snStr = m_pUsbDriver->Usb_getSerialNumber( 0 );
    }
    return snStr;
}

/**
 * @brief Spectrograph::waitting
 * @param timeout
 */
void Spectrograph::waitting(int timeout)
{
    QElapsedTimer t;
    t.start();
    while(t.elapsed() < timeout) {
        QCoreApplication::processEvents();
    }
}

/**
 * @brief Spectrograph::avgSlidingFilter 平均滑动滤波
 * @param width 时间窗宽度
 * @param y 滤波后的数据
 */
void Spectrograph::avgSlidingFilter(int width, QVector<double> &y) {

    if (m_xSource.isEmpty() || m_ySource.isEmpty()) {
        return;
    }

    int size = m_xSource.size();
    if (width <= 0 || width > size || width%2 == 0) {
        return;
    }

    QVector<double> data;//lt:g
    /*
    data.append( m_ySource.mid( 0, width/2 ) );
    data.append( m_ySource );
    data.append( m_ySource.mid( size - width/2, width/2) );
    */
    data<<( m_ySource.mid( 0, width/2 ) );
    data<<( m_ySource );
    data<<( m_ySource.mid( size - width/2, width/2) );


    y.clear();
    double sum = 0.0;
    for (int i = 0; i < m_ySource.size(); i ++) {
        sum = 0;
        for (int w = 0; w < width; w ++) {
            sum += data.at( i + w );
        }
        y.append( sum/(double)width );
    }
}

/**
 * @brief Spectrograph::integerProcess
 *      把光谱数据整数化
 *      把整数波长所属的所有光谱数据平均，如：
 *          key = 201.036383, value = 807.484821
 *          key = 201.419255, value = 849.614464
 *          key = 201.802095, value = 837.911786
 *      整数化的结果为：
 *          key = 201,        value = 831.670357
 *      整数化后波长值范围：[189, 891]
 * @param x 处理后的x轴数据
 * @param y 处理后的y轴数据
 */
void Spectrograph::integerProcess(QVector<int> &x, QVector<double> &y) {

    int    key = 0;
    int    valueCount = 0;
    double valueTotal = 0;

    x.clear();
    y.clear();

    int size = m_xSource.size();
    for (int i = 0; i < size; ) {
        key = m_xSource.at( i );
        valueCount = 0;
        valueTotal = 0;
        while (i < size && (int)m_xSource.at( i ) == key) {
            valueTotal += m_ySource.at( i );
            valueCount ++;
            i ++;
        }
        x.append( key + m_offset );//lt:m_offset = 0
        y.append( valueTotal / valueCount );
    }
}

/**
 * @brief Spectrograph::initializeParameter
 */
void Spectrograph::initializeParameter() {
    m_pUsbDriver = NULL;
    m_pUsbData = NULL;
    m_integrationTime = 40000;
    m_offset = 0;
    //m_smoothingWidth = 11;
    m_isOpened = false;
    m_xSource.clear();
    m_ySource.clear();
    m_yFilter.clear();

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
    m_offset = configIniReader->value( "/System/Offset" ).toInt();//lt:0

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief Spectrograph::initialize 初始化
 */
void Spectrograph::initializeDevice() {

    int status = 0;
    // 加载UsbDriver动态库
    if (NULL == m_pUsbDriver) {
        m_pUsbDriver = new UsbDriver();
    }

    // 1.加载动态库OmniDriver32.dll及API
    status = m_pUsbDriver->UsbDriverInit();
    if (status) {
        emit error( status, tr( "Load OmniDriver32.dll and API Failed!") );
    } else {
        status = m_pUsbDriver->Usb_Create();
        if (status) {
            emit error( status, tr( "Excute OmniDriver32.dll->Create Failed!") );
        }
    }

    // 加载UsbData动态库
    if (NULL == m_pUsbData) {
        m_pUsbData = new UsbData();
    }

    // 2.加载动态库common32.dll及API
    status = 0;
    status = m_pUsbData->UsbDataInit();
    if (status) {
        emit error( status, tr( "Load common32.dll and API Failed!") );
    }
}

