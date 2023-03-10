// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_test_internal.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_test_internal.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace ipc {
namespace invalidation {

    void protobuf_ShutdownFile_client_5ftest_5finternal_2eproto()
    {
        delete RegistrationManagerStateP::default_instance_;
    }

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    void protobuf_AddDesc_client_5ftest_5finternal_2eproto_impl()
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
    void protobuf_AddDesc_client_5ftest_5finternal_2eproto()
    {
        static bool already_here = false;
        if (already_here)
            return;
        already_here = true;
        GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
        ::ipc::invalidation::protobuf_AddDesc_client_5fprotocol_2eproto();
        RegistrationManagerStateP::default_instance_ = new RegistrationManagerStateP();
        RegistrationManagerStateP::default_instance_->InitAsDefaultInstance();
        ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_client_5ftest_5finternal_2eproto);
    }

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_client_5ftest_5finternal_2eproto_once_);
    void protobuf_AddDesc_client_5ftest_5finternal_2eproto()
    {
        ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_client_5ftest_5finternal_2eproto_once_,
            &protobuf_AddDesc_client_5ftest_5finternal_2eproto_impl);
    }
#else
    // Force AddDescriptors() to be called at static initialization time.
    struct StaticDescriptorInitializer_client_5ftest_5finternal_2eproto {
        StaticDescriptorInitializer_client_5ftest_5finternal_2eproto()
        {
            protobuf_AddDesc_client_5ftest_5finternal_2eproto();
        }
    } static_descriptor_initializer_client_5ftest_5finternal_2eproto_;
#endif

    namespace {

        static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
        GOOGLE_ATTRIBUTE_NOINLINE static void MergeFromFail(int line)
        {
            GOOGLE_CHECK(false) << __FILE__ << ":" << line;
        }

    } // namespace

    // ===================================================================

    static ::std::string* MutableUnknownFieldsForRegistrationManagerStateP(
        RegistrationManagerStateP* ptr)
    {
        return ptr->mutable_unknown_fields();
    }

#if !defined(_MSC_VER) || _MSC_VER >= 1900
    const int RegistrationManagerStateP::kClientSummaryFieldNumber;
    const int RegistrationManagerStateP::kServerSummaryFieldNumber;
    const int RegistrationManagerStateP::kRegisteredObjectsFieldNumber;
