NULL :=

GENERATED_SRCS := generated-srcs
SRCS := srcs

DJINNI_DIR := ./djinni
DJINNI_BIN := $(DJINNI_DIR)/src/run
DJINNI_SUPPORT_DIR := $(DJINNI_DIR)/support-lib

JAVA_OPTS := \
	--java-out $(GENERATED_SRCS)/java/com/xplatform/lib \
	--java-package com.xplatform.lib \
	$(NULL)

JNI_OPTS := \
	--jni-out $(GENERATED_SRCS)/jni \
	--ident-jni-class NativeFooBar \
	--ident-jni-file NativeFooBar \
	$(NULL)

CPP_OPTS := \
	--cpp-out $(GENERATED_SRCS)/cpp \
	--cpp-namespace xplatform \
	--ident-cpp-enum-type foo_bar \
	--cpp-ext cc \
	--hpp-ext h \
	--cpp-optional-template "boost::optional" \
	--cpp-optional-header "<boost/optional.hpp>" \
	$(NULL)

OBJC_OPTS := \
	--objc-out $(GENERATED_SRCS)/objc \
	--objcpp-out $(GENERATED_SRCS)/objc \
	--objc-type-prefix XPL \
	--objcpp-namespace "djinni" \
	$(NULL)

DJINNI = $(DJINNI_BIN) $(JAVA_OPTS) $(JNI_OPTS) $(CPP_OPTS) $(OBJC_OPTS)

DJINNI_SRCS := \
	xplatform.djinni \
	$(NULL)

build: $(DJINNI_SRCS)
	mkdir -p $(GENERATED_SRCS)
	$(DJINNI) --idl $<

all: build

clean:
	rm -rf $(GENERATED_SRCS)