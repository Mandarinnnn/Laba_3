#include <iostream>
#include "texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_pImage = NULL;
}

bool Texture::Load()
{
    try {
        m_pImage = new Magick::Image(m_fileName);//инициализаци€ свойства класса типа Magick::Image использу€ им€ файла текстуры
                                                 //этот вызов загружает текстуру в пам€ть, котора€ задана private и не может быть напр€мую использована OpenGL
        m_pImage->write(&m_blob, "RGBA");//записываем изображение в объект Magick::Blob, использу€ формат RGBA 
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &m_textureObj);//эта функци€ генерирует указанное число объектов текстур и помещает их в указатель на массив GLuint
    glBindTexture(m_textureTarget, m_textureObj);//ќна сообщает OpenGL объект текстуры, который относитс€ ко всем вызовам, св€занным с текстурами, до тех пор, 
                                                 //пока новый объект текстур не будет передан
    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());//первый параметр - позици€
            //второй - уровень детализации, третий - формат, в котором OpenGL хранит текстуру, 4,5 - ширина и высота в тексел€х, 6 - рамка, 7,8,9 - формат, тип и адрес в пам€ти
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//указываем фильтры, которые будут использованы дл€ увеличени€ и минимализации.
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);//прив€зываем объект текстур к модулю
}