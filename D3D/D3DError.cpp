//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "D3DError.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TD3DError::TD3DError()
{
}

void TD3DError::Display(HRESULT res)
{
    String err;

    switch(res)
    {
        //direct draw errors
        case DD_OK  : err = "The request completed successfully."; break;
        case DDERR_ALREADYINITIALIZED : err = "The object has already been initialized."; break;
        case DDERR_BLTFASTCANTCLIP : err = "A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface7::BltFast method."; break;
        case DDERR_CANNOTATTACHSURFACE : err = "A surface cannot be attached to another requested surface."; break;
        case DDERR_CANNOTDETACHSURFACE : err = "A surface cannot be detached from another requested surface."; break;
        case DDERR_CANTCREATEDC : err = "Windows cannot create any more device contexts (DCs), or a DC has requested a palette-indexed surface when the surface had no palette and the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC)."; break;
        case DDERR_CANTDUPLICATE : err = "Primary and 3-D surfaces, or surfaces that are implicitly created, cannot be duplicated."; break;
        case DDERR_CANTLOCKSURFACE : err = "Access to this surface is refused because an attempt was made to lock the primary surface without DCI support."; break;
        case DDERR_CANTPAGELOCK : err = "An attempt to page-lock a surface failed. Page lock does not work on a display-memory surface or an emulated primary surface."; break;
        case DDERR_CANTPAGEUNLOCK : err = "An attempt to page-unlock a surface failed. Page unlock does not work on a display-memory surface or an emulated primary surface."; break;
        case DDERR_CLIPPERISUSINGHWND : err = "An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle."; break;
        case DDERR_COLORKEYNOTSET : err = "No source color key is specified for this operation."; break;
        case DDERR_CURRENTLYNOTAVAIL : err = "No support is currently available."; break;
        case DDERR_DDSCAPSCOMPLEXREQUIRED : err = "New for DirectX 7.0. The surface requires the DDSCAPS_COMPLEX flag."; break;
        case DDERR_DCALREADYCREATED : err = "A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface."; break;
        case DDERR_DEVICEDOESNTOWNSURFACE : err = "Surfaces created by one DirectDraw device cannot be used directly by another DirectDraw device."; break;
        case DDERR_DIRECTDRAWALREADYCREATED : err = "A DirectDraw object representing this driver has already been created for this process."; break;
        case DDERR_EXCEPTION : err = "An exception was encountered while performing the requested operation."; break;
        case DDERR_EXCLUSIVEMODEALREADYSET : err = "An attempt was made to set the cooperative level when it was already set to exclusive."; break;
        case DDERR_EXPIRED : err = "The data has expired and is therefore no longer valid."; break;
        case DDERR_GENERIC : err = "There is an undefined error condition."; break;
        case DDERR_HEIGHTALIGN : err = "The height of the provided rectangle is not a multiple of the required alignment."; break;
        case DDERR_HWNDALREADYSET : err = "The DirectDraw cooperative-level window handle has already been set. It cannot be reset while the process has surfaces or palettes created."; break;
        case DDERR_HWNDSUBCLASSED : err = "DirectDraw is prevented from restoring state because the DirectDraw cooperative-level window handle has been subclassed."; break;
        case DDERR_IMPLICITLYCREATED : err = "The surface cannot be restored because it is an implicitly created surface."; break;
        case DDERR_INCOMPATIBLEPRIMARY : err = "The primary surface creation request does not match the existing primary surface."; break;
        case DDERR_INVALIDCAPS : err = "One or more of the capability bits passed to the callback function are incorrect."; break;
        case DDERR_INVALIDCLIPLIST : err = "DirectDraw does not support the provided clip list."; break;
        case DDERR_INVALIDDIRECTDRAWGUID : err = "The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier."; break;
        case DDERR_INVALIDMODE : err = "DirectDraw does not support the requested mode."; break;
        case DDERR_INVALIDOBJECT : err = "DirectDraw received a pointer that was an invalid DirectDraw object."; break;
        case DDERR_INVALIDPARAMS : err = "One or more of the parameters passed to the method are incorrect."; break;
        case DDERR_INVALIDPIXELFORMAT : err = "The pixel format was invalid as specified."; break;
        case DDERR_INVALIDPOSITION : err = "The position of the overlay on the destination is no longer legal."; break;
        case DDERR_INVALIDRECT : err = "The provided rectangle was invalid."; break;
        case DDERR_INVALIDSTREAM : err = "The specified stream contains invalid data."; break;
        case DDERR_INVALIDSURFACETYPE : err = "The surface was of the wrong type."; break;
        case DDERR_LOCKEDSURFACES : err = "One or more surfaces are locked, causing the failure of the requested operation."; break;
        case DDERR_MOREDATA : err = "There is more data available than the specified buffer size can hold."; break;
        case DDERR_NEWMODE : err = "New for DirectX 7.0. When IDirectDraw7::StartModeTest is called with the DDSMT_ISTESTREQUIRED flag, it may return this value to denote that some or all of the resolutions can and should be tested. IDirectDraw7::EvaluateMode returns this value to indicate that the test has switched to a new display mode."; break;
        case DDERR_NO3D : err = "No 3-D hardware or emulation is present."; break;
        case DDERR_NOALPHAHW : err = "No alpha-acceleration hardware is present or available, causing the failure of the requested operation."; break;
        case DDERR_NOBLTHW : err = "No blitter hardware is present."; break;
        case DDERR_NOCLIPLIST : err = "No clip list is available."; break;
        case DDERR_NOCLIPPERATTACHED : err = "No DirectDrawClipper object is attached to the surface object."; break;
        case DDERR_NOCOLORCONVHW : err = "No color-conversion hardware is present or available."; break;
        case DDERR_NOCOLORKEY : err = "The surface does not currently have a color key."; break;
        case DDERR_NOCOLORKEYHW : err = "There is no hardware support for the destination color key."; break;
        case DDERR_NOCOOPERATIVELEVELSET : err = "A create function was called without the IDirectDraw7::SetCooperativeLevel method."; break;
        case DDERR_NODC : err = "No device context (DC) has ever been created for this surface."; break;
        case DDERR_NODDROPSHW : err = "No DirectDraw raster-operation (ROP) hardware is available."; break;
        case DDERR_NODIRECTDRAWHW : err = "Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware."; break;
        case DDERR_NODIRECTDRAWSUPPORT : err = "DirectDraw support is not possible with the current display driver."; break;
        case DDERR_NODRIVERSUPPORT : err = "New for DirectX 7.0. Testing cannot proceed because the display adapter driver does not enumerate refresh rates."; break;
        case DDERR_NOEMULATION : err = "Software emulation is not available."; break;
        case DDERR_NOEXCLUSIVEMODE : err = "The operation requires the application to have exclusive mode, but the application does not have exclusive mode."; break;
        case DDERR_NOFLIPHW : err = "Flipping visible surfaces is not supported."; break;
        case DDERR_NOFOCUSWINDOW : err = "An attempt was made to create or set a device window without first setting the focus window."; break;
        case DDERR_NOGDI : err = "No GDI is present."; break;
        case DDERR_NOHWND : err = "Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle."; break;
        case DDERR_NOMIPMAPHW : err = "No mipmap-capable texture mapping hardware is present or available."; break;
        case DDERR_NOMIRRORHW : err = "No mirroring hardware is present or available."; break;
        case DDERR_NOMONITORINFORMATION : err = "New for DirectX 7.0. Testing cannot proceed because the monitor has no associated EDID data."; break;
        case DDERR_NONONLOCALVIDMEM : err = "An attempt was made to allocate nonlocal video memory from a device that does not support nonlocal video memory."; break;
        case DDERR_NOOPTIMIZEHW : err = "The device does not support optimized surfaces."; break;
        case DDERR_NOOVERLAYDEST : err = "The IDirectDrawSurface7::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface7::UpdateOverlay method has not been called on to establish as a destination."; break;
        case DDERR_NOOVERLAYHW : err = "No overlay hardware is present or available."; break;
        case DDERR_NOPALETTEATTACHED : err = "No palette object is attached to this surface."; break;
        case DDERR_NOPALETTEHW : err = "There is no hardware support for 16- or 256-color palettes."; break;
        case DDERR_NORASTEROPHW : err = "No appropriate raster-operation hardware is present or available."; break;
        case DDERR_NOROTATIONHW : err = "No rotation hardware is present or available."; break;
        case DDERR_NOSTEREOHARDWARE : err = "There is no stereo hardware present or available."; break;
        case DDERR_NOSTRETCHHW : err = "There is no hardware support for stretching."; break;
        case DDERR_NOSURFACELEFT : err = "There is no hardware present that supports stereo surfaces."; break;
        case DDERR_NOT4BITCOLOR : err = "The DirectDrawSurface object is not using a 4-bit color palette, and the requested operation requires a 4-bit color palette."; break;
        case DDERR_NOT4BITCOLORINDEX : err = "The DirectDrawSurface object is not using a 4-bit color index palette, and the requested operation requires a 4-bit color index palette."; break;
        case DDERR_NOT8BITCOLOR : err = "The DirectDrawSurface object is not using an 8-bit color palette, and the requested operation requires an 8-bit color palette."; break;
        case DDERR_NOTAOVERLAYSURFACE : err = "An overlay component is called for a nonoverlay surface."; break;
        case DDERR_NOTEXTUREHW : err = "The operation cannot be carried out because no texture-mapping hardware is present or available."; break;
        case DDERR_NOTFLIPPABLE : err = "An attempt was made to flip a surface that cannot be flipped."; break;
        case DDERR_NOTFOUND : err = "The requested item was not found."; break;
        case DDERR_NOTINITIALIZED : err = "An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized."; break;
        case DDERR_NOTLOADED : err = "The surface is an optimized surface, but it has not yet been allocated any memory."; break;
        case DDERR_NOTLOCKED : err = "An attempt was made to unlock a surface that was not locked."; break;
        case DDERR_NOTPAGELOCKED : err = "An attempt was made to page-unlock a surface with no outstanding page locks."; break;
        case DDERR_NOTPALETTIZED : err = "The surface being used is not a palette-based surface."; break;
        case DDERR_NOVSYNCHW : err = "There is no hardware support for vertical blank–synchronized operations."; break;
        case DDERR_NOZBUFFERHW : err = "The operation to create a z-buffer in display memory or to perform a blit, using a z-buffer cannot be carried out because there is no hardware support for z-buffers."; break;
        case DDERR_NOZOVERLAYHW : err = "The overlay surfaces cannot be z-layered, based on the z-order because the hardware does not support z-ordering of overlays."; break;
        case DDERR_OUTOFCAPS : err = "The hardware needed for the requested operation has already been allocated."; break;
        case DDERR_OUTOFMEMORY : err = "DirectDraw does not have enough memory to perform the operation."; break;
        case DDERR_OUTOFVIDEOMEMORY : err = "DirectDraw does not have enough display memory to perform the operation."; break;
        case DDERR_OVERLAPPINGRECTS : err = "The source and destination rectangles are on the same surface and overlap each other."; break;
        case DDERR_OVERLAYCANTCLIP : err = "The hardware does not support clipped overlays."; break;
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE : err = "An attempt was made to have more than one color key active on an overlay."; break;
        case DDERR_OVERLAYNOTVISIBLE : err = "The IDirectDrawSurface7::GetOverlayPosition method was called on a hidden overlay."; break;
        case DDERR_PALETTEBUSY : err = "Access to this palette is refused because the palette is locked by another thread."; break;
        case DDERR_PRIMARYSURFACEALREADYEXISTS : err = "This process has already created a primary surface."; break;
        case DDERR_REGIONTOOSMALL : err = "The region passed to the IDirectDrawClipper::GetClipList method is too small."; break;
        case DDERR_SURFACEALREADYATTACHED : err = "An attempt was made to attach a surface to another surface to which it is already attached."; break;
        case DDERR_SURFACEALREADYDEPENDENT : err = "An attempt was made to make a surface a dependency of another surface on which it is already dependent."; break;
        case DDERR_SURFACEBUSY : err = "Access to the surface is refused because the surface is locked by another thread."; break;
        case DDERR_SURFACEISOBSCURED : err = "Access to the surface is refused because the surface is obscured."; break;
        case DDERR_SURFACELOST : err = "Access to the surface is refused because the surface memory is gone. Call the IDirectDrawSurface7::Restore method on this surface to restore the memory associated with it."; break;
        case DDERR_SURFACENOTATTACHED : err = "The requested surface is not attached."; break;
        case DDERR_TESTFINISHED : err = "New for DirectX 7.0. When returned by the IDirectDraw7::StartModeTest method, this value means that no test could be initiated because all the resolutions chosen for testing already have refresh rate information in the registry. When returned by IDirectDraw7::EvaluateMode, the value means that DirectDraw has completed a refresh rate test."; break;
        case DDERR_TOOBIGHEIGHT : err = "The height requested by DirectDraw is too large."; break;
        case DDERR_TOOBIGSIZE : err = "The size requested by DirectDraw is too large. However, the individual height and width are valid sizes."; break;
        case DDERR_TOOBIGWIDTH : err = "The width requested by DirectDraw is too large."; break;
        case DDERR_UNSUPPORTED : err = "The operation is not supported."; break;
        case DDERR_UNSUPPORTEDFORMAT : err = "The pixel format requested is not supported by DirectDraw."; break;
        case DDERR_UNSUPPORTEDMASK : err = "The bitmask in the pixel format requested is not supported by DirectDraw."; break;
        case DDERR_UNSUPPORTEDMODE : err = "The display is currently in an unsupported mode."; break;
        case DDERR_VERTICALBLANKINPROGRESS : err = "A vertical blank is in progress."; break;
        case DDERR_VIDEONOTACTIVE : err = "The video port is not active."; break;
        case DDERR_WASSTILLDRAWING : err = "The previous blit operation that is transferring information to or from this surface is incomplete."; break;
        case DDERR_WRONGMODE : err = "This surface cannot be restored because it was created in a different mode."; break;
        case DDERR_XALIGN : err = "The provided rectangle was not horizontally aligned on a required boundary."; break;

        //direct 3D errors
        case D3DERR_BADMAJORVERSION : err = "The service that you requested is unavailable in this major version of DirectX. (A major version denotes a primary release, such as DirectX 6.0.)"; break;
        case D3DERR_BADMINORVERSION : err = "The service that you requested is available in this major version of DirectX, but not in this minor version. Get the latest version of the component run time from Microsoft. (A minor version denotes a secondary release, such as DirectX 6.1.)"; break;
        case D3DERR_COLORKEYATTACHED : err = "The application attempted to create a texture with a surface that uses a color key for transparency."; break;
        case D3DERR_CONFLICTINGTEXTUREFILTER : err = "The current texture filters cannot be used together."; break;
        case D3DERR_CONFLICTINGTEXTUREPALETTE : err = "The current textures cannot be used simultaneously. This generally occurs when a multitexture device requires that all palettized textures simultaneously enabled also share the same palette."; break;
        case D3DERR_CONFLICTINGRENDERSTATE : err = "The currently set render states cannot be used together."; break;
        case D3DERR_DEVICEAGGREGATED : err = "The IDirect3DDevice7::SetRenderTarget method was called on a device that was retrieved from the render target surface."; break;
        case D3DERR_EXECUTE_CLIPPED_FAILED : err = "The execute buffer could not be clipped during execution."; break;
        case D3DERR_EXECUTE_CREATE_FAILED : err = "The execute buffer could not be created. This typically occurs when no memory is available to allocate the execute buffer."; break;
        case D3DERR_EXECUTE_DESTROY_FAILED : err = "The memory for the execute buffer could not be deallocated."; break;
        case D3DERR_EXECUTE_FAILED : err = "The contents of the execute buffer are invalid and cannot be executed."; break;
        case D3DERR_EXECUTE_LOCK_FAILED : err = "The execute buffer could not be locked."; break;
        case D3DERR_EXECUTE_LOCKED : err = "The operation requested by the application could not be completed because the execute buffer is locked."; break;
        case D3DERR_EXECUTE_NOT_LOCKED : err = "The execute buffer could not be unlocked because it is not currently locked."; break;
        case D3DERR_EXECUTE_UNLOCK_FAILED : err = "The execute buffer could not be unlocked."; break;
        case D3DERR_INBEGIN : err = "The requested operation cannot be completed while scene rendering is taking place. Try again after the scene is completed and the IDirect3DDevice7::EndScene method is called."; break;
        case D3DERR_INBEGINSTATEBLOCK : err = "The operation cannot be completed while recording states for a state block. Complete recording by calling the IDirect3DDevice7::EndStateBlock method, and try again."; break;
        case D3DERR_INITFAILED : err = "A rendering device could not be created because the new device could not be initialized."; break;
        case D3DERR_INVALID_DEVICE : err = "The requested device type is not valid."; break;
        case D3DERR_INVALIDCURRENTVIEWPORT : err = "The currently selected viewport is not valid."; break;
        case D3DERR_INVALIDMATRIX : err = "The requested operation could not be completed because the combination of the currently set world, view, and projection matrices is invalid (the determinant of the combined matrix is 0)."; break;
        case D3DERR_INVALIDPALETTE : err = "The palette associated with a surface is invalid."; break;
        case D3DERR_INVALIDPRIMITIVETYPE : err = "The primitive type specified by the application is invalid."; break;
        case D3DERR_INVALIDRAMPTEXTURE : err = "Ramp mode is being used, and the texture handle in the current material does not match the current texture handle that is set as a render state."; break;
        case D3DERR_INVALIDSTATEBLOCK : err = "The state block handle is invalid."; break;
        case D3DERR_INVALIDVERTEXFORMAT : err = "The combination of flexible vertex format flags specified by the application is not valid."; break;
        case D3DERR_INVALIDVERTEXTYPE : err = "The vertex type specified by the application is invalid."; break;
        case D3DERR_LIGHT_SET_FAILED : err = "The attempt to set lighting parameters for a light object failed."; break;
        case D3DERR_LIGHTHASVIEWPORT : err = "The requested operation failed because the light object is associated with another viewport."; break;
        case D3DERR_LIGHTNOTINTHISVIEWPORT : err = "The requested operation failed because the light object has not been associated with this viewport."; break;
        case D3DERR_MATERIAL_CREATE_FAILED : err = "The material could not be created. This typically occurs when no memory is available to allocate for the material."; break;
        case D3DERR_MATERIAL_DESTROY_FAILED : err = "The memory for the material could not be deallocated."; break;
        case D3DERR_MATERIAL_GETDATA_FAILED : err = "The material parameters could not be retrieved."; break;
        case D3DERR_MATERIAL_SETDATA_FAILED : err = "The material parameters could not be set."; break;
        case D3DERR_MATRIX_CREATE_FAILED : err = "The matrix could not be created. This can occur when no memory is available to allocate for the matrix."; break;
        case D3DERR_MATRIX_DESTROY_FAILED : err = "The memory for the matrix could not be deallocated."; break;
        case D3DERR_MATRIX_GETDATA_FAILED : err = "The matrix data could not be retrieved. This can occur when the matrix was not created by the current device."; break;
        case D3DERR_MATRIX_SETDATA_FAILED : err = "The matrix data could not be set. This can occur when the matrix was not created by the current device."; break;
        case D3DERR_NOCURRENTVIEWPORT : err = "The viewport parameters could not be retrieved because none have been set."; break;
        case D3DERR_NOTINBEGIN : err = "The requested rendering operation could not be completed because scene rendering has not begun. Call IDirect3DDevice7::BeginScene to begin rendering, and try again."; break;
        case D3DERR_NOTINBEGINSTATEBLOCK : err = "The requested operation could not be completed because it is only valid while recording a state block. Call the IDirect3DDevice7::BeginStateBlock method, and try again."; break;
        case D3DERR_NOVIEWPORTS : err = "The requested operation failed because the device currently has no viewports associated with it."; break;
        case D3DERR_SCENE_BEGIN_FAILED : err = "Scene rendering could not begin."; break;
        case D3DERR_SCENE_END_FAILED : err = "Scene rendering could not be completed."; break;
        case D3DERR_SCENE_IN_SCENE : err = "Scene rendering could not begin because a previous scene was not completed by a call to the IDirect3DDevice7::EndScene method."; break;
        case D3DERR_SCENE_NOT_IN_SCENE : err = "Scene rendering could not be completed because a scene was not started by a previous call to the IDirect3DDevice7::BeginScene method."; break;
        case D3DERR_SETVIEWPORTDATA_FAILED : err = "The viewport parameters could not be set."; break;
        case D3DERR_STENCILBUFFER_NOTPRESENT : err = "The requested stencil buffer operation could not be completed because there is no stencil buffer attached to the render target surface."; break;
        case D3DERR_SURFACENOTINVIDMEM : err = "The device could not be created because the render target surface is not located in video memory. (Hardware-accelerated devices require video-memory render target surfaces.)"; break;
        case D3DERR_TEXTURE_BADSIZE : err = "The dimensions of a current texture are invalid. This can occur when an application attempts to use a texture that has dimensions that are not a power of 2 with a device that requires them."; break;
        case D3DERR_TEXTURE_CREATE_FAILED : err = "The texture handle for the texture could not be retrieved from the driver."; break;
        case D3DERR_TEXTURE_DESTROY_FAILED : err = "The device was unable to deallocate the texture memory."; break;
        case D3DERR_TEXTURE_GETSURF_FAILED : err = "The DirectDraw surface used to create the texture could not be retrieved."; break;
        case D3DERR_TEXTURE_LOAD_FAILED : err = "The texture could not be loaded."; break;
        case D3DERR_TEXTURE_LOCK_FAILED : err = "The texture could not be locked."; break;
        case D3DERR_TEXTURE_LOCKED : err = "The requested operation could not be completed because the texture surface is currently locked."; break;
        case D3DERR_TEXTURE_NO_SUPPORT : err = "The device does not support texture mapping."; break;
        case D3DERR_TEXTURE_NOT_LOCKED : err = "The requested operation could not be completed because the texture surface is not locked."; break;
        case D3DERR_TEXTURE_SWAP_FAILED : err = "The texture handles could not be swapped."; break;
        case D3DERR_TEXTURE_UNLOCK_FAILED : err = "The texture surface could not be unlocked."; break;
        case D3DERR_TOOMANYOPERATIONS : err = "The application is requesting more texture-filtering operations than the device supports."; break;
        case D3DERR_TOOMANYPRIMITIVES : err = "The device is unable to render the provided number of primitives in a single pass."; break;
        case D3DERR_UNSUPPORTEDALPHAARG : err = "The device does not support one of the specified texture-blending arguments for the alpha channel."; break;
        case D3DERR_UNSUPPORTEDALPHAOPERATION : err = "The device does not support one of the specified texture-blending operations for the alpha channel."; break;
        case D3DERR_UNSUPPORTEDCOLORARG : err = "The device does not support one of the specified texture-blending arguments for color values."; break;
        case D3DERR_UNSUPPORTEDCOLOROPERATION : err = "The device does not support one of the specified texture-blending operations for color values."; break;
        case D3DERR_UNSUPPORTEDFACTORVALUE : err = "The specified texture factor value is not supported by the device."; break;
        case D3DERR_UNSUPPORTEDTEXTUREFILTER : err = "The specified texture filter is not supported by the device."; break;
        case D3DERR_VBUF_CREATE_FAILED : err = "The vertex buffer could not be created. This can happen when there is insufficient memory to allocate a vertex buffer."; break;
        case D3DERR_VERTEXBUFFERLOCKED : err = "The requested operation could not be completed because the vertex buffer is locked."; break;
        case D3DERR_VERTEXBUFFEROPTIMIZED : err = "The requested operation could not be completed because the vertex buffer is optimized. (The contents of optimized vertex buffers are driver-specific and considered private.)"; break;
        case D3DERR_VERTEXBUFFERUNLOCKFAILED : err = "The vertex buffer could not be unlocked because the vertex buffer memory was overrun. Be sure that your application does not write beyond the size of the vertex buffer."; break;
        case D3DERR_VIEWPORTDATANOTSET : err = "The requested operation could not be completed because viewport parameters have not yet been set. Set the viewport parameters by calling the IDirect3DDevice7::SetViewport method, and try again."; break;
        case D3DERR_VIEWPORTHASNODEVICE : err = "This value is used only by the IDirect3DDevice3 interface and its predecessors. For the IDirect3DDevice7 interface, this error value is not used. The requested operation could not be completed because the viewport has not yet been associated with a device. Associate the viewport with a rendering device by calling the IDirect3DDevice3::AddViewport method, and try again."; break;
        case D3DERR_WRONGTEXTUREFORMAT : err = "The pixel format of the texture surface is not valid."; break;
        case D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY : err = "The requested operation could not be completed because the specified device requires system-memory depth-buffer surfaces. (Software rendering devices require system-memory depth buffers.)"; break;
        case D3DERR_ZBUFF_NEEDS_VIDEOMEMORY : err = "The requested operation could not be completed because the specified device requires video-memory depth-buffer surfaces. (Hardware-accelerated devices require video-memory depth buffers.)"; break;
        case D3DERR_ZBUFFER_NOTPRESENT : err = "The requested operation could not be completed because the render target surface does not have an attached depth buffer."; break;

        default : err = "Unknown error!";
    }

    Application->MessageBox(err.c_str(), "Error", MB_OK|MB_ICONERROR);
}
//---------------------------------------------------------------------------
