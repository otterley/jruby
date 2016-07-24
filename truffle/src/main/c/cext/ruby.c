/*
 * Copyright (c) 2016 Oracle and/or its affiliates. All rights reserved. This
 * code is released under a tri EPL/GPL/LGPL license. You can use it,
 * redistribute it and/or modify it under the terms of the:
 *
 * Eclipse Public License version 1.0
 * GNU General Public License version 2
 * GNU Lesser General Public License version 2.1
 *
 * This file contains code that is based on the Ruby API headers,
 * copyright (C) Yukihiro Matsumoto, licensed under the 2-clause BSD licence
 * as described in the file BSDL included with JRuby+Truffle.
 */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <truffle.h>

#include <ruby.h>

#define RUBY_CEXT truffle_import_cached("ruby_cext")

// Types

int rb_type(VALUE value) {
  return truffle_invoke_i(RUBY_CEXT, "rb_type", value);
}

bool RB_TYPE_P(VALUE value, int type) {
  return truffle_invoke_i(RUBY_CEXT, "RB_TYPE_P", value, type);
}

void rb_check_type(VALUE value, int type) {
  truffle_invoke(RUBY_CEXT, "rb_check_type", value);
}

VALUE rb_obj_is_kind_of(VALUE object, VALUE ruby_class) {
  return truffle_invoke(object, "kind_of?", ruby_class);
}

// Constants

VALUE get_Qfalse(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "Qfalse");
}

VALUE get_Qtrue(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "Qtrue");
}

VALUE get_Qnil(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "Qnil");
}

VALUE get_rb_cObject(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_cObject");
}

VALUE get_rb_cArray(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_cArray");
}

VALUE get_rb_cHash(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_cHash");
}

VALUE get_rb_cProc(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_cProc");
}

VALUE get_rb_cTime(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_cTime");
}

VALUE get_rb_mKernel() {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_mKernel");
}

VALUE get_rb_eException() {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_eException");
}

VALUE get_rb_eRuntimeError() {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_eRuntimeError");
}

VALUE get_rb_eStandardError(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_eStandardError");
}

VALUE get_rb_eNoMemError(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_eNoMemError");
}

VALUE get_rb_eTypeError(void) {
  return (VALUE) truffle_read(RUBY_CEXT, "rb_eTypeError");
}

// Conversions

VALUE CHR2FIX(char ch) {
  return INT2FIX((unsigned char) ch);
}

int NUM2INT(VALUE value) {
  return truffle_invoke_i(RUBY_CEXT, "NUM2INT", value);
}

unsigned int NUM2UINT(VALUE value) {
  return (unsigned int) truffle_invoke_i(RUBY_CEXT, "NUM2UINT", value);
}

long NUM2LONG(VALUE value) {
  return truffle_invoke_l(RUBY_CEXT, "NUM2LONG", value);
}

int FIX2INT(VALUE value) {
  return truffle_invoke_i(RUBY_CEXT, "FIX2INT", value);
}

unsigned int FIX2UINT(VALUE value) {
  return (unsigned int) truffle_invoke_i(RUBY_CEXT, "FIX2UINT", value);
}

long FIX2LONG(VALUE value) {
  return truffle_invoke_l(RUBY_CEXT, "FIX2LONG", value);
}

VALUE INT2NUM(long value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "INT2NUM", value);
}

VALUE INT2FIX(long value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "INT2FIX", value);
}

VALUE UINT2NUM(unsigned int value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "UINT2NUM", value);
}

VALUE LONG2NUM(long value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "LONG2NUM", value);
}

VALUE LONG2FIX(long value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "LONG2FIX", value);
}

int rb_fix2int(VALUE value) {
  return truffle_invoke_i(RUBY_CEXT, "rb_fix2int", value);
}

unsigned long rb_fix2uint(VALUE value) {
  return truffle_invoke_l(RUBY_CEXT, "rb_fix2uint", value);
}

