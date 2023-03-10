// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rectf.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rectf.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace cc {
namespace proto {

    void protobuf_ShutdownFile_rectf_2eproto()
    {
        delete RectF::default_instance_;
    }

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    void protobuf_AddDesc_rectf_2eproto_impl()
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
    void protobuf_AddDesc_rectf_2eproto()
    {
        static bool already_here = false;
        if (already_here)
            return;
        already_here = true;
        GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
        ::cc::proto::protobuf_AddDesc_pointf_2eproto();
        ::cc::proto::protobuf_AddDesc_sizef_2eproto();
        RectF::default_instance_ = new RectF();
        RectF::default_instance_->InitAsDefaultInstance();
        ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_rectf_2eproto);
    }

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_rectf_2eproto_once_);
    void protobuf_AddDesc_rectf_2eproto()
    {
        ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_rectf_2eproto_once_,
            &protobuf_AddDesc_rectf_2eproto_impl);
    }
#else
    // Force AddDescriptors() to be called at static initialization time.
    struct StaticDescriptorInitializer_rectf_2eproto {
        StaticDescriptorInitializer_rectf_2eproto()
        {
            protobuf_AddDesc_rectf_2eproto();
        }
    } static_descriptor_initializer_rectf_2eproto_;
#endif

    namespace {

        static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
        GOOGLE_ATTRIBUTE_NOINLINE static void MergeFromFail(int line)
        {
            GOOGLE_CHECK(false) << __FILE__ << ":" << line;
        }

    } // namespace

    // ===================================================================

    static ::std::string* MutableUnknownFieldsForRectF(
        RectF* ptr)
    {
        return ptr->mutable_unknown_fields();
    }

#if !defined(_MSC_VER) || _MSC_VER >= 1900
    const int RectF::kOriginFieldNumber;
    const int RectF::kSizeFieldNumber;
#endif // !defined(_MSC_VER) || _MSC_VER >= 1900

    RectF::RectF()
        : ::google::protobuf::MessageLite()
        , _arena_ptr_(NULL)
    {
        SharedCtor();
        // @@protoc_insertion_point(constructor:cc.proto.RectF)
    }

    void RectF::InitAsDefaultInstance()
    {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        origin_ = const_cast<::cc::proto::PointF*>(
            ::cc::proto::PointF::internal_default_instance());
#else
        origin_ = const_cast<::cc::proto::PointF*>(&::cc::proto::PointF::default_instance());
#endif
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        size_ = const_cast<::cc::proto::SizeF*>(
            ::cc::proto::SizeF::internal_default_instance());
#else
        size_ = const_cast<::cc::proto::SizeF*>(&::cc::proto::SizeF::default_instance());
#endif
    }

    RectF::RectF(const RectF& from)
        : ::google::protobuf::MessageLite()
        , _arena_ptr_(NULL)
    {
        SharedCtor();
        MergeFrom(from);
        // @@protoc_insertion_point(copy_constructor:cc.proto.RectF)
    }

    void RectF::SharedCtor()
    {
        ::google::protobuf::internal::GetEmptyString();
        _cached_size_ = 0;
        _unknown_fields_.UnsafeSetDefault(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
        origin_ = NULL;
        size_ = NULL;
        ::memset(_has_bits_, 0, sizeof(_has_bits_));
    }

    RectF::~RectF()
    {
        // @@protoc_insertion_point(destructor:cc.proto.RectF)
        SharedDtor();
    }

    void RectF::SharedDtor()
    {
        _unknown_fields_.DestroyNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        if (this != &default_instance()) {
#else
        if (this != default_instance_) {
#endif
            delete origin_;
            delete size_;
        }
    }

    void RectF::SetCachedSize(int size) const
    {
        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _cached_size_ = size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
    }
    const RectF& RectF::default_instance()
    {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        protobuf_AddDesc_rectf_2eproto();
#else
        if (default_instance_ == NULL)
            protobuf_AddDesc_rectf_2eproto();
#endif
        return *default_instance_;
    }

    RectF* RectF::default_instance_ = NULL;

    RectF* RectF::New(::google::protobuf::Arena* arena) const
    {
        RectF* n = new RectF;
        if (arena != NULL) {
            arena->Own(n);
        }
        return n;
    }

    void RectF::Clear()
    {
        // @@protoc_insertion_point(message_clear_start:cc.proto.RectF)
        if (_has_bits_[0 / 32] & 3u) {
            if (has_origin()) {
                if (origin_ != NULL)
                    origin_->::cc::proto::PointF::Clear();
            }
            if (has_size()) {
                if (size_ != NULL)
                    size_->::cc::proto::SizeF::Clear();
            }
        }
        ::memset(_has_bits_, 0, sizeof(_has_bits_));
        _unknown_fields_.ClearToEmptyNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }

    bool RectF::MergePartialFromCodedStream(
        ::google::protobuf::io::CodedInputStream* input)
    {
#define DO_(EXPRESSION)                   \
    if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) \
    goto failure
        ::google::protobuf::uint32 tag;
        ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
            ::google::protobuf::internal::NewPermanentCallback(
                &MutableUnknownFieldsForRectF, this));
        ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
            &unknown_fields_string, false);
        // @@protoc_insertion_point(parse_start:cc.proto.RectF)
        for (;;) {
            ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
            tag = p.first;
            if (!p.second)
                goto handle_unusual;
            switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional .cc.proto.PointF origin = 1;
            case 1: {
                if (tag == 10) {
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                        input, mutable_origin()));
                } else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(18))
                    goto parse_size;
                break;
            }

            // optional .cc.proto.SizeF size = 2;
            case 2: {
                if (tag == 18) {
                parse_size:
                    DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                        input, mutable_size()));
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
        // @@protoc_insertion_point(parse_success:cc.proto.RectF)
        return true;
    failure:
        // @@protoc_insertion_point(parse_failure:cc.proto.RectF)
        return false;
