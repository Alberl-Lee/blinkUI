// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: point3f.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "point3f.pb.h"

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

    void protobuf_ShutdownFile_point3f_2eproto()
    {
        delete Point3F::default_instance_;
    }

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    void protobuf_AddDesc_point3f_2eproto_impl()
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
    void protobuf_AddDesc_point3f_2eproto()
    {
        static bool already_here = false;
        if (already_here)
            return;
        already_here = true;
        GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
        Point3F::default_instance_ = new Point3F();
        Point3F::default_instance_->InitAsDefaultInstance();
        ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_point3f_2eproto);
    }

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_point3f_2eproto_once_);
    void protobuf_AddDesc_point3f_2eproto()
    {
        ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_point3f_2eproto_once_,
            &protobuf_AddDesc_point3f_2eproto_impl);
    }
#else
    // Force AddDescriptors() to be called at static initialization time.
    struct StaticDescriptorInitializer_point3f_2eproto {
        StaticDescriptorInitializer_point3f_2eproto()
        {
            protobuf_AddDesc_point3f_2eproto();
        }
    } static_descriptor_initializer_point3f_2eproto_;
#endif

    namespace {

        static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
        GOOGLE_ATTRIBUTE_NOINLINE static void MergeFromFail(int line)
        {
            GOOGLE_CHECK(false) << __FILE__ << ":" << line;
        }

    } // namespace

    // ===================================================================

    static ::std::string* MutableUnknownFieldsForPoint3F(
        Point3F* ptr)
    {
        return ptr->mutable_unknown_fields();
    }

#if !defined(_MSC_VER) || _MSC_VER >= 1900
    const int Point3F::kXFieldNumber;
    const int Point3F::kYFieldNumber;
    const int Point3F::kZFieldNumber;
#endif // !defined(_MSC_VER) || _MSC_VER >= 1900

    Point3F::Point3F()
        : ::google::protobuf::MessageLite()
        , _arena_ptr_(NULL)
    {
        SharedCtor();
        // @@protoc_insertion_point(constructor:cc.proto.Point3F)
    }

    void Point3F::InitAsDefaultInstance()
    {
    }

    Point3F::Point3F(const Point3F& from)
        : ::google::protobuf::MessageLite()
        , _arena_ptr_(NULL)
    {
        SharedCtor();
        MergeFrom(from);
        // @@protoc_insertion_point(copy_constructor:cc.proto.Point3F)
    }

    void Point3F::SharedCtor()
    {
        ::google::protobuf::internal::GetEmptyString();
        _cached_size_ = 0;
        _unknown_fields_.UnsafeSetDefault(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
        x_ = 0;
        y_ = 0;
        z_ = 0;
        ::memset(_has_bits_, 0, sizeof(_has_bits_));
    }

    Point3F::~Point3F()
    {
        // @@protoc_insertion_point(destructor:cc.proto.Point3F)
        SharedDtor();
    }

    void Point3F::SharedDtor()
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

    void Point3F::SetCachedSize(int size) const
    {
        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _cached_size_ = size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
    }
    const Point3F& Point3F::default_instance()
    {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        protobuf_AddDesc_point3f_2eproto();
#else
        if (default_instance_ == NULL)
            protobuf_AddDesc_point3f_2eproto();
#endif
        return *default_instance_;
    }

    Point3F* Point3F::default_instance_ = NULL;

    Point3F* Point3F::New(::google::protobuf::Arena* arena) const
    {
        Point3F* n = new Point3F;
        if (arena != NULL) {
            arena->Own(n);
        }
        return n;
    }

    void Point3F::Clear()
    {
// @@protoc_insertion_point(message_clear_start:cc.proto.Point3F)
#if defined(__clang__)
#define ZR_HELPER_(f)                                                                             \
    _Pragma("clang diagnostic push")                                                              \
        _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") __builtin_offsetof(Point3F, f) \
            _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>( \
    &reinterpret_cast<Point3F*>(16)->f)
#endif

#define ZR_(first, last)                                          \
    do {                                                          \
        ::memset(&first, 0,                                       \
            ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last)); \
    } while (0)

        ZR_(x_, z_);

#undef ZR_HELPER_
#undef ZR_

        ::memset(_has_bits_, 0, sizeof(_has_bits_));
        _unknown_fields_.ClearToEmptyNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }

    bool Point3F::MergePartialFromCodedStream(
        ::google::protobuf::io::CodedInputStream* input)
    {
#define DO_(EXPRESSION)                   \
    if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) \
    goto failure
        ::google::protobuf::uint32 tag;
        ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
            ::google::protobuf::internal::NewPermanentCallback(
                &MutableUnknownFieldsForPoint3F, this));
        ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
            &unknown_fields_string, false);
        // @@protoc_insertion_point(parse_start:cc.proto.Point3F)
        for (;;) {
            ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
            tag = p.first;
            if (!p.second)
                goto handle_unusual;
            switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
            // optional float x = 1;
            case 1: {
                if (tag == 13) {
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                        float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                        input, &x_)));
                    set_has_x();
                } else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(21))
                    goto parse_y;
                break;
            }

            // optional float y = 2;
            case 2: {
                if (tag == 21) {
                parse_y:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                        float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                        input, &y_)));
                    set_has_y();
                } else {
                    goto handle_unusual;
                }
                if (input->ExpectTag(29))
                    goto parse_z;
                break;
            }

            // optional float z = 3;
            case 3: {
                if (tag == 29) {
                parse_z:
                    DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                        float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                        input, &z_)));
                    set_has_z();
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
        // @@protoc_insertion_point(parse_success:cc.proto.Point3F)
        return true;
    failure:
        // @@protoc_insertion_point(parse_failure:cc.proto.Point3F)
        return false;
