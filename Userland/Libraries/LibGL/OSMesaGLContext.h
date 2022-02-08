/*
 * Copyright (c) 2022, Sviatoslav Peleshko <speles@mail.ua>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/StringView.h>
#include <LibGL/GL/gl.h>
#include <LibGL/GL/glext.h>
#include <LibGL/GL/glplatform.h>
#include <LibGL/GLContext.h>
#include <dlfcn.h>

namespace GL {

// FIXME: These defines are really-really ugly, I guess some better approach is needed here.

#define DECLARE_PROXY_GL_FUNC_VOID_ARG0(proxy_name, func_name) \
    void proxy_name() override                                 \
    {                                                          \
        static void* address = find_symbol_in_lib(#func_name); \
        ((void (*)())address)();                               \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG1(proxy_name, func_name, arg_type_1, arg_name_1) \
    void proxy_name(arg_type_1 arg_name_1) override                                    \
    {                                                                                  \
        static void* address = find_symbol_in_lib(#func_name);                         \
        ((void (*)(arg_type_1))address)(arg_name_1);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG2(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2) override                                     \
    {                                                                                                          \
        static void* address = find_symbol_in_lib(#func_name);                                                 \
        ((void (*)(arg_type_1, arg_type_2))address)(arg_name_1, arg_name_2);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG3(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3) override                                      \
    {                                                                                                                                  \
        static void* address = find_symbol_in_lib(#func_name);                                                                         \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3))address)(arg_name_1, arg_name_2, arg_name_3);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG4(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3, arg_type_4, arg_name_4) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3, arg_type_4 arg_name_4) override                                       \
    {                                                                                                                                                          \
        static void* address = find_symbol_in_lib(#func_name);                                                                                                 \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3, arg_type_4))address)(arg_name_1, arg_name_2, arg_name_3, arg_name_4);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG5(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3, arg_type_4, arg_name_4, arg_type_5, arg_name_5) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3, arg_type_4 arg_name_4, arg_type_5 arg_name_5) override                                        \
    {                                                                                                                                                                                  \
        static void* address = find_symbol_in_lib(#func_name);                                                                                                                         \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5))address)(arg_name_1, arg_name_2, arg_name_3, arg_name_4, arg_name_5);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG6(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3, arg_type_4, arg_name_4, arg_type_5, arg_name_5, arg_type_6, arg_name_6) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3, arg_type_4 arg_name_4, arg_type_5 arg_name_5, arg_type_6 arg_name_6) override                                         \
    {                                                                                                                                                                                                          \
        static void* address = find_symbol_in_lib(#func_name);                                                                                                                                                 \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5, arg_type_6))address)(arg_name_1, arg_name_2, arg_name_3, arg_name_4, arg_name_5, arg_name_6);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG7(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3, arg_type_4, arg_name_4, arg_type_5, arg_name_5, arg_type_6, arg_name_6, arg_type_7, arg_name_7) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3, arg_type_4 arg_name_4, arg_type_5 arg_name_5, arg_type_6 arg_name_6, arg_type_7 arg_name_7) override                                          \
    {                                                                                                                                                                                                                                  \
        static void* address = find_symbol_in_lib(#func_name);                                                                                                                                                                         \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5, arg_type_6, arg_type_7))address)(arg_name_1, arg_name_2, arg_name_3, arg_name_4, arg_name_5, arg_name_6, arg_name_7);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG8(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3, arg_type_4, arg_name_4, arg_type_5, arg_name_5, arg_type_6, arg_name_6, arg_type_7, arg_name_7, arg_type_8, arg_name_8) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3, arg_type_4 arg_name_4, arg_type_5 arg_name_5, arg_type_6 arg_name_6, arg_type_7 arg_name_7, arg_type_8 arg_name_8) override                                           \
    {                                                                                                                                                                                                                                                          \
        static void* address = find_symbol_in_lib(#func_name);                                                                                                                                                                                                 \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5, arg_type_6, arg_type_7, arg_type_8))address)(arg_name_1, arg_name_2, arg_name_3, arg_name_4, arg_name_5, arg_name_6, arg_name_7, arg_name_8);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_VOID_ARG9(proxy_name, func_name, arg_type_1, arg_name_1, arg_type_2, arg_name_2, arg_type_3, arg_name_3, arg_type_4, arg_name_4, arg_type_5, arg_name_5, arg_type_6, arg_name_6, arg_type_7, arg_name_7, arg_type_8, arg_name_8, arg_type_9, arg_name_9) \
    void proxy_name(arg_type_1 arg_name_1, arg_type_2 arg_name_2, arg_type_3 arg_name_3, arg_type_4 arg_name_4, arg_type_5 arg_name_5, arg_type_6 arg_name_6, arg_type_7 arg_name_7, arg_type_8 arg_name_8, arg_type_9 arg_name_9) override                                            \
    {                                                                                                                                                                                                                                                                                  \
        static void* address = find_symbol_in_lib(#func_name);                                                                                                                                                                                                                         \
        ((void (*)(arg_type_1, arg_type_2, arg_type_3, arg_type_4, arg_type_5, arg_type_6, arg_type_7, arg_type_8, arg_type_9))address)(arg_name_1, arg_name_2, arg_name_3, arg_name_4, arg_name_5, arg_name_6, arg_name_7, arg_name_8, arg_name_9);                                   \
    }

#define DECLARE_PROXY_GL_FUNC_RET_ARG0(ret_type, proxy_name, func_name) \
    ret_type proxy_name() override                                      \
    {                                                                   \
        static void* address = find_symbol_in_lib(#func_name);          \
        return ((ret_type(*)())address)();                              \
    }

#define DECLARE_PROXY_GL_FUNC_RET_ARG1(ret_type, proxy_name, func_name, arg_type_1, arg_name_1) \
    ret_type proxy_name(arg_type_1 arg_name_1) override                                         \
    {                                                                                           \
        static void* address = find_symbol_in_lib(#func_name);                                  \
        return ((ret_type(*)(arg_type_1))address)(arg_name_1);                                  \
    }

class OSMesaGLContext : public GLContext {
public:
    OSMesaGLContext(Gfx::Bitmap&);
    ~OSMesaGLContext() override;

    void activate() override;
    void present() override;

    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_begin, glBegin, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_clear, glClear, GLbitfield, mask)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_clear_color, glClearColor, GLclampf, red, GLclampf, green, GLclampf, blue, GLclampf, alpha)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_clear_depth, glClearDepth, GLdouble, depth)

    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_clear_stencil, glClearStencil, GLint, s)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_color, glColor4d, GLdouble, r, GLdouble, g, GLdouble, b, GLdouble, a)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_delete_textures, glDeleteTextures, GLsizei, n, const GLuint*, textures)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_end, glEnd)
    DECLARE_PROXY_GL_FUNC_VOID_ARG6(gl_frustum, glFrustum, GLdouble, left, GLdouble, right, GLdouble, bottom, GLdouble, top, GLdouble, near_val, GLdouble, far_val)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_gen_textures, glGenTextures, GLsizei, n, GLuint*, textures)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_load_identity, glLoadIdentity)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_matrix_mode, glMatrixMode, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG6(gl_ortho, glOrtho, GLdouble, left, GLdouble, right, GLdouble, bottom, GLdouble, top, GLdouble, near_val, GLdouble, far_val)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_push_matrix, glPushMatrix)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_pop_matrix, glPopMatrix)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_rotate, glRotated, GLdouble, angle, GLdouble, x, GLdouble, y, GLdouble, z)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_scale, glScaled, GLdouble, x, GLdouble, y, GLdouble, z)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_translate, glTranslated, GLdouble, x, GLdouble, y, GLdouble, z)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_vertex, glVertex3d, GLdouble, x, GLdouble, y, GLdouble, z, GLdouble, w)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_viewport, glViewport, GLint, x, GLint, y, GLsizei, width, GLsizei, height)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_enable, glEnable, GLenum, cap)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_disable, glDisable, GLenum, cap)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_front_face, glFrontFace, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_cull_face, glCullFace, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_call_list, glCallList, GLuint, list)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_call_lists, glCallLists, GLsizei, n, GLenum, type, void const*, lists)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_delete_lists, glDeleteLists, GLuint, list, GLsizei, range)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_list_base, glListBase, GLuint, base)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_end_list, glEndList)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_new_list, glNewList, GLuint, list, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_flush, glFlush)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_finish, glFinish)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_blend_func, glBlendFunc, GLenum, src_factor, GLenum, dst_factor)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_shade_model, glShadeModel, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_alpha_func, glAlphaFunc, GLenum, func, GLclampf, ref)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_hint, glHint, GLenum, target, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_read_buffer, glReadBuffer, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_draw_buffer, glDrawBuffer, GLenum, buffer)
    DECLARE_PROXY_GL_FUNC_VOID_ARG7(gl_read_pixels, glReadPixels, GLint, x, GLint, y, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, GLvoid*, pixels)
    DECLARE_PROXY_GL_FUNC_VOID_ARG9(gl_tex_image_2d, glTexImage2D, GLenum, target, GLint, level, GLint, internal_format, GLsizei, width, GLsizei, height, GLint, border, GLenum, format, GLenum, type, const GLvoid*, data)
    DECLARE_PROXY_GL_FUNC_VOID_ARG9(gl_tex_sub_image_2d, glTexSubImage2D, GLenum, target, GLint, level, GLint, xoffset, GLint, yoffset, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, const GLvoid*, data)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_tex_parameter, glTexParameterf, GLenum, target, GLenum, pname, GLfloat, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_tex_coord, glTexCoord3f, GLfloat, s, GLfloat, t, GLfloat, r, GLfloat, q)
    DECLARE_PROXY_GL_FUNC_VOID_ARG5(gl_multi_tex_coord, glMultiTexCoord4f, GLenum, target, GLfloat, s, GLfloat, t, GLfloat, r, GLfloat, q)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_tex_env, glTexEnvf, GLenum, target, GLenum, pname, GLfloat, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_bind_texture, glBindTexture, GLenum, target, GLuint, texture)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_active_texture, glActiveTexture, GLenum, texture)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_depth_mask, glDepthMask, GLboolean, flag)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_enable_client_state, glEnableClientState, GLenum, cap)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_disable_client_state, glDisableClientState, GLenum, cap)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_client_active_texture, glClientActiveTexture, GLenum, target)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_vertex_pointer, glVertexPointer, GLint, size, GLenum, type, GLsizei, stride, const void*, pointer)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_color_pointer, glColorPointer, GLint, size, GLenum, type, GLsizei, stride, const void*, pointer)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_tex_coord_pointer, glTexCoordPointer, GLint, size, GLenum, type, GLsizei, stride, const void*, pointer)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_draw_arrays, glDrawArrays, GLenum, mode, GLint, first, GLsizei, count)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_draw_elements, glDrawElements, GLenum, mode, GLsizei, count, GLenum, type, const void*, indices)
    DECLARE_PROXY_GL_FUNC_VOID_ARG5(gl_draw_pixels, glDrawArrays, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, const void*, data)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_color_mask, glColorMask, GLboolean, red, GLboolean, green, GLboolean, blue, GLboolean, alpha)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_get_booleanv, glGetBooleanv, GLenum, pname, GLboolean*, data)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_get_doublev, glGetDoublev, GLenum, pname, GLdouble*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_get_floatv, glGetFloatv, GLenum, pname, GLfloat*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_get_integerv, glGetIntegerv, GLenum, pname, GLint*, data)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_depth_range, glDepthRange, GLdouble, min, GLdouble, max)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_depth_func, glDepthFunc, GLenum, func)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_polygon_mode, glPolygonMode, GLenum, face, GLenum, mode)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_polygon_offset, glPolygonOffset, GLfloat, factor, GLfloat, units)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_fogfv, glFogfv, GLenum, pname, GLfloat*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_fogf, glFogf, GLenum, pname, GLfloat, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_fogi, glFogi, GLenum, pname, GLint, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_pixel_storei, glPixelStorei, GLenum, pname, GLint, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_scissor, glScissor, GLint, x, GLint, y, GLsizei, width, GLsizei, height)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_stencil_func_separate, glStencilFuncSeparate, GLenum, face, GLenum, func, GLint, ref, GLuint, mask)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_stencil_mask_separate, glStencilMaskSeparate, GLenum, face, GLuint, mask)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_stencil_op_separate, glStencilOpSeparate, GLenum, face, GLenum, sfail, GLenum, dpfail, GLenum, dppass)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_normal, glNormal3f, GLfloat, nx, GLfloat, ny, GLfloat, nz)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_normal_pointer, glNormalPointer, GLenum, type, GLsizei, stride, void const*, pointer)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_raster_pos, glRasterPos4f, GLfloat, x, GLfloat, y, GLfloat, z, GLfloat, w)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_line_width, glLineWidth, GLfloat, width)
    DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_push_attrib, glPushAttrib, GLbitfield, mask)
    DECLARE_PROXY_GL_FUNC_VOID_ARG0(gl_pop_attrib, glPopAttrib)
    DECLARE_PROXY_GL_FUNC_VOID_ARG7(gl_bitmap, glBitmap, GLsizei, width, GLsizei, height, GLfloat, xorig, GLfloat, yorig, GLfloat, xmove, GLfloat, ymove, GLubyte const*, bitmap)
    DECLARE_PROXY_GL_FUNC_VOID_ARG8(gl_copy_tex_image_2d, glCopyTexImage2D, GLenum, target, GLint, level, GLenum, internalformat, GLint, x, GLint, y, GLsizei, width, GLsizei, height, GLint, border)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_get_tex_parameter_integerv, glGetTexLevelParameteriv, GLenum, target, GLint, level, GLenum, pname, GLint*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_rect, glRectd, GLdouble, x1, GLdouble, y1, GLdouble, x2, GLdouble, y2)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_tex_gen, glTexGeni, GLenum, coord, GLenum, pname, GLint, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_tex_gen_floatv, glTexGenfv, GLenum, coord, GLenum, pname, GLfloat const*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_lightf, glLightf, GLenum, light, GLenum, pname, GLfloat, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_lightfv, glLightfv, GLenum, light, GLenum, pname, GLfloat const*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_lightiv, glLightiv, GLenum, light, GLenum, pname, GLint const*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_materialf, glMaterialf, GLenum, face, GLenum, pname, GLfloat, param)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_materialfv, glMaterialfv, GLenum, face, GLenum, pname, GLfloat const*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG3(gl_materialiv, glMaterialiv, GLenum, face, GLenum, pname, GLint const*, params)
    DECLARE_PROXY_GL_FUNC_VOID_ARG2(gl_color_material, glColorMaterial, GLenum, face, GLenum, mode)

    DECLARE_PROXY_GL_FUNC_RET_ARG0(GLenum, gl_get_error, glGetError)
    DECLARE_PROXY_GL_FUNC_RET_ARG1(GLubyte*, gl_get_string, glGetString, GLenum, name)
    DECLARE_PROXY_GL_FUNC_RET_ARG1(GLboolean, gl_is_enabled, glIsEnabled, GLenum, cap)
    DECLARE_PROXY_GL_FUNC_RET_ARG1(GLboolean, gl_is_list, glIsList, GLuint, list)
    DECLARE_PROXY_GL_FUNC_RET_ARG1(GLboolean, gl_is_texture, glIsTexture, GLuint, texture)
    DECLARE_PROXY_GL_FUNC_RET_ARG1(GLuint, gl_gen_lists, glGenLists, GLsizei, range)

    // FIXME: These functions have mismatch of arguments in context and real GL lib, so they need wrappers
    //        Maybe contexts should use the same prototype as GL lib functions?
    // DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_light_model, , GLenum, pname, GLfloat, x, GLfloat, y, GLfloat, z, GLfloat, w)
    void gl_light_model(GLenum pname, GLfloat x, GLfloat y, GLfloat z, GLfloat w) override;

    // DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_get_light, , GLenum, light, GLenum, pname, void*, params, GLenum, type)
    void gl_get_light(GLenum light, GLenum pname, void* params, GLenum type) override;

    // DECLARE_PROXY_GL_FUNC_VOID_ARG4(gl_get_material, glGetMaterialfv, GLenum, face, GLenum, pname, void*, params, GLenum, type)
    void gl_get_material(GLenum face, GLenum pname, void* params, GLenum type) override;

    // FIXME: These functions also have prototype mismatch (although not significant), but more importantly
    //        they receive pre-inverted matrices (from GLMatrix.cpp), so we need to invert them back for GL.
    // DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_load_matrix, glLoadMatrixf, const GLfloat*, matrix)
    void gl_load_matrix(const FloatMatrix4x4& matrix) override;

    // DECLARE_PROXY_GL_FUNC_VOID_ARG1(gl_mult_matrix, glMultMatrixf, const GLfloat*, matrix)
    void gl_mult_matrix(FloatMatrix4x4 const& matrix) override;

private:
    typedef void* OSMesaContext;

    void* m_mesa_lib_handle;
    NonnullRefPtr<Gfx::Bitmap> m_frontbuffer;
    OSMesaContext m_mesa_context;

    void* find_symbol_in_lib(const char* symbol_name) const;

    OSMesaContext os_mesa_create_context(GLenum format, OSMesaContext sharelist);
    GLboolean os_mesa_make_current(OSMesaContext ctx, void* buffer, GLenum type, GLsizei width, GLsizei height);
    void os_mesa_pixel_store(GLint pname, GLint value);
};
}
