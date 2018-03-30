#include "usbdriver.h"
#include <QDebug>

UsbDriver::UsbDriver()
{
    lib_omni_dll = NULL;
    m_pWrapper = NULL;
}

UsbDriver::~UsbDriver()
{
    if (lib_omni_dll != NULL)
    {
        lib_omni_dll->unload();
        lib_omni_dll = NULL;
    }
}

/**
 * 函数名  UsbDriverInit
 * 描述   ：加载动态库，验证是否所有API成功加载
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：1：加载动态库失败
 *          2：加载部分API失败
 *          0：加载动态库及API成功
 */
int UsbDriver::UsbDriverInit()
{
    // 如果已经加载，直接返回，避免重复加载
    if (lib_omni_dll != NULL)
    {
        return 0;
    }

    lib_omni_dll = new QLibrary("OmniDriver32.dll");
    if (!lib_omni_dll->load())
    {
        lib_omni_dll = NULL;
        return 1;
    }

    Wrapper_Create_t                = (Wrapper_Create_T                 )lib_omni_dll->resolve("Wrapper_Create");
    Wrapper_Destroy_t               = (Wrapper_Destroy_T                )lib_omni_dll->resolve("Wrapper_Destroy");
    Wrapper_getApiVersion_t         = (Wrapper_getApiVersion_T          )lib_omni_dll->resolve("Wrapper_getApiVersion");
    Wrapper_getBuildNumber_t        = (Wrapper_getBuildNumber_T         )lib_omni_dll->resolve("Wrapper_getBuildNumber");
    Wrapper_getSerialNumber_t       = (Wrapper_getSerialNumber_T        )lib_omni_dll->resolve("Wrapper_getSerialNumber");
    Wrapper_openAllSpectrometers_t  = (Wrapper_openAllSpectrometers_T   )lib_omni_dll->resolve("Wrapper_openAllSpectrometers");
    Wrapper_closeAllSpectrometers_t = (Wrapper_closeAllSpectrometers_T  )lib_omni_dll->resolve("Wrapper_closeAllSpectrometers");
    Wrapper_setIntegrationTime_t    = (Wrapper_setIntegrationTime_T     )lib_omni_dll->resolve("Wrapper_setIntegrationTime");
    Wrapper_getIntegrationTime_t    = (Wrapper_getIntegrationTime_T     )lib_omni_dll->resolve("Wrapper_getIntegrationTime");
    Wrapper_setTimeout_t            = (Wrapper_setTimeout_T             )lib_omni_dll->resolve("Wrapper_setTimeout");
    Wrapper_setStrobeEnable_t       = (Wrapper_setStrobeEnable_T        )lib_omni_dll->resolve("Wrapper_setStrobeEnable");
    Wrapper_getWavelengths_t        = (Wrapper_getWavelengths_T         )lib_omni_dll->resolve("Wrapper_getWavelengths");
    Wrapper_getSpectrum_t           = (Wrapper_getSpectrum_T            )lib_omni_dll->resolve("Wrapper_getSpectrum");

    if (    Wrapper_Create_t                && Wrapper_Destroy_t &&
            Wrapper_getApiVersion_t         && Wrapper_getBuildNumber_t &&
            Wrapper_getSerialNumber_t       &&
            Wrapper_openAllSpectrometers_t  && Wrapper_closeAllSpectrometers_t &&
            Wrapper_setIntegrationTime_t    && Wrapper_getIntegrationTime_t &&
            Wrapper_setTimeout_t            &&
            Wrapper_setStrobeEnable_t       &&
            Wrapper_getWavelengths_t        && Wrapper_getSpectrum_t)
    {
        return 0;
    }

    lib_omni_dll->unload();
    lib_omni_dll = NULL;

    return 2;
}

/**
 * 函数名  UsbDriverClose
 * 描述   ：卸载动态库
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：无
 */
void UsbDriver::UsbDriverClose()
{
    if (lib_omni_dll != NULL)
    {
        lib_omni_dll->unload();
        lib_omni_dll = NULL;
    }
}

/**
 * 函数名  Usb_Create
 * 描述   ：新建一个Wrapper实例。
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：Wrapper实例指针
 */
int UsbDriver::Usb_Create()
{
    if (lib_omni_dll != NULL)
    {
        m_pWrapper = Wrapper_Create_t();
    }
    return (m_pWrapper == NULL) ? 1 : 0;
}

/**
 * 函数名  Usb_Destroy
 * 描述   ：释放Wrapper实例。
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：无
 */
void UsbDriver::Usb_Destroy()
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_Destroy_t(m_pWrapper);
    }
}

/**
 * 函数名  Usb_getApiVersion
 * 描述   ：获取动态库的API版本号。
 * 输入   ：无
 * 输出   ：JSTRING_T retval：动态库的API版本号
 * 返回值  ：无
 */
void UsbDriver::Usb_getApiVersion(JSTRING_T retval)
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_getApiVersion_t(m_pWrapper, retval);
    }
}

