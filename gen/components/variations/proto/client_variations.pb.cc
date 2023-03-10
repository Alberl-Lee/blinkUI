// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_variations.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_variations.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace variations {

void protobuf_ShutdownFile_client_5fvariations_2eproto()
{
    delete ClientVariations::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_client_5fvariations_2eproto_impl()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_client_5fvariations_2eproto()
{
    static bool already_here = false;
    if (already_here)
        return;
    already_here = true;
    GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
    ClientVariations::default_instance_ = new ClientVariations();
    ClientVariations::default_instance_->InitAsDefaultInstance();
    ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_client_5fvariations_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_client_5fvariations_2eproto_once_);
void protobuf_AddDesc_client_5fvariations_2eproto()
{
    ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_client_5fvariations_2eproto_once_,
        &protobuf_AddDesc_client_5fvariations_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_client_5fvariations_2eproto {
    StaticDescriptorInitializer_client_5fvariations_2eproto()
    {
        protobuf_AddDesc_client_5fvariations_2eproto();
    }
} static_descriptor_initializer_client_5fvariations_2eproto_;
#endif

namespace {

    static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
    GOOGLE_ATTRIBUTE_NOINLINE static void MergeFromFail(int line)
    {
        GOOGLE_CHECK(false) << __FILE__ << ":" << line;
    }

} // namespace

// ===================================================================

static ::std::string* MutableUnknownFieldsForClientVariations(
    ClientVariations* ptr)
{
    return ptr->mutable_unknown_fields();
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ClientVariations::kVariationIdFieldNumber;
const int ClientVariations::kTriggerVariationIdFieldNumber;
#endif // !defined(_MSC_VER) || _MSC_VER >= 1900

ClientVariations::ClientVariations()
    : ::google::protobuf::MessageLite()
    , _arena_ptr_(NULL)
{
    SharedCtor();
    // @@protoc_insertion_point(constructor:variations.ClientVariations)
}

void ClientVariations::InitAsDefaultInstance()
{
}

ClientVariations::ClientVariations(const ClientVariations& from)
    : ::google::protobuf::MessageLite()
    , _arena_ptr_(NULL)
{
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:variations.ClientVariations)
}

void ClientVariations::SharedCtor()
{
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    _unknown_fields_.UnsafeSetDefault(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ClientVariations::~ClientVariations()
{
    // @@protoc_insertion_point(destructor:variations.ClientVariations)
    SharedDtor();
}

void ClientVariations::SharedDtor()
{
    _unknown_fields_.DestroyNoArena(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    if (this != &default_instance()) {
#else
    if (this != default_instance_) {
#endif
    }
}

void ClientVariations::SetCachedSize(int size) const
{
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ClientVariations& ClientVariations::default_instance()
{
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    protobuf_AddDesc_client_5fvariations_2eproto();
#else
    if (default_instance_ == NULL)
        protobuf_AddDesc_client_5fvariations_2eproto();
#endif
    return *default_instance_;
}

ClientVariations* ClientVariations::default_instance_ = NULL;

ClientVariations* ClientVariations::New(::google::protobuf::Arena* arena) const
{
    ClientVariations* n = new ClientVariations;
    if (arena != NULL) {
        arena->Own(n);
    }
    return n;
}

void ClientVariations::Clear()
{
    // @@protoc_insertion_point(message_clear_start:variations.ClientVariations)
    variation_id_.Clear();
    trigger_variation_id_.Clear();
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    _unknown_fields_.ClearToEmptyNoArena(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool ClientVariations::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input)
{
#define DO_(EXPRESSION)                   \
    if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) \
    goto failure
    ::google::protobuf::uint32 tag;
    ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
        ::google::protobuf::internal::NewPermanentCallback(
            &MutableUnknownFieldsForClientVariations, this));
    ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
        &unknown_fields_string, false);
    // @@protoc_insertion_point(parse_start:variations.ClientVariations)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second)
            goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
        // repeated int32 variation_id = 1;
        case 1: {
            if (tag == 8) {
            parse_variation_id:
                DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                    ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                    1, 8, input, this->mutable_variation_id())));
            } else if (tag == 10) {
                DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                    ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                    input, this->mutable_variation_id())));
            } else {
                goto handle_unusual;
            }
            if (input->ExpectTag(8))
                goto parse_variation_id;
            if (input->ExpectTag(24))
                goto parse_trigger_variation_id;
            break;
        }

        // repeated int32 trigger_variation_id = 3;
        case 3: {
            if (tag == 24) {
            parse_trigger_variation_id:
                DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                    ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                    1, 24, input, this->mutable_trigger_variation_id())));
            } else if (tag == 26) {
                DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                    ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                    input, this->mutable_trigger_variation_id())));
            } else {
                goto handle_unusual;
            }
            if (input->ExpectTag(24))
                goto parse_trigger_variation_id;
            if (input->ExpectAtEnd())
                goto success;
            break;
        }

        default: {
        handle_unusual:
            if (tag == 0 || ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) == ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
                goto success;
            }
            DO_(::google::protobuf::internal::WireFormatLite::SkipField(
                input, tag, &unknown_fields_stream));
            break;
        }
        }
    }
success:
    // @@protoc_insertion_point(parse_success:variations.ClientVariations)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:variations.ClientVariations)
    return false;
#undef DO_
}