ID SYM2ID(VALUE value) {
  return (ID) value;
}

VALUE ID2SYM(ID value) {
  return (VALUE) value;
}

// Type checks

int NIL_P(VALUE value) {
  return truffle_invoke_b(RUBY_CEXT, "NIL_P", value);
}

int FIXNUM_P(VALUE value) {
  return truffle_invoke_b(RUBY_CEXT, "FIXNUM_P", value);
}

int RTEST(VALUE value) {
  return truffle_invoke_b(RUBY_CEXT, "RTEST", value);
}

// Float

VALUE rb_float_new(double value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "rb_float_new", value);
}

VALUE rb_Float(VALUE value) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "rb_Float", value);
}

double RFLOAT_VALUE(VALUE value){
  return truffle_invoke_d(RUBY_CEXT, "RFLOAT_VALUE", value);
}

// String

char *RSTRING_PTR(VALUE string) {
  return truffle_invoke(RUBY_CEXT, "CExtString", string);
}

int rb_str_len(VALUE string) {
  return truffle_invoke_i(string, "bytesize");
}

VALUE rb_str_new(const char *string, long length) {
  if (truffle_is_truffle_object((VALUE) string)) {
    return truffle_invoke(RUBY_CEXT, "rb_str_new", string, length);
  } else {
    return (VALUE) truffle_invoke(RUBY_CEXT, "rb_str_new_cstr", truffle_read_n_string(string, length));
  }
}

VALUE rb_str_new_cstr(const char *string) {
  if (truffle_is_truffle_object((VALUE) string)) {
    return truffle_invoke(RUBY_CEXT, "to_ruby_string", string);
  } else {
    return (VALUE) truffle_invoke(RUBY_CEXT, "rb_str_new_cstr", truffle_read_string(string));
  }
}

VALUE rb_intern_str(VALUE string) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "rb_intern_str", string);
}

VALUE rb_str_cat(VALUE string, const char *to_concat, long length) {
  truffle_invoke(RUBY_CEXT, "rb_str_cat", string, rb_str_new_cstr(to_concat), length);
  return string;
}

VALUE rb_str_cat2(VALUE string, const char *to_concat) {
  truffle_invoke(string, "concat", rb_str_new_cstr(to_concat));
  return string;
}

VALUE rb_str_to_str(VALUE string) {
  return (VALUE) truffle_invoke(string, "to_str");
}

VALUE rb_string_value(VALUE *value_pointer) {
  VALUE value = *value_pointer;
  
  if (!RB_TYPE_P(value, T_STRING)) {
    value = rb_str_to_str(value);
    *value_pointer = value;
  }
  
  return value;
}

VALUE rb_str_buf_new(long capacity) {
  return rb_str_new_cstr("");
}

VALUE rb_sprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  VALUE *string = rb_vsprintf(format, args);
  va_end(args);
  return string;
}

VALUE rb_vsprintf(const char *format, va_list args) {
  fprintf(stderr, "rb_vsprintf not implemented\n");
  abort();
}

// Symbol

ID rb_intern(const char *string) {
  return (ID) truffle_invoke(RUBY_CEXT, "rb_intern", rb_str_new_cstr(string));
}

// Array

int RARRAY_LEN(VALUE array) {
  return truffle_get_size(array);
}

int RARRAY_LENINT(VALUE array) {
  return truffle_get_size(array);
}

VALUE *RARRAY_PTR(VALUE array) {
  // Needs to return a fake VALUE* which actually calls back into Ruby when read or written
  return (VALUE*) truffle_invoke(RUBY_CEXT, "RARRAY_PTR", array);
}

VALUE RARRAY_AREF(VALUE array, long index) {
  return truffle_read_idx(array, (int) index);
}

VALUE rb_Array(VALUE array) {
  return truffle_invoke(RUBY_CEXT, "rb_Array", array);
}

VALUE rb_ary_new() {
  return (VALUE) truffle_invoke(RUBY_CEXT, "rb_ary_new");
}

