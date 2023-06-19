//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// Copyright (c) 2023 Vinnie Falco (vinnie.falco@gmail.com)
//
// Official repository: https://github.com/cppalliance/mrdox
//

#include <mrdox/Support/Dom.hpp>

namespace clang {
namespace mrdox {
namespace dom {

Any::~Any() = default;

//------------------------------------------------

std::size_t
Array::
length() const noexcept
{
    return 0;
}

Value
Array::
get(std::size_t) const
{
    return nullptr;
}

bool
Object::
empty() const noexcept
{
    return true;
}

Value
Object::
get(std::string_view) const
{
    return nullptr;
}

auto
Object::
props() const ->
    std::vector<std::string_view>
{
    return {};
}

//------------------------------------------------

Value::
~Value()
{
    switch(kind_)
    {
    case Kind::Array:
        array_.~Pointer();
        break;
    case Kind::Object:
        object_.~Pointer();
        break;
    case Kind::String:
        string_.~basic_string();
        break;
    case Kind::Integer:
    case Kind::Boolean:
    case Kind::Null:
        break;
    default:
        MRDOX_UNREACHABLE();
    }
}

Value::
Value() noexcept
    : kind_(Kind::Null)
{
}

Value::
Value(
    Value&& other) noexcept
    : kind_(other.kind_)
{
    switch(kind_)
    {
    case Kind::Array:
        new(&array_) ArrayPtr(std::move(other.array_));
        other.array_.~Pointer();
        break;
    case Kind::Object:
        new(&object_) ObjectPtr(std::move(other.object_));
        object_.~Pointer();
        break;
    case Kind::String:
        new(&string_) std::string(std::move(other.string_));
        string_.~basic_string();
        break;
    case Kind::Integer:
    case Kind::Boolean:
        number_ = other.number_;
    case Kind::Null:
        break;
    default:
        MRDOX_UNREACHABLE();
    }
    other.kind_ = Kind::Null;
}

Value::
Value(
    Value const& other)
    : kind_(other.kind_)
{
    switch(kind_)
    {
    case Kind::Array:
        new(&array_) ArrayPtr(other.array_);
        break;
    case Kind::Object:
        new(&object_) ObjectPtr(other.object_);
        break;
    case Kind::String:
        new(&string_) std::string(other.string_);
        break;
    case Kind::Integer:
    case Kind::Boolean:
        number_ = other.number_;
    case Kind::Null:
        break;
    default:
        MRDOX_UNREACHABLE();
    }
}

Value::
Value(bool b) noexcept
    : kind_(Kind::Boolean)
    , number_(b)
{
}

Value::
Value(
    ArrayPtr const& arr) noexcept
    : kind_(Kind::Array)
    , array_(std::move(arr))
{
}

Value::
Value(
    ObjectPtr const& obj) noexcept
    : kind_(Kind::Object)
    , object_(std::move(obj))
{
}

Value::
Value(std::nullptr_t) noexcept
    : kind_(Kind::Null)
{
}

Value::
Value(char const* s) noexcept
    : kind_(Kind::String)
    , string_(s)
{
}

Value::
Value(
    std::string_view s) noexcept
    : kind_(Kind::String)
    , string_(s)
{
}

Value::
Value(
    std::string string) noexcept
    : kind_(Kind::String)
    , string_(std::move(string))
{
}

bool
Value::
isTruthy() const noexcept
{
    switch(kind_)
    {
    case Kind::Array: return array_->length() > 0;
    case Kind::Object: return object_->empty();
    case Kind::String: return string_.size() > 0;
    case Kind::Integer:
    case Kind::Boolean: return number_ != 0;
    case Kind::Null: return false;
    default: MRDOX_UNREACHABLE();
    }
}

//------------------------------------------------

} // dom
} // mrdox
} // clang