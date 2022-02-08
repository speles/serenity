/*
 * Copyright (c) 2021, Jesse Buhagiar <jooster669@gmail.com>
 * Copyright (c) 2021, Stephan Unverwerth <s.unverwerth@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "GLContext.h"
#include "OSMesaGLContext.h"
#include "SoftwareGLContext.h"
#include <AK/Debug.h>
#include <LibGfx/Bitmap.h>

__attribute__((visibility("hidden"))) GL::GLContext* g_gl_context;

namespace GL {

GLContext::~GLContext()
{
    dbgln_if(GL_DEBUG, "GLContext::~GLContext() {:p}", this);
    if (g_gl_context == this)
        make_context_current(nullptr);
}

NonnullOwnPtr<GLContext> create_context(Gfx::Bitmap& bitmap)
{
    OwnPtr<GLContext> context;

    StringView gl_backend_choice(getenv("SERENITY_GL_BACKEND"));
    if (gl_backend_choice.is_null() || gl_backend_choice.equals_ignoring_case("software")) {
        dbgln_if(GL_DEBUG, "GL::create_context() will use SoftwareGLContext");

        context = make<SoftwareGLContext>(bitmap);
    } else if (gl_backend_choice.equals_ignoring_case("osmesa")) {
        dbgln_if(GL_DEBUG, "GL::create_context() will use OSMesaGLContext");

        context = make<OSMesaGLContext>(bitmap);
    } else {
        VERIFY_NOT_REACHED();
    }

    dbgln_if(GL_DEBUG, "GL::create_context({}) -> {:p}", bitmap.size(), context.ptr());

    if (!g_gl_context)
        make_context_current(context);

    return context.release_nonnull();
}

void make_context_current(GLContext* context)
{
    if (g_gl_context == context)
        return;

    dbgln_if(GL_DEBUG, "GL::make_context_current({:p})", context);
    g_gl_context = context;

    if (context)
        context->activate();
}

void present_context(GLContext* context)
{
    context->present();
}

}
