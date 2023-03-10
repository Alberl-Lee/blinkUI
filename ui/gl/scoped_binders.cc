// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gl/scoped_binders.h"
#include "ui/gl/gl_bindings.h"
#include "ui/gl/gl_context.h"
#include "ui/gl/gl_state_restorer.h"

namespace gfx {

ScopedFrameBufferBinder::ScopedFrameBufferBinder(unsigned int fbo)
    : state_restorer_(!GLContext::GetCurrent()
            ? NULL
            : GLContext::GetCurrent()->GetGLStateRestorer())
    , old_fbo_(-1)
{
    if (!state_restorer_)
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &old_fbo_);
    glBindFramebufferEXT(GL_FRAMEBUFFER, fbo);
}

ScopedFrameBufferBinder::~ScopedFrameBufferBinder()
{
    if (state_restorer_) {
        DCHECK(!!GLContext::GetCurrent());
        DCHECK_EQ(state_restorer_, GLContext::GetCurrent()->GetGLStateRestorer());
        state_restorer_->RestoreFramebufferBindings();
    } else {
        glBindFramebufferEXT(GL_FRAMEBUFFER, old_fbo_);
    }
}

ScopedActiveTexture::ScopedActiveTexture(unsigned int texture)
    : old_texture_(-1)
{
    glGetIntegerv(GL_ACTIVE_TEXTURE, &old_texture_);
    glActiveTexture(texture);
}

ScopedActiveTexture::~ScopedActiveTexture()
{
    glActiveTexture(old_texture_);
}

ScopedTextureBinder::ScopedTextureBinder(unsigned int target, unsigned int id)
    : state_restorer_(!GLContext::GetCurrent()
            ? NULL
            : GLContext::GetCurrent()->GetGLStateRestorer())
    , target_(target)
    , old_id_(-1)
{
    if (!state_restorer_) {
        GLenum target_getter = 0;
        switch (target) {
        case GL_TEXTURE_2D:
            target_getter = GL_TEXTURE_BINDING_2D;
            break;
        case GL_TEXTURE_CUBE_MAP:
            target_getter = GL_TEXTURE_BINDING_CUBE_MAP;
            break;
        case GL_TEXTURE_EXTERNAL_OES:
            target_getter = GL_TEXTURE_BINDING_EXTERNAL_OES;
            break;
        case GL_TEXTURE_RECTANGLE_ARB:
            target_getter = GL_TEXTURE_BINDING_RECTANGLE_ARB;
            break;
        default:
            NOTIMPLEMENTED() << " Target not supported.";
        }
        glGetIntegerv(target_getter, &old_id_);
    }
    glBindTexture(target_, id);
}

ScopedTextureBinder::~ScopedTextureBinder()
{
    if (state_restorer_) {
        DCHECK(!!GLContext::GetCurrent());
        DCHECK_EQ(state_restorer_, GLContext::GetCurrent()->GetGLStateRestorer());
        state_restorer_->RestoreActiveTextureUnitBinding(target_);
    } else {
        glBindTexture(target_, old_id_);
    }
}

ScopedUseProgram::ScopedUseProgram(unsigned int program)
    : old_program_(-1)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, &old_program_);
    glUseProgram(program);
}

ScopedUseProgram::~ScopedUseProgram()
{
    glUseProgram(old_program_);
}

ScopedVertexAttribArray::ScopedVertexAttribArray(unsigned int index,
    int size,
    unsigned int type,
    char normalized,
    int stride,
    const void* pointer)
    : buffer_(0)
    , enabled_(GL_FALSE)
    , index_(index)
    , size_(-1)
    , type_(-1)
    , normalized_(GL_FALSE)
    , stride_(0)
    , pointer_(0)
{
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &buffer_);
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled_);
    glEnableVertexAttribArray(index);

    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size_);
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type_);
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized_);
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride_);
    glGetVertexAttribPointerv(index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &pointer_);

    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

ScopedVertexAttribArray::~ScopedVertexAttribArray()
{
    ScopedBufferBinder buffer_binder(GL_ARRAY_BUFFER, buffer_);
    glVertexAttribPointer(index_, size_, type_, normalized_, stride_, pointer_);
    if (enabled_ == GL_FALSE) {
        glDisableVertexAttribArray(index_);
    }
}

ScopedBufferBinder::ScopedBufferBinder(unsigned int target, unsigned int id)
    : target_(target)
    , old_id_(-1)
{
    GLenum target_getter = 0;
    switch (target) {
    case GL_ARRAY_BUFFER:
        target_getter = GL_ARRAY_BUFFER_BINDING;
        break;
    default:
        NOTIMPLEMENTED() << " Target not supported.";
    }
    glGetIntegerv(target_getter, &old_id_);
    glBindBuffer(target_, id);
}

ScopedBufferBinder::~ScopedBufferBinder()
{
    glBindBuffer(target_, old_id_);
}

ScopedViewport::ScopedViewport(int x, int y, int width, int height)
{
    glGetIntegerv(GL_VIEWPORT, data_);
    glViewport(x, y, width, height);
}

ScopedViewport::~ScopedViewport()
{
    glViewport(data_[0], data_[1], data_[2], data_[3]);
}

ScopedColorMask::ScopedColorMask(char red, char green, char blue, char alpha)
{
    glGetBooleanv(GL_COLOR_WRITEMASK, colors_);
    glColorMask(red, green, blue, alpha);
}

ScopedColorMask::~ScopedColorMask()
{
    glColorMask(colors_[0], colors_[1], colors_[2], colors_[3]);
}

ScopedCapability::ScopedCapability(unsigned capability, unsigned char enabled)
    : capability_(capability)
{
    enabled_ = glIsEnabled(capability_);
    if (enabled == GL_TRUE) {
        glEnable(capability);
    } else {
        glDisable(capability);
    }
}

ScopedCapability::~ScopedCapability()
{
    if (enabled_ == GL_TRUE) {
        glEnable(capability_);
    } else {
        glDisable(capability_);
    }
}

} // namespace gfx
