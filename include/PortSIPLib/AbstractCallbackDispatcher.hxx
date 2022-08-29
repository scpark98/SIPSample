#ifndef PORTSIP_ABSTRACTCALLBACKDISPATCHER_hxx
#define PORTSIP_ABSTRACTCALLBACKDISPATCHER_hxx

namespace PortSIP
{

class AbstractCallbackDispatcher
{
public:

	virtual void onMessage(void * params) = 0;

protected:


private:

};


}


#endif