#undef DO_
    }

    void RectF::SerializeWithCachedSizes(
        ::google::protobuf::io::CodedOutputStream* output) const
    {
        // @@protoc_insertion_point(serialize_start:cc.proto.RectF)
        // optional .cc.proto.PointF origin = 1;
        if (has_origin()) {
            ::google::protobuf::internal::WireFormatLite::WriteMessage(
                1, *this->origin_, output);
        }

        // optional .cc.proto.SizeF size = 2;
        if (has_size()) {
            ::google::protobuf::internal::WireFormatLite::WriteMessage(
                2, *this->size_, output);
        }

        output->WriteRaw(unknown_fields().data(),
            static_cast<int>(unknown_fields().size()));
        // @@protoc_insertion_point(serialize_end:cc.proto.RectF)
    }

    int RectF::ByteSize() const
    {
        // @@protoc_insertion_point(message_byte_size_start:cc.proto.RectF)
        int total_size = 0;

        if (_has_bits_[0 / 32] & 3u) {
            // optional .cc.proto.PointF origin = 1;
            if (has_origin()) {
                total_size += 1 + ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(*this->origin_);
            }

            // optional .cc.proto.SizeF size = 2;
            if (has_size()) {
                total_size += 1 + ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(*this->size_);
            }
        }
        total_size += unknown_fields().size();

        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _cached_size_ = total_size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
        return total_size;
    }

    void RectF::CheckTypeAndMergeFrom(
        const ::google::protobuf::MessageLite& from)
    {
        MergeFrom(*::google::protobuf::down_cast<const RectF*>(&from));
    }

    void RectF::MergeFrom(const RectF& from)
    {
        // @@protoc_insertion_point(class_specific_merge_from_start:cc.proto.RectF)
        if (GOOGLE_PREDICT_FALSE(&from == this))
            MergeFromFail(__LINE__);
        if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
            if (from.has_origin()) {
                mutable_origin()->::cc::proto::PointF::MergeFrom(from.origin());
            }
            if (from.has_size()) {
                mutable_size()->::cc::proto::SizeF::MergeFrom(from.size());
            }
        }
        if (!from.unknown_fields().empty()) {
            mutable_unknown_fields()->append(from.unknown_fields());
        }
    }

    void RectF::CopyFrom(const RectF& from)
    {
        // @@protoc_insertion_point(class_specific_copy_from_start:cc.proto.RectF)
        if (&from == this)
            return;
        Clear();
        MergeFrom(from);
    }

    bool RectF::IsInitialized() const
    {

        return true;
    }

    void RectF::Swap(RectF* other)
    {
        if (other == this)
            return;
        InternalSwap(other);
    }
    void RectF::InternalSwap(RectF* other)
    {
        std::swap(origin_, other->origin_);
        std::swap(size_, other->size_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }

    ::std::string RectF::GetTypeName() const
    {
        return "cc.proto.RectF";
    }

#if PROTOBUF_INLINE_NOT_IN_HEADERS
    // RectF

    // optional .cc.proto.PointF origin = 1;
    bool RectF::has_origin() const
    {
        return (_has_bits_[0] & 0x00000001u) != 0;
    }
    void RectF::set_has_origin()
    {
        _has_bits_[0] |= 0x00000001u;
    }
    void RectF::clear_has_origin()
    {
        _has_bits_[0] &= ~0x00000001u;
    }
    void RectF::clear_origin()
    {
        if (origin_ != NULL)
            origin_->::cc::proto::PointF::Clear();
        clear_has_origin();
    }
    const ::cc::proto::PointF& RectF::origin() const
    {
        // @@protoc_insertion_point(field_get:cc.proto.RectF.origin)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        return origin_ != NULL ? *origin_ : *default_instance().origin_;
#else
        return origin_ != NULL ? *origin_ : *default_instance_->origin_;
#endif
    }
    ::cc::proto::PointF* RectF::mutable_origin()
    {
        set_has_origin();
        if (origin_ == NULL) {
            origin_ = new ::cc::proto::PointF;
        }
        // @@protoc_insertion_point(field_mutable:cc.proto.RectF.origin)
        return origin_;
    }
    ::cc::proto::PointF* RectF::release_origin()
    {
        // @@protoc_insertion_point(field_release:cc.proto.RectF.origin)
        clear_has_origin();
        ::cc::proto::PointF* temp = origin_;
        origin_ = NULL;
        return temp;
    }
    void RectF::set_allocated_origin(::cc::proto::PointF* origin)
    {
        delete origin_;
        origin_ = origin;
        if (origin) {
            set_has_origin();
        } else {
            clear_has_origin();
        }
        // @@protoc_insertion_point(field_set_allocated:cc.proto.RectF.origin)
    }

    // optional .cc.proto.SizeF size = 2;
    bool RectF::has_size() const
    {
        return (_has_bits_[0] & 0x00000002u) != 0;
    }
    void RectF::set_has_size()
    {
        _has_bits_[0] |= 0x00000002u;
    }
    void RectF::clear_has_size()
    {
        _has_bits_[0] &= ~0x00000002u;
    }
    void RectF::clear_size()
    {
        if (size_ != NULL)
            size_->::cc::proto::SizeF::Clear();
        clear_has_size();
    }
    const ::cc::proto::SizeF& RectF::size() const
    {
        // @@protoc_insertion_point(field_get:cc.proto.RectF.size)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        return size_ != NULL ? *size_ : *default_instance().size_;
#else
        return size_ != NULL ? *size_ : *default_instance_->size_;
#endif
    }
    ::cc::proto::SizeF* RectF::mutable_size()
    {
        set_has_size();
        if (size_ == NULL) {
            size_ = new ::cc::proto::SizeF;
        }
        // @@protoc_insertion_point(field_mutable:cc.proto.RectF.size)
        return size_;
    }
    ::cc::proto::SizeF* RectF::release_size()
    {
        // @@protoc_insertion_point(field_release:cc.proto.RectF.size)
        clear_has_size();
        ::cc::proto::SizeF* temp = size_;
        size_ = NULL;
        return temp;
    }
    void RectF::set_allocated_size(::cc::proto::SizeF* size)
    {
        delete size_;
        size_ = size;
        if (size) {
            set_has_size();
        } else {
            clear_has_size();
        }
        // @@protoc_insertion_point(field_set_allocated:cc.proto.RectF.size)
    }

#endif // PROTOBUF_INLINE_NOT_IN_HEADERS

    // @@protoc_insertion_point(namespace_scope)

} // namespace proto
} // namespace cc

// @@protoc_insertion_point(global_scope)