VALUE rb_ary_new_capa(long capacity) {
  return (VALUE) truffle_invoke(RUBY_CEXT, "rb_ary_new_capa", capacity);
}

VALUE rb_ary_new_from_args(long n, ...) {
  VALUE array = rb_ary_new_capa(n);
  for (int i = 0; i < n; i++) {
    rb_ary_store(array, i, (VALUE) truffle_get_arg(1+i));
  }
  return array;
}

VALUE rb_ary_new4(long n, const VALUE *values) {
  VALUE array = rb_ary_new_capa(n);
  for (int i = 0; i < n; i++) {
    rb_ary_store(array, i, values[i]);
  }
  return array;
}

VALUE rb_ary_push(VALUE array, VALUE value) {
  truffle_invoke(array, "push", value);
  return array;
}

VALUE rb_ary_pop(VALUE array) {
  return truffle_invoke(array, "pop");
}

void rb_ary_store(VALUE array, long index, VALUE value) {
  truffle_write_idx(array, (int) index, value);
}

VALUE rb_ary_entry(VALUE array, long index) {
  return truffle_read_idx(array, (int) index);
}

VALUE rb_ary_dup(VALUE array) {
  return (VALUE) truffle_invoke(array, "dup");
}

// Hash

VALUE rb_hash_new() {
  return (VALUE) truffle_invoke(RUBY_CEXT, "rb_hash_new");
}

VALUE rb_hash_aref(VALUE hash, VALUE key) {
  return truffle_read(hash, key);
}

VALUE rb_hash_aset(VALUE hash, VALUE key, VALUE value) {
  truffle_write(hash, key, value);
  return value;
}

// Class

const char* rb_class2name(VALUE module) {
  return RSTRING_PTR(truffle_invoke(module, "name"));
}

// Proc

VALUE rb_proc_new(void *function, VALUE value) {
  return truffle_invoke(RUBY_CEXT, "rb_proc_new", truffle_address_to_function(function), value);
}

// Utilities

void rb_warn(const char *format, ...) {
  if (!truffle_invoke_b(truffle_invoke(RUBY_CEXT, "verbose"), "nil?")) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }
}

void rb_warning(const char *format, ...) {
  if (truffle_invoke(RUBY_CEXT, "verbose") == Qtrue) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }
}

int rb_scan_args(int argc, VALUE *argv, const char *format, ...) {
  return truffle_invoke_i(RUBY_CEXT, "rb_scan_args", argc, argv, format /*, where to get args? */);
}

// Calls

int rb_respond_to(VALUE object, ID name) {
  return truffle_invoke_b(object, "respond_to?", name);
}

VALUE rb_yield(VALUE value) {
  return truffle_invoke(RUBY_CEXT, "rb_yield", value);
}

// Instance variables

VALUE rb_iv_get(VALUE object, const char *name) {
  return truffle_read(object, rb_intern(name));
}

VALUE rb_iv_set(VALUE object, const char *name, VALUE value) {
  truffle_write(object, rb_intern(name), value);
  return value;
}

// Accessing constants

int rb_const_defined(VALUE module, ID name) {
  return truffle_invoke_b(module, "const_defined?", name);
}

int rb_const_defined_at(VALUE module, ID name) {
  return truffle_invoke_b(module, "const_defined?", name, Qfalse);
}

VALUE rb_const_get(VALUE module, ID name) {
  return truffle_invoke(module, "const_get", name);
}

VALUE rb_const_get_at(VALUE module, ID name) {
  return truffle_invoke(module, "const_get", name, Qfalse);
}

VALUE rb_const_get_from(VALUE module, ID name) {
  return truffle_invoke(RUBY_CEXT, "rb_const_get_from", module, name);
}

VALUE rb_const_set(VALUE module, ID name, VALUE value) {
  return truffle_invoke(module, "const_set", name, value);
}

