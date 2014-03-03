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
};