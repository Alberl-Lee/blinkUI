// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: dictionary_specifics.proto

#ifndef PROTOBUF_dictionary_5fspecifics_2eproto__INCLUDED
#define PROTOBUF_dictionary_5fspecifics_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
// @@protoc_insertion_point(includes)

namespace sync_pb {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_dictionary_5fspecifics_2eproto();
void protobuf_AssignDesc_dictionary_5fspecifics_2eproto();
void protobuf_ShutdownFile_dictionary_5fspecifics_2eproto();

class DictionarySpecifics;

// ===================================================================

class DictionarySpecifics : public ::google::protobuf::MessageLite {
public:
    DictionarySpecifics();
    virtual ~DictionarySpecifics();

    DictionarySpecifics(const DictionarySpecifics& from);

    inline DictionarySpecifics& operator=(const DictionarySpecifics& from)
    {
        CopyFrom(from);
        return *this;
    }

    inline const ::std::string& unknown_fields() const
    {
        return _unknown_fields_.GetNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }

    inline ::std::string* mutable_unknown_fields()
    {
        return _unknown_fields_.MutableNoArena(
            &::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }

    static const DictionarySpecifics& default_instance();

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    // Returns the internal default instance pointer. This function can
    // return NULL thus should not be used by the user. This is intended
    // for Protobuf internal code. Please use default_instance() declared
    // above instead.
    static inline const DictionarySpecifics* internal_default_instance()
    {
        return default_instance_;
    }
#endif

    GOOGLE_ATTRIBUTE_NOINLINE void Swap(DictionarySpecifics* other);

    // implements Message ----------------------------------------------

    inline DictionarySpecifics* New() const { return New(NULL); }

    DictionarySpecifics* New(::google::protobuf::Arena* arena) const;
    void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
    void CopyFrom(const DictionarySpecifics& from);
    void MergeFrom(const DictionarySpecifics& from);
    void Clear();
    bool IsInitialized() const;

    int ByteSize() const;
    bool MergePartialFromCodedStream(
        ::google::protobuf::io::CodedInputStream* input);
    void SerializeWithCachedSizes(
        ::google::protobuf::io::CodedOutputStream* output) const;
    void DiscardUnknownFields();
    int GetCachedSize() const { return _cached_size_; }

private:
    void SharedCtor();
    void SharedDtor();
    void SetCachedSize(int size) const;
    void InternalSwap(DictionarySpecifics* other);

private:
    inline ::google::protobuf::Arena* GetArenaNoVirtual() const
    {
        return _arena_ptr_;
    }
    inline ::google::protobuf::Arena* MaybeArenaPtr() const
    {
        return _arena_ptr_;
    }

public:
    ::std::string GetTypeName() const;

    // nested types ----------------------------------------------------

    // accessors -------------------------------------------------------

    // optional string word = 1;
    bool has_word() const;
    void clear_word();
    static const int kWordFieldNumber = 1;
    const ::std::string& word() const;
    void set_word(const ::std::string& value);
    void set_word(const char* value);
    void set_word(const char* value, size_t size);
    ::std::string* mutable_word();
    ::std::string* release_word();
    void set_allocated_word(::std::string* word);

    // @@protoc_insertion_point(class_scope:sync_pb.DictionarySpecifics)
private:
    inline void set_has_word();
    inline void clear_has_word();

    ::google::protobuf::internal::ArenaStringPtr _unknown_fields_;
    ::google::protobuf::Arena* _arena_ptr_;

    ::google::protobuf::uint32 _has_bits_[1];
    mutable int _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr word_;
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
    friend void protobuf_AddDesc_dictionary_5fspecifics_2eproto_impl();
#else
    friend void protobuf_AddDesc_dictionary_5fspecifics_2eproto();
#endif
    friend void protobuf_AssignDesc_dictionary_5fspecifics_2eproto();
    friend void protobuf_ShutdownFile_dictionary_5fspecifics_2eproto();

    void InitAsDefaultInstance();
    static DictionarySpecifics* default_instance_;
};
// ===================================================================

// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// DictionarySpecifics

// optional string word = 1;
inline bool DictionarySpecifics::has_word() const
{
    return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DictionarySpecifics::set_has_word()
{
    _has_bits_[0] |= 0x00000001u;
}
inline void DictionarySpecifics::clear_has_word()
{
    _has_bits_[0] &= ~0x00000001u;
}
inline void DictionarySpecifics::clear_word()
{
    word_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    clear_has_word();
}
inline const ::std::string& DictionarySpecifics::word() const
{
    // @@protoc_insertion_point(field_get:sync_pb.DictionarySpecifics.word)
    return word_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DictionarySpecifics::set_word(const ::std::string& value)
{
    set_has_word();
    word_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
    // @@protoc_insertion_point(field_set:sync_pb.DictionarySpecifics.word)
}
inline void DictionarySpecifics::set_word(const char* value)
{
    set_has_word();
    word_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
    // @@protoc_insertion_point(field_set_char:sync_pb.DictionarySpecifics.word)
}
inline void DictionarySpecifics::set_word(const char* value, size_t size)
{
    set_has_word();
    word_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
        ::std::string(reinterpret_cast<const char*>(value), size));
    // @@protoc_insertion_point(field_set_pointer:sync_pb.DictionarySpecifics.word)
}
inline ::std::string* DictionarySpecifics::mutable_word()
{
    set_has_word();
    // @@protoc_insertion_point(field_mutable:sync_pb.DictionarySpecifics.word)
    return word_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DictionarySpecifics::release_word()
{
    // @@protoc_insertion_point(field_release:sync_pb.DictionarySpecifics.word)
    clear_has_word();
    return word_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DictionarySpecifics::set_allocated_word(::std::string* word)
{
    if (word != NULL) {
        set_has_word();
    } else {
        clear_has_word();
    }
    word_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), word);
    // @@protoc_insertion_point(field_set_allocated:sync_pb.DictionarySpecifics.word)
}

#endif // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

} // namespace sync_pb

// @@protoc_insertion_point(global_scope)

#endif // PROTOBUF_dictionary_5fspecifics_2eproto__INCLUDED
