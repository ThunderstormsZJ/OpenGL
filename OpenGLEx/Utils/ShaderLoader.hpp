#pragma once
#ifndef ShaderLoader_HPP

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include "Logger.hpp"

namespace Utils {
	// 清除字符串前后空格
	inline std::string trim(const std::string& str, const std::string& spaces = " \t\r\n")
	{
		size_t a = str.find_first_not_of(spaces);
		size_t b = str.find_last_not_of(spaces) + 1;
		if (b <= a) {
			return std::string();
		}
		return str.substr(a, b - a);
	}

	class ShaderLoader
	{
	public:
		// source 行类型
		enum class line_mode
		{
			GLSL_CODE,              // 代码，包括注释、空行等
			GLSL_VERSION,           // 版本信息
			GLSL_INCLUDE,           // 引用。可以是 "" 或者 <>，都只检索主源码目录
		};

		// 源码行
		struct glsl_line
		{
			enum class line_mode mode;         // 行模式
			std::string source;     // 源

			glsl_line(line_mode m = line_mode::GLSL_CODE, const std::string& str = std::string()) :
				mode(m),
				source(str)
			{

			}
		};

		// 源码
		struct glsl_source
		{
			std::string filename;
			std::string version;
			bool included;
			std::vector<glsl_line> lines;
			glsl_source* parent;

			glsl_source()
			{
				included = false;
				parent = NULL;
			}
		};
	protected:
		// shader 源码行
		struct shader_line
		{
			const glsl_source* source;
			size_t line;

			shader_line(const glsl_source* src, size_t n) : source(src), line(n)
			{
			}
		};

		typedef std::map<std::string, glsl_source>::iterator iterator;

		std::map<std::string, glsl_source> m_sources;   // 加载的所有源码
		std::vector<shader_line> m_lines;               // shader 最终源码结构
		std::vector<char> m_log_buffer;                 // 错误日志缓冲

	protected:
#pragma region private
		// 释放
		void dispose()
		{
			m_sources.clear();
			m_lines.clear();
		}

		// 创建 source
		glsl_source* create_source(const std::string& filename)
		{
			glsl_source* source = &m_sources.insert(std::make_pair(filename, glsl_source())).first->second;
			source->filename = filename;
			return source;
		}

		int load_source(const std::string& filename, glsl_source* main = NULL) {
			using namespace std;

			glsl_source* source;

			// 检查是否已经加载过
			source = find_source(filename);
			if (source) {
				return 0;
			}

			// 打开文件
			std::ifstream in(filename);

			//in.exceptions(ifstream::failbit || ifstream::badbit);

			if (in.fail()) {
				Logger.Instance->error("ShaderLoader> file({}) open failed.", filename);
				return -1;
			}
			else {
				Logger.Instance->info("ShaderLoader> load source({}).", filename);
			}

			// 创建 map 对象
			source = create_source(filename);

			// 解析目录
			string dir = filename.substr(0, filename.find_last_of("/\\") + 1);

			string line;
			string tag;
			size_t pos;

			// 建立父级索引
			if (main != NULL) {
				source->version = main->version;
				source->parent = main;
			}

			// 解析文件
			while (getline(in, line)) {

				if (line.empty()) {
					source->lines.push_back(glsl_line(line_mode::GLSL_CODE, line));
					continue;
				}

				pos = line.find_first_not_of(" \t");

				if (pos != string::npos && line[pos] == '#') {
					stringstream stm(line);
					stm >> tag;

					if (tag == "#version") {
						stm >> tag;
						source->version = tag;   // 主版本
						stm >> tag;
						if (!tag.empty() && tag[0] != '/') {    // 版本副描述
							source->version.push_back(' ');
							source->version.append(tag);
						}
						//cout << "glsl> version " << source->version << endl;
						source->lines.push_back(glsl_line(line_mode::GLSL_VERSION, source->version));
					}
					else if (tag == "#include") {
						stm >> tag;
						tag = tag.substr(0, tag.find('/')); // 过滤注释
						tag = trim(tag, " \t\r\n\"<>");
						//cout << "glsl> include \"" << tag << "\"" << endl;

						// 加载 include 文件
						string tempFile = dir + tag;
						if (load_source(tempFile, source) != 0) {
							return -1;
						}

						source->lines.push_back(glsl_line(line_mode::GLSL_INCLUDE, tempFile));
					}
					else {
						source->lines.push_back(glsl_line(line_mode::GLSL_CODE, line));
					}
				}
				else {
					source->lines.push_back(glsl_line(line_mode::GLSL_CODE, line));
				}
			}// end while

			 // 添加文件结尾标识，阻断错误验证跳到其他文件里面
			tag = "// end ";
			tag.append(filename);
			source->lines.push_back(glsl_line(line_mode::GLSL_CODE, tag));

			return 0;
		}

		glsl_source* find_source(const std::string& filename) {
			iterator itr = m_sources.find(filename);
			if (itr != m_sources.end()) {
				return &itr->second;
			}
			return NULL;
		}

