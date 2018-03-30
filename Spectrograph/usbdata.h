#ifndef USBDATA_H
#define USBDATA_H

#include <QLibrary>
#include <ArrayTypes.h>

typedef DOUBLEARRAY_T   (* DoubleArray_Create_T             )();
typedef double*         (* DoubleArray_getDoubleValues_T    )(DOUBLEARRAY_T);
typedef int             (* DoubleArray_getLength_T          )(DOUBLEARRAY_T);
typedef void            (* DoubleArray_setDoubleValues_T    )(DOUBLEARRAY_T, double*, int);
typedef void            (* DoubleArray_Destroy_T            )(DOUBLEARRAY_T);
typedef double          (* DoubleArray_getElementAt_T       )(DOUBLEARRAY_T, int);
typedef int             (* DoubleArray_copyDoubleValues_T   )(DOUBLEARRAY_T, double*, int);

class UsbData
{
public:
    UsbData();
    ~UsbData();

    int UsbDataInit(void);
    void UsbDataClose(void);

    DOUBLEARRAY_T   Usb_Create          ();
    double*         Usb_getDoubleValues (DOUBLEARRAY_T double_array);
    int             Usb_getLength       (DOUBLEARRAY_T double_array);
    void            Usb_setDoubleValues (DOUBLEARRAY_T double_array, double* values, int len);
    void            Usb_Destroy         (DOUBLEARRAY_T double_array);
    double          Usb_getElementAt    (DOUBLEARRAY_T double_array, int i);
    int             Usb_copyDoubleValues(DOUBLEARRAY_T double_array, double* target, int length);

private:
    QLibrary                *lib_array_dll;

    DoubleArray_Create_T            DoubleArray_Create_t;
    DoubleArray_getDoubleValues_T   DoubleArray_getDoubleValues_t;
    DoubleArray_getLength_T         DoubleArray_getLength_t;
    DoubleArray_setDoubleValues_T   DoubleArray_setDoubleValues_t;
    DoubleArray_Destroy_T           DoubleArray_Destroy_t;
    DoubleArray_getElementAt_T      DoubleArray_getElementAt_t;
    DoubleArray_copyDoubleValues_T  DoubleArray_copyDoubleValues_t;
};

#endif // USBDATA_H
