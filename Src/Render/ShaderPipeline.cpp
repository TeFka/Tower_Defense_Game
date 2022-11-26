
#include <Render/ShaderPipeline.h>

template<class verticeType>
ShaderPipeline<verticeType>::ShaderPipeline()
{
    this->type = TRIANGLES;
    std::vector<verticeType> newVertList;
    this->vertices.push_back(newVertList);
    std::vector<Texture*> newTextrList;
    this->activeTextures.push_back(newTextrList);

}

template<class verticeType>
ShaderPipeline<verticeType>::ShaderPipeline(std::vector<verticeInfo*> verticeDataInf)
{
    this->type = TRIANGLES;
}

template<class verticeType>
ShaderPipeline<verticeType>::ShaderPipeline(const char* vertexFile, const char* fragmentFile, int useGeometryShader, const char* geometryFile,
        std::vector<verticeInfo*> verticeDataInf)
{

    this->verticeDataInfo = verticeDataInf;
    this->theShader = new Shader(vertexFile, fragmentFile, useGeometryShader, geometryFile);

    this->type = TRIANGLES;

}

template<class verticeType>
ShaderPipeline<verticeType>::~ShaderPipeline()
{

    delete this->theShader;
    this->vertices.clear();
    this->verticeDataInfo.clear();

}

template<class verticeType>
void ShaderPipeline<verticeType>::setVerticeInfo(std::vector<verticeInfo*> verticeDataInf)
{

    this->verticeDataInfo = verticeDataInf;

}

template<class verticeType>
void ShaderPipeline<verticeType>::setSource(const char* vertexFile, const char* fragmentFile, int useGeometryShader, const char* geometryFile)
{

    this->theShader = new Shader(vertexFile, fragmentFile, useGeometryShader, geometryFile);

}

template<class verticeType>
void ShaderPipeline<verticeType>::setType(drawType newType)
{

    this->type = newType;
}

template<class verticeType>
void ShaderPipeline<verticeType>::setupVertex()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

}

template<class verticeType>
void ShaderPipeline<verticeType>::updateVertex(int verticesIndex)
{

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticeType)*this->vertices[verticesIndex].size(), this->vertices[verticesIndex].data(), GL_STATIC_DRAW);
    int runningSize = 0;
    if(this->verticeDataInfo[0]->dataType==1)
    {
        glVertexAttribIPointer(0, this->verticeDataInfo[0]->dataAmount, GL_UNSIGNED_INT,
                               sizeof(verticeType),
                               (void*)0);
        runningSize += sizeof(int)*this->verticeDataInfo[0]->dataAmount;
    }
    else if(this->verticeDataInfo[0]->dataType==2)
    {
        glVertexAttribPointer(0, this->verticeDataInfo[0]->dataAmount, GL_FLOAT, GL_FALSE,
                              sizeof(verticeType),
                              (void*)0);
        runningSize += sizeof(float)*this->verticeDataInfo[0]->dataAmount;
    }

    glEnableVertexAttribArray(0);
    for(int i = 1; i<this->verticeDataInfo.size(); i++)
    {
        glEnableVertexAttribArray(i);
        if(this->verticeDataInfo[i]->dataType==1)
        {
            glVertexAttribIPointer(i, this->verticeDataInfo[i]->dataAmount, GL_UNSIGNED_INT,
                                   sizeof(verticeType),
                                   (void*) runningSize);
            runningSize += sizeof(int)*this->verticeDataInfo[i]->dataAmount;
        }
        else if(this->verticeDataInfo[i]->dataType==2)
        {
            glVertexAttribPointer(i, this->verticeDataInfo[i]->dataAmount, GL_FLOAT, GL_FALSE,
                                  sizeof(verticeType),
                                  (void*) runningSize);
            runningSize += sizeof(float)*this->verticeDataInfo[i]->dataAmount;
        }
        glEnableVertexAttribArray(i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


template<class verticeType>
Texture* ShaderPipeline<verticeType>::getTexture(int index, int vertsIndex)
{

    return this->activeTextures[vertsIndex][index];

}

template<class verticeType>
void ShaderPipeline<verticeType>::setTexture(const char* file, int place, int type, int vertsIndex)
{

    if(type==1)
    {
        this->activeTextures[vertsIndex].push_back(new Texture(file,GL_TEXTURE_2D,place));
    }

}
template<class verticeType>
void ShaderPipeline<verticeType>::addTexture(Texture* newTexture, int vertsIndex)
{

    this->activeTextures[vertsIndex].push_back(newTexture);

}

template<class verticeType>
void ShaderPipeline<verticeType>::addTextureList()
{

    std::vector<Texture*> newTextrList;
    this->activeTextures.push_back(newTextrList);
}

template<class verticeType>
void ShaderPipeline<verticeType>::removeTextureList(int verticesIndex)
{
    if(this->activeTextures.size()>verticesIndex){
        this->activeTextures.erase(this->activeTextures.begin()+verticesIndex);
    }

}

template<class verticeType>
void ShaderPipeline<verticeType>::textureStage(int verticesIndex, bool useSubVBO)
{
    if(this->activeTextures.size()>verticesIndex){
        for(int i = 0; i<this->activeTextures[verticesIndex].size(); i++)
        {
            std::stringstream ms;
            std::string mIndex;
            ms<<i;
            mIndex=ms.str();
            this->theShader->set1i(this->activeTextures[verticesIndex][i]->getUnit(),("textr["+mIndex+"]").c_str());
            this->activeTextures[verticesIndex][i]->bindT();
        }
    }


}
template<class verticeType>
void ShaderPipeline<verticeType>::endTextureStage(int verticesIndex, bool useSubVBO)
{
    if(this->activeTextures.size()>verticesIndex){
        for(int i = 0; i<this->activeTextures[verticesIndex].size(); i++)
        {

            this->activeTextures[verticesIndex][i]->unBindT();
        }
    }
}

template<class verticeType>
void ShaderPipeline<verticeType>::use(int verticesIndex, bool useSubVBO)
{
    if(verticesIndex==0)
    {
        for(int i=0; i<this->vertices.size(); i++)
        {
            this->updateVertex(i);
            this->textureStage(i);
            glBindVertexArray(this->VAO);
            if(useSubVBO)
            {
                glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
                glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(verticeType)*this->vertices[i].size(),this->vertices[i].data());
            }
            this->theShader->use();

            if(this->type == TRIANGLES)
            {

                glDrawArrays(GL_TRIANGLES,0,this->vertices[i].size());

            }
            else if(this->type == POINTS)
            {

                glDrawArrays(GL_POINTS, 0, this->vertices[i].size());

            }
            this->endTextureStage(i);

        }
    }
    else
    {
        if(this->vertices.size()>verticesIndex-1){
            this->updateVertex(verticesIndex-1);
            this->textureStage(verticesIndex-1);
            glBindVertexArray(this->VAO);
            if(useSubVBO)
            {
                glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
                glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(verticeType)*this->vertices[verticesIndex-1].size(),this->vertices[verticesIndex-1].data());
            }
            this->theShader->use();

            if(this->type == TRIANGLES)
            {

                glDrawArrays(GL_TRIANGLES,0,this->vertices[verticesIndex-1].size());

            }
            else if(this->type == POINTS)
            {

                glDrawArrays(GL_POINTS, 0, this->vertices[verticesIndex-1].size());

            }
            this->endTextureStage(verticesIndex-1);
        }
    }
}

