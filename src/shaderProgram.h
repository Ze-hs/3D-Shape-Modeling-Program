#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {

        // create shader
        GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

        // load shader source from file
        std::string vs = loadShaderSrc(vertexShaderPath);
        const char* vss = vs.c_str();
        std::string fs = loadShaderSrc(fragmentShaderPath);
        const char* fss = fs.c_str();

        // specify shader source
        glShaderSource(vertID, 1, &(vss), NULL);
        glShaderSource(fragID, 1, &(fss), NULL);

        // compile the shader
        glCompileShader(vertID);
        glCompileShader(fragID);

        // create program and attach shaders
        ID = glCreateProgram();
        glAttachShader(ID, vertID);
        glAttachShader(ID, fragID);

        // link the program
        glLinkProgram(ID);
    }
    // activate the shader
    // ------------------------------------------------------------------------

    void use()
    {
        glUseProgram(ID);
    }

    void setVec3(const char *name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name), x, y, z);
    }

private:
    std::string loadShaderSrc(const std::string& filename) {
        std::ifstream is(filename);
        if (is.is_open()) {
            std::stringstream buffer;
            buffer << is.rdbuf();
            return buffer.str();
        }
        std::cerr << "Unable to open file " << filename << std::endl;
        exit(1);
    }
};
