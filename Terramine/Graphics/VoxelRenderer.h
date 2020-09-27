#pragma once
#ifndef VOXELRENDERER_H_
#define VOXELRENDERER_H_

#include <stdlib.h>

class Mesh;
class Chunk;

class VoxelRenderer {
	float* buffer;
	unsigned long long capacity;
public:
	VoxelRenderer(unsigned long long capacity);
	~VoxelRenderer();

	Mesh* render(Chunk* chunk, const Chunk** chunks, bool AmbientOcclusion);
};

#endif // !VOXELRENDERER_H_