/**
 * 函数名  Usb_getBuildNumber
 * 描述   ：获取动态库的Build版本号。
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：动态库的Build版本号
 */
int UsbDriver::Usb_getBuildNumber()
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_getBuildNumber_t(m_pWrapper);
    }
    return 0;
}

/*
    // 读取Serial Number
    int address;
    JSTRING_T retJStr = &address;
    usbDriver.Usb_getSerialNumber(0, retJStr);

    char test[128];

    int i = 0;
    char *charAddr = (char *)address;
    while ((*charAddr) != 0)
    {
        test[i++] = *charAddr;
        charAddr++;
    }
    qDebug("%s", test);
 * */
QString UsbDriver::Usb_getSerialNumber(int spectrometerIndex)
{
    QString serialNumber = "";
    int address;
    char *charAddress;
    JSTRING_T retval = &address;
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        Wrapper_getSerialNumber_t(m_pWrapper, spectrometerIndex, retval);
        charAddress = (char *)address;
        while ((*charAddress) != 0)
        {
            serialNumber.append(*charAddress++);
        }
    }
    return serialNumber;
}

/**
 * 函数名  Usb_openAllSpectrometers
 * 描述   ：打开所有基于USB的分光仪
 *          如果用户在应用程序启动并调用此函数后，才插入分光仪，你必须先调用Usb_closeAllSpectrometers，再调用此函数
 *          如果不调用Usb_closeAllSpectrometers，重复调用此函数，什么也不会做。
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：分光仪个数
 *          I/O错误：-1，调用getLastException()获取真实错误信息(未实现)
 */
int UsbDriver::Usb_openAllSpectrometers()
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_openAllSpectrometers_t(m_pWrapper);
    }
    return 0;
}

/**
 * 函数名  Usb_closeAllSpectrometers
 * 描述   ：释放分光仪资源
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：无
 */
void UsbDriver::Usb_closeAllSpectrometers()
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_closeAllSpectrometers_t(m_pWrapper);
    }
}

/**
 * 函数名  Usb_setIntegrationTime
 * 描述   ：设置积分时间
 * 输入   ：spectrometerIndex：分光仪索引，0-n
 *         usec：单位ms
 * 输出   ：无
 * 返回值  ：无
 */
void UsbDriver::Usb_setIntegrationTime(int spectrometerIndex, int usec)
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_setIntegrationTime_t(m_pWrapper, spectrometerIndex, usec);
    }
}

/**
 * 函数名  Usb_getIntegrationTime
 * 描述   ：得到积分时间
 * 输入   ：spectrometerIndex：分光仪索引，0-n
 * 输出   ：无
 * 返回值  ：积分时间，单位ms
 */
int UsbDriver::Usb_getIntegrationTime(int spectrometerIndex)
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_getIntegrationTime_t(m_pWrapper, spectrometerIndex);
    }
    return 0;
}

/**
 * @brief UsbDriver::Usb_setTimeout
 * @param spectrometerIndex
 * @param timeoutMilliseconds
 * @return
 */
int UsbDriver::Usb_setTimeout(int spectrometerIndex, int timeoutMilliseconds)
{
    int n = 0;
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        n = Wrapper_setTimeout_t(m_pWrapper, spectrometerIndex, timeoutMilliseconds);
    }
    return n;
}

/**
 * 函数名  Usb_setStrobeEnable
 * 描述   ： 设置灯的状态
 *          注意：灯的状态直接下一次调用Usb_getSpectrum才会响应
 * 输入   ： spectrometerIndex：分光仪索引，0-n
 *          lampOn：0：灯灭，非0：灯亮
 * 输出   ：无
 * 返回值  ：无
 */
void UsbDriver::Usb_setStrobeEnable(int spectrometerIndex, int lampOn)
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_setStrobeEnable_t(m_pWrapper, spectrometerIndex, lampOn);
    }
}

/**
 * 函数名  Usb_getWavelengths
 * 描述   ： 获取波长数据
 * 输入   ： spectrometerIndex：分光仪索引，0-n
 * 输出   ：DOUBLEARRAY_T retval：计算出的波长值，与每一个光谱像素值对应
 * 返回值  ：无
 */
void UsbDriver::Usb_getWavelengths(int spectrometerIndex, DOUBLEARRAY_T retval)
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_getWavelengths_t(m_pWrapper, spectrometerIndex, retval);
    }
}

/**
 * 函数名  Usb_getSpectrum
 * 描述   ： 从指定的分光仪获取下一个可用的光谱数据
 *          调用此函数后，你能够调用isSaturated(未实现)来设置最近获取的光谱是否是饱和的。
 * 输入   ： spectrometerIndex：分光仪索引，0-n
 * 输出   ：DOUBLEARRAY_T retval：光谱像素值
 * 返回值  ：无
 */
void UsbDriver::Usb_getSpectrum(int spectrometerIndex, DOUBLEARRAY_T retval)
{
    if (lib_omni_dll != NULL && m_pWrapper != NULL)
    {
        return Wrapper_getSpectrum_t(m_pWrapper, spectrometerIndex, retval);
    }
}
