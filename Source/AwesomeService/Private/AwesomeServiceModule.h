#pragma once

#include "IAwesomeServiceModuleInterface.h"

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Stats/Stats.h"
#include "Stats/Stats2.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAwesomeService, VeryVerbose, All);

DECLARE_STATS_GROUP(TEXT("AwesomeService"), STATGROUP_AwesomeService, STATCAT_Advanced);

class FAwesomeServiceModule
    : public IAwesomeServiceModuleInterface
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};