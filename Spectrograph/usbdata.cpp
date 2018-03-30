#include "usbdata.h"

UsbData::UsbData()
{
    lib_array_dll = NULL;
}

UsbData::~UsbData()
{
    if (lib_array_dll != NULL)
    {
        lib_array_dll->unload();
        lib_array_dll = NULL;
    }
}

/**
 * 函数名  UsbDataInit
 * 描述   ：加载动态库，验证是否所有API成功加载
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：1：加载动态库失败
 *          2：加载部分API失败
 *          0：加载动态库及API成功
 */
int UsbData::UsbDataInit()
{
    // 如果已经加载，直接返回，避免重复加载
    if (lib_array_dll != NULL)
    {
        return 0;
    }

    lib_array_dll = new QLibrary("common32.dll");
    if (!lib_array_dll->load())
    {
        lib_array_dll = NULL;
        return 1;
    }

    DoubleArray_Create_t            = (DoubleArray_Create_T             )lib_array_dll->resolve("DoubleArray_Create");
    DoubleArray_Destroy_t           = (DoubleArray_Destroy_T            )lib_array_dll->resolve("DoubleArray_Destroy");
    DoubleArray_getDoubleValues_t   = (DoubleArray_getDoubleValues_T    )lib_array_dll->resolve("DoubleArray_getDoubleValues");
    DoubleArray_getLength_t         = (DoubleArray_getLength_T          )lib_array_dll->resolve("DoubleArray_getLength");
    DoubleArray_setDoubleValues_t   = (DoubleArray_setDoubleValues_T    )lib_array_dll->resolve("DoubleArray_setDoubleValues");
    DoubleArray_getElementAt_t      = (DoubleArray_getElementAt_T       )lib_array_dll->resolve("DoubleArray_getElementAt");
    DoubleArray_copyDoubleValues_t  = (DoubleArray_copyDoubleValues_T   )lib_array_dll->resolve("DoubleArray_copyDoubleValues");

    if (    DoubleArray_Create_t && DoubleArray_Destroy_t &&
            DoubleArray_getDoubleValues_t && DoubleArray_getLength_t &&
            DoubleArray_setDoubleValues_t &&
            DoubleArray_getElementAt_t &&
            DoubleArray_copyDoubleValues_t)
    {
        return 0;
    }

    lib_array_dll->unload();
    lib_array_dll = NULL;

    return 2;
}

/**
 * 函数名  UsbDataClose
 * 描述   ：卸载动态库
 * 输入   ：无
 * 输出   ：无
 * 返回值  ：无
 */
void UsbData::UsbDataClose()
{
    if (lib_array_dll != NULL)
    {
        lib_array_dll->unload();
        lib_array_dll = NULL;
    }
}

DOUBLEARRAY_T UsbData::Usb_Create()
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_Create_t();
    }
    return NULL;
}

void UsbData::Usb_Destroy(DOUBLEARRAY_T double_array)
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_Destroy_t(double_array);
    }
}

double* UsbData::Usb_getDoubleValues(DOUBLEARRAY_T double_array)
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_getDoubleValues_t(double_array);
    }
    return NULL;
}

int UsbData::Usb_getLength(DOUBLEARRAY_T double_array)
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_getLength_t(double_array);
    }
    return 0;
}

void UsbData::Usb_setDoubleValues(DOUBLEARRAY_T double_array, double *values, int len)
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_setDoubleValues_t(double_array, values, len);
    }
}

double UsbData::Usb_getElementAt(DOUBLEARRAY_T double_array, int i)
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_getElementAt_t(double_array, i);
    }
    return 0;
}

int UsbData::Usb_copyDoubleValues(DOUBLEARRAY_T double_array, double *target, int length)
{
    if (lib_array_dll != NULL)
    {
        return DoubleArray_copyDoubleValues_t(double_array, target, length);
    }
    return 0;
}

