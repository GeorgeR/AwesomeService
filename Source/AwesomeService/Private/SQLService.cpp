#include "SQLService.h"

#include "DbRequestProcessor.h"

FSQLField::FSQLField()
    : DataType(ESQLDataType::SQL_Unknown),
    bIsNull(false) { }

FSQLField::FSQLField(const ESQLDataType InDataType)
    : DataType(InDataType),
    bIsNull(true) { }

FSQLField::FSQLField(const int8& InValue)
    : DataType(ESQLDataType::SQL_Int8),
    bIsNull(false)
{
    FIntegerContainer IntegerContainer;
    IntegerContainer.SetSubtype<int8>(InValue);

    Value.SetSubtype<FIntegerContainer>(IntegerContainer);
}

FSQLField::FSQLField(const uint8& InValue)
    : DataType(ESQLDataType::SQL_UInt8),
    bIsNull(false)
{
    FIntegerContainer IntegerContainer;
    IntegerContainer.SetSubtype<uint8>(InValue);

    Value.SetSubtype<FIntegerContainer>(IntegerContainer);
}

FSQLField::FSQLField(const int16& InValue)
    : DataType(ESQLDataType::SQL_Int16),
    bIsNull(false)
{
    FIntegerContainer IntegerContainer;
    IntegerContainer.SetSubtype<int16>(InValue);

    Value.SetSubtype<FIntegerContainer>(IntegerContainer);
}

FSQLField::FSQLField(const uint16& InValue)
    : DataType(ESQLDataType::SQL_UInt16),
    bIsNull(false)
{
    FIntegerContainer IntegerContainer;
    IntegerContainer.SetSubtype<uint16>(InValue);

    Value.SetSubtype<FIntegerContainer>(IntegerContainer);
}

FSQLField::FSQLField(const int32& InValue)
    : DataType(ESQLDataType::SQL_Int32),
    bIsNull(false)
{
    FIntegerContainer IntegerContainer;
    IntegerContainer.SetSubtype<int32>(InValue);

    Value.SetSubtype<FIntegerContainer>(IntegerContainer);
}

FSQLField::FSQLField(const uint32& InValue)
    : DataType(ESQLDataType::SQL_UInt32),
    bIsNull(false)
{
    FIntegerContainer IntegerContainer;
    IntegerContainer.SetSubtype<uint32>(InValue);

    Value.SetSubtype<FIntegerContainer>(IntegerContainer);
}

FSQLField::FSQLField(const int64& InValue)
    : DataType(ESQLDataType::SQL_Int64),
    bIsNull(false)
{
    FIntegerContainer2 IntegerContainer;
    IntegerContainer.SetSubtype<int64>(InValue);

    Value.SetSubtype<FIntegerContainer2>(IntegerContainer);
}

FSQLField::FSQLField(const uint64& InValue)
    : DataType(ESQLDataType::SQL_UInt64),
    bIsNull(false)
{
    FIntegerContainer2 IntegerContainer;
    IntegerContainer.SetSubtype<uint64>(InValue);

    Value.SetSubtype<FIntegerContainer2>(IntegerContainer);
}

FSQLField::FSQLField(const float& InValue)
    : DataType(ESQLDataType::SQL_Float),
    bIsNull(false)
{
    FFloatContainer FloatContainer;
    FloatContainer.SetSubtype<float>(InValue);
    
    Value.SetSubtype<FFloatContainer>(FloatContainer);
}

FSQLField::FSQLField(const double& InValue)
    : DataType(ESQLDataType::SQL_Double),
    bIsNull(false)
{
    FFloatContainer FloatContainer;
    FloatContainer.SetSubtype<double>(InValue);
    
    Value.SetSubtype<FFloatContainer>(FloatContainer);
}

FSQLField::FSQLField(const FString& InValue)
    : DataType(ESQLDataType::SQL_String),
    bIsNull(false)
{
    FStringContainer StringContainer;
    StringContainer.SetSubtype<FString>(InValue);
    
    Value.SetSubtype<FStringContainer>(StringContainer);
}

