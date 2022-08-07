#ifndef SHADERPROGRAM_H_INCLUDED
#define SHADERPROGRAM_H_INCLUDED

#include <any>
#include <Render/Shader.h>
#include <Render/Texture.h>

struct verticeInfo
{

    int dataType;
    int dataAmount;

};

enum drawType{

    TRIANGLES,
    POINTS

};

class AbstractPipeline
{
public:

    virtual void setSource(const char* vert, const char* frag, int useGeom, const char* geom) = 0;

    virtual void setType(drawType) = 0;

    virtual void setupVertex() = 0;
    virtual void updateVertex(int=0) = 0;

    virtual Texture* getTexture(int, int=0) = 0;
    virtual void setTexture(const char*, int, int, int=0) = 0;
    virtual void addTexture(Texture*, int=0) = 0;
    virtual void addTextureList() = 0;
    virtual void removeTextureList(int) = 0;
    virtual void textureStage(int=0, bool=false) = 0;
    virtual void endTextureStage(int=0, bool=false) = 0;

    virtual void use(int=1, bool = false) = 0;

    virtual void clearVerts(int=1) = 0;

    virtual Shader* getShader() = 0;

    virtual int getVerticesListSize() = 0;
    virtual int getTextureListSize() = 0;

    virtual void addVerticesList() = 0;

    virtual void addPipeline() = 0;
    virtual void removePipeline(int) = 0;

    virtual void removeVerticesList(int) = 0;

    virtual void addVertex(std::any vert, int=0) = 0;

    virtual int getVerticeSize(int=0) = 0;

    virtual std::any getVertex(int index, int=0) = 0;
};

template<class verticeType>
class ShaderPipeline : public AbstractPipeline
{

private:

    Shader* theShader;

    std::vector<std::vector<Texture*>> activeTextures;
    std::vector<std::vector<verticeType>> vertices;

    unsigned int VAO;
    unsigned int VBO;

    drawType type;

    std::vector<verticeInfo*> verticeDataInfo;

public:

    ShaderPipeline();

    ShaderPipeline(std::vector<verticeInfo*>);

    ShaderPipeline(const char*, const char*, int, const char*,
                   std::vector<verticeInfo*>);

    ~ShaderPipeline();

    void setVerticeInfo(std::vector<verticeInfo*>);

    void setSource(const char*, const char*, int=0, const char* = "");

    void setType(drawType);

    void setupVertex();
    void updateVertex(int=0);

    Texture* getTexture(int, int=0);
    void setTexture(const char*, int, int, int=0);
    void addTexture(Texture*, int=0);
    void addTextureList();
    void removeTextureList(int);
    void textureStage(int=0, bool=false);
    void endTextureStage(int=0, bool=false);

    void use(int = 1, bool = false);

    void clearVerts(int=1);

    Shader* getShader();
    int getVerticesListSize();
    int getTextureListSize();

    void addVerticesList();

    void addPipeline();
    void removePipeline(int);

    void removeVerticesList(int);

    void addVertex(std::any, int=0);

    int getVerticeSize(int);

    std::any getVertex(int,int=0);
};

#endif // SHADERPROGRAM_H_INCLUDED
