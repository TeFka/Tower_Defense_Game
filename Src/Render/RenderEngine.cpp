#include "Render/RenderEngine.h"

#include "helpers/RootDir.h"

glm::vec4 vertices2D[6] =
{
    glm::vec4(-1.0,-1.0,0.0,0.0),
    glm::vec4(1.0,-1.0,1.0,0.0),
    glm::vec4(-1.0,1.0,0.0,1.0),
    glm::vec4(-1.0,1.0,0.0,1.0),
    glm::vec4(1.0,-1.0,1.0,0.0),
    glm::vec4(1.0,1.0,1.0,1.0)
};

void RenderEngine::frameBufferRez(GLFWwindow *window, int fbW, int fbH)
{
    glViewport(0,0, fbW, fbH);
}

void  RenderEngine::setGLFW(const char* windwName, const int width, const int height, const int majorVersion, const int minorVersion)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    this->windax = glfwCreateWindow(width, height, windwName, NULL, NULL);

    glfwGetFramebufferSize(windax, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(this->windax, frameBufferRez);

    glfwMakeContextCurrent(this->windax); //Important!!!!

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(this->windax, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
}

void  RenderEngine::enableModes()
{
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderEngine::setScreen()
{
    //rbo
    glGenRenderbuffers(1,&this->RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER,0);

    //FBOs
    glGenFramebuffers(1,&this->basicFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->basicFBO);
    //texture
    glGenTextures(1, &this->screenTexture);
    glBindTexture(GL_TEXTURE_2D,this->screenTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,this->windowWidth,this->windowHeight,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,this->screenTexture,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,this->RBO);
    unsigned int attachment = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &attachment);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"ERROR:FRAMEBUFFER1:Framebuffer is not complete!"<<std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    unsigned int mRBO;
    glGenRenderbuffers(1,&this->mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);
    unsigned int mFBO;
    glGenFramebuffers(1,&this->mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER,this->mFBO);
    unsigned int mFBOtext;
    glGenTextures(1,&this->mFBOtext);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,this->mFBOtext);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,this->windowWidth,this->windowHeight,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,this->mFBOtext,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,this->mRBO);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: multisample Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void  RenderEngine::updateDefaultUniforms()
{

    glBindBuffer(GL_UNIFORM_BUFFER,this->defaultUbo);
    glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(this->projectionMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(this->perspectiveProjectionMatrix));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

void  RenderEngine::updateViewport()
{

    glfwGetWindowSize(this->windax,&this->framebufferWidth,&this->framebufferHeight);
    if(this->windowWidth != this->framebufferWidth||this->windowHeight != this->framebufferHeight)
    {
        this->windowWidth = this->framebufferWidth;
        this->windowHeight = this->framebufferHeight;
        this->projectionMatrix = glm::ortho(0.0f, float(this->windowWidth),float(this->windowHeight),0.0f,-1.0f,1.0f);
        glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
        glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
        glBindRenderbuffer(GL_RENDERBUFFER,0);

        glBindTexture(GL_TEXTURE_2D,this->screenTexture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,this->windowWidth,this->windowHeight,0,GL_RGBA,GL_FLOAT,NULL);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,this->windowWidth,this->windowHeight);
        glBindRenderbuffer(GL_RENDERBUFFER,this->mRBO);

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,this->mFBOtext);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,this->windowWidth,this->windowHeight,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);
    }
}

