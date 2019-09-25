#include "AwesomeServiceModule.h"

DEFINE_LOG_CATEGORY(LogAwesomeService);

#define LOCTEXT_NAMESPACE "AwesomeService"

void FAwesomeServiceModule::StartupModule()
{

}

void FAwesomeServiceModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAwesomeServiceModule, AwesomeService)