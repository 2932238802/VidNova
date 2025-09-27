#pragma once


#include "net/netClient.h"

void TestFromRequest()
{
    net::netClient* httpClient = new net::netClient();
    httpClient->hello();
}
