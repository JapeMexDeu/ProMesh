

#ifndef __H__UG_PROMESH__my_tools__
#define __H__UG_PROMESH__my_tools__

#include "../mesh.h"
#include "lib_grid/algorithms/geom_obj_util/misc_util.h"
#include "common/node_tree/node_tree.h"
#include "lib_grid/algorithms/crease_util.h"
#include "lib_grid/algorithms/mark_util.h"
#include "lib_grid/algorithms/problem_detection_util.h"
#include "lib_grid/algorithms/refinement_mark_util.h"
#include "lib_grid/algorithms/selection_util.h"
#include "lib_grid/algorithms/remeshing/edge_length_adjustment.h"
#include "lib_grid/algorithms/trees/octree.h"
#include "lib_grid/callbacks/callbacks.h"

#include "lib_grid/algorithms/volume_calculation.h"
#include "lib_grid/algorithms/geom_obj_util/edge_util.h"

namespace ug{
namespace promesh{

void SelectGivenSubset(
			Mesh* obj,
			int si,
			bool selVrts,
			bool selEdges,
			bool selFaces,
			bool selVols);

number SelectObstacleSurface(Mesh* obj);
size_t GetInfoFromObstacleSurface(Mesh* obj);
number MeasureObstacleSubsetLength(Mesh* obj);
number MeasureAverageEdgeLengthInObstacleSurface(Mesh* obj);
number FindLongestEdgeInObstacleSurface(Mesh* obj);
number FindShortestEdgeInObstacleSurface(Mesh* obj);
number GetNumberOfEdgesOnObstacleSurface(Mesh* obj);

}}// end of namespace

#endif