#pragma once

#include "CoreMinimal.h"

#include "AwesomeServiceTypes.generated.h"

UENUM()
enum class EAwesomeRequestPriority : uint8
{
    RP_FireForget_Low       UMETA(DisplayName = "Fire&Forget Low Priority"),
    RP_FireForget_Normal    UMETA(DisplayName = "Fire&Forget Normal Priority"),
    RP_FireForget_High      UMETA(DisplayName = "Fire&Forget High Priority"),
    RP_Query_Low            UMETA(DisplayName = "Query Low Priority"),
    RP_Query_Normal         UMETA(DisplayName = "Query Normal Priority"),
    RP_Query_High           UMETA(DisplayName = "Query High Priority")
};
