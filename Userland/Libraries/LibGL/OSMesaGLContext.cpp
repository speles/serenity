/*
 * Copyright (c) 2022, Sviatoslav Peleshko <speles@mail.ua>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibGL/OSMesaGLContext.h>

namespace GL {

#define OSMESA_RGBA GL_RGBA
#define OSMESA_BGRA 0x1
#define OSMESA_ARGB 0x2
#define OSMESA_RGB GL_RGB
#define OSMESA_BGR 0x4
#define OSMESA_RGB_565 0x5

#define OSMESA_Y_UP 0x11

OSMesaGLContext::OSMesaGLContext(Gfx::Bitmap& frontbuffer)
    : m_frontbuffer(frontbuffer)
{
    m_mesa_lib_handle = dlopen("libOSMesa.so", RTLD_LAZY | RTLD_LOCAL);
    if (!m_mesa_lib_handle) {
        dbgln("Can't load libOSMesa.so. Please check that you've built mesa port");
        VERIFY_NOT_REACHED();
    }

    GLenum context_format;
    switch (frontbuffer.format()) {
    case Gfx::BitmapFormat::BGRx8888:
    case Gfx::BitmapFormat::BGRA8888:
        context_format = OSMESA_BGRA;
        break;
    case Gfx::BitmapFormat::RGBA8888:
        context_format = OSMESA_RGBA;
        break;
    default:
        VERIFY_NOT_REACHED();
    }

    m_mesa_context = os_mesa_create_context(context_format, NULL);
    if (!m_mesa_context) {
        dbgln("OSMesaCreateContext failed!");
        VERIFY_NOT_REACHED();
    }
}

OSMesaGLContext::~OSMesaGLContext()
{
    dlclose(m_mesa_lib_handle);
}

void* OSMesaGLContext::find_symbol_in_lib(const char* symbol_name) const
{
    void* sym = dlsym(m_mesa_lib_handle, symbol_name);
    if (!sym) {
        dbgln("Can't find symbol {}", symbol_name);
        VERIFY_NOT_REACHED();
    }

    return sym;
}

void OSMesaGLContext::activate()
{
    if (GL_TRUE != os_mesa_make_current(m_mesa_context, m_frontbuffer->scanline_u8(0), GL_UNSIGNED_BYTE, m_frontbuffer->width(), m_frontbuffer->height())) {
        dbgln("OSMesaMakeCurrent failed");
        VERIFY_NOT_REACHED();
    }

    os_mesa_pixel_store(OSMESA_Y_UP, 0);
}

void OSMesaGLContext::present()
{
    glFinish();
}

void OSMesaGLContext::gl_light_model(GLenum pname, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    static void* address = find_symbol_in_lib("glLightModelfv");
    const GLfloat params[4] { x, y, z, w };
    ((void (*)(GLenum, const GLfloat*))address)(pname, params);
}

void OSMesaGLContext::gl_get_light(GLenum light, GLenum pname, void* params, GLenum type)
{
    if (type == GL_FLOAT) {
        static void* address = find_symbol_in_lib("glGetLightfv");
        ((void (*)(GLenum, GLenum, const GLfloat*))address)(light, pname, (const GLfloat*)params);
    } else if (type == GL_INT) {
        static void* address = find_symbol_in_lib("glGetLightiv");
        ((void (*)(GLenum, GLenum, const GLint*))address)(light, pname, (const GLint*)params);
    } else
        VERIFY_NOT_REACHED();
}

void OSMesaGLContext::gl_get_material(GLenum face, GLenum pname, void* params, GLenum type)
{
    if (type == GL_FLOAT) {
        static void* address = find_symbol_in_lib("glGetMaterialfv");
        ((void (*)(GLenum, GLenum, const GLfloat*))address)(face, pname, (const GLfloat*)params);
    } else if (type == GL_INT) {
        static void* address = find_symbol_in_lib("glGetMaterialiv");
        ((void (*)(GLenum, GLenum, const GLint*))address)(face, pname, (const GLint*)params);
    } else
        VERIFY_NOT_REACHED();
}

void OSMesaGLContext::gl_load_matrix(const FloatMatrix4x4& matrix)
{
    static void* address = find_symbol_in_lib("glLoadMatrixf");
    FloatMatrix4x4 transposed_matrix(matrix.transpose());
    ((void (*)(const GLfloat*))address)((const GLfloat*)(&transposed_matrix));
}

void OSMesaGLContext::gl_mult_matrix(FloatMatrix4x4 const& matrix)
{
    static void* address = find_symbol_in_lib("glMultMatrixf");
    FloatMatrix4x4 transposed_matrix(matrix.transpose());
    ((void (*)(const GLfloat*))address)((const GLfloat*)(&transposed_matrix));
}

OSMesaGLContext::OSMesaContext OSMesaGLContext::os_mesa_create_context(GLenum format, OSMesaContext sharelist)
{
    static void* address = find_symbol_in_lib("OSMesaCreateContext");
    return ((OSMesaContext(*)(GLenum, OSMesaContext))address)(format, sharelist);
}

GLboolean OSMesaGLContext::os_mesa_make_current(OSMesaContext ctx, void* buffer, GLenum type, GLsizei width, GLsizei height)
{
    static void* address = find_symbol_in_lib("OSMesaMakeCurrent");
    return ((GLboolean(*)(OSMesaContext, void*, GLenum, GLsizei, GLsizei))address)(ctx, buffer, type, width, height);
}

void OSMesaGLContext::os_mesa_pixel_store(GLint pname, GLint value)
{
    static void* address = find_symbol_in_lib("OSMesaPixelStore");
    ((void (*)(GLint, GLint))address)(pname, value);
}

}
