#pragma once

struct Tri
{
	unsigned int v[3];

	Tri(unsigned int x = 0, unsigned int y = 0,unsigned int z = 0)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
	}
};