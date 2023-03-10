// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: encryption.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "encryption.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace sync_pb {

void protobuf_ShutdownFile_encryption_2eproto()
{
    delete EncryptedData::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_encryption_2eproto_impl()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_encryption_2eproto()
{
    static bool already_here = false;
    if (already_here)
        return;
    already_here = true;
    GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
    EncryptedData::default_instance_ = new EncryptedData();
    EncryptedData::default_instance_->InitAsDefaultInstance();
    ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_encryption_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_encryption_2eproto_once_);
void protobuf_AddDesc_encryption_2eproto()
{
    ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_encryption_2eproto_once_,
        &protobuf_AddDesc_encryption_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_encryption_2eproto {
    StaticDescriptorInitializer_encryption_2eproto()
    {
        protobuf_AddDesc_encryption_2eproto();
    }
} static_descriptor_initializer_encryption_2eproto_;
#endif

namespace {

    static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
    GOOGLE_ATTRIBUTE_NOINLINE static void MergeFromFail(int line)
    {
        GOOGLE_CHECK(false) << __FILE__ << ":" << line;
    }

} // namespace

// ===================================================================

static ::std::string* MutableUnknownFieldsForEncryptedData(
    EncryptedData* ptr)
{
    return ptr->mutable_unknown_fields();
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int EncryptedData::kKeyNameFieldNumber;
const int EncryptedData::kBlobFieldNumber;
#endif // !defined(_MSC_VER) || _MSC_VER >= 1900

EncryptedData::EncryptedData()
    : ::google::protobuf::MessageLite()
    , _arena_ptr_(NULL)
{
    SharedCtor();
    // @@protoc_insertion_point(constructor:sync_pb.EncryptedData)
}

void EncryptedData::InitAsDefaultInstance()
{
}

EncryptedData::EncryptedData(const EncryptedData& from)
    : ::google::protobuf::MessageLite()
    , _arena_ptr_(NULL)
{
    SharedCtor();
    MergeFrom(from);
    // @@protoc_insertion_point(copy_constructor:sync_pb.EncryptedData)
}

void EncryptedData::SharedCtor()
{
    ::google::protobuf::internal::GetEmptyString();
    _cached_size_ = 0;
    _unknown_fields_.UnsafeSetDefault(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    key_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    blob_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

EncryptedData::~EncryptedData()
{
    // @@protoc_insertion_point(destructor:sync_pb.EncryptedData)
    SharedDtor();
}

void EncryptedData::SharedDtor()
{
    _unknown_fields_.DestroyNoArena(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    key_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    blob_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    if (this != &default_instance()) {
#else
    if (this != default_instance_) {
#endif
    }
}

void EncryptedData::SetCachedSize(int size) const
{
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const EncryptedData& EncryptedData::default_instance()
{
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    protobuf_AddDesc_encryption_2eproto();
#else
    if (default_instance_ == NULL)
        protobuf_AddDesc_encryption_2eproto();
#endif
    return *default_instance_;
}

EncryptedData* EncryptedData::default_instance_ = NULL;

EncryptedData* EncryptedData::New(::google::protobuf::Arena* arena) const
{
    EncryptedData* n = new EncryptedData;
    if (arena != NULL) {
        arena->Own(n);
    }
    return n;
}

void EncryptedData::Clear()
{
    // @@protoc_insertion_point(message_clear_start:sync_pb.EncryptedData)
    if (_has_bits_[0 / 32] & 3u) {
        if (has_key_name()) {
            key_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
        }
        if (has_blob()) {
            blob_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
        }
    }
    ::memset(_has_bits_, 0, sizeof(_has_bits_));
    _unknown_fields_.ClearToEmptyNoArena(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool EncryptedData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input)
{
#define DO_(EXPRESSION)                   \
    if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) \
    goto failure
    ::google::protobuf::uint32 tag;
    ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
        ::google::protobuf::internal::NewPermanentCallback(
            &MutableUnknownFieldsForEncryptedData, this));
    ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
        &unknown_fields_string, false);
    // @@protoc_insertion_point(parse_start:sync_pb.EncryptedData)
    for (;;) {
        ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
        tag = p.first;
        if (!p.second)
            goto handle_unusual;
        switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
        // optional string key_name = 1;
        case 1: {
            if (tag == 10) {
                DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                    input, this->mutable_key_name()));
            } else {
                goto handle_unusual;
            }
            if (input->ExpectTag(18))
                goto parse_blob;
            break;
        }

        // optional string blob = 2;
        case 2: {
            if (tag == 18) {
            parse_blob:
                DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                    input, this->mutable_blob()));
            } else {
                goto handle_unusual;
            }
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
    // @@protoc_insertion_point(parse_success:sync_pb.EncryptedData)
    return true;
failure:
    // @@protoc_insertion_point(parse_failure:sync_pb.EncryptedData)
    return false;
#undef DO_
}

void EncryptedData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const
{
    // @@protoc_insertion_point(serialize_start:sync_pb.EncryptedData)
    // optional string key_name = 1;
    if (has_key_name()) {
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            1, this->key_name(), output);
    }

    // optional string blob = 2;
    if (has_blob()) {
        ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
            2, this->blob(), output);
    }

    output->WriteRaw(unknown_fields().data(),
        static_cast<int>(unknown_fields().size()));
    // @@protoc_insertion_point(serialize_end:sync_pb.EncryptedData)
}

int EncryptedData::ByteSize() const
{
    // @@protoc_insertion_point(message_byte_size_start:sync_pb.EncryptedData)
    int total_size = 0;

    if (_has_bits_[0 / 32] & 3u) {
        // optional string key_name = 1;
        if (has_key_name()) {
            total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(this->key_name());
        }

        // optional string blob = 2;
        if (has_blob()) {
            total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(this->blob());
        }
    }
    total_size += unknown_fields().size();

    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _cached_size_ = total_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    return total_size;
}

void EncryptedData::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from)
{
    MergeFrom(*::google::protobuf::down_cast<const EncryptedData*>(&from));
}

void EncryptedData::MergeFrom(const EncryptedData& from)
{
    // @@protoc_insertion_point(class_specific_merge_from_start:sync_pb.EncryptedData)
    if (GOOGLE_PREDICT_FALSE(&from == this))
        MergeFromFail(__LINE__);
    if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
        if (from.has_key_name()) {
            set_has_key_name();
            key_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.key_name_);
        }
        if (from.has_blob()) {
            set_has_blob();
            blob_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.blob_);
        }
    }
    if (!from.unknown_fields().empty()) {
        mutable_unknown_fields()->append(from.unknown_fields());
    }
}

