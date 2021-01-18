Galaxies simulation (3D)

The Barnes-Hut Approximation

Speed up calculations to O(nlogn) instead of O(n²) for the native algorithm

1. Construct the spatial index : quadtree in 2D (octree in 3d)
2. Calculate centers of mass
3. Estimate forces

1. Construct the spatial index : quadtree in 2D (octree in 3d)
Each square can only have 0 or 1 point

2. Calculate centers of mass
Calculate center of mass of each cell

