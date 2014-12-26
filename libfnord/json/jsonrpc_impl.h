/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "fnord/json/jsonrpcrequest.h"
#include "fnord/json/jsonrpcresponse.h"

namespace fnord {
namespace json {

template <class ServiceType>
void JSONRPC::registerService(
    const std::string& service_name,
    ServiceType* service) {
  JSONRPC::ReflectionTarget<ServiceType> target(this, service_name, service);
  reflect::MetaClass<ServiceType>::reflectMethods(&target);
}

template <class MethodType>
void JSONRPC::registerMethod(
    const std::string& method_name,
    MethodType* method_call,
    typename MethodType::ClassType* service) {
  registerMethod(method_name, [method_call, service] (
      JSONRPCRequest* req,
      JSONRPCResponse* res) {
    res->successAndReturn(method_call->call(service, *req));
  });
}

template <class ClassType>
JSONRPC::ReflectionTarget<ClassType>::ReflectionTarget(
    JSONRPC* self,
    const std::string service_name,
    ClassType* service) :
    self_(self),
    service_name_(service_name),
    service_(service) {}

template <typename ClassType>
template <typename MethodType>
void JSONRPC::ReflectionTarget<ClassType>::method(MethodType* method_call) {
  self_->registerMethod(
      StringUtil::format("$0.$1", service_name_, method_call->name()),
      method_call,
      service_);
}

}
}