#endif // !defined(_MSC_VER) || _MSC_VER >= 1900

    RegistrationManagerStateP::RegistrationManagerStateP()
        : ::google::protobuf::MessageLite()
        , _arena_ptr_(NULL)
    {
        SharedCtor();
        // @@protoc_insertion_point(constructor:ipc.invalidation.RegistrationManagerStateP)
    }

    void RegistrationManagerStateP::InitAsDefaultInstance()
    {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        client_summary_ = const_cast<::ipc::invalidation::RegistrationSummary*>(
            ::ipc::invalidation::RegistrationSummary::internal_default_instance());
#else
        client_summary_ = const_cast<::ipc::invalidation::RegistrationSummary*>(&::ipc::invalidation::RegistrationSummary::default_instance());
#endif
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        server_summary_ = const_cast<::ipc::invalidation::RegistrationSummary*>(
            ::ipc::invalidation::RegistrationSummary::internal_default_instance());
#else
        server_summary_ = const_cast<::ipc::invalidation::RegistrationSummary*>(&::ipc::invalidation::RegistrationSummary::default_instance());
#endif
    }

    RegistrationManagerStateP::RegistrationManagerStateP(const RegistrationManagerStateP& from)
        : ::google::protobuf::MessageLite()
        , _arena_ptr_(NULL)
    {
        SharedCtor();
        MergeFrom(from);
        // @@protoc_insertion_point(copy_constructor:ipc.invalidation.RegistrationManagerStateP)
    }

    void RegistrationManagerStateP::SharedCtor()
    {
        ::google::protobuf::internal::GetEmptyString();
        _cached_size_ = 0;
        _unknown_fields_.UnsafeSetDefault(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
        client_summary_ = NULL;
        server_summary_ = NULL;
        ::memset(_has_bits_, 0, sizeof(_has_bits_));
    }

    RegistrationManagerStateP::~RegistrationManagerStateP()
    {
        // @@protoc_insertion_point(destructor:ipc.invalidation.RegistrationManagerStateP)
        SharedDtor();
    }

    void RegistrationManagerStateP::SharedDtor()
    {
        _unknown_fields_.DestroyNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        if (this != &default_instance()) {
#else
        if (this != default_instance_) {
#endif
            delete client_summary_;
            delete server_summary_;
        }
    }

    void RegistrationManagerStateP::SetCachedSize(int size) const
    {
        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _cached_size_ = size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
    }
    const RegistrationManagerStateP& RegistrationManagerStateP::default_instance()
    {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        protobuf_AddDesc_client_5ftest_5finternal_2eproto();
#else
        if (default_instance_ == NULL)
            protobuf_AddDesc_client_5ftest_5finternal_2eproto();
#endif
        return *default_instance_;
    }

    RegistrationManagerStateP* RegistrationManagerStateP::default_instance_ = NULL;

    RegistrationManagerStateP* RegistrationManagerStateP::New(::google::protobuf::Arena* arena) const
    {
        RegistrationManagerStateP* n = new RegistrationManagerStateP;
        if (arena != NULL) {
            arena->Own(n);
        }
        return n;
    }

    void RegistrationManagerStateP::Clear()
    {
        // @@protoc_insertion_point(message_clear_start:ipc.invalidation.RegistrationManagerStateP)
        if (_has_bits_[0 / 32] & 3u) {
            if (has_client_summary()) {
                if (client_summary_ != NULL)
                    client_summary_->::ipc::invalidation::RegistrationSummary::Clear();
            }
            if (has_server_summary()) {
                if (server_summary_ != NULL)
                    server_summary_->::ipc::invalidation::RegistrationSummary::Clear();
            }
        }
        registered_objects_.Clear();
        ::memset(_has_bits_, 0, sizeof(_has_bits_));
        _unknown_fields_.ClearToEmptyNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }

    bool RegistrationManagerStateP::MergePartialFromCodedStream(
        ::google::protobuf::io::CodedInputStream* input)
    {
#define DO_(EXPRESSION)                   \
    if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) \
    goto failure
        ::google::protobuf::uint32 tag;
        ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
            ::google::protobuf::internal::NewPermanentCallback(
                &MutableUnknownFieldsForRegistrationManagerStateP, this));
        ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
            &unknown_fields_string, false);
        // @@protoc_insertion_point(parse_start:ipc.invalidation.RegistrationManagerStateP)
        for (;;) {
            ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
            tag = p.first;
            if (!p.second)
                goto handle_unusual;
            switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .ipc.invalidation.RegistrationSummary client_summary = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                        input, mutable_client_summary()));
                } else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18))
                    goto parse_server_summary;
                break;
            }

            // optional .ipc.invalidation.RegistrationSummary server_summary = 2;
            case 2: {
                if (tag == 18) {
                parse_server_summary:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                        input, mutable_server_summary()));
                } else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26))
                    goto parse_registered_objects;
                break;
            }

            // repeated .ipc.invalidation.ObjectIdP registered_objects = 3;
            case 3: {
                if (tag == 26) {
                parse_registered_objects:
                    DO_(input->IncrementRecursionDepth());
                parse_loop_registered_objects:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                        input, add_registered_objects()));
                } else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(26))
                    goto parse_loop_registered_objects;
                input->UnsafeDecrementRecursionDepth();
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
        // @@protoc_insertion_point(parse_success:ipc.invalidation.RegistrationManagerStateP)
        return true;
    failure:
        // @@protoc_insertion_point(parse_failure:ipc.invalidation.RegistrationManagerStateP)
        return false;
