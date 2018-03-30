#ifndef USBDRIVER_H
#define USBDRIVER_H

#include <QLibrary>
#include <Wrapper.h>


typedef WRAPPER_T   (* Wrapper_Create_T                 )();
typedef void        (* Wrapper_Destroy_T                )(WRAPPER_T);
typedef void        (* Wrapper_getApiVersion_T          )(WRAPPER_T, JSTRING_T);
typedef int         (* Wrapper_getBuildNumber_T         )(WRAPPER_T);
typedef void        (* Wrapper_getSerialNumber_T        )(WRAPPER_T, int, JSTRING_T);
typedef int         (* Wrapper_openAllSpectrometers_T   )(WRAPPER_T);
typedef void        (* Wrapper_closeAllSpectrometers_T  )(WRAPPER_T);
typedef void        (* Wrapper_setIntegrationTime_T     )(WRAPPER_T, int, int);
typedef int         (* Wrapper_setTimeout_T             )(WRAPPER_T, int, int);
typedef int         (* Wrapper_getIntegrationTime_T     )(WRAPPER_T, int);
typedef void        (* Wrapper_setStrobeEnable_T        )(WRAPPER_T, int, int);
typedef void        (* Wrapper_getWavelengths_T         )(WRAPPER_T, int, DOUBLEARRAY_T);
typedef void        (* Wrapper_getSpectrum_T            )(WRAPPER_T, int, DOUBLEARRAY_T);


class UsbDriver
{
public:
    UsbDriver();
    ~UsbDriver();

    int UsbDriverInit(void);
    void UsbDriverClose(void);

    int         Usb_Create                  ();
    void        Usb_Destroy                 ();
    void        Usb_getApiVersion           (JSTRING_T retval);
    int         Usb_getBuildNumber          ();
    QString     Usb_getSerialNumber         (int spectrometerIndex);
    int         Usb_openAllSpectrometers    ();
    void        Usb_closeAllSpectrometers   ();
    void        Usb_setIntegrationTime      (int spectrometerIndex, int usec);
    int         Usb_getIntegrationTime      (int spectrometerIndex);
    int         Usb_setTimeout              (int spectrometerIndex, int timeoutMilliseconds);
    void        Usb_setStrobeEnable         (int spectrometerIndex, int lampOn);
    void        Usb_getWavelengths          (int spectrometerIndex, DOUBLEARRAY_T retval);
    void        Usb_getSpectrum             (int spectrometerIndex, DOUBLEARRAY_T retval);

private:
    QLibrary                        *lib_omni_dll;

    Wrapper_Create_T                Wrapper_Create_t;
    Wrapper_Destroy_T               Wrapper_Destroy_t;
    Wrapper_getApiVersion_T         Wrapper_getApiVersion_t;
    Wrapper_getBuildNumber_T        Wrapper_getBuildNumber_t;
    Wrapper_getSerialNumber_T       Wrapper_getSerialNumber_t;
    Wrapper_openAllSpectrometers_T  Wrapper_openAllSpectrometers_t;
    Wrapper_closeAllSpectrometers_T Wrapper_closeAllSpectrometers_t;
    Wrapper_setIntegrationTime_T    Wrapper_setIntegrationTime_t;
    Wrapper_getIntegrationTime_T    Wrapper_getIntegrationTime_t;
    Wrapper_setTimeout_T            Wrapper_setTimeout_t;
    Wrapper_setStrobeEnable_T       Wrapper_setStrobeEnable_t;
    Wrapper_getWavelengths_T        Wrapper_getWavelengths_t;
    Wrapper_getSpectrum_T           Wrapper_getSpectrum_t;

    WRAPPER_T m_pWrapper;
};

#endif // USBDRIVER_H