RenderEngine::RenderEngine(const char* title,
                               const int windowW, const int windowH,
                               const int glMajor, const int glMinor,
                               std::string shareFolder)
{

    this->windowWidth = windowW;
    this->windowHeight = windowH;
    this->GLFWminorVersion = glMinor;
    this->GLFWminorVersion = glMajor;
    this->setGLFW(title, windowW, windowH, glMajor, glMinor);
    this->enableModes();
    this->theTexter = new TextManager(this);

    std::cout<<"window parameters: "<<this->windowWidth<<" "<<this->windowHeight<<std::endl;
    std::vector<verticeInfo*> testVertsInf = {new verticeInfo{2,2}};
    this->testShadProgram.setSource((shareFolder+this->defaultShaderNames[0]).c_str(),(shareFolder+this->defaultShaderNames[1]).c_str());
    this->testShadProgram.setVerticeInfo(testVertsInf);
    this->testShadProgram.setupVertex();
    this->shaderPrograms.push_back(&testShadProgram);

    this->shaderPrograms[0]->addVertex(glm::vec2(-0.5f, -0.5f));
    this->shaderPrograms[0]->addVertex(glm::vec2(0.5f, -0.5f));
    this->shaderPrograms[0]->addVertex(glm::vec2(0.0f,  0.5f));

    std::vector<verticeInfo*> screenVertsInf = {new verticeInfo{2,4}};
    this->screenShadProgram.setSource((shareFolder+this->defaultShaderNames[2]).c_str(),(shareFolder+this->defaultShaderNames[3]).c_str());
    this->screenShadProgram.setVerticeInfo(screenVertsInf);
    this->screenShadProgram.setupVertex();
    this->shaderPrograms.push_back(&screenShadProgram);

    this->shaderPrograms[1]->addVertex(glm::vec4(-1.0,-1.0,0.0,0.0));
    this->shaderPrograms[1]->addVertex(glm::vec4(1.0,-1.0,1.0,0.0));
    this->shaderPrograms[1]->addVertex(glm::vec4(-1.0,1.0,0.0,1.0));
    this->shaderPrograms[1]->addVertex(glm::vec4(-1.0,1.0,0.0,1.0));
    this->shaderPrograms[1]->addVertex(glm::vec4(1.0,-1.0,1.0,0.0));
    this->shaderPrograms[1]->addVertex(glm::vec4(1.0,1.0,1.0,1.0));

    std::vector<verticeInfo*> charVertsInf = {new verticeInfo{2,4}};
    this->charShadProgram.setSource((shareFolder+this->defaultShaderNames[4]).c_str(),(shareFolder+this->defaultShaderNames[5]).c_str());
    this->charShadProgram.setVerticeInfo(charVertsInf);
    this->charShadProgram.setupVertex();
    this->shaderPrograms.push_back(&charShadProgram);

    std::vector<verticeInfo*> basic2DVertsInf = {new verticeInfo{2,2},new verticeInfo{2,2},new verticeInfo{2,4},new verticeInfo{1,1}};
    this->basic2DShadProgram.setSource((shareFolder+this->defaultShaderNames[6]).c_str(),(shareFolder+this->defaultShaderNames[7]).c_str());
    this->basic2DShadProgram.setVerticeInfo(basic2DVertsInf);
    this->basic2DShadProgram.setupVertex();

    this->shaderPrograms.push_back(&basic2DShadProgram);

    std::vector<verticeInfo*> basic3DVertsInf = {new verticeInfo{2,3},new verticeInfo{2,2},new verticeInfo{2,4},new verticeInfo{1,1}};
    this->basic3DShadProgram.setSource((shareFolder+this->defaultShaderNames[8]).c_str(),(shareFolder+this->defaultShaderNames[9]).c_str());
    this->basic3DShadProgram.setVerticeInfo(basic3DVertsInf);
    this->basic3DShadProgram.setupVertex();

    this->shaderPrograms.push_back(&basic3DShadProgram);

    std::vector<verticeInfo*> basicTrans2DVertsInf = {new verticeInfo{2,2},new verticeInfo{2,2},new verticeInfo{2,4},new verticeInfo{1,1}};
    this->basicTransparent2DShadProgram.setSource((shareFolder+this->defaultShaderNames[6]).c_str(),(shareFolder+this->defaultShaderNames[7]).c_str());
    this->basicTransparent2DShadProgram.setVerticeInfo(basicTrans2DVertsInf);
    this->basicTransparent2DShadProgram.setupVertex();

    this->shaderPrograms.push_back(&basicTransparent2DShadProgram);

    std::vector<verticeInfo*> basicTrans3DVertsInf = {new verticeInfo{2,3},new verticeInfo{2,2},new verticeInfo{2,4},new verticeInfo{1,1}};
    this->basicTransparent3DShadProgram.setSource((shareFolder+this->defaultShaderNames[8]).c_str(),(shareFolder+this->defaultShaderNames[9]).c_str());
    this->basicTransparent3DShadProgram.setVerticeInfo(basicTrans3DVertsInf);
    this->basicTransparent3DShadProgram.setupVertex();

    this->shaderPrograms.push_back(&basicTransparent3DShadProgram);

    this->setScreen();

}
RenderEngine::~RenderEngine()
{

    glfwDestroyWindow(this->windax);
    glfwTerminate();
}

