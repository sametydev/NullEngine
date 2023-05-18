#pragma once

#pragma comment(lib, "opengl32")
//#define GL_GLEXT_PROTOTYPES 1

#include <GL\glcorearb.h>
//#include <GL\glext.h>
#include <GL\wglext.h>
#include <GL\GL.h> //[GL_VERSION_1_1]
#include <stdio.h>
#include <stdlib.h>

#define GL_EXT_PROC(type, func) \
do{\
	char buf[128]; \
	if(func) { \
		sprintf_s(buf, "file : %s\nline : %d\n%s's already exist.", __FILE__, __LINE__, #func); \
		if(MessageBox(NULL, buf, "Error", MB_OK)) exit(0); \
	}\
    func = (type)wglGetProcAddress(#func);\
	if(!func) { \
		sprintf_s(buf, "file : %s\nline : %d\n%s's failed to load.", __FILE__, __LINE__, #func); \
		if(MessageBox(NULL, buf, "Error", MB_OK)) exit(0); \
	}\
}while(false)

//[GL_VERSION_1_2]
GLAPI PFNGLDRAWRANGEELEMENTSPROC	_glDrawRangeElements;
#define glDrawRangeElements			_glDrawRangeElements

//[GL_VERSION_1_3]
GLAPI PFNGLACTIVETEXTUREPROC		_glActiveTexture;
#define glActiveTexture				_glActiveTexture

//[GL_VERSION_1_4]
GLAPI PFNGLMULTIDRAWARRAYSPROC		_glMultiDrawArrays;
GLAPI PFNGLMULTIDRAWELEMENTSPROC	_glMultiDrawElements;
GLAPI PFNGLBLENDCOLORPROC			_glBlendColor;
GLAPI PFNGLBLENDEQUATIONPROC		_glBlendEquation;
#define glMultiDrawArrays			_glMultiDrawArrays
#define glMultiDrawElements			_glMultiDrawElements
#define glBlendColor				_glBlendColor
#define glBlendEquation				_glBlendEquation

//[GL_VERSION_1_5]
GLAPI PFNGLGENQUERIESPROC			_glGenQueries;
GLAPI PFNGLDELETEQUERIESPROC		_glDeleteQueries;
GLAPI PFNGLISQUERYPROC				_glIsQuery;
GLAPI PFNGLBINDBUFFERPROC			_glBindBuffer;
GLAPI PFNGLDELETEBUFFERSPROC		_glDeleteBuffers;
GLAPI PFNGLGENBUFFERSPROC			_glGenBuffers;
GLAPI PFNGLISBUFFERPROC				_glIsBuffer;
GLAPI PFNGLBUFFERDATAPROC			_glBufferData;
GLAPI PFNGLBUFFERSUBDATAPROC		_glBufferSubData;
GLAPI PFNGLGETBUFFERSUBDATAPROC		_glGetBufferSubData;
GLAPI PFNGLMAPBUFFERPROC			_glMapBuffer;
GLAPI PFNGLUNMAPBUFFERPROC			_glUnmapBuffer;
GLAPI PFNGLGETBUFFERPARAMETERIVPROC	_glGetBufferParameteriv;
GLAPI PFNGLGETBUFFERPOINTERVPROC	_glGetBufferPointerv;
#define glGenQueries			    _glGenQueries
#define glDeleteQueries			    _glDeleteQueries
#define glIsQuery				    _glIsQuery
#define glBindBuffer			    _glBindBuffer
#define glDeleteBuffers			    _glDeleteBuffers
#define glGenBuffers			    _glGenBuffers
#define glIsBuffer				    _glIsBuffer
#define glBufferData			    _glBufferData
#define glBufferSubData			    _glBufferSubData
#define glGetBufferSubData		    _glGetBufferSubData
#define glMapBuffer				    _glMapBuffer
#define glUnmapBuffer			    _glUnmapBuffer
#define glGetBufferParameteriv	    _glGetBufferParameteriv
#define glGetBufferPointerv		    _glGetBufferPointerv

//[GL_VERSION_2_0]
GLAPI PFNGLDRAWBUFFERPROC					_glDrawBuffers;
GLAPI PFNGLATTACHSHADERPROC					_glAttachShader;
GLAPI PFNGLBINDATTRIBLOCATIONPROC			_glBindAttribLocation;
GLAPI PFNGLCOMPILESHADERPROC				_glCompileShader;
GLAPI PFNGLCREATEPROGRAMPROC				_glCreateProgram;
GLAPI PFNGLCREATESHADERPROC					_glCreateShader;
GLAPI PFNGLDELETEPROGRAMPROC				_glDeleteProgram;
GLAPI PFNGLDELETESHADERPROC					_glDeleteShader;
GLAPI PFNGLDETACHSHADERPROC					_glDetachShader;
GLAPI PFNGLDISABLEVERTEXATTRIBARRAYPROC		_glDisableVertexAttribArray;
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC		_glEnableVertexAttribArray;
GLAPI PFNGLGETACTIVEATTRIBPROC				_glGetActiveAttrib;
GLAPI PFNGLGETACTIVEUNIFORMPROC				_glGetActiveUniform;
GLAPI PFNGLGETATTACHEDSHADERSPROC			_glGetAttachedShaders;
GLAPI PFNGLGETATTRIBLOCATIONPROC			_glGetAttribLocation;
GLAPI PFNGLGETPROGRAMIVPROC					_glGetProgramiv;
GLAPI PFNGLGETPROGRAMINFOLOGPROC			_glGetProgramInfoLog;
GLAPI PFNGLGETSHADERIVPROC					_glGetShaderiv;
GLAPI PFNGLGETSHADERINFOLOGPROC				_glGetShaderInfoLog;
GLAPI PFNGLGETSHADERSOURCEPROC				_glGetShaderSource;
GLAPI PFNGLGETUNIFORMLOCATIONPROC			_glGetUniformLocation;
GLAPI PFNGLGETUNIFORMFVPROC					_glGetUniformfv;
GLAPI PFNGLGETUNIFORMIVPROC					_glGetUniformiv;
GLAPI PFNGLGETVERTEXATTRIBDVPROC			_glGetVertexAttribdv;
GLAPI PFNGLGETVERTEXATTRIBPOINTERVPROC		_glGetVertexAttribPointerv;
GLAPI PFNGLGETVERTEXATTRIBFVPROC			_glGetVertexAttribfv;
GLAPI PFNGLGETVERTEXATTRIBIVPROC			_glGetVertexAttribiv;
GLAPI PFNGLLINKPROGRAMPROC					_glLinkProgram;
GLAPI PFNGLSHADERSOURCEPROC					_glShaderSource;
GLAPI PFNGLUSEPROGRAMPROC					_glUseProgram;
GLAPI PFNGLUNIFORM1FPROC					_glUniform1f;
GLAPI PFNGLUNIFORM2FPROC					_glUniform2f;
GLAPI PFNGLUNIFORM3FPROC					_glUniform3f;
GLAPI PFNGLUNIFORM4FPROC					_glUniform4f;
GLAPI PFNGLUNIFORM1IPROC					_glUniform1i;
GLAPI PFNGLUNIFORM2IPROC					_glUniform2i;
GLAPI PFNGLVERTEXATTRIBPOINTERPROC          _glVertexAttribPointer;
#define glDrawBuffers						_glDrawBuffers
#define glAttachShader						_glAttachShader
#define glBindAttribLocation				_glBindAttribLocation
#define glCompileShader						_glCompileShader
#define glCreateProgram						_glCreateProgram
#define glCreateShader						_glCreateShader
#define glDeleteProgram						_glDeleteProgram
#define glDeleteShader						_glDeleteShader
#define glDetachShader						_glDetachShader
#define glDisableVertexAttribArray			_glDisableVertexAttribArray
#define glEnableVertexAttribArray			_glEnableVertexAttribArray
#define glGetActiveAttrib					_glGetActiveAttrib
#define glGetActiveUniform					_glGetActiveUniform
#define glGetAttachedShaders				_glGetAttachedShaders
#define glGetAttribLocation					_glGetAttribLocation
#define glGetProgramiv						_glGetProgramiv
#define glGetProgramInfoLog					_glGetProgramInfoLog
#define glGetShaderiv						_glGetShaderiv
#define glGetShaderInfoLog					_glGetShaderInfoLog
#define glGetShaderSource					_glGetShaderSource
#define glGetUniformLocation				_glGetUniformLocation
#define glGetUniformfv						_glGetUniformfv
#define glGetUniformiv						_glGetUniformiv
#define glGetVertexAttribdv					_glGetVertexAttribdv
#define glGetVertexAttribPointerv			_glGetVertexAttribPointerv
#define glGetVertexAttribfv					_glGetVertexAttribfv
#define glGetVertexAttribiv					_glGetVertexAttribiv
#define glLinkProgram						_glLinkProgram
#define glShaderSource						_glShaderSource
#define glUseProgram						_glUseProgram
#define glUniform1f							_glUniform1f
#define glUniform2f							_glUniform2f
#define glUniform3f							_glUniform3f
#define glUniform4f							_glUniform4f
#define glUniform1i							_glUniform1i
#define glUniform2i							_glUniform2i
#define glVertexAttribPointer				_glVertexAttribPointer

//[GL_VERSION_3_0]
GLAPI PFNGLBINDBUFFERRANGEPROC				_glBindBufferRange;
GLAPI PFNGLBINDBUFFERBASEPROC				_glBindBufferBase;
GLAPI PFNGLGETUNIFORMUIVPROC				_glGetUniformuiv;
GLAPI PFNGLISRENDERBUFFERPROC				_glIsRenderbuffer;
GLAPI PFNGLBINDRENDERBUFFERPROC				_glBindRenderbuffer;
GLAPI PFNGLDELETERENDERBUFFERSPROC			_glDeleteRenderbuffers;
GLAPI PFNGLGENRENDERBUFFERSPROC				_glGenRenderbuffers;
GLAPI PFNGLRENDERBUFFERSTORAGEPROC			_glRenderbufferStorage;
GLAPI PFNGLGETRENDERBUFFERPARAMETERIVPROC	_glGetRenderbufferParameteriv;
GLAPI PFNGLISFRAMEBUFFERPROC				_glIsFramebuffer;
GLAPI PFNGLBINDFRAMEBUFFERPROC				_glBindFramebuffer;
GLAPI PFNGLDELETEFRAMEBUFFERSPROC			_glDeleteFramebuffers;
GLAPI PFNGLGENFRAMEBUFFERSPROC				_glGenFramebuffers;
GLAPI PFNGLCHECKFRAMEBUFFERSTATUSPROC		_glCheckFramebufferStatus;
GLAPI PFNGLFRAMEBUFFERRENDERBUFFERPROC		_glFramebufferRenderbuffer;
GLAPI PFNGLGENERATEMIPMAPPROC				_glGenerateMipmap;
GLAPI PFNGLBLITFRAMEBUFFERPROC				_glBlitFramebuffer;
GLAPI PFNGLBINDVERTEXARRAYPROC				_glBindVertexArray;
GLAPI PFNGLDELETEVERTEXARRAYSPROC			_glDeleteVertexArrays;
GLAPI PFNGLGENVERTEXARRAYSPROC				_glGenVertexArrays;
GLAPI PFNGLMAPBUFFERRANGEPROC				_glMapBufferRange;
#define glBindBufferRange					_glBindBufferRange
#define glBindBufferBase					_glBindBufferBase
#define glGetUniformuiv						_glGetUniformuiv
#define glIsRenderbuffer					_glIsRenderbuffer
#define glBindRenderbuffer					_glBindRenderbuffer
#define glDeleteRenderbuffers				_glDeleteRenderbuffers
#define glGenRenderbuffers					_glGenRenderbuffers
#define glRenderbufferStorage				_glRenderbufferStorage
#define glGetRenderbufferParameteriv		_glGetRenderbufferParameteriv
#define glIsFramebuffer						_glIsFramebuffer
#define glBindFramebuffer					_glBindFramebuffer
#define glDeleteFramebuffers				_glDeleteFramebuffers
#define glGenFramebuffers					_glGenFramebuffers
#define glCheckFramebufferStatus			_glCheckFramebufferStatus
#define glFramebufferRenderbuffer			_glFramebufferRenderbuffer
#define glGenerateMipmap					_glGenerateMipmap
#define glBlitFramebuffer					_glBlitFramebuffer
#define glBindVertexArray					_glBindVertexArray
#define glDeleteVertexArrays				_glDeleteVertexArrays
#define glGenVertexArrays					_glGenVertexArrays
#define glMapBufferRange					_glMapBufferRange

//[GL_VERSION_3_1]
GLAPI PFNGLDRAWARRAYSINSTANCEDPROC			_glDrawArraysInstanced;
GLAPI PFNGLDRAWELEMENTSINSTANCEDPROC		_glDrawElementsInstanced;
GLAPI PFNGLTEXBUFFERPROC					_glTexBuffer;
GLAPI PFNGLPRIMITIVERESTARTINDEXPROC		_glPrimitiveRestartIndex;
GLAPI PFNGLCOPYBUFFERSUBDATAPROC			_glCopyBufferSubData;
#define glDrawArraysInstanced				_glDrawArraysInstanced
#define glDrawElementsInstanced				_glDrawElementsInstanced
#define glTexBuffer							_glTexBuffer
#define glPrimitiveRestartIndex				_glPrimitiveRestartIndex
#define glCopyBufferSubData					_glCopyBufferSubData

//[GL_VERSION_3_2]
GLAPI PFNGLFRAMEBUFFERTEXTUREPROC           _glFramebufferTexture;
#define glFramebufferTexture                _glFramebufferTexture

//[GL_VERSION_3_3]
GLAPI PFNGLGENSAMPLERSPROC					_glGenSamplers;
GLAPI PFNGLDELETESAMPLERSPROC				_glDeleteSamplers;
GLAPI PFNGLISSAMPLERPROC					_glIsSampler;
GLAPI PFNGLBINDSAMPLERPROC					_glBindSampler;
GLAPI PFNGLVERTEXATTRIBDIVISORPROC			_glVertexAttribDivisor;
#define glGenSamplers						_glGenSamplers
#define glDeleteSamplers					_glDeleteSamplers
#define glIsSampler							_glIsSampler
#define glBindSampler						_glBindSampler
#define glVertexAttribDivisor				_glVertexAttribDivisor

//[GL_VERSION_4_0]
GLAPI PFNGLDRAWARRAYSINDIRECTPROC			_glDrawArraysIndirect;
GLAPI PFNGLDRAWELEMENTSINDIRECTPROC			_glDrawElementsIndirect;
#define glDrawArraysIndirect				_glDrawArraysIndirect
#define glDrawElementsIndirect				_glDrawElementsIndirect

//[GL_VERSION_4_1]
GLAPI PFNGLRELEASESHADERCOMPILERPROC		_glReleaseShaderCompiler;
GLAPI PFNGLSHADERBINARYPROC					_glShaderBinary;
GLAPI PFNGLGETSHADERPRECISIONFORMATPROC		_glGetShaderPrecisionFormat;
GLAPI PFNGLDEPTHRANGEFPROC					_glDepthRangef;
GLAPI PFNGLCLEARDEPTHFPROC					_glClearDepthf;
GLAPI PFNGLGETPROGRAMBINARYPROC				_glGetProgramBinary;
GLAPI PFNGLPROGRAMBINARYPROC				_glProgramBinary;
GLAPI PFNGLPROGRAMPARAMETERIPROC			_glProgramParameteri;
GLAPI PFNGLUSEPROGRAMSTAGESPROC				_glUseProgramStages;
GLAPI PFNGLACTIVESHADERPROGRAMPROC			_glActiveShaderProgram;
GLAPI PFNGLCREATESHADERPROGRAMVPROC			_glCreateShaderProgramv;
GLAPI PFNGLBINDPROGRAMPIPELINEPROC			_glBindProgramPipeline;
GLAPI PFNGLDELETEPROGRAMPIPELINESPROC		_glDeleteProgramPipelines;
GLAPI PFNGLGENPROGRAMPIPELINESPROC			_glGenProgramPipelines;
GLAPI PFNGLISPROGRAMPIPELINEPROC			_glIsProgramPipeline;
GLAPI PFNGLGETPROGRAMPIPELINEIVPROC			_glGetProgramPipelineiv;
GLAPI PFNGLVALIDATEPROGRAMPIPELINEPROC		_glValidateProgramPipeline;
GLAPI PFNGLGETPROGRAMPIPELINEINFOLOGPROC	_glGetProgramPipelineInfoLog;
#define glReleaseShaderCompiler				_glReleaseShaderCompiler
#define glShaderBinary						_glShaderBinary
#define glGetShaderPrecisionFormat			_glGetShaderPrecisionFormat
#define glDepthRangef						_glDepthRangef
#define glClearDepthf						_glClearDepthf
#define glGetProgramBinary					_glGetProgramBinary
#define glProgramBinary						_glProgramBinary
#define glProgramParameteri					_glProgramParameteri
#define glUseProgramStages					_glUseProgramStages
#define glActiveShaderProgram				_glActiveShaderProgram
#define glCreateShaderProgramv				_glCreateShaderProgramv
#define glBindProgramPipeline				_glBindProgramPipeline
#define glDeleteProgramPipelines			_glDeleteProgramPipelines
#define glGenProgramPipelines				_glGenProgramPipelines
#define glIsProgramPipeline					_glIsProgramPipeline
#define glGetProgramPipelineiv				_glGetProgramPipelineiv
#define glValidateProgramPipeline			_glValidateProgramPipeline
#define glGetProgramPipelineInfoLog			_glGetProgramPipelineInfoLog

//[GL_VERSION_4_2]
GLAPI PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC				_glDrawArraysInstancedBaseInstance;
GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC			_glDrawElementsInstancedBaseInstance;
GLAPI PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC	_glDrawElementsInstancedBaseVertexBaseInstance;
GLAPI PFNGLGETINTERNALFORMATIVPROC							_glGetInternalformativ;
GLAPI PFNGLMEMORYBARRIERPROC								_glMemoryBarrier;
GLAPI PFNGLTEXSTORAGE2DPROC									_glTexStorage2D;
#define glDrawArraysInstancedBaseInstance					_glDrawArraysInstancedBaseInstance
#define glDrawElementsInstancedBaseInstance					_glDrawElementsInstancedBaseInstance
#define glDrawElementsInstancedBaseVertexBaseInstance		_glDrawElementsInstancedBaseVertexBaseInstance
#define glGetInternalformativ								_glGetInternalformativ
#define glMemoryBarrier										_glMemoryBarrier
#define glTexStorage2D										_glTexStorage2D
														   
//[GL_VERSION_4_3]
GLAPI PFNGLCLEARBUFFERDATAPROC					_glClearBufferData;
GLAPI PFNGLCLEARBUFFERSUBDATAPROC				_glClearBufferSubData;
GLAPI PFNGLDISPATCHCOMPUTEPROC					_glDispatchCompute;
GLAPI PFNGLDISPATCHCOMPUTEINDIRECTPROC			_glDispatchComputeIndirect;
GLAPI PFNGLCOPYIMAGESUBDATAPROC					_glCopyImageSubData;
GLAPI PFNGLFRAMEBUFFERPARAMETERIPROC			_glFramebufferParameteri;
GLAPI PFNGLGETFRAMEBUFFERPARAMETERIVPROC		_glGetFramebufferParameteriv;
GLAPI PFNGLGETINTERNALFORMATI64VPROC			_glGetInternalformati64v;
GLAPI PFNGLINVALIDATETEXSUBIMAGEPROC			_glInvalidateTexSubImage;
GLAPI PFNGLINVALIDATETEXIMAGEPROC				_glInvalidateTexImage;
GLAPI PFNGLINVALIDATEBUFFERSUBDATAPROC			_glInvalidateBufferSubData;
GLAPI PFNGLINVALIDATEBUFFERDATAPROC				_glInvalidateBufferData;
GLAPI PFNGLINVALIDATEFRAMEBUFFERPROC			_glInvalidateFramebuffer;
GLAPI PFNGLINVALIDATESUBFRAMEBUFFERPROC			_glInvalidateSubFramebuffer;
GLAPI PFNGLMULTIDRAWARRAYSINDIRECTPROC			_glMultiDrawArraysIndirect;
GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTPROC		_glMultiDrawElementsIndirect;
GLAPI PFNGLGETPROGRAMINTERFACEIVPROC			_glGetProgramInterfaceiv;
GLAPI PFNGLGETPROGRAMRESOURCEINDEXPROC			_glGetProgramResourceIndex;
GLAPI PFNGLGETPROGRAMRESOURCENAMEPROC			_glGetProgramResourceName;
GLAPI PFNGLGETPROGRAMRESOURCEIVPROC				_glGetProgramResourceiv;
GLAPI PFNGLGETPROGRAMRESOURCELOCATIONPROC		_glGetProgramResourceLocation;
GLAPI PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC	_glGetProgramResourceLocationIndex;
GLAPI PFNGLSHADERSTORAGEBLOCKBINDINGPROC		_glShaderStorageBlockBinding;
GLAPI PFNGLTEXBUFFERRANGEPROC					_glTexBufferRange;
GLAPI PFNGLTEXSTORAGE2DMULTISAMPLEPROC			_glTexStorage2DMultisample;
GLAPI PFNGLTEXSTORAGE3DMULTISAMPLEPROC			_glTexStorage3DMultisample;
GLAPI PFNGLTEXTUREVIEWPROC						_glTextureView;
GLAPI PFNGLBINDVERTEXBUFFERPROC					_glBindVertexBuffer;
GLAPI PFNGLVERTEXATTRIBFORMATPROC				_glVertexAttribFormat;
GLAPI PFNGLVERTEXATTRIBIFORMATPROC				_glVertexAttribIFormat;
GLAPI PFNGLVERTEXATTRIBLFORMATPROC				_glVertexAttribLFormat;
GLAPI PFNGLVERTEXATTRIBBINDINGPROC				_glVertexAttribBinding;
GLAPI PFNGLVERTEXBINDINGDIVISORPROC				_glVertexBindingDivisor;
GLAPI PFNGLDEBUGMESSAGECONTROLPROC				_glDebugMessageControl;
GLAPI PFNGLDEBUGMESSAGEINSERTPROC				_glDebugMessageInsert;
GLAPI PFNGLDEBUGMESSAGECALLBACKPROC				_glDebugMessageCallback;
GLAPI PFNGLGETDEBUGMESSAGELOGPROC				_glGetDebugMessageLog;
GLAPI PFNGLPUSHDEBUGGROUPPROC					_glPushDebugGroup;
GLAPI PFNGLPOPDEBUGGROUPPROC					_glPopDebugGroup;
GLAPI PFNGLOBJECTLABELPROC						_glObjectLabel;
GLAPI PFNGLGETOBJECTLABELPROC					_glGetObjectLabel;
GLAPI PFNGLOBJECTPTRLABELPROC					_glObjectPtrLabel;
GLAPI PFNGLGETOBJECTPTRLABELPROC				_glGetObjectPtrLabel;
#define glClearBufferData 						_glClearBufferData 
#define glClearBufferSubData 					_glClearBufferSubData 
#define glDispatchCompute 						_glDispatchCompute 
#define glDispatchComputeIndirect 				_glDispatchComputeIndirect 
#define glCopyImageSubData 						_glCopyImageSubData 
#define glFramebufferParameteri 				_glFramebufferParameteri 
#define glGetFramebufferParameteriv 			_glGetFramebufferParameteriv 
#define glGetInternalformati64v					_glGetInternalformati64v
#define glInvalidateTexSubImage					_glInvalidateTexSubImage
#define glInvalidateTexImage					_glInvalidateTexImage
#define glInvalidateBufferSubData				_glInvalidateBufferSubData
#define glInvalidateBufferData					_glInvalidateBufferData
#define glInvalidateFramebuffer					_glInvalidateFramebuffer
#define glInvalidateSubFramebuffer				_glInvalidateSubFramebuffer
#define glMultiDrawArraysIndirect				_glMultiDrawArraysIndirect
#define glMultiDrawElementsIndirect				_glMultiDrawElementsIndirect
#define glGetProgramInterfaceiv					_glGetProgramInterfaceiv
#define glGetProgramResourceIndex				_glGetProgramResourceIndex
#define glGetProgramResourceName				_glGetProgramResourceName
#define glGetProgramResourceiv					_glGetProgramResourceiv
#define glGetProgramResourceLocation			_glGetProgramResourceLocation
#define glGetProgramResourceLocationIndex		_glGetProgramResourceLocationIndex
#define glShaderStorageBlockBinding				_glShaderStorageBlockBinding
#define glTexBufferRange						_glTexBufferRange
#define glTexStorage2DMultisample				_glTexStorage2DMultisample
#define glTexStorage3DMultisample				_glTexStorage3DMultisample
#define glTextureView							_glTextureView
#define glBindVertexBuffer						_glBindVertexBuffer
#define glVertexAttribFormat					_glVertexAttribFormat
#define glVertexAttribIFormat					_glVertexAttribIFormat
#define glVertexAttribLFormat					_glVertexAttribLFormat
#define glVertexAttribBinding					_glVertexAttribBinding
#define glVertexBindingDivisor					_glVertexBindingDivisor
#define glDebugMessageControl					_glDebugMessageControl
#define glDebugMessageInsert					_glDebugMessageInsert
#define glDebugMessageCallback					_glDebugMessageCallback
#define glGetDebugMessageLog					_glGetDebugMessageLog
#define glPushDebugGroup						_glPushDebugGroup
#define glPopDebugGroup							_glPopDebugGroup
#define glObjectLabel							_glObjectLabel
#define glGetObjectLabel						_glGetObjectLabel
#define glObjectPtrLabel						_glObjectPtrLabel
#define glGetObjectPtrLabel						_glGetObjectPtrLabel

//[GL_VERSION_4_4]
GLAPI PFNGLBUFFERSTORAGEPROC			_glBufferStorage;
GLAPI PFNGLCLEARTEXIMAGEPROC			_glClearTexImage;
GLAPI PFNGLCLEARTEXSUBIMAGEPROC 		_glClearTexSubImage;
GLAPI PFNGLBINDBUFFERSBASEPROC			_glBindBuffersBase;
GLAPI PFNGLBINDBUFFERSRANGEPROC 		_glBindBuffersRange;
GLAPI PFNGLBINDTEXTURESPROC				_glBindTextures;
GLAPI PFNGLBINDSAMPLERSPROC				_glBindSamplers;
GLAPI PFNGLBINDIMAGETEXTURESPROC		_glBindImageTextures;
GLAPI PFNGLBINDVERTEXBUFFERSPROC		_glBindVertexBuffers;
#define glBufferStorage					_glBufferStorage
#define glClearTexImage					_glClearTexImage
#define glClearTexSubImage				_glClearTexSubImage
#define glBindBuffersBase				_glBindBuffersBase
#define glBindBuffersRange				_glBindBuffersRange
#define glBindTextures					_glBindTextures
#define glBindSamplers					_glBindSamplers
#define glBindImageTextures				_glBindImageTextures
#define glBindVertexBuffers				_glBindVertexBuffers

//[GL_VERSION_4_5]
GLAPI PFNGLCLIPCONTROLPROC								_glClipControl;
GLAPI PFNGLCREATETRANSFORMFEEDBACKSPROC					_glCreateTransformFeedbacks;
GLAPI PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC				_glTransformFeedbackBufferBase;
GLAPI PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC				_glTransformFeedbackBufferRange;
GLAPI PFNGLGETTRANSFORMFEEDBACKIVPROC					_glGetTransformFeedbackiv;
GLAPI PFNGLGETTRANSFORMFEEDBACKI_VPROC					_glGetTransformFeedbacki_v;
GLAPI PFNGLGETTRANSFORMFEEDBACKI64_VPROC				_glGetTransformFeedbacki64_v;
GLAPI PFNGLCREATEBUFFERSPROC							_glCreateBuffers;
GLAPI PFNGLNAMEDBUFFERSTORAGEPROC						_glNamedBufferStorage;
GLAPI PFNGLNAMEDBUFFERDATAPROC							_glNamedBufferData;
GLAPI PFNGLNAMEDBUFFERSUBDATAPROC						_glNamedBufferSubData;
GLAPI PFNGLCOPYNAMEDBUFFERSUBDATAPROC					_glCopyNamedBufferSubData;
GLAPI PFNGLCLEARNAMEDBUFFERDATAPROC						_glClearNamedBufferData;
GLAPI PFNGLCLEARNAMEDBUFFERSUBDATAPROC					_glClearNamedBufferSubData;
GLAPI PFNGLMAPNAMEDBUFFERPROC							_glMapNamedBuffer;
GLAPI PFNGLMAPNAMEDBUFFERRANGEPROC						_glMapNamedBufferRange;
GLAPI PFNGLUNMAPNAMEDBUFFERPROC							_glUnmapNamedBuffer;
GLAPI PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC				_glFlushMappedNamedBufferRange;
GLAPI PFNGLGETNAMEDBUFFERPARAMETERIVPROC				_glGetNamedBufferParameteriv;
GLAPI PFNGLGETNAMEDBUFFERPARAMETERI64VPROC				_glGetNamedBufferParameteri64v;
GLAPI PFNGLGETNAMEDBUFFERPOINTERVPROC					_glGetNamedBufferPointerv;
GLAPI PFNGLGETNAMEDBUFFERSUBDATAPROC					_glGetNamedBufferSubData;
GLAPI PFNGLCREATEFRAMEBUFFERSPROC						_glCreateFramebuffers;
GLAPI PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC				_glNamedFramebufferRenderbuffer;
GLAPI PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC				_glNamedFramebufferParameteri;
GLAPI PFNGLNAMEDFRAMEBUFFERTEXTUREPROC					_glNamedFramebufferTexture;
GLAPI PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC				_glNamedFramebufferTextureLayer;
GLAPI PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC				_glNamedFramebufferDrawBuffer;
GLAPI PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC				_glNamedFramebufferDrawBuffers;
GLAPI PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC				_glNamedFramebufferReadBuffer;
GLAPI PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC			_glInvalidateNamedFramebufferData;
GLAPI PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC		_glInvalidateNamedFramebufferSubData;
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERIVPROC					_glClearNamedFramebufferiv;
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC					_glClearNamedFramebufferuiv;
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERFVPROC					_glClearNamedFramebufferfv;
GLAPI PFNGLCLEARNAMEDFRAMEBUFFERFIPROC					_glClearNamedFramebufferfi;
GLAPI PFNGLBLITNAMEDFRAMEBUFFERPROC						_glBlitNamedFramebuffer;
GLAPI PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC				_glCheckNamedFramebufferStatus;
GLAPI PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC			_glGetNamedFramebufferParameteriv;
GLAPI PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC	_glGetNamedFramebufferAttachmentParameteriv;
GLAPI PFNGLCREATERENDERBUFFERSPROC						_glCreateRenderbuffers;
GLAPI PFNGLNAMEDRENDERBUFFERSTORAGEPROC					_glNamedRenderbufferStorage;
GLAPI PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC		_glNamedRenderbufferStorageMultisample;
GLAPI PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC			_glGetNamedRenderbufferParameteriv;
GLAPI PFNGLCREATETEXTURESPROC							_glCreateTextures;
GLAPI PFNGLTEXTUREBUFFERPROC							_glTextureBuffer;
GLAPI PFNGLTEXTUREBUFFERRANGEPROC						_glTextureBufferRange;
GLAPI PFNGLTEXTURESTORAGE1DPROC							_glTextureStorage1D;
GLAPI PFNGLTEXTURESTORAGE2DPROC							_glTextureStorage2D;
GLAPI PFNGLTEXTURESTORAGE3DPROC							_glTextureStorage3D;
GLAPI PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC				_glTextureStorage2DMultisample;
GLAPI PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC				_glTextureStorage3DMultisample;
GLAPI PFNGLTEXTURESUBIMAGE1DPROC						_glTextureSubImage1D;
GLAPI PFNGLTEXTURESUBIMAGE2DPROC						_glTextureSubImage2D;
GLAPI PFNGLTEXTURESUBIMAGE3DPROC						_glTextureSubImage3D;
GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC				_glCompressedTextureSubImage1D;
GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC				_glCompressedTextureSubImage2D;
GLAPI PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC				_glCompressedTextureSubImage3D;
GLAPI PFNGLCOPYTEXTURESUBIMAGE1DPROC					_glCopyTextureSubImage1D;
GLAPI PFNGLCOPYTEXTURESUBIMAGE2DPROC					_glCopyTextureSubImage2D;
GLAPI PFNGLCOPYTEXTURESUBIMAGE3DPROC					_glCopyTextureSubImage3D;
GLAPI PFNGLTEXTUREPARAMETERFPROC						_glTextureParameterf;
GLAPI PFNGLTEXTUREPARAMETERFVPROC						_glTextureParameterfv;
GLAPI PFNGLTEXTUREPARAMETERIPROC						_glTextureParameteri;
GLAPI PFNGLTEXTUREPARAMETERIIVPROC						_glTextureParameterIiv;
GLAPI PFNGLTEXTUREPARAMETERIUIVPROC						_glTextureParameterIuiv;
GLAPI PFNGLTEXTUREPARAMETERIVPROC						_glTextureParameteriv;
GLAPI PFNGLGENERATETEXTUREMIPMAPPROC					_glGenerateTextureMipmap;
GLAPI PFNGLBINDTEXTUREUNITPROC							_glBindTextureUnit;
GLAPI PFNGLGETTEXTUREIMAGEPROC							_glGetTextureImage;
GLAPI PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC				_glGetCompressedTextureImage;
GLAPI PFNGLGETTEXTURELEVELPARAMETERFVPROC				_glGetTextureLevelParameterfv;
GLAPI PFNGLGETTEXTURELEVELPARAMETERIVPROC				_glGetTextureLevelParameteriv;
GLAPI PFNGLGETTEXTUREPARAMETERFVPROC					_glGetTextureParameterfv;
GLAPI PFNGLGETTEXTUREPARAMETERIIVPROC					_glGetTextureParameterIiv;
GLAPI PFNGLGETTEXTUREPARAMETERIUIVPROC					_glGetTextureParameterIuiv;
GLAPI PFNGLGETTEXTUREPARAMETERIVPROC					_glGetTextureParameteriv;
GLAPI PFNGLCREATEVERTEXARRAYSPROC						_glCreateVertexArrays;
GLAPI PFNGLDISABLEVERTEXARRAYATTRIBPROC					_glDisableVertexArrayAttrib;
GLAPI PFNGLENABLEVERTEXARRAYATTRIBPROC					_glEnableVertexArrayAttrib;
GLAPI PFNGLVERTEXARRAYELEMENTBUFFERPROC					_glVertexArrayElementBuffer;
GLAPI PFNGLVERTEXARRAYVERTEXBUFFERPROC					_glVertexArrayVertexBuffer;
GLAPI PFNGLVERTEXARRAYVERTEXBUFFERSPROC					_glVertexArrayVertexBuffers;
GLAPI PFNGLVERTEXARRAYATTRIBBINDINGPROC					_glVertexArrayAttribBinding;
GLAPI PFNGLVERTEXARRAYATTRIBFORMATPROC					_glVertexArrayAttribFormat;
GLAPI PFNGLVERTEXARRAYATTRIBIFORMATPROC					_glVertexArrayAttribIFormat;
GLAPI PFNGLVERTEXARRAYATTRIBLFORMATPROC					_glVertexArrayAttribLFormat;
GLAPI PFNGLVERTEXARRAYBINDINGDIVISORPROC				_glVertexArrayBindingDivisor;
GLAPI PFNGLGETVERTEXARRAYIVPROC							_glGetVertexArrayiv;
GLAPI PFNGLGETVERTEXARRAYINDEXEDIVPROC					_glGetVertexArrayIndexediv;
GLAPI PFNGLGETVERTEXARRAYINDEXED64IVPROC				_glGetVertexArrayIndexed64iv;
GLAPI PFNGLCREATESAMPLERSPROC							_glCreateSamplers;
GLAPI PFNGLCREATEPROGRAMPIPELINESPROC					_glCreateProgramPipelines;
GLAPI PFNGLCREATEQUERIESPROC							_glCreateQueries;
GLAPI PFNGLGETQUERYBUFFEROBJECTI64VPROC					_glGetQueryBufferObjecti64v;
GLAPI PFNGLGETQUERYBUFFEROBJECTIVPROC					_glGetQueryBufferObjectiv;
GLAPI PFNGLGETQUERYBUFFEROBJECTUI64VPROC				_glGetQueryBufferObjectui64v;
GLAPI PFNGLGETQUERYBUFFEROBJECTUIVPROC					_glGetQueryBufferObjectuiv;
GLAPI PFNGLMEMORYBARRIERBYREGIONPROC					_glMemoryBarrierByRegion;
GLAPI PFNGLGETTEXTURESUBIMAGEPROC						_glGetTextureSubImage;
GLAPI PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC				_glGetCompressedTextureSubImage;
GLAPI PFNGLGETGRAPHICSRESETSTATUSPROC					_glGetGraphicsResetStatus;
GLAPI PFNGLGETNCOMPRESSEDTEXIMAGEPROC					_glGetnCompressedTexImage;
GLAPI PFNGLGETNTEXIMAGEPROC								_glGetnTexImage;
GLAPI PFNGLGETNUNIFORMDVPROC							_glGetnUniformdv;
GLAPI PFNGLGETNUNIFORMFVPROC							_glGetnUniformfv;
GLAPI PFNGLGETNUNIFORMIVPROC							_glGetnUniformiv;
GLAPI PFNGLGETNUNIFORMUIVPROC							_glGetnUniformuiv;
GLAPI PFNGLREADNPIXELSPROC								_glReadnPixels;
GLAPI PFNGLTEXTUREBARRIERPROC							_glTextureBarrier;
#define glClipControl									_glClipControl
#define glCreateTransformFeedbacks						_glCreateTransformFeedbacks
#define glTransformFeedbackBufferBase					_glTransformFeedbackBufferBase
#define glTransformFeedbackBufferRange					_glTransformFeedbackBufferRange
#define glGetTransformFeedbackiv						_glGetTransformFeedbackiv
#define glGetTransformFeedbacki_v						_glGetTransformFeedbacki_v
#define glGetTransformFeedbacki64_v						_glGetTransformFeedbacki64_v
#define glCreateBuffers									_glCreateBuffers
#define glNamedBufferStorage							_glNamedBufferStorage
#define glNamedBufferData								_glNamedBufferData
#define glNamedBufferSubData							_glNamedBufferSubData
#define glCopyNamedBufferSubData						_glCopyNamedBufferSubData
#define glClearNamedBufferData							_glClearNamedBufferData
#define glClearNamedBufferSubData						_glClearNamedBufferSubData
#define glMapNamedBuffer								_glMapNamedBuffer
#define glMapNamedBufferRange							_glMapNamedBufferRange
#define glUnmapNamedBuffer								_glUnmapNamedBuffer
#define glFlushMappedNamedBufferRange					_glFlushMappedNamedBufferRange
#define glGetNamedBufferParameteriv						_glGetNamedBufferParameteriv
#define glGetNamedBufferParameteri64v					_glGetNamedBufferParameteri64v
#define glGetNamedBufferPointerv						_glGetNamedBufferPointerv
#define glGetNamedBufferSubData							_glGetNamedBufferSubData
#define glCreateFramebuffers							_glCreateFramebuffers
#define glNamedFramebufferRenderbuffer					_glNamedFramebufferRenderbuffer
#define glNamedFramebufferParameteri					_glNamedFramebufferParameteri
#define glNamedFramebufferTexture						_glNamedFramebufferTexture
#define glNamedFramebufferTextureLayer					_glNamedFramebufferTextureLayer
#define glNamedFramebufferDrawBuffer					_glNamedFramebufferDrawBuffer
#define glNamedFramebufferDrawBuffers					_glNamedFramebufferDrawBuffers
#define glNamedFramebufferReadBuffer					_glNamedFramebufferReadBuffer
#define glInvalidateNamedFramebufferData				_glInvalidateNamedFramebufferData
#define glInvalidateNamedFramebufferSubData				_glInvalidateNamedFramebufferSubData
#define glClearNamedFramebufferiv						_glClearNamedFramebufferiv
#define glClearNamedFramebufferuiv						_glClearNamedFramebufferuiv
#define glClearNamedFramebufferfv						_glClearNamedFramebufferfv
#define glClearNamedFramebufferfi						_glClearNamedFramebufferfi
#define glBlitNamedFramebuffer							_glBlitNamedFramebuffer
#define glCheckNamedFramebufferStatus					_glCheckNamedFramebufferStatus
#define glGetNamedFramebufferParameteriv				_glGetNamedFramebufferParameteriv
#define glGetNamedFramebufferAttachmentParameteriv		_glGetNamedFramebufferAttachmentParameteriv
#define glCreateRenderbuffers							_glCreateRenderbuffers
#define glNamedRenderbufferStorage						_glNamedRenderbufferStorage
#define glNamedRenderbufferStorageMultisample			_glNamedRenderbufferStorageMultisample
#define glGetNamedRenderbufferParameteriv				_glGetNamedRenderbufferParameteriv
#define glCreateTextures								_glCreateTextures
#define glTextureBuffer									_glTextureBuffer
#define glTextureBufferRange							_glTextureBufferRange
#define glTextureStorage1D								_glTextureStorage1D
#define glTextureStorage2D								_glTextureStorage2D
#define glTextureStorage3D								_glTextureStorage3D
#define glTextureStorage2DMultisample					_glTextureStorage2DMultisample
#define glTextureStorage3DMultisample					_glTextureStorage3DMultisample
#define glTextureSubImage1D								_glTextureSubImage1D
#define glTextureSubImage2D								_glTextureSubImage2D
#define glTextureSubImage3D								_glTextureSubImage3D
#define glCompressedTextureSubImage1D					_glCompressedTextureSubImage1D
#define glCompressedTextureSubImage2D					_glCompressedTextureSubImage2D
#define glCompressedTextureSubImage3D					_glCompressedTextureSubImage3D
#define glCopyTextureSubImage1D							_glCopyTextureSubImage1D
#define glCopyTextureSubImage2D							_glCopyTextureSubImage2D
#define glCopyTextureSubImage3D							_glCopyTextureSubImage3D
#define glTextureParameterf								_glTextureParameterf
#define glTextureParameterfv							_glTextureParameterfv
#define glTextureParameteri								_glTextureParameteri
#define glTextureParameterIiv							_glTextureParameterIiv
#define glTextureParameterIuiv							_glTextureParameterIuiv
#define glTextureParameteriv							_glTextureParameteriv
#define glGenerateTextureMipmap							_glGenerateTextureMipmap
#define glBindTextureUnit								_glBindTextureUnit
#define glGetTextureImage								_glGetTextureImage
#define glGetCompressedTextureImage						_glGetCompressedTextureImage
#define glGetTextureLevelParameterfv					_glGetTextureLevelParameterfv
#define glGetTextureLevelParameteriv					_glGetTextureLevelParameteriv
#define glGetTextureParameterfv							_glGetTextureParameterfv
#define glGetTextureParameterIiv						_glGetTextureParameterIiv
#define glGetTextureParameterIuiv						_glGetTextureParameterIuiv
#define glGetTextureParameteriv							_glGetTextureParameteriv
#define glCreateVertexArrays							_glCreateVertexArrays
#define glDisableVertexArrayAttrib						_glDisableVertexArrayAttrib
#define glEnableVertexArrayAttrib						_glEnableVertexArrayAttrib
#define glVertexArrayElementBuffer						_glVertexArrayElementBuffer
#define glVertexArrayVertexBuffer						_glVertexArrayVertexBuffer
#define glVertexArrayVertexBuffers						_glVertexArrayVertexBuffers
#define glVertexArrayAttribBinding						_glVertexArrayAttribBinding
#define glVertexArrayAttribFormat						_glVertexArrayAttribFormat
#define glVertexArrayAttribIFormat						_glVertexArrayAttribIFormat
#define glVertexArrayAttribLFormat						_glVertexArrayAttribLFormat
#define glVertexArrayBindingDivisor						_glVertexArrayBindingDivisor
#define glGetVertexArrayiv								_glGetVertexArrayiv
#define glGetVertexArrayIndexediv						_glGetVertexArrayIndexediv
#define glGetVertexArrayIndexed64iv						_glGetVertexArrayIndexed64iv
#define glCreateSamplers								_glCreateSamplers
#define glCreateProgramPipelines						_glCreateProgramPipelines
#define glCreateQueries									_glCreateQueries
#define glGetQueryBufferObjecti64v						_glGetQueryBufferObjecti64v
#define glGetQueryBufferObjectiv						_glGetQueryBufferObjectiv
#define glGetQueryBufferObjectui64v						_glGetQueryBufferObjectui64v
#define glGetQueryBufferObjectuiv						_glGetQueryBufferObjectuiv
#define glMemoryBarrierByRegion							_glMemoryBarrierByRegion
#define glGetTextureSubImage							_glGetTextureSubImage
#define glGetCompressedTextureSubImage					_glGetCompressedTextureSubImage
#define glGetGraphicsResetStatus						_glGetGraphicsResetStatus
#define glGetnCompressedTexImage						_glGetnCompressedTexImage
#define glGetnTexImage									_glGetnTexImage
#define glGetnUniformdv									_glGetnUniformdv
#define glGetnUniformfv									_glGetnUniformfv
#define glGetnUniformiv									_glGetnUniformiv
#define glGetnUniformuiv								_glGetnUniformuiv
#define glReadnPixels									_glReadnPixels
#define glTextureBarrier								_glTextureBarrier

//[GL_VERSION_4_6]
GLAPI PFNGLSPECIALIZESHADERPROC					_glSpecializeShader;
GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC		_glMultiDrawArraysIndirectCount;
GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC	_glMultiDrawElementsIndirectCount;
GLAPI PFNGLPOLYGONOFFSETCLAMPPROC				_glPolygonOffsetClamp;
#define glSpecializeShader						_glSpecializeShader
#define glMultiDrawArraysIndirectCount			_glMultiDrawArraysIndirectCount
#define glMultiDrawElementsIndirectCount		_glMultiDrawElementsIndirectCount
#define glPolygonOffsetClamp					_glPolygonOffsetClamp

//[WGLEXT]
GLAPI PFNWGLCHOOSEPIXELFORMATARBPROC			_wglChoosePixelFormatARB;
GLAPI PFNWGLCREATECONTEXTATTRIBSARBPROC         _wglCreateContextAttribsARB;
GLAPI PFNWGLMAKECONTEXTCURRENTARBPROC			_wglMakeContextCurrentARB;
#define wglChoosePixelFormatARB					_wglChoosePixelFormatARB
#define wglCreateContextAttribsARB				_wglCreateContextAttribsARB
#define wglMakeContextCurrentARB 				_wglMakeContextCurrentARB

namespace GL {
	void Load_GL_VERSION_1_2();
	void Load_GL_VERSION_1_3();
	void Load_GL_VERSION_1_4();
	void Load_GL_VERSION_1_5();
	void Load_GL_VERSION_2_0();
	void Load_GL_VERSION_3_0();
	void Load_GL_VERSION_3_1();
	void Load_GL_VERSION_3_2();
	void Load_GL_VERSION_3_3();
	void Load_GL_VERSION_4_0();
	void Load_GL_VERSION_4_1();
	void Load_GL_VERSION_4_2();
	void Load_GL_VERSION_4_3();
	void Load_GL_VERSION_4_4();
	void Load_GL_VERSION_4_5();
	void Load_GL_VERSION_4_6();
	void Load_WGLEXT();
	void LoadGLExtension();
}