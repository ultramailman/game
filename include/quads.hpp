#ifndef QUADS_HPP
#define QUADS_HPP
#include "opengl_util.hpp"
#include "texturedquad.hpp"
#include <vector>

struct RealQuadID{
	unsigned value;
};

struct IndexedQuadID{
	unsigned value;
};

// This is a list of quads.
// Each quad must have all its vertices added consecutively.
class Quads{
public:
	typedef unsigned short IndexType;
	static const GLuint IndexTypeID = GL_UNSIGNED_SHORT;

	typedef Vertex3 VertexType;

	typedef glm::mat4 MatrixType;

	static const unsigned INDEX_QUAD_COMPONENTS = 6;

private:
	std::vector<VertexType> vertices;
	std::vector<IndexType> indices;
	std::vector<MatrixType> transforms;

	GLuint vertexAndTextureBuf;
	GLuint transformBuf;
	GLuint indexBuf;
public:

	Quads();

	// Appends a real quad to the vertex list.
	// Returns Quad ID.
	RealQuadID addVertex(TexturedQuad);

	// Appends an indexed quad to the index list.
	// The input quadID must be the ID of an existing concrete quad in the list.
	// returns the quad number.
	IndexedQuadID addIndex(RealQuadID quadID);

private:
	unsigned vertexDataCount() const;
	unsigned indexDataCount() const;
	unsigned transformDataCount() const;

	unsigned vertexDataByteCount() const;
	unsigned indexDataByteCount() const;
	unsigned transformDataByteCount() const;

	const VertexType * vertexData() const;
	const IndexType * indexData() const;
	const MatrixType * transformData() const;

public:

	// Bind and upload vertex/index/matrix data
	void uploadVertices() const;
	void uploadIndices() const;
	void uploadTransforms() const;

	// Sets up vbo data interpretation.
	void setupVertexFormat(GLuint location) const;
	void setupTextureCoordinateFormat(GLuint location) const;
	void setupTransformFormat(GLuint location) const;

	// Access a transformation matrix.
	MatrixType & transform(IndexedQuadID);

	// Perform an indexed, instanced draw.
	void draw() const;
};

#endif
