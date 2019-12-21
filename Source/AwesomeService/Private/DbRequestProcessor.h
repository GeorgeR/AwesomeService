#pragma once

#include "AwesomeGenericRequestProcessor.h"

#include "SQLService.h"

template <typename RequestType, typename ResponseType>
class TDbRequestProcessor
    : public TAwesomeGenericRequestProcessor<RequestType, ResponseType>
{
public:
    void ProcessRequests() override;
};

template <typename RequestType, typename ResponseType>
class TSQLRequestProcessor
    : public TDbRequestProcessor<RequestType, ResponseType>
{
public:
    void ProcessRequests() override;
};

class FSQLRequestProcessor
    : public TSQLRequestProcessor<FSQLRequest, FSQLResponse>
{
public:
    void ProcessRequests() override;
};

template <typename RequestType, typename ResponseType>
void TDbRequestProcessor<RequestType, ResponseType>::ProcessRequests()
{
}

template <typename RequestType, typename ResponseType>
void TSQLRequestProcessor<RequestType, ResponseType>::ProcessRequests()
{
}