void ClientVariations::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const
{
    // @@protoc_insertion_point(serialize_start:variations.ClientVariations)
    // repeated int32 variation_id = 1;
    for (int i = 0; i < this->variation_id_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(
            1, this->variation_id(i), output);
    }

    // repeated int32 trigger_variation_id = 3;
    for (int i = 0; i < this->trigger_variation_id_size(); i++) {
        ::google::protobuf::internal::WireFormatLite::WriteInt32(
            3, this->trigger_variation_id(i), output);
    }

    output->WriteRaw(unknown_fields().data(),
        static_cast<int>(unknown_fields().size()));
    // @@protoc_insertion_point(serialize_end:variations.ClientVariations)
}

int ClientVariations::ByteSize() const
{
    // @@protoc_insertion_point(message_byte_size_start:variations.ClientVariations)
    int total_size = 0;

    // repeated int32 variation_id = 1;
    {
        int data_size = 0;
        for (int i = 0; i < this->variation_id_size(); i++) {
            data_size += ::google::protobuf::internal::WireFormatLite::
                Int32Size(this->variation_id(i));
        }
        total_size += 1 * this->variation_id_size() + data_size;
    }

    // repeated int32 trigger_variation_id = 3;
    {
        int data_size = 0;
        for (int i = 0; i < this->trigger_variation_id_size(); i++) {
            data_size += ::google::protobuf::internal::WireFormatLite::
                Int32Size(this->trigger_variation_id(i));
        }
        total_size += 1 * this->trigger_variation_id_size() + data_size;
    }

    total_size += unknown_fields().size();

    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = total_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    return total_size;
}

void ClientVariations::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from)
{
    MergeFrom(*::google::protobuf::down_cast<const ClientVariations*>(&from));
}

void ClientVariations::MergeFrom(const ClientVariations& from)
{
    // @@protoc_insertion_point(class_specific_merge_from_start:variations.ClientVariations)
    if (GOOGLE_PREDICT_FALSE(&from == this))
        MergeFromFail(__LINE__);
    variation_id_.MergeFrom(from.variation_id_);
    trigger_variation_id_.MergeFrom(from.trigger_variation_id_);
    if (!from.unknown_fields().empty()) {
        mutable_unknown_fields()->append(from.unknown_fields());
    }
}

void ClientVariations::CopyFrom(const ClientVariations& from)
{
    // @@protoc_insertion_point(class_specific_copy_from_start:variations.ClientVariations)
    if (&from == this)
        return;
    Clear();
    MergeFrom(from);
}

bool ClientVariations::IsInitialized() const
{

    return true;
}

void ClientVariations::Swap(ClientVariations* other)
{
    if (other == this)
        return;
    InternalSwap(other);
}
void ClientVariations::InternalSwap(ClientVariations* other)
{
    variation_id_.UnsafeArenaSwap(&other->variation_id_);
    trigger_variation_id_.UnsafeArenaSwap(&other->trigger_variation_id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
}

::std::string ClientVariations::GetTypeName() const
{
    return "variations.ClientVariations";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ClientVariations

// repeated int32 variation_id = 1;
int ClientVariations::variation_id_size() const
{
    return variation_id_.size();
}
void ClientVariations::clear_variation_id()
{
    variation_id_.Clear();
}
::google::protobuf::int32 ClientVariations::variation_id(int index) const
{
    // @@protoc_insertion_point(field_get:variations.ClientVariations.variation_id)
    return variation_id_.Get(index);
}
void ClientVariations::set_variation_id(int index, ::google::protobuf::int32 value)
{
    variation_id_.Set(index, value);
    // @@protoc_insertion_point(field_set:variations.ClientVariations.variation_id)
}
void ClientVariations::add_variation_id(::google::protobuf::int32 value)
{
    variation_id_.Add(value);
    // @@protoc_insertion_point(field_add:variations.ClientVariations.variation_id)
}
const ::google::protobuf::RepeatedField<::google::protobuf::int32>&
ClientVariations::variation_id() const
{
    // @@protoc_insertion_point(field_list:variations.ClientVariations.variation_id)
    return variation_id_;
}
::google::protobuf::RepeatedField<::google::protobuf::int32>*
ClientVariations::mutable_variation_id()
{
    // @@protoc_insertion_point(field_mutable_list:variations.ClientVariations.variation_id)
    return &variation_id_;
}

// repeated int32 trigger_variation_id = 3;
int ClientVariations::trigger_variation_id_size() const
{
    return trigger_variation_id_.size();
}
void ClientVariations::clear_trigger_variation_id()
{
    trigger_variation_id_.Clear();
}
::google::protobuf::int32 ClientVariations::trigger_variation_id(int index) const
{
    // @@protoc_insertion_point(field_get:variations.ClientVariations.trigger_variation_id)
    return trigger_variation_id_.Get(index);
}
void ClientVariations::set_trigger_variation_id(int index, ::google::protobuf::int32 value)
{
    trigger_variation_id_.Set(index, value);
    // @@protoc_insertion_point(field_set:variations.ClientVariations.trigger_variation_id)
}
void ClientVariations::add_trigger_variation_id(::google::protobuf::int32 value)
{
    trigger_variation_id_.Add(value);
    // @@protoc_insertion_point(field_add:variations.ClientVariations.trigger_variation_id)
}
const ::google::protobuf::RepeatedField<::google::protobuf::int32>&
ClientVariations::trigger_variation_id() const
{
    // @@protoc_insertion_point(field_list:variations.ClientVariations.trigger_variation_id)
    return trigger_variation_id_;
}
::google::protobuf::RepeatedField<::google::protobuf::int32>*
ClientVariations::mutable_trigger_variation_id()
{
    // @@protoc_insertion_point(field_mutable_list:variations.ClientVariations.trigger_variation_id)
    return &trigger_variation_id_;
}

#endif // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

} // namespace variations

// @@protoc_insertion_point(global_scope)