#undef DO_
    }

    void Point3F::SerializeWithCachedSizes(
        ::google::protobuf::io::CodedOutputStream* output) const
    {
        // @@protoc_insertion_point(serialize_start:cc.proto.Point3F)
        // optional float x = 1;
        if (has_x()) {
            ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->x(), output);
        }

        // optional float y = 2;
        if (has_y()) {
            ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->y(), output);
        }

        // optional float z = 3;
        if (has_z()) {
            ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->z(), output);
        }

        output->WriteRaw(unknown_fields().data(),
            static_cast<int>(unknown_fields().size()));
        // @@protoc_insertion_point(serialize_end:cc.proto.Point3F)
    }

    int Point3F::ByteSize() const
    {
        // @@protoc_insertion_point(message_byte_size_start:cc.proto.Point3F)
        int total_size = 0;

        if (_has_bits_[0 / 32] & 7u) {
            // optional float x = 1;
            if (has_x()) {
                total_size += 1 + 4;
            }

            // optional float y = 2;
            if (has_y()) {
                total_size += 1 + 4;
            }

            // optional float z = 3;
            if (has_z()) {
                total_size += 1 + 4;
            }
        }
        total_size += unknown_fields().size();

        GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
        _cached_size_ = total_size;
        GOOGLE_SAFE_CONCURRENT_WRITES_END();
        return total_size;
    }

    void Point3F::CheckTypeAndMergeFrom(
        const ::google::protobuf::MessageLite& from)
    {
        MergeFrom(*::google::protobuf::down_cast<const Point3F*>(&from));
    }

    void Point3F::MergeFrom(const Point3F& from)
    {
        // @@protoc_insertion_point(class_specific_merge_from_start:cc.proto.Point3F)
        if (GOOGLE_PREDICT_FALSE(&from == this))
            MergeFromFail(__LINE__);
        if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
            if (from.has_x()) {
                set_x(from.x());
            }
            if (from.has_y()) {
                set_y(from.y());
            }
            if (from.has_z()) {
                set_z(from.z());
            }
        }
        if (!from.unknown_fields().empty()) {
            mutable_unknown_fields()->append(from.unknown_fields());
        }
    }

    void Point3F::CopyFrom(const Point3F& from)
    {
        // @@protoc_insertion_point(class_specific_copy_from_start:cc.proto.Point3F)
        if (&from == this)
            return;
        Clear();
        MergeFrom(from);
    }

    bool Point3F::IsInitialized() const
    {

        return true;
    }

    void Point3F::Swap(Point3F* other)
    {
        if (other == this)
            return;
        InternalSwap(other);
    }
    void Point3F::InternalSwap(Point3F* other)
    {
        std::swap(x_, other->x_);
        std::swap(y_, other->y_);
        std::swap(z_, other->z_);
        std::swap(_has_bits_[0], other->_has_bits_[0]);
        _unknown_fields_.Swap(&other->_unknown_fields_);
        std::swap(_cached_size_, other->_cached_size_);
    }

    ::std::string Point3F::GetTypeName() const
    {
        return "cc.proto.Point3F";
    }

#if PROTOBUF_INLINE_NOT_IN_HEADERS
    // Point3F

    // optional float x = 1;
    bool Point3F::has_x() const
    {
        return (_has_bits_[0] & 0x00000001u) != 0;
    }
    void Point3F::set_has_x()
    {
        _has_bits_[0] |= 0x00000001u;
    }
    void Point3F::clear_has_x()
    {
        _has_bits_[0] &= ~0x00000001u;
    }
    void Point3F::clear_x()
    {
        x_ = 0;
        clear_has_x();
    }
    float Point3F::x() const
    {
        // @@protoc_insertion_point(field_get:cc.proto.Point3F.x)
        return x_;
    }
    void Point3F::set_x(float value)
    {
        set_has_x();
        x_ = value;
        // @@protoc_insertion_point(field_set:cc.proto.Point3F.x)
    }

    // optional float y = 2;
    bool Point3F::has_y() const
    {
        return (_has_bits_[0] & 0x00000002u) != 0;
    }
    void Point3F::set_has_y()
    {
        _has_bits_[0] |= 0x00000002u;
    }
    void Point3F::clear_has_y()
    {
        _has_bits_[0] &= ~0x00000002u;
    }
    void Point3F::clear_y()
    {
        y_ = 0;
        clear_has_y();
    }
    float Point3F::y() const
    {
        // @@protoc_insertion_point(field_get:cc.proto.Point3F.y)
        return y_;
    }
    void Point3F::set_y(float value)
    {
        set_has_y();
        y_ = value;
        // @@protoc_insertion_point(field_set:cc.proto.Point3F.y)
    }

    // optional float z = 3;
    bool Point3F::has_z() const
    {
        return (_has_bits_[0] & 0x00000004u) != 0;
    }
    void Point3F::set_has_z()
    {
        _has_bits_[0] |= 0x00000004u;
    }
    void Point3F::clear_has_z()
    {
        _has_bits_[0] &= ~0x00000004u;
    }
    void Point3F::clear_z()
    {
        z_ = 0;
        clear_has_z();
    }
    float Point3F::z() const
    {
        // @@protoc_insertion_point(field_get:cc.proto.Point3F.z)
        return z_;
    }
    void Point3F::set_z(float value)
    {
        set_has_z();
        z_ = value;
        // @@protoc_insertion_point(field_set:cc.proto.Point3F.z)
    }

#endif // PROTOBUF_INLINE_NOT_IN_HEADERS

    // @@protoc_insertion_point(namespace_scope)

} // namespace proto
} // namespace cc

// @@protoc_insertion_point(global_scope)
