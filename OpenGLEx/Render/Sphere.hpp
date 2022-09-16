#include "Node.h"
#include "Mesh.h"
#ifndef h_Sphere

// ����
//������ݻ��ֳ�50*50������
const int Y_SEGMENTS = 50;
const int X_SEGMENTS = 50;
const GLfloat PI = 3.14159265358979323846f;

class Sphere: public Node
{
public:
	Sphere(Shader& shader) : Node(shader) {
		this->InitMeash();
		this->SetRotate(90);
	}

	~Sphere() {
		Destroy();
	}

	void SetTexture(std::string imgPath, GLint param = GL_REPEAT) {
		stbi_set_flip_vertically_on_load(true);
		Texture texture;
		texture.Id = ImgCache::GetInstance().addTexture(imgPath, param);	// ����ͼƬ
		texture.Name = "texture_normal";
		texture.Type = "texture_normal";
		texture.Path = imgPath;

		for (int i = 0; i < this->m_meshs.size(); i++)
		{
			this->m_meshs[i].AddTexture(texture);
		}
	}

	virtual void Render() {
		Node::Render();
		for (int i = 0; i < this->m_meshs.size(); i++)
		{
			this->m_meshs[i].Draw(shader);
		}
	};
	virtual void Destroy() {
		for (int i = 0; i < this->m_meshs.size(); i++)
		{
			this->m_meshs[i].Dispose();
		}
	};
	virtual void Update(float delataTime) {
	};

private:
	std::vector<Mesh> m_meshs;

	// v���������ԭ���������z������ļн�
	// u��ʾ������xyƽ���ͶӰ��x������ļн�
	// x = sin(PI * v)*cos(2 * PI * u);
	// y = sin(PI * v)*sin(2 * PI * u);
	// z = cos(PI * v);
	glm::vec3 GetPoint(float u, float v) {
		float xPos = sin(PI * v) * cos(2 * PI * u);
		float yPos = sin(PI * v) * sin(2 * PI * u);
		float zPos = cos(PI * v);

		return glm::vec3(xPos, yPos, zPos);
	}

	void InitMeash() {
		std::vector<Vertex> vertices = CreateVertices();
		std::vector<GLuint> indices = CreateIndices();
		this->m_meshs.push_back(Mesh(vertices, indices));
	}

	// ��������
	std::vector<Vertex> CreateVertices() {
		std::vector<Vertex> vertices;
		// �������
		for (int y = 0; y <= Y_SEGMENTS; y++)
		{
			// �������
			for (int x = 0; x <= X_SEGMENTS; x++)
			{
				Vertex vec;
				float u = (float)x / (float)X_SEGMENTS;
				float v = (float)y / (float)Y_SEGMENTS;
				glm::vec3 point = GetPoint(u, v);
				vec.Position = point;
				vec.TexCoords = glm::vec2(u, v);
				vec.Normal = point;
				vertices.push_back(vec);
			}
		}

		return vertices;
	}

	// ��������
	std::vector<GLuint> CreateIndices() {
		std::vector<GLuint> sphereIndices;
		for (int i = 0; i < Y_SEGMENTS; i++)
		{
			for (int j = 0; j <= X_SEGMENTS; j++)
			{
				/**
					P1  --  P2
					P3  --  P4
				*/
				GLuint P1 = i * (X_SEGMENTS + 1) + j;
				GLuint P2 = P1 + 1;
				GLuint P3 = (i + 1) * (X_SEGMENTS + 1) + j;
				GLuint P4 = P3 + 1;
				// ��β����
				if (j == X_SEGMENTS) {
					P2 = P1;
					P4 = P3;
				}

				sphereIndices.push_back(P1);
				sphereIndices.push_back(P3);
				sphereIndices.push_back(P4);
				sphereIndices.push_back(P1);
				sphereIndices.push_back(P4);
				sphereIndices.push_back(P2);
			}
		}

		//bool oddRow = false;
		//for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
		//{
		//	if (!oddRow) // even rows: y == 0, y == 2; and so on
		//	{
		//		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		//		{
		//			sphereIndices.push_back(y * (X_SEGMENTS + 1) + x);
		//			sphereIndices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
		//		}
		//	}

		//	// ������ż�ֿ�������е���ģ���ż�ֿ���ӣ�������λ�������Լ������ñʻ�һ��
		//	else
		//	{
		//		for (int x = X_SEGMENTS; x >= 0; --x)
		//		{
		//			sphereIndices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
		//			sphereIndices.push_back(y * (X_SEGMENTS + 1) + x);
		//		}
		//	}
		//	oddRow = !oddRow;
		//}

		return sphereIndices;
	}
};


#endif // !h_Sphere
