// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fzrpc.proto

#ifndef PROTOBUF_fzrpc_2eproto__INCLUDED
#define PROTOBUF_fzrpc_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
//#if 3002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
//#error This file was generated by an older version of protoc which is
//#error incompatible with your Protocol Buffer headers.  Please
//#error regenerate this file with a newer version of protoc.
//#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
class FzRequest;
class FzRequestDefaultTypeInternal;
extern FzRequestDefaultTypeInternal _FzRequest_default_instance_;
class FzResponse;
class FzResponseDefaultTypeInternal;
extern FzResponseDefaultTypeInternal _FzResponse_default_instance_;

namespace protobuf_fzrpc_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_fzrpc_2eproto

// ===================================================================

class FzRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:FzRequest) */ {
 public:
  FzRequest();
  virtual ~FzRequest();

  FzRequest(const FzRequest& from);

  inline FzRequest& operator=(const FzRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FzRequest& default_instance();

  static inline const FzRequest* internal_default_instance() {
    return reinterpret_cast<const FzRequest*>(
               &_FzRequest_default_instance_);
  }

  void Swap(FzRequest* other);

  // implements Message ----------------------------------------------

  inline FzRequest* New() const PROTOBUF_FINAL { return New(NULL); }

  FzRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const FzRequest& from);
  void MergeFrom(const FzRequest& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(FzRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string cmd = 2;
  void clear_cmd();
  static const int kCmdFieldNumber = 2;
  const ::std::string& cmd() const;
  void set_cmd(const ::std::string& value);
  #if LANG_CXX11
  void set_cmd(::std::string&& value);
  #endif
  void set_cmd(const char* value);
  void set_cmd(const char* value, size_t size);
  ::std::string* mutable_cmd();
  ::std::string* release_cmd();
  void set_allocated_cmd(::std::string* cmd);

  // uint32 jobID = 1;
  void clear_jobid();
  static const int kJobIDFieldNumber = 1;
  ::google::protobuf::uint32 jobid() const;
  void set_jobid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:FzRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr cmd_;
  ::google::protobuf::uint32 jobid_;
  mutable int _cached_size_;
  friend struct  protobuf_fzrpc_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class FzResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:FzResponse) */ {
 public:
  FzResponse();
  virtual ~FzResponse();

  FzResponse(const FzResponse& from);

  inline FzResponse& operator=(const FzResponse& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FzResponse& default_instance();

  static inline const FzResponse* internal_default_instance() {
    return reinterpret_cast<const FzResponse*>(
               &_FzResponse_default_instance_);
  }

  void Swap(FzResponse* other);

  // implements Message ----------------------------------------------

  inline FzResponse* New() const PROTOBUF_FINAL { return New(NULL); }

  FzResponse* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const FzResponse& from);
  void MergeFrom(const FzResponse& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(FzResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string ret = 3;
  void clear_ret();
  static const int kRetFieldNumber = 3;
  const ::std::string& ret() const;
  void set_ret(const ::std::string& value);
  #if LANG_CXX11
  void set_ret(::std::string&& value);
  #endif
  void set_ret(const char* value);
  void set_ret(const char* value, size_t size);
  ::std::string* mutable_ret();
  ::std::string* release_ret();
  void set_allocated_ret(::std::string* ret);

  // string cmd = 4;
  void clear_cmd();
  static const int kCmdFieldNumber = 4;
  const ::std::string& cmd() const;
  void set_cmd(const ::std::string& value);
  #if LANG_CXX11
  void set_cmd(::std::string&& value);
  #endif
  void set_cmd(const char* value);
  void set_cmd(const char* value, size_t size);
  ::std::string* mutable_cmd();
  ::std::string* release_cmd();
  void set_allocated_cmd(::std::string* cmd);

  // uint32 jobID = 1;
  void clear_jobid();
  static const int kJobIDFieldNumber = 1;
  ::google::protobuf::uint32 jobid() const;
  void set_jobid(::google::protobuf::uint32 value);

  // bool flag = 2;
  void clear_flag();
  static const int kFlagFieldNumber = 2;
  bool flag() const;
  void set_flag(bool value);

  // @@protoc_insertion_point(class_scope:FzResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr ret_;
  ::google::protobuf::internal::ArenaStringPtr cmd_;
  ::google::protobuf::uint32 jobid_;
  bool flag_;
  mutable int _cached_size_;
  friend struct  protobuf_fzrpc_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// FzRequest

// uint32 jobID = 1;
inline void FzRequest::clear_jobid() {
  jobid_ = 0u;
}
inline ::google::protobuf::uint32 FzRequest::jobid() const {
  // @@protoc_insertion_point(field_get:FzRequest.jobID)
  return jobid_;
}
inline void FzRequest::set_jobid(::google::protobuf::uint32 value) {
  
  jobid_ = value;
  // @@protoc_insertion_point(field_set:FzRequest.jobID)
}

// string cmd = 2;
inline void FzRequest::clear_cmd() {
  cmd_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FzRequest::cmd() const {
  // @@protoc_insertion_point(field_get:FzRequest.cmd)
  return cmd_.GetNoArena();
}
inline void FzRequest::set_cmd(const ::std::string& value) {
  
  cmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:FzRequest.cmd)
}
#if LANG_CXX11
inline void FzRequest::set_cmd(::std::string&& value) {
  
  cmd_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:FzRequest.cmd)
}
#endif
inline void FzRequest::set_cmd(const char* value) {
  
  cmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:FzRequest.cmd)
}
inline void FzRequest::set_cmd(const char* value, size_t size) {
  
  cmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:FzRequest.cmd)
}
inline ::std::string* FzRequest::mutable_cmd() {
  
  // @@protoc_insertion_point(field_mutable:FzRequest.cmd)
  return cmd_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FzRequest::release_cmd() {
  // @@protoc_insertion_point(field_release:FzRequest.cmd)
  
  return cmd_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FzRequest::set_allocated_cmd(::std::string* cmd) {
  if (cmd != NULL) {
    
  } else {
    
  }
  cmd_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), cmd);
  // @@protoc_insertion_point(field_set_allocated:FzRequest.cmd)
}

// -------------------------------------------------------------------

// FzResponse

// uint32 jobID = 1;
inline void FzResponse::clear_jobid() {
  jobid_ = 0u;
}
inline ::google::protobuf::uint32 FzResponse::jobid() const {
  // @@protoc_insertion_point(field_get:FzResponse.jobID)
  return jobid_;
}
inline void FzResponse::set_jobid(::google::protobuf::uint32 value) {
  
  jobid_ = value;
  // @@protoc_insertion_point(field_set:FzResponse.jobID)
}

// bool flag = 2;
inline void FzResponse::clear_flag() {
  flag_ = false;
}
inline bool FzResponse::flag() const {
  // @@protoc_insertion_point(field_get:FzResponse.flag)
  return flag_;
}
inline void FzResponse::set_flag(bool value) {
  
  flag_ = value;
  // @@protoc_insertion_point(field_set:FzResponse.flag)
}

// string ret = 3;
inline void FzResponse::clear_ret() {
  ret_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FzResponse::ret() const {
  // @@protoc_insertion_point(field_get:FzResponse.ret)
  return ret_.GetNoArena();
}
inline void FzResponse::set_ret(const ::std::string& value) {
  
  ret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:FzResponse.ret)
}
#if LANG_CXX11
inline void FzResponse::set_ret(::std::string&& value) {
  
  ret_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:FzResponse.ret)
}
#endif
inline void FzResponse::set_ret(const char* value) {
  
  ret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:FzResponse.ret)
}
inline void FzResponse::set_ret(const char* value, size_t size) {
  
  ret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:FzResponse.ret)
}
inline ::std::string* FzResponse::mutable_ret() {
  
  // @@protoc_insertion_point(field_mutable:FzResponse.ret)
  return ret_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FzResponse::release_ret() {
  // @@protoc_insertion_point(field_release:FzResponse.ret)
  
  return ret_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FzResponse::set_allocated_ret(::std::string* ret) {
  if (ret != NULL) {
    
  } else {
    
  }
  ret_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ret);
  // @@protoc_insertion_point(field_set_allocated:FzResponse.ret)
}

// string cmd = 4;
inline void FzResponse::clear_cmd() {
  cmd_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& FzResponse::cmd() const {
  // @@protoc_insertion_point(field_get:FzResponse.cmd)
  return cmd_.GetNoArena();
}
inline void FzResponse::set_cmd(const ::std::string& value) {
  
  cmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:FzResponse.cmd)
}
#if LANG_CXX11
inline void FzResponse::set_cmd(::std::string&& value) {
  
  cmd_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:FzResponse.cmd)
}
#endif
inline void FzResponse::set_cmd(const char* value) {
  
  cmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:FzResponse.cmd)
}
inline void FzResponse::set_cmd(const char* value, size_t size) {
  
  cmd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:FzResponse.cmd)
}
inline ::std::string* FzResponse::mutable_cmd() {
  
  // @@protoc_insertion_point(field_mutable:FzResponse.cmd)
  return cmd_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FzResponse::release_cmd() {
  // @@protoc_insertion_point(field_release:FzResponse.cmd)
  
  return cmd_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FzResponse::set_allocated_cmd(::std::string* cmd) {
  if (cmd != NULL) {
    
  } else {
    
  }
  cmd_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), cmd);
  // @@protoc_insertion_point(field_set_allocated:FzResponse.cmd)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_fzrpc_2eproto__INCLUDED