VALUE rb_define_const(VALUE module, const char *name, VALUE value) {
  return rb_const_set(module, rb_str_new_cstr(name), value);
}

void rb_define_global_const(const char *name, VALUE value) {
  rb_define_const(rb_cObject, name, value);
}

// Raising exceptions

VALUE rb_exc_new3(VALUE exception_class, VALUE message) {
  return truffle_invoke(exception_class, "new", message);
}

void rb_exc_raise(VALUE exception) {
  truffle_invoke(RUBY_CEXT, "rb_exc_raise", exception);
  abort();
}

void rb_raise(VALUE exception, const char *format, ...) {
  fprintf(stderr, "rb_raise not implemented\n");
  truffle_invoke(RUBY_CEXT, "rb_raise", format /*, where to get args? */);
  abort();
}

VALUE rb_protect(VALUE (*function)(VALUE), VALUE data, int *status) {
  // TODO CS 23-Jul-16
  return function(data);
}

void rb_jump_tag(int status) {
  if (status) {
    // TODO CS 23-Jul-16
    fprintf(stderr, "rb_jump_tag not implemented\n");
    abort();
  }
}

void rb_set_errinfo(VALUE error) {
  // TODO CS 23-Jul-16
  fprintf(stderr, "rb_set_errinfo not implemented\n");
  abort();
}

// Defining classes, modules and methods

VALUE rb_define_class(const char *name, VALUE superclass) {
  return rb_define_class_under(rb_cObject, name, superclass);
}

VALUE rb_define_class_under(VALUE module, const char *name, VALUE superclass) {
  return rb_define_class_id_under(module, rb_str_new_cstr(name), superclass);
}

VALUE rb_define_class_id_under(VALUE module, ID name, VALUE superclass) {
  return truffle_invoke(RUBY_CEXT, "rb_define_class_under", module, name, superclass);
}

VALUE rb_define_module(const char *name) {
  return rb_define_module_under(rb_cObject, name);
}

VALUE rb_define_module_under(VALUE module, const char *name) {
  return truffle_invoke(RUBY_CEXT, "rb_define_module_under", module, rb_str_new_cstr(name));
}

void rb_define_method(VALUE module, const char *name, void *function, int argc) {
  truffle_invoke(RUBY_CEXT, "rb_define_method", module, rb_str_new_cstr(name), truffle_address_to_function(function), argc);
}

void rb_define_private_method(VALUE module, const char *name, void *function, int argc) {
  truffle_invoke(RUBY_CEXT, "rb_define_private_method", module, rb_str_new_cstr(name), truffle_address_to_function(function), argc);
}

void rb_define_protected_method(VALUE module, const char *name, void *function, int argc) {
  truffle_invoke(RUBY_CEXT, "rb_define_protected_method", module, rb_str_new_cstr(name), truffle_address_to_function(function), argc);
}

void rb_define_module_function(VALUE module, const char *name, void *function, int argc) {
  truffle_invoke(RUBY_CEXT, "rb_define_module_function", module, rb_str_new_cstr(name), truffle_address_to_function(function), argc);
}

void rb_define_global_function(const char *name, void *function, int argc) {
  rb_define_module_function(rb_mKernel, name, function, argc);
}

void rb_define_singleton_method(VALUE object, const char *name, void *function, int argc) {
  truffle_invoke(RUBY_CEXT, "rb_define_singleton_method", object, rb_str_new_cstr(name), truffle_address_to_function(function), argc);
}

void rb_define_alias(VALUE module, const char *new_name, const char *old_name) {
  rb_alias(module, rb_str_new_cstr(new_name), rb_str_new_cstr(old_name));
}

void rb_alias(VALUE module, ID new_name, ID old_name) {
  truffle_invoke(RUBY_CEXT, "rb_alias", module, new_name, old_name);
}

void rb_undef_method(VALUE module, const char *name) {
  rb_undef(module, rb_str_new_cstr(name));
}

