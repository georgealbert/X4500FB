#ifndef _X4500FB_h
#define _X4500FB_h

#include <IOKit/IOService.h>
#include <IOKit/graphics/IOFrameBuffer.h>

class X4500 : public IOService

{
    
    OSDeclareDefaultStructors(X4500)
    
public:
    
    virtual bool init(OSDictionary *dictionary = 0);
    
    virtual void free(void);
    
    virtual IOService *probe(IOService *provider, SInt32 *score);
    
    virtual bool start(IOService *provider);
    
    virtual void stop(IOService *provider);
    
};

class X4500FB : public IOFramebuffer
{
    OSDeclareDefaultStructors(X4500FB)
    
public:
    
    virtual IOItemCount getDisplayModeCount(void);
    
    virtual IOReturn getCurrentDisplayMode( IODisplayModeID *displayMode, IOIndex *depth );
    
    virtual IODeviceMemory * getApertureRange( IOPixelAperture aperture );
    
    virtual IOReturn getDisplayModes( IODisplayModeID *allDisplayModes ); 
    
    virtual IOReturn getInformationForDisplayMode( IODisplayModeID displayMode, IODisplayModeInformation *info ); 
    
    virtual const char * getPixelFormats( void ); 
    
    virtual UInt64 getPixelFormatsForDisplayMode( IODisplayModeID displayMode, IOIndex depth ); 
    
    virtual IOReturn getPixelInformation( IODisplayModeID displayMode, IOIndex depth, IOPixelAperture aperture, IOPixelInformation *pixelInfo ); 
};

#endif /*_X4500_h*/
