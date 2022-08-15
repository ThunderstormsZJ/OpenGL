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
	// ����ַ���ǰ��ո�
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
		// source ������
		enum class line_mode
		{
			GLSL_CODE,              // ���룬����ע�͡����е�
			GLSL_VERSION,           // �汾��Ϣ
			GLSL_INCLUDE,           // ���á������� "" ���� <>����ֻ������Դ��Ŀ¼
		};

		// Դ����
		struct glsl_line
		{
			enum class line_mode mode;         // ��ģʽ
			std::string source;     // Դ

			glsl_line(line_mode m = line_mode::GLSL_CODE, const std::string& str = std::string()) :
				mode(m),
				source(str)
			{

			}
		};

		// Դ��
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
		// shader Դ����
		struct shader_line
		{
			const glsl_source* source;
			size_t line;

			shader_line(const glsl_source* src, size_t n) : source(src), line(n)
			{
			}
		};

		typedef std::map<std::string, glsl_source>::iterator iterator;

		std::map<std::string, glsl_source> m_sources;   // ���ص�����Դ��
		std::vector<shader_line> m_lines;               // shader ����Դ��ṹ
		std::vector<char> m_log_buffer;                 // ������־����

	protected:
#pragma region private
		// �ͷ�
		void dispose()
		{
			m_sources.clear();
			m_lines.clear();
		}

		// ���� source
		glsl_source* create_source(const std::string& filename)
		{
			glsl_source* source = &m_sources.insert(std::make_pair(filename, glsl_source())).first->second;
			source->filename = filename;
			return source;
		}

		int load_source(const std::string& filename, glsl_source* main = NULL) {
			using namespace std;

			glsl_source* source;

			// ����Ƿ��Ѿ����ع�
			source = find_source(filename);
			if (source) {
				return 0;
			}

			// ���ļ�
			std::ifstream in(filename);

			//in.exceptions(ifstream::failbit || ifstream::badbit);

			if (in.fail()) {
				Logger.Instance->error("ShaderLoader> file({}) open failed.", filename);
				return -1;
			}
			else {
				Logger.Instance->info("ShaderLoader> load source({}).", filename);
			}

			// ���� map ����
			source = create_source(filename);

			// ����Ŀ¼
			string dir = filename.substr(0, filename.find_last_of("/\\") + 1);

			string line;
			string tag;
			size_t pos;

			// ������������
			if (main != NULL) {
				source->version = main->version;
				source->parent = main;
			}

			// �����ļ�
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
						source->version = tag;   // ���汾
						stm >> tag;
						if (!tag.empty() && tag[0] != '/') {    // �汾������
							source->version.push_back(' ');
							source->version.append(tag);
						}
						//cout << "glsl> version " << source->version << endl;
						source->lines.push_back(glsl_line(line_mode::GLSL_VERSION, source->version));
					}
					else if (tag == "#include") {
						stm >> tag;
						tag = tag.substr(0, tag.find('/')); // ����ע��
						tag = trim(tag, " \t\r\n\"<>");
						//cout << "glsl> include \"" << tag << "\"" << endl;

						// ���� include �ļ�
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

			 // ����ļ���β��ʶ����ϴ�����֤���������ļ�����
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

			// �жϰ汾
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

			// ����Ѿ�����
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

		// ���� shader ��������
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
					// ��������λ��
					stm >> pos;
					x = pos.find(':');
					a = pos.substr(0, x);
					b = pos.substr(x + 1, pos.length() - x - 2);

					x = atoi(a.c_str());
					y = atoi(b.c_str());

					// ���������Դ�룬y ֵ��һ����ʼ���� 0
					if (m_lines[y].source->parent != NULL) {
						--y;
					}

					const shader_line& shaderLine = m_lines[y];

					// �����к�����ʼ 1
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

		// ����Դ��
		int load(const std::string& filename)
		{
			this->dispose();

			// ������Դ��
			if (this->load_source(filename) != 0) {
				this->dispose();
				return -1;
			}

			// ��¼��Դ��
			//m_main = this->find_source(filename);

			// Ԥ����
			return this->process_sources(filename);
		}

		// ���룬���� shader ID
		GLuint compile(GLenum type, bool debug = false)
		{
			// �Ƿ��Ѿ�����汾���
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

			// ����
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
