#include "Node.h"
#include "Mesh.h"
#ifndef h_Sphere

// 球体
//将球横纵划分成50*50的网格
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
		texture.Id = ImgCache::GetInstance().addTexture(imgPath, param);	// 加载图片
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

	// v是球面点与原点的连线与z轴正向的夹角
	// u表示连线在xy平面的投影与x轴正向的夹角
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

	// 创建顶点
	std::vector<Vertex> CreateVertices() {
		std::vector<Vertex> vertices;
		// 纵轴遍历
		for (int y = 0; y <= Y_SEGMENTS; y++)
		{
			// 横轴遍历
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

	// 创建索引
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
				// 首尾相连
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

		//	// 这里奇偶分开添加是有道理的，奇偶分开添加，就能首位相连，自己可以拿笔画一画
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
