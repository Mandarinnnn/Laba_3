#ifndef LIGHTINGTECHNIQUE_H
#define LIGHTINGTECHNIQUE_H

#include "technique.h"
#include "math_3d.h"

struct DirectionLight
{
    Vector3f Color;//цвет
    float AmbientIntensity;///фоновая интенсивность, которая определяет насколько темный или яркий свет
    Vector3f Direction;//направление в виде 3 вектора, указываемое в мировом пространстве
    float DiffuseIntensity;//интенсивность
};

//LightingTechnique наследуется от Technique, и представляет собой инвентарь света, 
//используя основой функционал компиляции и линковки, которые предлагает базовый класс
class LightingTechnique : public Technique
{
public:
    LightingTechnique();
    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
    void SetWorldMatrix(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionLight& Light);

private:
    GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_samplerLocation;
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
    } m_dirLightLocation;
};

#endif
