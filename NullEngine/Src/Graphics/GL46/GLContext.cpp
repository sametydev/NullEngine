#include <PCH.h>
#include <Graphics/GL46/GLContext.h>
#include <Graphics/GL46/GLConfig.h>

GLContext::GLContext(int cx, int cy, HWND hwnd) : Context(cx,cy,hwnd),mDC(nullptr),mRC(nullptr)
{
	mApiType = GraphicAPI::OpenGL46;
    GL::LoadGLExtension();
    CreateDevice();
}

GLContext::~GLContext()
{
    if (!mHwnd) return;
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(mRC);
    ReleaseDC(mHwnd, mDC);
}

void GLContext::CreateDevice()
{
	mDC = GetDC(mHwnd);

	if (WGL_ARB_create_context && WGL_ARB_pixel_format)
	{
		LOG << "-- Support WGL ARB Extension" << ENDL;
        int pixelFormatAttribs[] =
        {
            WGL_SUPPORT_OPENGL_ARB,        GL_TRUE,
            WGL_COLOR_BITS_ARB,            32,
            WGL_DEPTH_BITS_ARB,            24,
            WGL_STENCIL_BITS_ARB,        8,
            WGL_DOUBLE_BUFFER_ARB,        GL_TRUE,
            0
        };

        float pixelFormatFloatAttribs[] = { 0.0f };

        int contextAttribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,
            WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            WGL_CONTEXT_RELEASE_BEHAVIOR_ARB, WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB,
            0
        };

        int pixelFormat;
        int numFormats;
        if (!wglChoosePixelFormatARB(mDC, pixelFormatAttribs,
            pixelFormatFloatAttribs, 1, &pixelFormat, (unsigned int*)&numFormats))
        {
            LOG_ERROR("failed to find pixel format from attribs");
        }

        PIXELFORMATDESCRIPTOR pfd{};        //get more infomation of pixel format
        DescribePixelFormat(mDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

        if (!SetPixelFormat(mDC, pixelFormat, &pfd)) {
            LOG_ERROR("failed to set pixel format");
        }


        mRC = wglCreateContextAttribsARB(mDC, 0, contextAttribs);

        wglMakeCurrent(mDC, mRC);

        const char* version = (char*)glGetString(GL_VERSION);
        const char* vendor = (char*)glGetString(GL_VENDOR);
        const char* hardware = (char*)glGetString(GL_RENDERER);
        const char* glslVer = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

        char apiInfo[128]{};
        sprintf_s(apiInfo, "--API  : OpenGL %s\nGLSL : %s\nHW   : %s\n", version, glslVer, hardware);
        printf(apiInfo);
        if (GL_ARB_clip_control) {
            //https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_clip_control.txt
            glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

            glDepthRange(0.0f, 1.0f);
        }
        if (GL_ARB_direct_state_access) {
            printf("--DSA is supported\n");
        }

       
        wglSwapIntervalEXT(mVSync ? 1 : 0);
    
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        glEnable(GL_STENCIL_TEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

	}
}

void GLContext::ClearBuffer(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLContext::SwapBuffer()
{
    if (mDC)
    {
        SwapBuffers(mDC);
    }
}

void GLContext::ResizeRenderBuffer(uint cx, uint cy)
{
    glViewport(0, 0, cx, cy);
}
