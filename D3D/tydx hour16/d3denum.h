//-----------------------------------------------------------------------------
// File: D3DEnum.h
//
// Desc: Functions to enumerate DDraw/D3D drivers, devices, and modes.
//
// Copyright (c) 1997-1999 Microsoft Corporation. All rights reserved
//-----------------------------------------------------------------------------
#ifndef D3DENUM_H
#define D3DENUM_H
#include <d3d.h>


//-----------------------------------------------------------------------------
// Flag and error definitions
//-----------------------------------------------------------------------------
#define D3DENUM_SOFTWAREONLY           0x00000001 // Software only flag
#define D3DENUM_FULLSCREENONLY         0x00000002 // Fullscreen only flag

#define D3DENUMERR_ENUMERATIONFAILED   0x81000001 // Enumeration failed
#define D3DENUMERR_SUGGESTREFRAST      0x81000002 // Suggest using the RefRast
#define D3DENUMERR_NOCOMPATIBLEDEVICES 0x81000003 // No devices were found that
                                                  // meet the app's desired
                                                  // capabilities


//-----------------------------------------------------------------------------
// Name: struct D3DEnum_DeviceInfo
// Desc: Structure to hold info about the enumerated Direct3D devices.
//-----------------------------------------------------------------------------
struct D3DEnum_DeviceInfo
{
    // D3D Device info
    CHAR           strDesc[40];
    GUID*          pDeviceGUID;
    D3DDEVICEDESC7 ddDeviceDesc;
    BOOL           bHardware;

    // DDraw Driver info
    GUID*          pDriverGUID;
    DDCAPS         ddDriverCaps;
    DDCAPS         ddHELCaps;

    // DDraw Mode Info
    DDSURFACEDESC2 ddsdFullscreenMode;
    BOOL           bWindowed;
    BOOL           bStereo;

    // For internal use (apps should not need these)
    GUID           guidDevice;
    GUID           guidDriver;
    DDSURFACEDESC2 ddsdModes[100];
    DWORD          dwNumModes;
    DWORD          dwCurrentMode;
    BOOL           bDesktopCompatible;
};


// For code not yet switched to new struct name
typedef D3DEnum_DeviceInfo D3DDEVICEINFO;




//-----------------------------------------------------------------------------
// Name: D3DEnum_SetEnumerationCallback()
// Desc: Specifies a function, called during enumeration for each device, to
//       confirm that the device supports the feature set required by the app.
//-----------------------------------------------------------------------------
VOID D3DEnum_SetEnumerationCallback( HRESULT (*fn)(DDCAPS*, D3DDEVICEDESC7*) );




//-----------------------------------------------------------------------------
// Name: D3DEnum_EnumerateDevices()
// Desc: Enumerates all drivers, devices, and modes.
//-----------------------------------------------------------------------------
HRESULT D3DEnum_EnumerateDevices();




//-----------------------------------------------------------------------------
// Name: D3DEnum_SelectDefaultDevice()
// Desc: Picks a driver based on a set of passed in criteria.
//-----------------------------------------------------------------------------
HRESULT D3DEnum_SelectDefaultDevice( DWORD dwFlags );




//-----------------------------------------------------------------------------
// Name: D3DEnum_UserDlgSelectDevice()
// Desc: Displays a dialog box for the user to select a device and/or mode.
//       The return values are identical to the DialogBox() function.
// Note: The calling app must supply a valid dialog resource with at least two
//       combo boxes: one for the devices and one for the display modes.
//-----------------------------------------------------------------------------
INT D3DEnum_UserDlgSelectDevice( HWND hWnd, const TCHAR* strTemplate,
                                 WORD wDeviceComboID, WORD wModeComboID,
                                 BOOL bAppCurrentlyWindowed );




//-----------------------------------------------------------------------------
// Name: D3DEnum_GetSelectedDevice()
// Desc: Returns info about the currently selected device.
//-----------------------------------------------------------------------------
HRESULT D3DEnum_GetSelectedDevice( D3DEnum_DeviceInfo** pDeviceInfo );




//-----------------------------------------------------------------------------
// Name: D3DEnum_GetDevices()
// Desc: Returns a ptr to the array of D3DDEVICEINFO structures.
//-----------------------------------------------------------------------------
VOID D3DEnum_GetDevices( D3DEnum_DeviceInfo** ppDevices, DWORD* pdwCount );




#endif // D3DENUM_H



