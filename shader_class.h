#pragma once

#include <string>

class Shader
{
   public:
    unsigned ID;

    Shader(const char* vertShader, const char* fragShader);
    ~Shader();
    void cleanup();

    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};