void RenderEngine::setDefaultShaderUniforms()
{
    glGenBuffers(1,&this->defaultUbo);
    glBindBuffer(GL_UNIFORM_BUFFER,this->defaultUbo);
    glBufferData(GL_UNIFORM_BUFFER,2*sizeof(glm::mat4),NULL,GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    glBindBufferRange(GL_UNIFORM_BUFFER,0,this->defaultUbo,0,2*sizeof(glm::mat4));

    for(int i=0; i<this->shaderPrograms.size(); i++)
    {
        this->shaderPrograms[i]->getShader()->setUb("defaultUBO",0);
    }

    this->projectionMatrix = glm::ortho(0.0f, float(this->windowWidth), 0.0f, float(this->windowHeight),-1.0f,1.0f);
    this->perspectiveProjectionMatrix = glm::perspective(glm::radians(45.0f), (float(this->windowWidth)/float(this->windowHeight)),0.1f,100.0f);

    this->updateDefaultUniforms();
    GLfloat offset = 1.0/300.0;
    GLfloat offsets[9][2]=
    {
        {-offset,offset},
        {0.0,offset},
        {offset,offset},
        {0.0,0.0},
        {offset,0.0},
        {offset,-offset},
        {0.0,-offset},
        {-offset,-offset},
        {-offset,0.0},
    };
    float edgeKernels[9]=
    {
        1,2,1,
        2,4,2,
        1,2,1
    };
    for(int i=0; i<9; i++)
    {
        std::stringstream ms;
        std::string daI;
        ms<<i;
        daI = ms.str();
        this->shaderPrograms[this->SCREEN_SHADER]->getShader()->set1i(edgeKernels[i],("edgeKern["+daI+"]").c_str());
        this->shaderPrograms[this->SCREEN_SHADER]->getShader()->set1f(edgeKernels[i]/16,("blurKern["+daI+"]").c_str());
    }
    this->shaderPrograms[this->SCREEN_SHADER]->getShader()->use();
    glUniform2fv(glGetUniformLocation(this->shaderPrograms[this->SCREEN_SHADER]->getShader()->id, "offsets"), 9, (GLfloat*)offsets);
    this->shaderPrograms[this->SCREEN_SHADER]->getShader()->set1i(0,"textr");

    this->shaderPrograms[this->CHAR_SHADER]->getShader()->set1i(0,"textur");
    this->updateDefaultUniforms();
}

void RenderEngine::addDefaultUboToShader(int index, bool fixed)
{

    if(fixed)
    {
        return this->shaderPrograms[index]->getShader()->setUb("defaultUBO",0);
    }
    else
    {
        return this->shaderPrograms[this->defaultShaderNum+index]->getShader()->setUb("defaultUBO",0);
    }

}

void RenderEngine::setUbo(const char* name, int index)
{

    for(int i=0; i<this->shaderPrograms.size(); i++)
    {
        this->shaderPrograms[i]->getShader()->setUb(name,index);
    }

}

void RenderEngine::setTextureToAll(const char* file, int place, int type, int vertsIndex)
{
    for(int i=0;i<this->shaderPrograms.size();i++){
        this->shaderPrograms[i]->setTexture(file, place, type, vertsIndex);
    }
}

void RenderEngine::addTextureToAll(Texture* newTexture, int vertsIndex)
{
    for(int i=0;i<this->shaderPrograms.size();i++){
        this->shaderPrograms[i]->addTexture(newTexture, vertsIndex);
    }
}

GLFWwindow* RenderEngine::getWindow()
{
    return this->windax;
}

AbstractPipeline* RenderEngine::getShaderProgram(int index, bool fixed)
{
    if(fixed)
    {
        return this->shaderPrograms[index];
    }
    else
    {
        return this->shaderPrograms[this->defaultShaderNum+index];
    }

}

TextManager* RenderEngine::getTextManager()
{

    return this->theTexter;

}

int RenderEngine::getWindowWidth()
{

    return this->windowWidth;
}

int RenderEngine::getWindowHeight()
{

    return this->windowHeight;
}

unsigned int RenderEngine::getMainFBO()
{

    return this->mFBO;
}

void RenderEngine::setBasic2DSprite(glm::vec2 pos, glm::vec2 siz, glm::vec4 color, int textN, bool relative, bool trasparent, int verticesIndex)
{
    if(relative)
    {
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2((pos.x-(siz.x*0.5))*this->windowWidth,(pos.y+siz.y/2)*this->windowHeight),glm::vec2(0.0,1.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2((pos.x-(siz.x*0.5))*this->windowWidth,(pos.y-siz.y/2)*this->windowHeight),glm::vec2(0.0,0.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2((pos.x+siz.x/2)*this->windowWidth,(pos.y-siz.y/2)*this->windowHeight),glm::vec2(1.0,0.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2((pos.x-(siz.x*0.5))*this->windowWidth,(pos.y+siz.y/2)*this->windowHeight),glm::vec2(0.0,1.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2((pos.x+siz.x/2)*this->windowWidth,(pos.y-siz.y/2)*this->windowHeight),glm::vec2(1.0,0.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2((pos.x+siz.x/2)*this->windowWidth,(pos.y+siz.y/2)*this->windowHeight),glm::vec2(1.0,1.0),color,textN}, verticesIndex);

    }
    else
    {
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(pos.x-(siz.x*0.5),pos.y+siz.y/2),glm::vec2(0.0,1.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(pos.x-(siz.x*0.5),pos.y-siz.y/2),glm::vec2(0.0,0.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(pos.x+siz.x/2,pos.y-siz.y/2),glm::vec2(1.0,0.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(pos.x-(siz.x*0.5),pos.y+siz.y/2),glm::vec2(0.0,1.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(pos.x+siz.x/2,pos.y-siz.y/2),glm::vec2(1.0,0.0),color,textN}, verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(pos.x+siz.x/2,pos.y+siz.y/2),glm::vec2(1.0,1.0),color,textN}, verticesIndex);
    }
}

void RenderEngine::setBasic3DSprite(glm::vec3 pos, glm::vec3 siz, glm::vec4 color, int textN, bool transparent, int verticesIndex)
{
    //positiveY
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+siz.y/2,
            pos.z-siz.z/2),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,1.0),
            color,textN}, verticesIndex);
    //negativeY

    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,1.0),
            color,textN}, verticesIndex);
    //positiveX
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+siz.x/2,
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,1.0),
            color,textN}, verticesIndex);

    //negativeX

    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,1.0),
            color,textN}, verticesIndex);
    //positiveZ

    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z+(siz.z*0.5)),
            glm::vec2(1.0,1.0),
            color,textN}, verticesIndex);
    //negaticeZ

    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x+(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(0.0,1.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y-(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,0.0),
            color,textN}, verticesIndex);
    this->shaderPrograms[BASIC_3D_SHADER]->addVertex(basic3DVertex{glm::vec3(pos.x-(siz.x*0.5),
            pos.y+(siz.y*0.5),
            pos.z-(siz.z*0.5)),
            glm::vec2(1.0,1.0),
            color,textN}, verticesIndex);
}

