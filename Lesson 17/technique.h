#ifndef TEXHNIQUE_H
#define TEXHNIQUE_H

#include <GL/glew.h>
#include <list>
//Technique оборачивает основной функционал внутри себ€ и позвол€ет наследуемым классам сфокусироватьс€ только на главной задаче 
class Technique
{
public:
    Technique();
    ~Technique();
    virtual bool Init();
    void Enable();//Enable() выполн€ет glUseProgram()

protected:
    bool AddShader(GLenum ShaderType, const char* pShaderText);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

private:
    GLuint m_shaderProg;
    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif
