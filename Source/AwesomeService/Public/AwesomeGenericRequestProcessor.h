#pragma once

#include "Future.h"
#include "Guid.h"
#include "Queue.h"
#include "Runnable.h"
#include "RunnableThread.h"
#include "SingleThreadRunnable.h"
#include "TaskGraphInterfaces.h"
#include "ThreadSafeBool.h"

#include "AwesomeServiceTypes.h"

namespace Concepts
{
    struct CHasMemberFunction
    {
        template <typename T, typename FuncType>
        auto Requires(const T& Value, TFunction<FuncType> Function, FString& FunctionName) -> decltype(
            Value.FuncName()
		);
    };

    struct CHasGetResponsePromise
    {
        template <typename RequestType, typename ResponseType>
        auto Requires(RequestType& Request) -> decltype(
            Request.GetPromise()
		);
    };
}

template <typename RequestType, typename ResponseType>
using THasGetResponsePromise = decltype(DeclVal<RequestType&>().GetPromise());

template <typename RequestType, typename ResponseType>
class TAwesomeGenericRequestProcessor
	: public FRunnable,
	public FSingleThreadRunnable
{
    //static_assert(TModels<Concepts::CHasMemberFunction, RequestType, TSharedPtr<TPromise<ResponseType>>(), GetPromise>::Value, "RequestType must have a GetPromise function.");
    static_assert(TModels<Concepts::CHasGetResponsePromise, RequestType, ResponseType>::Value, "RequestType must have a GetPromise function.");

    public : TAwesomeGenericRequestProcessor();
    virtual ~TAwesomeGenericRequestProcessor();

    virtual TFuture<ResponseType> AddRequest(RequestType& Request, const EAwesomeRequestPriority& Priority = EAwesomeRequestPriority::RP_Query_Normal);

#pragma region FRunnable
  public:
    bool Init() override;
    uint32 Run() override;
    void Stop() override;
#pragma endregion FRunnable

#pragma region FSingleThreadRunnable
  public:
    void Tick() override;
    class FSingleThreadRunnable* GetSingleThreadInterface() override
    {
        return this;
    }
#pragma endregion FSingleThreadRunnable

  protected:
	TQueue<RequestType, EQueueMode::Spsc> RequestQueue;
	
    virtual void ProcessRequests() = 0;

  private:
    FThreadSafeBool ExitRequest;
    FRunnableThread* Thread;
    FEvent* Semaphore;
};

template <typename RequestType, typename ResponseType>
TAwesomeGenericRequestProcessor<RequestType, ResponseType>::TAwesomeGenericRequestProcessor() : Thread(nullptr), Semaphore(nullptr)
{
    Semaphore = FGenericPlatformProcess::GetSynchEventFromPool(false);
    Thread = FRunnableThread::Create(this, TEXT("AwesomeGenericService"), 0, EThreadPriority::TPri_BelowNormal);
}

template <typename RequestType, typename ResponseType>
TAwesomeGenericRequestProcessor<RequestType, ResponseType>::~TAwesomeGenericRequestProcessor()
{
    if (Semaphore)
    {
        Semaphore->Trigger();
        if (Thread)
            Thread->WaitForCompletion();

        FGenericPlatformProcess::ReturnSynchEventToPool(Semaphore);
        Semaphore = nullptr;
    }

    if (Thread)
    {
        delete Thread;
        Thread = nullptr;
    }
}

template <typename RequestType, typename ResponseType>
TFuture<ResponseType> TAwesomeGenericRequestProcessor<RequestType, ResponseType>::AddRequest(RequestType& Request, const EAwesomeRequestPriority& Priority)
{
    auto Promise = Request.GetPromise();
    RequestQueue.Enqueue(MoveTemp(Request));

    /** Call this after adding the actual request */
    if (Semaphore)
        Semaphore->Trigger();

    return Promise->GetFuture();
}

template <typename RequestType, typename ResponseType>
bool TAwesomeGenericRequestProcessor<RequestType, ResponseType>::Init()
{
    Semaphore->Trigger();

    // FTaskGraphInterface::Get().AttachToThread(ENamedThreads::GameThread);
    return true;
}

template <typename RequestType, typename ResponseType>
uint32 TAwesomeGenericRequestProcessor<RequestType, ResponseType>::Run()
{
    while (!ExitRequest)
    {
        if (!RequestQueue.IsEmpty())
            ProcessRequests();
        else
            // Waits until Trigger() called
            Semaphore->Wait();
    }

    return 0;
}

template <typename RequestType, typename ResponseType>
void TAwesomeGenericRequestProcessor<RequestType, ResponseType>::Stop()
{
    if (Semaphore)
        Semaphore->Trigger();

    ExitRequest.AtomicSet(true);
}

template <typename RequestType, typename ResponseType>
void TAwesomeGenericRequestProcessor<RequestType, ResponseType>::Tick()
{
    if (!ExitRequest)
    {
        if (!RequestQueue.IsEmpty())
            ProcessRequests();
    }
}