template<class T>
void RenderEngine::setCustomSprite(std::vector<T> spriteInfo, int shaderNum, int verticesIndex)
{

    for(int i = 0; i<spriteInfo.size(); i++)
    {

        this->shaderPrograms[shaderNum + this->defaultShaderNum]->addVertex(spriteInfo[i], verticesIndex);

    }

}

void RenderEngine::clearVerts(int index, bool fixed, int verticesIndex)
{
    if(fixed)
    {
        this->shaderPrograms[index]->clearVerts(verticesIndex);
    }
    else
    {
        this->shaderPrograms[this->defaultShaderNum+index]->clearVerts(verticesIndex);
    }

}

void RenderEngine::update()
{

    this->updateViewport();

}

void RenderEngine::renderBegin()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClearColor(1.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glViewport(0,0,this->windowWidth,this->windowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER,this->mFBO);
}

void RenderEngine::drawTest(int stage)
{
    std::cout<<"test0"<<std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glClearColor(0.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,this->windowWidth,this->windowHeight);

    if(stage == 0)
    {
        std::cout<<"vector test"<<std::endl;
        this->shaderPrograms[TEST_SHADER]->use();

    }
    else if(stage == 1)
    {
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(400, 300),glm::vec2(0.0, 0.0),glm::vec4(1.0, 0.0,0.0,1.0), 15});
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(800, 300),glm::vec2(0.0, 0.0),glm::vec4(0.0, 1.0,0.0,1.0), 15});
        this->shaderPrograms[BASIC_2D_SHADER]->addVertex(basic2DVertex{glm::vec2(600,  600),glm::vec2(0.0, 0.0),glm::vec4(0.0, 0.0,1.0,1.0), 15});
        std::cout<<"basic vertex test"<<std::endl;
        for(int b = 0; b<this->shaderPrograms[BASIC_2D_SHADER]->getVerticeSize(); b++)
        {
            std::cout<<std::any_cast<basic2DVertex>(this->shaderPrograms[BASIC_2D_SHADER]->getVertex(b)).pos.x<<"  "<<std::any_cast<basic2DVertex>(this->shaderPrograms[BASIC_2D_SHADER]->getVertex(b)).pos.y<<std::endl;
            std::cout<<(this->projectionMatrix*glm::vec4(std::any_cast<basic2DVertex>(this->shaderPrograms[BASIC_2D_SHADER]->getVertex(b)).pos,0.0,1.0)).x<<"  "<<(this->projectionMatrix*glm::vec4(std::any_cast<basic2DVertex>(this->shaderPrograms[BASIC_2D_SHADER]->getVertex(b)).pos,0.0,1.0)).y<<std::endl;
        }
        this->shaderPrograms[BASIC_2D_SHADER]->use();

    }

    this->theTexter->writeMessage("The Test", 0.5f, 0.8f, 2.0f, 1.0f, 0.2f, glm::vec3(1.0,0.0,0.0));

    std::cout<<"test done"<<std::endl;
    glfwSwapBuffers(this->windax);
    glFlush();
    glfwPollEvents();
    glBindVertexArray(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
}

void RenderEngine::drawBasic2D(bool useTransparent, int verticesIndex)
{
    //std::cout<<"drawing"<<std::endl;
    //blocks
    if(useTransparent)
    {
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        this->shaderPrograms[BASIC_TRANSPARENT_2D_SHADER]->textureStage(verticesIndex);
        this->shaderPrograms[BASIC_TRANSPARENT_2D_SHADER]->use(verticesIndex);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
    else
    {
        this->shaderPrograms[BASIC_2D_SHADER]->textureStage(verticesIndex);
        this->shaderPrograms[BASIC_2D_SHADER]->use(verticesIndex);
    }
    //std::cout<<" done drawing"<<std::endl;
}

void RenderEngine::drawBasic3D(bool useTransparent, int verticesIndex)
{
    //std::cout<<"drawing 3D"<<std::endl;
    //blocks
    if(useTransparent)
    {
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        this->shaderPrograms[BASIC_TRANSPARENT_3D_SHADER]->textureStage(verticesIndex);
        this->shaderPrograms[BASIC_TRANSPARENT_3D_SHADER]->use(verticesIndex);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
    else
    {
        this->shaderPrograms[BASIC_3D_SHADER]->textureStage(verticesIndex);
        this->shaderPrograms[BASIC_3D_SHADER]->use(verticesIndex);
    }
     //std::cout<<"done drawing 3D"<<std::endl;
}

void RenderEngine::drawCustom(int shaderIndex, bool tranparentDraw, int verticesIndex)
{

    if(tranparentDraw)
    {
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
    }

    this->shaderPrograms[this->defaultShaderNum + shaderIndex]->textureStage(verticesIndex);
    this->shaderPrograms[this->defaultShaderNum + shaderIndex]->use(verticesIndex);

    if(tranparentDraw)
    {
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }

}

void RenderEngine::updateScreen()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER,this->mFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,this->basicFBO);
    glBlitFramebuffer(0,0,this->windowWidth,this->windowHeight,0,0,this->windowWidth,this->windowHeight,GL_COLOR_BUFFER_BIT,GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClearColor(0.0,1.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,this->windowWidth,this->windowHeight);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,this->screenTexture);
    this->shaderPrograms[this->SCREEN_SHADER]->use();
}

void RenderEngine::renderEnd()
{
    glfwSwapBuffers(this->windax);
    glFlush();
    glfwPollEvents();
    glBindVertexArray(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D,0);
    glUseProgram(0);
}

