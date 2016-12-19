#include "GbxRemote.h"

bool GbxRemote::Init(int port)
{
    return InitWithIp("localhost", port);
}

bool GbxRemote::InitWithIp(std::string host, int port)
{
    server.conn("178.63.88.110", 5090);
    char* data = server.receive(4);
    const first_response* response = reinterpret_cast<const first_response*>(data);
    int size = (int)response->size;
    if(size > 64)
    {
        currentError->number = -32300;
        currentError->message = "transport error - wrong lowlevel protocol header";
        return false;
    }

    char protocolResponse[(size+1)];
    strcpy(protocolResponse, server.receive(size));

    if(strcmp(protocolResponse, "GBXRemote 1") == 0)
    {
        currentError->number = -32300;
        currentError->message = "transport error - old version of trackmania server detected";
        return false;
    }
    else if(strcmp(protocolResponse, "GBXRemote 2") == 0)
    {
        protocol = 2;
    }
    else
    {
        currentError->number = -32300;
        currentError->message = "transport error - wrong lowlevel protocol version";
        return false;
    }

    return true;
}

void GbxRemote::Terminate()
{
    server.close();
}

bool GbxRemote::Query(GbxMessage* query)
{
    if(!server.send_data(query->GetXml()))
    {
        currentError->number = -32300;
        currentError->message = "transport error - connection interrupted!";
        return false;
    }

    unsigned long handle = -1;
    int size = 0;
    do
    {
        char* data = server.receive(8);
        const message_response* message = reinterpret_cast<const message_response*>(data);
        size = message->size;
        std::cout << "Size: " << size << std::endl;
        std::cout << "Handle: " << (message->handle & 0x80000000) << std::endl;
        std::cout << "Current handle: " << (server.reqhandle & 0x80000000) << std::endl;

        if(size > (4096*1024))
        {
            currentError->number = -32300;
            std::stringstream errorMessage;
            errorMessage << "transport error - response too large " << size;
            currentError->message = errorMessage.str();
            return false;
        }

        handle = (message->handle & 0x80000000);
    } while(handle != (server.reqhandle & 0x80000000));

    currentResponse = server.receive(size);
    return true;
}

GbxError* GbxRemote::GetCurrentError()
{
    return currentError;
}

char* GbxRemote::GetResponse()
{
    if(currentResponse != NULL)
    {
        char* returnResponse = currentResponse;
        currentResponse = NULL;
        return returnResponse;
    }

    return NULL;
}

int GbxRemote::GetProtocol()
{
    return protocol;
}