template<class verticeType>
void ShaderPipeline<verticeType>::clearVerts(int verticesIndex)
{
    if(verticesIndex==0)
    {
        for(int i=0; i<this->vertices.size(); i++)
        {
            this->vertices[i].clear();
        }
    }
    else
    {
        this->vertices[verticesIndex-1].clear();
    }

}

template<class verticeType>
Shader* ShaderPipeline<verticeType>::getShader()
{

    return this->theShader;
}

template<class verticeType>
int ShaderPipeline<verticeType>::getVerticesListSize()
{

    return this->vertices.size();
}

template<class verticeType>
int ShaderPipeline<verticeType>::getTextureListSize()
{

    return this->activeTextures.size();
}

template<class verticeType>
void ShaderPipeline<verticeType>::addVerticesList()
{

    std::vector<verticeType> newList;
    this->vertices.push_back(newList);

}

template<class verticeType>
void ShaderPipeline<verticeType>::addPipeline()
{

    this->addVerticesList();
    this->addTextureList();
}

template<class verticeType>
void ShaderPipeline<verticeType>::removePipeline(int verticesIndex)
{

    this->vertices.erase(this->vertices.begin()+verticesIndex);
    this->activeTextures.erase(this->activeTextures.begin()+verticesIndex);

}

template<class verticeType>
void ShaderPipeline<verticeType>::removeVerticesList(int verticesIndex)
{
    if(this->vertices.size()>verticesIndex){
        this->vertices.erase(this->vertices.begin()+verticesIndex);
    }

}

template<class verticeType>
void ShaderPipeline<verticeType>::addVertex(std::any newVert, int verticesIndex)
{

    this->vertices[verticesIndex].push_back(std::any_cast<verticeType>(newVert));

}

template<class verticeType>
int ShaderPipeline<verticeType>::getVerticeSize(int verticesIndex)
{

    return this->vertices[verticesIndex].size();

}

template<class verticeType>
std::any ShaderPipeline<verticeType>::getVertex(int index, int verticesIndex)
{

    return this->vertices[verticesIndex][index];

}
