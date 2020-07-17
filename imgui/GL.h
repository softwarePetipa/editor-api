#ifndef petipa_gl_h_included
#define petipa_gl_h_included

#ifdef __APPLE__
#include <SDL_opengles2.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/egl.h>
#include <GLES/glplatform.h>
#endif

#endif
