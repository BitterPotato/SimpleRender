#define TESS_MODE1

#include "shape.hpp"

class Sphere : public Shape {
public:
	Sphere(fvec3 c, float r) : center(c), radius(r) {}
	void tessellate(vector<FVertex>& outVertexData) const;
private:
	fvec3 center;
	float radius;
	int t;
	void callPush(const fvec3& vertexA, const fvec3& vertexB, const fvec3& vertexC,
		const fvec3& vertexAB, const fvec3& vertexBC, const fvec3& vertexCA,
		vector<FVertex>& outVertexData) const {
		// TODO: refactor vector<FVertex> vertex Index : vertex Interpolate wrap them together

	}
	void middleof(const fvec3& vertexThis, const fvec3& vertexThat, fvec3& outVertex) const {

	}
	// ����ÿ���˷�֮һ���壬�ֳ�pow(4, t+1)��
	void subTessellate(const fvec3& vertexA, const fvec3& vertexB, const fvec3& vertexC,
		vector<FVertex>& outVertexData) const {
		fvec3 vertexAB, vertexBC, vertexCA;
		middleof(vertexA, vertexB, vertexAB);
		middleof(vertexB, vertexC, vertexBC);
		middleof(vertexC, vertexA, vertexCA);

		callPush(vertexA, vertexB, vertexC, vertexAB, vertexBC, vertexCA, outVertexData);
	}
};

// TODO: ���ʹ��������ʽһ���Ի���
void Sphere::tessellate(vector<FVertex>& outVertexData) const{
	fvec3 vertexXp = fvec3(center[0] + radius, center[1], center[2]);
	fvec3 vertexXn = fvec3(center[0] - radius, center[1], center[2]);
	fvec3 vertexYp = fvec3(center[0], center[1] + radius, center[2]);
	fvec3 vertexYn = fvec3(center[0], center[1] - radius, center[2]);
	fvec3 vertexZp = fvec3(center[0], center[1], center[2] + radius);
	fvec3 vertexZn = fvec3(center[0], center[1], center[2] - radius);

	// ��ʱ������Ϊ��
	subTessellate(vertexXp, vertexYp, vertexZp, outVertexData);
	subTessellate(vertexZn, vertexYp, vertexXp, outVertexData);
	subTessellate(vertexXn, vertexYp, vertexZn, outVertexData);
	subTessellate(vertexZp, vertexYp, vertexXn, outVertexData);

	subTessellate(vertexZp, vertexYn, vertexXp, outVertexData);
	subTessellate(vertexXp, vertexYn, vertexZn, outVertexData);
	subTessellate(vertexZn, vertexYn, vertexXn, outVertexData);
	subTessellate(vertexXn, vertexYn, vertexZp, outVertexData);

}