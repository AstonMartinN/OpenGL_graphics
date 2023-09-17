#include "shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "gl.h"

/*
    SHADER CORE
*/

ShaderProgramCore::~ShaderProgramCore() {
    if(m_program != 0u) {
        glDeleteProgram(m_program);
    }
}

std::string ShaderProgramCore::read_file(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Shader::readFile - " << path << " not open" << std::endl;
    }
    std::stringstream fileBuffer;
    fileBuffer << file.rdbuf();

    return fileBuffer.str();
}

bool ShaderProgramCore::check_compile_error(GLuint sh) {
    GLint success;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(sh, 512, NULL, infoLog);
        std::cout << "ShaderCore::checkCompileError "<< infoLog << std::endl;
        return false;
    }
    return true;
}

/*
    SHADER
*/

ShaderProgram::ShaderProgram(std::string vs_path, std::string fs_path) {
    m_vs_path = vs_path;
    m_fs_path = fs_path;
}

void ShaderProgram::set_paths(std::string vs_path, std::string fs_path) {
    m_vs_path = vs_path;
    m_fs_path = fs_path;
}

bool ShaderProgram::compile_program() {
    // vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    m_source_code = read_file(m_vs_path);
    const char * vs_source = m_source_code.c_str();
    glShaderSource(vertex_shader, 1, (GLchar * const *)&vs_source, nullptr);
    glCompileShader(vertex_shader);
    if (!check_compile_error(vertex_shader)) {
        std::cout << "vertex shader " << m_vs_path << " compilation failed" << std::endl;
        return false;
    }

    // fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    m_source_code = read_file(m_fs_path);
    const char * fs_source = m_source_code.c_str();
    glShaderSource(fragment_shader, 1, (GLchar * const *)&fs_source, nullptr);
    glCompileShader(fragment_shader);
    if (!check_compile_error(fragment_shader)) {
        std::cout << "fragment shader " << m_fs_path << " compilation failed" << std::endl;
        return false;
    }

    // linc shader
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);
    glLinkProgram(m_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return true;
}

/*
    COMPUTE SHADER
*/

ComputeShaderProgram::ComputeShaderProgram(std::string path){
    m_comp_path = path;
}

void ComputeShaderProgram::set_paths(std::string path){
    m_comp_path = path;
}

bool ComputeShaderProgram::compile_program() {
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    m_source_code = read_file(m_comp_path);
    const char * compSource = m_source_code.c_str();
    glShaderSource(compute_shader, 1, (GLchar * const *)&compSource, nullptr);
    glCompileShader(compute_shader);
    if(!check_compile_error(compute_shader)){
        return false;
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, compute_shader);
    glLinkProgram(m_program);

    glDeleteShader(compute_shader);

    return true;
}
