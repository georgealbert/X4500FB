#include <IOKit/IOLib.h>
#include <IOKit/graphics/IOFrameBuffer.h>
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
    return kIOReturnSuccess;
}

