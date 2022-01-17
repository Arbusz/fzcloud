#!/usr/bin/env bash

protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin fzrpc.proto
protoc -I=. --cpp_out=. fzrpc.proto

