#pragma once

#include "CoreMinimal.h"
#include "DbService.h"

#include "SQLService.generated.h"

/** Base class for SQL db based service */
UCLASS()
class AWESOMESERVICE_API USQLService
    : public UDbService
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Connection")
    FString ConnectionString;
};