		int process_sources(const std::string filename) {
			glsl_source* source = this->find_source(filename);

			if (!source) {
				return -1;
			}

			if (source->included) {
				return 0;
			}

			// 判断版本
			//if (source != m_main) {
			//	if (source->version != m_main->version) {
			//		Logger.Instance->error("ShaderLoader> different source code versions({}).", filename);
			//		return -1;
			//	}
			//}

			for (size_t i = 0; i < source->lines.size(); ++i) {
				const glsl_line& line = source->lines[i];

				switch (line.mode) {
				case line_mode::GLSL_CODE:
					m_lines.push_back(shader_line(source, i));
					break;
				case line_mode::GLSL_VERSION:
					m_lines.push_back(shader_line(source, i));
					break;
				case line_mode::GLSL_INCLUDE:
					m_lines.push_back(shader_line(source, i));
					process_sources(line.source);
					break;
				default:
					break;
				}
			}

			// 标记已经引用
			source->included = true;

			return 0;
		}

		GLuint compile_shader(GLenum type, const char* source) {
			GLuint shader;

			// create the shader object
			shader = glCreateShader(type);

			// load the shader source
			glShaderSource(shader, 1, &source, NULL);

			// Compile the shader
			glCompileShader(shader);

			// check the compile status
			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1) {
					m_log_buffer.resize(infoLen);
					glGetShaderInfoLog(shader, infoLen, NULL, &m_log_buffer[0]);
					this->report(type, &m_log_buffer[0]);
				}

				glDeleteShader(shader);
				return GL_NONE;
			}

			return shader;
		}

		// 返回 shader 类型名字
		const char* shader_type_name(GLenum type)
		{
			switch (type) {
			case GL_FRAGMENT_SHADER:
				return "Fragment Shader";
			case GL_VERTEX_SHADER:
				return "Vertex Shader";
			case GL_GEOMETRY_SHADER:
				return "Geometry Shader";
			case GL_COMPUTE_SHADER:
				return "Compute Shader";
			default:
				return "Unknown Shader";
			}
		}

		void report(GLenum type, const char* log)
		{
			using namespace std;

			stringstream in(log);
			string line;
			string tag;
			string pos;
			string a, b;
			size_t x, y;

			while (!in.eof()) {
				getline(in, line);

				if (line.empty()) {
					continue;
				}

				stringstream stm(line);

				stm >> tag;
				if (tag == "ERROR:" || tag == "WARNING:") {
					// 解析错误位置
					stm >> pos;
					x = pos.find(':');
					a = pos.substr(0, x);
					b = pos.substr(x + 1, pos.length() - x - 2);

					x = atoi(a.c_str());
					y = atoi(b.c_str());

					// 如果不是主源码，y 值减一，起始索引 0
					if (m_lines[y].source->parent != NULL) {
						--y;
					}

					const shader_line& shaderLine = m_lines[y];

					// 错误行号是起始 1
					cout << "glsl> " << tag << ' ' << shader_type_name(type)
						<< ": \"" << shaderLine.source->filename << "\"" << endl;
					cout << "      " << x << ":" << shaderLine.line + 1
						<< ": " << line.substr(stm.tellg()) << endl;
				}
				else {
					cout << "glsl> " << log;
				}
			}
		}
#pragma endregion

	public:
		ShaderLoader() : m_sources(), m_lines()
		{

		}

		~ShaderLoader()
		{
			this->dispose();
		}

		// 加载源码
		int load(const std::string& filename)
		{
			this->dispose();

			// 加载主源码
			if (this->load_source(filename) != 0) {
				this->dispose();
				return -1;
			}

			// 记录主源码
			//m_main = this->find_source(filename);

			// 预处理
			return this->process_sources(filename);
		}

		// 编译，返回 shader ID
		GLuint compile(GLenum type, bool debug = false)
		{
			// 是否已经处理版本标记
			bool tag_version = false;
			std::string code;

			for (size_t i = 0; i < m_lines.size(); ++i) {
				size_t id = m_lines[i].line;
				const glsl_line& line = m_lines[i].source->lines[id];

				switch (line.mode) {
				case line_mode::GLSL_CODE:
					code.append(line.source);
					code.push_back('\n');
					if (debug) Logger.Instance->error("ShaderLoader.compile> LineNum({}) LineContent({}).", i+1, line.source.c_str());
					break;
				case line_mode::GLSL_VERSION:
					if (tag_version) {
						code.append("//");
						if (debug) Logger.Instance->error("ShaderLoader.compile> LineNum({}) Version({}).", i + 1, line.source.c_str());
					}
					else {
						tag_version = true;
						if (debug) Logger.Instance->error("ShaderLoader.compile> LineNum({}) Version({}).", i + 1, line.source.c_str());
					}
					code.append("#version ");
					code.append(line.source);
					code.push_back('\n');
					break;
				case line_mode::GLSL_INCLUDE:
					code.append("//");
					code.append(line.source);
					code.push_back('\n');

					if (debug) Logger.Instance->error("ShaderLoader.compile> LineNum({}) Include({}).", i + 1, line.source.c_str());
					break;
				default:
					break;
				}
			}

			// 编译
			GLuint shaderProgramID = GL_NONE;
			try {
				shaderProgramID = compile_shader(type, code.c_str());
			}
			catch (const std::exception& exc) {
				Logger.Instance->error(exc.what());
			}
			return shaderProgramID;
		}
	};
}

#endif // !ShaderLoader_HPP