#undef DO_
    }

    void RegistrationManagerStateP::SerializeWithCachedSizes(
        ::google::protobuf::io::CodedOutputStream* output) const
    {
        // @@protoc_insertion_point(serialize_start:ipc.invalidation.RegistrationManagerStateP)
        // optional .ipc.invalidation.RegistrationSummary client_summary = 1;
        if (has_client_summary()) {
            ::google::protobuf::internal::WireFormatLite::WriteMessage(
                1, *this->client_summary_, output);
        }

        // optional .ipc.invalidation.RegistrationSummary server_summary = 2;
        if (has_server_summary()) {
            ::google::protobuf::internal::WireFormatLite::WriteMessage(
                2, *this->server_summary_, output);
        }

        // repeated .ipc.invalidation.ObjectIdP registered_objects = 3;
        for (unsigned int i = 0, n = this->registered_objects_size(); i < n; i++) {
            ::google::protobuf::internal::WireFormatLite::WriteMessage(
                3, this->registered_objects(i), output);
        }

        output->WriteRaw(unknown_fields().data(),
            static_cast<int>(unknown_fields().size()));
        // @@protoc_insertion_point(serialize_end:ipc.invalidation.RegistrationManagerStateP)
    }

    int RegistrationManagerStateP::ByteSize() const
    {
        // @@protoc_insertion_point(message_byte_size_start:ipc.invalidation.RegistrationManagerStateP)
        int total_size = 0;

        if (_has_bits_[0 / 32] & 3u) {
            // optional .ipc.invalidation.RegistrationSummary client_summary = 1;
            if (has_client_summary()) {
                total_size += 1 + ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(*this->client_summary_);
            }

            // optional .ipc.invalidation.RegistrationSummary server_summary = 2;
            if (has_server_summary()) {
                total_size += 1 + ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(*this->server_summary_);
            }
        }
        // repeated .ipc.invalidation.ObjectIdP registered_objects = 3;
        total_size += 1 * this->registered_objects_size();
        for (int i = 0; i < this->registered_objects_size(); i++) {
            total_size += ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
                this->registered_objects(i));
        }

        total_size += unknown_fields().size();

        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _cached_size_ = total_size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
        return total_size;
    }

    void RegistrationManagerStateP::CheckTypeAndMergeFrom(
        const ::google::protobuf::MessageLite& from)
    {
        MergeFrom(*::google::protobuf::down_cast<const RegistrationManagerStateP*>(&from));
    }

    void RegistrationManagerStateP::MergeFrom(const RegistrationManagerStateP& from)
    {
        // @@protoc_insertion_point(class_specific_merge_from_start:ipc.invalidation.RegistrationManagerStateP)
        if (GOOGLE_PREDICT_FALSE(&from == this))
            MergeFromFail(__LINE__);
        registered_objects_.MergeFrom(from.registered_objects_);
        if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
            if (from.has_client_summary()) {
                mutable_client_summary()->::ipc::invalidation::RegistrationSummary::MergeFrom(from.client_summary());
            }
            if (from.has_server_summary()) {
                mutable_server_summary()->::ipc::invalidation::RegistrationSummary::MergeFrom(from.server_summary());
            }
        }
        if (!from.unknown_fields().empty()) {
            mutable_unknown_fields()->append(from.unknown_fields());
        }
    }

    void RegistrationManagerStateP::CopyFrom(const RegistrationManagerStateP& from)
    {
        // @@protoc_insertion_point(class_specific_copy_from_start:ipc.invalidation.RegistrationManagerStateP)
        if (&from == this)
            return;
        Clear();
        MergeFrom(from);
    }

    bool RegistrationManagerStateP::IsInitialized() const
    {

        return true;
    }

    void RegistrationManagerStateP::Swap(RegistrationManagerStateP* other)
    {
        if (other == this)
            return;
        InternalSwap(other);
    }
    void RegistrationManagerStateP::InternalSwap(RegistrationManagerStateP* other)
    {
        std::swap(client_summary_, other->client_summary_);
        std::swap(server_summary_, other->server_summary_);
        registered_objects_.UnsafeArenaSwap(&other->registered_objects_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }

    ::std::string RegistrationManagerStateP::GetTypeName() const
    {
        return "ipc.invalidation.RegistrationManagerStateP";
    }

#if PROTOBUF_INLINE_NOT_IN_HEADERS
    // RegistrationManagerStateP

    // optional .ipc.invalidation.RegistrationSummary client_summary = 1;
    bool RegistrationManagerStateP::has_client_summary() const
    {
        return (_has_bits_[0] & 0x00000001u) != 0;
    }
    void RegistrationManagerStateP::set_has_client_summary()
    {
        _has_bits_[0] |= 0x00000001u;
    }
    void RegistrationManagerStateP::clear_has_client_summary()
    {
        _has_bits_[0] &= ~0x00000001u;
    }
    void RegistrationManagerStateP::clear_client_summary()
    {
        if (client_summary_ != NULL)
            client_summary_->::ipc::invalidation::RegistrationSummary::Clear();
        clear_has_client_summary();
    }
    const ::ipc::invalidation::RegistrationSummary& RegistrationManagerStateP::client_summary() const
    {
        // @@protoc_insertion_point(field_get:ipc.invalidation.RegistrationManagerStateP.client_summary)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        return client_summary_ != NULL ? *client_summary_ : *default_instance().client_summary_;
#else
        return client_summary_ != NULL ? *client_summary_ : *default_instance_->client_summary_;
#endif
    }
    ::ipc::invalidation::RegistrationSummary* RegistrationManagerStateP::mutable_client_summary()
    {
        set_has_client_summary();
        if (client_summary_ == NULL) {
            client_summary_ = new ::ipc::invalidation::RegistrationSummary;
        }
        // @@protoc_insertion_point(field_mutable:ipc.invalidation.RegistrationManagerStateP.client_summary)
        return client_summary_;
    }
    ::ipc::invalidation::RegistrationSummary* RegistrationManagerStateP::release_client_summary()
    {
        // @@protoc_insertion_point(field_release:ipc.invalidation.RegistrationManagerStateP.client_summary)
        clear_has_client_summary();
        ::ipc::invalidation::RegistrationSummary* temp = client_summary_;
        client_summary_ = NULL;
        return temp;
    }
    void RegistrationManagerStateP::set_allocated_client_summary(::ipc::invalidation::RegistrationSummary* client_summary)
    {
        delete client_summary_;
        client_summary_ = client_summary;
        if (client_summary) {
            set_has_client_summary();
        } else {
            clear_has_client_summary();
        }
        // @@protoc_insertion_point(field_set_allocated:ipc.invalidation.RegistrationManagerStateP.client_summary)
    }

    // optional .ipc.invalidation.RegistrationSummary server_summary = 2;
    bool RegistrationManagerStateP::has_server_summary() const
    {
        return (_has_bits_[0] & 0x00000002u) != 0;
    }
    void RegistrationManagerStateP::set_has_server_summary()
    {
        _has_bits_[0] |= 0x00000002u;
    }
    void RegistrationManagerStateP::clear_has_server_summary()
    {
        _has_bits_[0] &= ~0x00000002u;
    }
    void RegistrationManagerStateP::clear_server_summary()
    {
        if (server_summary_ != NULL)
            server_summary_->::ipc::invalidation::RegistrationSummary::Clear();
        clear_has_server_summary();
    }
    const ::ipc::invalidation::RegistrationSummary& RegistrationManagerStateP::server_summary() const
    {
        // @@protoc_insertion_point(field_get:ipc.invalidation.RegistrationManagerStateP.server_summary)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        return server_summary_ != NULL ? *server_summary_ : *default_instance().server_summary_;
#else
        return server_summary_ != NULL ? *server_summary_ : *default_instance_->server_summary_;
#endif
    }
    ::ipc::invalidation::RegistrationSummary* RegistrationManagerStateP::mutable_server_summary()
    {
        set_has_server_summary();
        if (server_summary_ == NULL) {
            server_summary_ = new ::ipc::invalidation::RegistrationSummary;
        }
        // @@protoc_insertion_point(field_mutable:ipc.invalidation.RegistrationManagerStateP.server_summary)
        return server_summary_;
    }
    ::ipc::invalidation::RegistrationSummary* RegistrationManagerStateP::release_server_summary()
    {
        // @@protoc_insertion_point(field_release:ipc.invalidation.RegistrationManagerStateP.server_summary)
        clear_has_server_summary();
        ::ipc::invalidation::RegistrationSummary* temp = server_summary_;
        server_summary_ = NULL;
        return temp;
    }
    void RegistrationManagerStateP::set_allocated_server_summary(::ipc::invalidation::RegistrationSummary* server_summary)
    {
        delete server_summary_;
        server_summary_ = server_summary;
        if (server_summary) {
            set_has_server_summary();
        } else {
            clear_has_server_summary();
        }
        // @@protoc_insertion_point(field_set_allocated:ipc.invalidation.RegistrationManagerStateP.server_summary)
    }

    // repeated .ipc.invalidation.ObjectIdP registered_objects = 3;
    int RegistrationManagerStateP::registered_objects_size() const
    {
        return registered_objects_.size();
    }
    void RegistrationManagerStateP::clear_registered_objects()
    {
        registered_objects_.Clear();
    }
    const ::ipc::invalidation::ObjectIdP& RegistrationManagerStateP::registered_objects(int index) const
    {
        // @@protoc_insertion_point(field_get:ipc.invalidation.RegistrationManagerStateP.registered_objects)
        return registered_objects_.Get(index);
    }
    ::ipc::invalidation::ObjectIdP* RegistrationManagerStateP::mutable_registered_objects(int index)
    {
        // @@protoc_insertion_point(field_mutable:ipc.invalidation.RegistrationManagerStateP.registered_objects)
        return registered_objects_.Mutable(index);
    }
    ::ipc::invalidation::ObjectIdP* RegistrationManagerStateP::add_registered_objects()
    {
        // @@protoc_insertion_point(field_add:ipc.invalidation.RegistrationManagerStateP.registered_objects)
        return registered_objects_.Add();
    }
    ::google::protobuf::RepeatedPtrField<::ipc::invalidation::ObjectIdP>*
    RegistrationManagerStateP::mutable_registered_objects()
    {
        // @@protoc_insertion_point(field_mutable_list:ipc.invalidation.RegistrationManagerStateP.registered_objects)
        return &registered_objects_;
    }
    const ::google::protobuf::RepeatedPtrField<::ipc::invalidation::ObjectIdP>&
    RegistrationManagerStateP::registered_objects() const
    {
        // @@protoc_insertion_point(field_list:ipc.invalidation.RegistrationManagerStateP.registered_objects)
        return registered_objects_;
    }

#endif // PROTOBUF_INLINE_NOT_IN_HEADERS

    // @@protoc_insertion_point(namespace_scope)

} // namespace invalidation
} // namespace ipc

// @@protoc_insertion_point(global_scope)