void EncryptedData::CopyFrom(const EncryptedData& from)
{
    // @@protoc_insertion_point(class_specific_copy_from_start:sync_pb.EncryptedData)
    if (&from == this)
        return;
    Clear();
    MergeFrom(from);
}

bool EncryptedData::IsInitialized() const
{

    return true;
}

void EncryptedData::Swap(EncryptedData* other)
{
    if (other == this)
        return;
    InternalSwap(other);
}
void EncryptedData::InternalSwap(EncryptedData* other)
{
    key_name_.Swap(&other->key_name_);
    blob_.Swap(&other->blob_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
}

::std::string EncryptedData::GetTypeName() const
{
    return "sync_pb.EncryptedData";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// EncryptedData

// optional string key_name = 1;
bool EncryptedData::has_key_name() const
{
    return (_has_bits_[0] & 0x00000001u) != 0;
}
void EncryptedData::set_has_key_name()
{
    _has_bits_[0] |= 0x00000001u;
}
void EncryptedData::clear_has_key_name()
{
    _has_bits_[0] &= ~0x00000001u;
}
void EncryptedData::clear_key_name()
{
    key_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    clear_has_key_name();
}
const ::std::string& EncryptedData::key_name() const
{
    // @@protoc_insertion_point(field_get:sync_pb.EncryptedData.key_name)
    return key_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void EncryptedData::set_key_name(const ::std::string& value)
{
    set_has_key_name();
    key_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
    // @@protoc_insertion_point(field_set:sync_pb.EncryptedData.key_name)
}
void EncryptedData::set_key_name(const char* value)
{
    set_has_key_name();
    key_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
    // @@protoc_insertion_point(field_set_char:sync_pb.EncryptedData.key_name)
}
void EncryptedData::set_key_name(const char* value, size_t size)
{
    set_has_key_name();
    key_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
        ::std::string(reinterpret_cast<const char*>(value), size));
    // @@protoc_insertion_point(field_set_pointer:sync_pb.EncryptedData.key_name)
}
::std::string* EncryptedData::mutable_key_name()
{
    set_has_key_name();
    // @@protoc_insertion_point(field_mutable:sync_pb.EncryptedData.key_name)
    return key_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* EncryptedData::release_key_name()
{
    // @@protoc_insertion_point(field_release:sync_pb.EncryptedData.key_name)
    clear_has_key_name();
    return key_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void EncryptedData::set_allocated_key_name(::std::string* key_name)
{
    if (key_name != NULL) {
        set_has_key_name();
    } else {
        clear_has_key_name();
    }
    key_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key_name);
    // @@protoc_insertion_point(field_set_allocated:sync_pb.EncryptedData.key_name)
}

// optional string blob = 2;
bool EncryptedData::has_blob() const
{
    return (_has_bits_[0] & 0x00000002u) != 0;
}
void EncryptedData::set_has_blob()
{
    _has_bits_[0] |= 0x00000002u;
}
void EncryptedData::clear_has_blob()
{
    _has_bits_[0] &= ~0x00000002u;
}
void EncryptedData::clear_blob()
{
    blob_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    clear_has_blob();
}
const ::std::string& EncryptedData::blob() const
{
    // @@protoc_insertion_point(field_get:sync_pb.EncryptedData.blob)
    return blob_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void EncryptedData::set_blob(const ::std::string& value)
{
    set_has_blob();
    blob_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
    // @@protoc_insertion_point(field_set:sync_pb.EncryptedData.blob)
}
void EncryptedData::set_blob(const char* value)
{
    set_has_blob();
    blob_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
    // @@protoc_insertion_point(field_set_char:sync_pb.EncryptedData.blob)
}
void EncryptedData::set_blob(const char* value, size_t size)
{
    set_has_blob();
    blob_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
        ::std::string(reinterpret_cast<const char*>(value), size));
    // @@protoc_insertion_point(field_set_pointer:sync_pb.EncryptedData.blob)
}
::std::string* EncryptedData::mutable_blob()
{
    set_has_blob();
    // @@protoc_insertion_point(field_mutable:sync_pb.EncryptedData.blob)
    return blob_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* EncryptedData::release_blob()
{
    // @@protoc_insertion_point(field_release:sync_pb.EncryptedData.blob)
    clear_has_blob();
    return blob_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void EncryptedData::set_allocated_blob(::std::string* blob)
{
    if (blob != NULL) {
        set_has_blob();
    } else {
        clear_has_blob();
    }
    blob_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), blob);
    // @@protoc_insertion_point(field_set_allocated:sync_pb.EncryptedData.blob)
}

#endif // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

} // namespace sync_pb

// @@protoc_insertion_point(global_scope)
