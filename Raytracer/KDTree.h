#ifndef KDTREE_H
#define KDTREE_H
#define MAX_DEPTH 7

#include "BoundingBox.h"
#include <vector>


struct Object
{
	bool inBoundingBox(BoundingBox b);
};

enum Axis { X, Y, Z };

Axis nextAxis(Axis a)
{
	switch (a)
	{
	case X:
		return Y;
		break;
	case Y:
		return Z;
		break;
	case Z:
		return X;
		break;
	default:
		break;
	}
}

class KdTree {
public:
	KdTree * left = nullptr, *right = nullptr;
	bool isLeaf = true;
	std::vector<Object *> objects;
	BoundingBox boundingBox;

	KdTree() = default;
	KdTree(BoundingBox b) : boundingBox(b) { }

	//Subdivide current node
	void Subdivide(int depth, Axis subdividingAxis)
	{
		if (depth > MAX_DEPTH) { return; }

		isLeaf = false;
		//Creating new nodes
		left = new KdTree(boundingBox); right = new KdTree(boundingBox);

		if (subdividingAxis == X)
		{
			float center = (boundingBox.max.x - boundingBox.min.x) / 2;
			left->boundingBox.max.x = center;
			right->boundingBox.min.x = center;
		}
		else if (subdividingAxis == Y)
		{
			float center = (boundingBox.max.y - boundingBox.min.y) / 2;
			left->boundingBox.max.y = center;
			right->boundingBox.min.y = center;
		}
		else if (subdividingAxis == Z)
		{
			float center = (boundingBox.max.z - boundingBox.min.z) / 2;
			left->boundingBox.max.z = center;
			right->boundingBox.min.z = center;
		}

		for (Object* o : objects)
		{
			if (o->inBoundingBox(left->boundingBox))
				left->objects.push_back(o);
			else //Jó ez így?
				right->objects.push_back(o);
		}

		//Csak akkor osztjuk tovabb ha van benne objektum!
		if (!left->objects.empty())  left->Subdivide(depth + 1, nextAxis(subdividingAxis));
		if (!right->objects.empty()) right->Subdivide(depth + 1, nextAxis(subdividingAxis));
	}


};
#endif // !KDTREE_H