void rb_undef(VALUE module, ID name) {
  truffle_invoke(RUBY_CEXT, "rb_undef", module, name);
}

// Rational

VALUE rb_Rational(VALUE num, VALUE den) {
  return truffle_invoke(RUBY_CEXT, "rb_Rational", num, den);
}

VALUE rb_rational_raw(VALUE num, VALUE den) {
  return truffle_invoke(RUBY_CEXT, "rb_rational_raw", num, den);
}

VALUE rb_rational_new(VALUE num, VALUE den) {
  return truffle_invoke(RUBY_CEXT, "rb_rational_new", num, den);
}

VALUE rb_rational_num(VALUE rat) {
  return truffle_invoke(rat, "numerator");
}

VALUE rb_rational_den(VALUE rat) {
  return truffle_invoke(rat, "denominator");
}

VALUE rb_flt_rationalize_with_prec(VALUE value, VALUE precision) {
  return truffle_invoke(value, "rationalize", precision);
}

VALUE rb_flt_rationalize(VALUE value) {
  return truffle_invoke(value, "rationalize");
}

// Complex

VALUE rb_Complex(VALUE real, VALUE imag) {
  return truffle_invoke(RUBY_CEXT, "rb_Complex", real, imag);
}

VALUE rb_complex_new(VALUE real, VALUE imag) {
  return truffle_invoke(RUBY_CEXT, "rb_complex_new", real, imag);
}

VALUE rb_complex_raw(VALUE real, VALUE imag) {
  return truffle_invoke(RUBY_CEXT, "rb_complex_raw", real, imag);
}

VALUE rb_complex_polar(VALUE r, VALUE theta) {
  return truffle_invoke(RUBY_CEXT, "rb_complex_polar", r, theta);
}

VALUE rb_complex_set_real(VALUE complex, VALUE real) {
  return truffle_invoke(RUBY_CEXT, "rb_complex_set_real", complex, real);
}

VALUE rb_complex_set_imag(VALUE complex, VALUE imag) {
  return truffle_invoke(RUBY_CEXT, "rb_complex_set_imag", complex, imag);
}

// Mutexes

VALUE rb_mutex_new(void) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_new");
}

VALUE rb_mutex_locked_p(VALUE mutex) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_locked_p", mutex);
}

VALUE rb_mutex_trylock(VALUE mutex) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_trylock", mutex);
}

VALUE rb_mutex_lock(VALUE mutex) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_lock", mutex);
}

VALUE rb_mutex_unlock(VALUE mutex) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_unlock", mutex);
}

VALUE rb_mutex_sleep(VALUE mutex, VALUE timeout) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_sleep", mutex, timeout);
}

VALUE rb_mutex_synchronize(VALUE mutex, VALUE (*func)(VALUE arg), VALUE arg) {
  return truffle_invoke(RUBY_CEXT, "rb_mutex_synchronize", mutex, func, arg);
}

// GC

void rb_gc_register_address(VALUE *address) {
}

VALUE rb_gc_enable() {
  return truffle_invoke(RUBY_CEXT, "rb_gc_enable");
}

VALUE rb_gc_disable() {
  return truffle_invoke(RUBY_CEXT, "rb_gc_disable");
}

// Threads

rb_nativethread_id_t rb_nativethread_self() {
  return truffle_invoke(RUBY_CEXT, "rb_nativethread_self");
}

int rb_nativethread_lock_initialize(rb_nativethread_lock_t *lock) {
  *lock = truffle_invoke(RUBY_CEXT, "rb_nativethread_lock_initialize");
  return 0;
}

int rb_nativethread_lock_destroy(rb_nativethread_lock_t *lock) {
  *lock = NULL;
  return 0;
}

int rb_nativethread_lock_lock(rb_nativethread_lock_t *lock) {
  truffle_invoke(lock, "lock");
  return 0;
}

int rb_nativethread_lock_unlock(rb_nativethread_lock_t *lock) {
  truffle_invoke(lock, "unlock");
  return 0;
}
