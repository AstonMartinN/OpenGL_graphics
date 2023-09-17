#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "gl.h"

class ShaderProgramCore {
public:
    ShaderProgramCore() = default;
    ShaderProgramCore(const ShaderProgramCore &)=delete;
    ShaderProgramCore(ShaderProgramCore &&)=delete;
    ShaderProgramCore& operator=(const ShaderProgramCore &)=delete;
    ShaderProgramCore& operator=(ShaderProgramCore &&)=delete;
    ~ShaderProgramCore();

    GLuint const &get_program() { return m_program; }

protected:

    std::string read_file(std::string path);
    bool check_compile_error(GLuint shader);
    [[nodiscard]] GLuint compile_shader(GLuint type);
    virtual bool compile_program() = 0;

    GLuint m_program = 0u;
    std::string m_source_code{};
};

class ShaderProgram final : public ShaderProgramCore {
public:
    ShaderProgram() = default;
    ShaderProgram(std::string vs_path, std::string fs_path);
    ShaderProgram(const ShaderProgram &)=delete;
    ShaderProgram(ShaderProgram &&)=delete;
    ShaderProgram& operator=(const ShaderProgram &)=delete;
    ShaderProgram& operator=(ShaderProgram &&)=delete;
    ~ShaderProgram() = default;

    void set_paths(std::string vs_path, std::string fs_path);
    virtual bool compile_program();
private:
    std::string m_vs_path;
    std::string m_fs_path;
};

class ComputeShaderProgram final : public ShaderProgramCore {
public:
    ComputeShaderProgram() = default;
    ComputeShaderProgram(std::string path);
    ComputeShaderProgram(const ComputeShaderProgram &)=delete;
    ComputeShaderProgram(ComputeShaderProgram &&)=delete;
    ComputeShaderProgram& operator=(const ComputeShaderProgram &)=delete;
    ComputeShaderProgram& operator=(ComputeShaderProgram &&)=delete;
    ~ComputeShaderProgram() = default;

    void set_paths(std::string path);
    virtual bool compile_program();
private:
    std::string m_comp_path;
};

#endif // SHADER_H
