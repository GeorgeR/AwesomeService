#pragma once

#include "CoreMinimal.h"
#include "DbService.h"
#include "Async/AsyncResult.h"
#include "Containers/Union.h"

#include "SQLService.generated.h"

class FSQLRequestProcessor;

UENUM(BlueprintType)
enum class ESQLDataType : uint8
{
    SQL_Int8			UMETA(DisplayName = "Byte (signed)"),
	SQL_UInt8			UMETA(DisplayName = "Byte"),
	SQL_Int16			UMETA(DisplayName = "Integer16"),
    SQL_UInt16			UMETA(DisplayName = "Integer16 (unsigned)"),
	SQL_Int32			UMETA(DisplayName = "Integer32"),
    SQL_UInt32			UMETA(DisplayName = "Integer32 (unsigned)"),
	SQL_Int64			UMETA(DisplayName = "Integer64"),
    SQL_UInt64			UMETA(DisplayName = "Integer64 (unsigned)"),

	SQL_Float			UMETA(DisplayName = "Float"),
	SQL_Double			UMETA(DisplayName = "Double"),

	SQL_String			UMETA(DisplayName = "String"),
	SQL_Char			UMETA(DisplayName = "Char"),

	SQL_Boolean			UMETA(DisplayName = "Boolean"),

	SQL_Unknown = 255	UMETA(DisplayName = "Unknown (unsupported)")
};

USTRUCT(BlueprintType)
struct AWESOMESERVICE_API FSQLField
{
    GENERATED_BODY()

private:
    typedef TUnion<int8, uint8, int16, uint16, int32, uint32> FIntegerContainer;
    typedef TUnion<int64, uint64> FIntegerContainer2;
    typedef TUnion<float, double> FFloatContainer;
    typedef TUnion<FString, FChar> FStringContainer;
    TUnion<FIntegerContainer, FIntegerContainer2, FFloatContainer, FStringContainer, bool> Value;

public:
    FSQLField();
    explicit FSQLField(ESQLDataType InDataType);

    explicit FSQLField(const int8& InValue);
    explicit FSQLField(const uint8& InValue);
    explicit FSQLField(const int16& InValue);
    explicit FSQLField(const uint16& InValue);
    explicit FSQLField(const int32& InValue);
    explicit FSQLField(const uint32& InValue);
    explicit FSQLField(const int64& InValue);
    explicit FSQLField(const uint64& InValue);

    explicit FSQLField(const float& InValue);
    explicit FSQLField(const double& InValue);

    explicit FSQLField(const FString& InValue);
    explicit FSQLField(const FChar& InValue);

    explicit FSQLField(const bool& InValue);

    FORCEINLINE ESQLDataType GetDataType() const { return DataType; }
	FORCEINLINE bool IsNull() const { return bIsNull; }

    template <typename T>
    typename TDecay<T>::Type As() const;

    template <typename T>
	typename TDecay<T>::Type As(const T& DefaultValue) const;

    template <> int8 As<int8>() const;
    template <> int8 As<int8>(const int8& DefaultValue) const;

	template <> uint8 As<uint8>() const;
    template <> uint8 As<uint8>(const uint8& DefaultValue) const;

	template <> int16 As<int16>() const;
    template <> int16 As<int16>(const int16& DefaultValue) const;

	template <> uint16 As<uint16>() const;
    template <> uint16 As<uint16>(const uint16& DefaultValue) const;

	template <> int32 As<int32>() const;
    template <> int32 As<int32>(const int32& DefaultValue) const;

    template <> uint32 As<uint32>() const;
    template <> uint32 As<uint32>(const uint32& DefaultValue) const;

	template <> int64 As<int64>() const;
    template <> int64 As<int64>(const int64& DefaultValue) const;

	template <> uint64 As<uint64>() const;
    template <> uint64 As<uint64>(const uint64& DefaultValue) const;

	template <> float As<float>() const;
    template <> float As<float>(const float& DefaultValue) const;

	template <> double As<double>() const;
    template <> double As<double>(const double& DefaultValue) const;

	template <> FString As<FString>() const;
    template <> FString As<FString>(const FString& DefaultValue) const;

	template <> FChar As<FChar>() const;
    template <> FChar As<FChar>(const FChar& DefaultValue) const;

	template <> bool As<bool>() const;
    template <> bool As<bool>(const bool& DefaultValue) const;

    FString ToString() const;

private:
    ESQLDataType DataType;
    bool bIsNull;
};

USTRUCT(BlueprintType)
struct AWESOMESERVICE_API FSQLRow
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, FSQLField> Fields;

    FSQLRow() = default;

    FString ToString() const;
};

typedef TArray<FSQLRow> FSQLResponse;

USTRUCT(BlueprintType)
struct AWESOMESERVICE_API FSQLRequest
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Request")
    FString Query;

    //FSQLRequest();

public:
    TSharedPtr<TPromise<FSQLResponse>>& GetPromise() { return Promise; }

private:
    TSharedPtr<TPromise<FSQLResponse>> Promise;
};

/** Base class for SQL db based service */
UCLASS()
class AWESOMESERVICE_API USQLService
    : public UDbService
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Connection")
    FString ConnectionString;

    USQLService();
    virtual ~USQLService();

protected:
    TSharedPtr<FSQLRequestProcessor> RequestProcessor;
};