FSQLField::FSQLField(const FChar& InValue)
    : DataType(ESQLDataType::SQL_Char),
    bIsNull(false)
{
    FStringContainer StringContainer;
    StringContainer.SetSubtype<FChar>(InValue);
    
    Value.SetSubtype<FStringContainer>(StringContainer);
}

FSQLField::FSQLField(const bool& InValue)
    : DataType(ESQLDataType::SQL_Boolean),
    bIsNull(false)
{
    Value.SetSubtype<bool>(InValue);
}

template <>
int8 FSQLField::As<int8>() const
{
    return As<int8>(0);
}

template <>
int8 FSQLField::As<int8>(const int8& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer>().GetSubtype<int8>();
}

template <>
uint8 FSQLField::As<uint8>() const
{
    return As<uint8>(0);
}

template <>
uint8 FSQLField::As<uint8>(const uint8& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer>().GetSubtype<uint8>();
}

template <>
int16 FSQLField::As<int16>() const
{
    return As<int16>(0);
}

template <>
int16 FSQLField::As<int16>(const int16& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer>().GetSubtype<int16>();
}

template <>
uint16 FSQLField::As<uint16>() const
{
    return As<uint16>(0);
}

template <>
uint16 FSQLField::As<uint16>(const uint16& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer>().GetSubtype<uint16>();
}

template <>
int32 FSQLField::As<int32>() const
{
    return As<int32>(0);
}

template <>
int32 FSQLField::As<int32>(const int32& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer>().GetSubtype<int32>();
}

template <>
uint32 FSQLField::As<uint32>() const
{
    return As<uint32>(0);
}

template <>
uint32 FSQLField::As<uint32>(const uint32& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer>().GetSubtype<uint32>();
}

template <>
int64 FSQLField::As<int64>() const
{
    return As<int64>(0);
}

template <>
int64 FSQLField::As<int64>(const int64& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer2>().GetSubtype<int64>();
}

template <>
uint64 FSQLField::As<uint64>() const
{
    return As<uint64>(0);
}

template <>
uint64 FSQLField::As<uint64>(const uint64& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FIntegerContainer2>().GetSubtype<uint64>();
}

template <>
float FSQLField::As<float>() const
{
    return As<float>(0.0);
}

template <>
float FSQLField::As<float>(const float& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FFloatContainer>().GetSubtype<float>();
}

template <>
double FSQLField::As<double>() const
{
    return As<double>(0.0);
}

template <>
double FSQLField::As<double>(const double& DefaultValue) const
{
    return Value.GetSubtype<FFloatContainer>().GetSubtype<double>();
}

template <>
FString FSQLField::As<FString>() const
{
    return As<FString>(TEXT(""));
}

template <>
FString FSQLField::As<FString>(const FString& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FStringContainer>().GetSubtype<FString>();
}

template <>
FChar FSQLField::As<TChar<wchar_t>>() const
{
    return As<FChar>(FChar());
}

template <>
FChar FSQLField::As<TChar<wchar_t>>(const FChar& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<FStringContainer>().GetSubtype<FChar>();
}

template <>
bool FSQLField::As<bool>() const
{
    return As<bool>(false);
}

template <>
bool FSQLField::As<bool>(const bool& DefaultValue) const
{
    return IsNull() ? DefaultValue : Value.GetSubtype<bool>();
}

FString FSQLField::ToString() const
{
    unimplemented();
    return TEXT("");
}

FString FSQLRow::ToString() const
{
    unimplemented();
    return TEXT("");
}

USQLService::USQLService()
{
    RequestProcessor = MakeShared<FSQLRequestProcessor>();
}

USQLService::~USQLService()
{
    if(RequestProcessor.IsValid())
    {
        RequestProcessor->Stop();
        RequestProcessor.Reset();
    }
}
