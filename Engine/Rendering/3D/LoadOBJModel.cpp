#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel()
{
	currentMaterial = Material();
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	OnDestroy();
}


void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadObJModel.cpp", __LINE__);
		return;

	}
	std::string line;

	while (std::getline(in, line)) 
	{
		//VERTEX DATA
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			if (minX > x)
			{
				minX = x;
			}
			if (minY > y)
			{
				minY = y;
			}
			if (minZ > z)
			{
				minZ = z;
			}
			if (maxX < x)
			{
				maxX = x;
			}
			if (maxY < y)
			{
				maxY = y;
			}
			if (maxZ < z)
			{
				maxZ = z;
			}
			box.minVert.x = minX;
			box.minVert.y = minY;
			box.minVert.z = minZ;
			box.maxVert.x = maxX;
			box.maxVert.y = maxY;
			box.maxVert.z = maxZ;
			vertices.push_back(glm::vec3(x, y, z));
		}
		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") 
		{
			std::stringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//TEXTURE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			glm::vec2 vec;
			v >> vec.x >> vec.y;
			textureCoords.push_back(vec);
		}
		//FACE DATA
		if (line.substr(0, 2) == "f ") 
		{
			std::stringstream f(line.substr(2));

			int x, y, z;
			char Slash;

			for (int i = 0; i < 3; i++) {
				f >> x >> Slash >> y >> Slash >> z;

				indices.push_back(x - 1);
				textureIndices.push_back(y - 1);
				normalIndices.push_back(z - 1);
			}
		}
		//new Material / new Mesh
		else if (line.substr(0, 7) == "usemtl ") 
		{
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();

}

std::vector<Vertex> LoadOBJModel::GetVerts()
{
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return box;
}

void LoadOBJModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing()
{
	for (int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;

	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
