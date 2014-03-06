#include <IOKit/IOLib.h>
//#include <IOKit/ndrvsupport/IOMacOSTypes.h>
//#include <IOKit/graphics/IOFrameBuffer.h>
#include "X4500FB.h"

// This required macro defines the class's constructors, destructors,

// and several other methods I/O Kit requires.

OSDefineMetaClassAndStructors(X4500, IOService)


// Define the driver's superclass.

#define super IOService

bool X4500::init(OSDictionary *dict)
{
    bool result = super::init(dict);
    IOLog("Initializing\n");
    return result;
}

void X4500::free(void)
{
    IOLog("Freeing\n");
    super::free();
}


IOService *X4500::probe(IOService *provider, SInt32 *score)
{
    IOService *result = super::probe(provider, score);
    IOLog("Probing\n");
    return result;    
}

bool X4500::start(IOService *provider)
{    
    bool result = super::start(provider);   
    IOLog("Starting\n");
    return result;
}

void X4500::stop(IOService *provider)
{  
    IOLog("Stopping\n");
    super::stop(provider);
}

#undef super
#define super IOFramebuffer

OSDefineMetaClassAndStructors(X4500FB, IOFramebuffer)

/*
 only 1 mode support for test.
 */
IOItemCount X4500FB::getDisplayModeCount()
{
    return 1;
}

IOReturn X4500FB::getDisplayModes(IODisplayModeID *allDisplayModes)
{
    *allDisplayModes = 1;
    return kIOReturnSuccess;
}

/*
 * copy from IONDRVFramebuffer.cpp
 */
const char * X4500FB::getPixelFormats( void )
{
    static const char * ndrvPixelFormats =
    IO1BitIndexedPixels "\0"
    IO2BitIndexedPixels "\0"
    IO4BitIndexedPixels "\0"
    IO8BitIndexedPixels "\0"
    IO16BitDirectPixels "\0"
    IO32BitDirectPixels "\0"
    "\0";
    
    return (ndrvPixelFormats);
}

IOReturn X4500FB::getPixelInformation( IODisplayModeID displayMode, IOIndex depth, IOPixelAperture aperture, IOPixelInformation *info )
{
    PE_Video    bootDisplay;
    
    if (aperture || depth )
        return (kIOReturnUnsupportedMode);
    
    getPlatform()->getConsoleInfo( &bootDisplay );
    
    bzero( info, sizeof( *info));
    
    info->activeWidth           = 1280;
    info->activeHeight          = 800;
    info->bytesPerRow           = bootDisplay.v_rowBytes & 0x7fff;
    info->bytesPerPlane         = 0;
    
    switch (bootDisplay.v_depth)
    {
        case 8:
        default:
            strlcpy(info->pixelFormat, IO8BitIndexedPixels, sizeof(info->pixelFormat));
            info->pixelType             = kIOCLUTPixels;
            info->componentMasks[0]     = 0xff;
            info->bitsPerPixel          = 8;
            info->componentCount        = 1;
            info->bitsPerComponent      = 8;
            break;
        case 15:
        case 16:
            strlcpy(info->pixelFormat, IO16BitDirectPixels, sizeof(info->pixelFormat));
            info->pixelType     = kIORGBDirectPixels;
            info->componentMasks[0] = 0x7c00;
            info->componentMasks[1] = 0x03e0;
            info->componentMasks[2] = 0x001f;
            info->bitsPerPixel  = 16;
            info->componentCount        = 3;
            info->bitsPerComponent      = 5;
            break;
        case 24:
        case 32:
            strlcpy(info->pixelFormat, IO32BitDirectPixels, sizeof(info->pixelFormat));
            info->pixelType     = kIORGBDirectPixels;
            info->componentMasks[0] = 0x00ff0000;
            info->componentMasks[1] = 0x0000ff00;
            info->componentMasks[2] = 0x000000ff;
            info->bitsPerPixel  = 32;
            info->componentCount        = 3;
            info->bitsPerComponent      = 8;
            break;
    }
    
    return (kIOReturnSuccess);
}
