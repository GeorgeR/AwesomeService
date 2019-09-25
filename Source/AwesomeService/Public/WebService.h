#pragma once

#include "CoreMinimal.h"
#include "AwesomeServiceBase.h"

#include "WebService.generated.h"

/** Base class for web based service */
UCLASS()
class AWESOMESERVICE_API UWebService
    : public UAwesomeServiceBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Connection")
    FString Url;
};