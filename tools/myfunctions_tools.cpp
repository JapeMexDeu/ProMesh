/*
 * Copyright (c) 2017:  G-CSC, Goethe University Frankfurt
 * Author: Sebastian Reiter
 * 
 * This file is part of UG4.
 * 
 * UG4 is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 3 (as published by the
 * Free Software Foundation) with the following additional attribution
 * requirements (according to LGPL/GPL v3 §7):
 * 
 * (1) The following notice must be displayed in the Appropriate Legal Notices
 * of covered and combined works: "Based on UG4 (www.ug4.org/license)".
 * 
 * (2) The following notice must be displayed at a prominent place in the
 * terminal output of covered works: "Based on UG4 (www.ug4.org/license)".
 * 
 * (3) The following bibliography is recommended for citation and must be
 * preserved in all covered files:
 * "Reiter, S., Vogel, A., Heppner, I., Rupp, M., and Wittum, G. A massively
 *   parallel geometric multigrid solver on hierarchically distributed grids.
 *   Computing and visualization in science 16, 4 (2013), 151-164"
 * "Vogel, A., Reiter, S., Rupp, M., Nägel, A., and Wittum, G. UG4 -- a novel
 *   flexible software system for simulating pde based models on high performance
 *   computers. Computing and visualization in science 16, 4 (2013), 165-179"
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 */

#include "myfunctions_tools.h"
#include "common/util/index_list_util.h"
#include "lib_grid/algorithms/orientation_util.h"
#include "lib_grid/algorithms/selection_util.h"

#include <vector>

namespace ug {
namespace promesh {

void SelectGivenSubset(
	Mesh* obj,
	int si,
	bool selVrts,
	bool selEdges,
	bool selFaces,
	bool selVols)
{
	SubsetHandler& sh = obj->subset_handler();
	Selector& sel = obj->selector();

	if(si >= 0){
		if(selVrts)
			sel.select(sh.begin<Vertex>(si), sh.end<Vertex>(si));
		if(selEdges)
			sel.select(sh.begin<Edge>(si), sh.end<Edge>(si));
		if(selFaces)
			sel.select(sh.begin<Face>(si), sh.end<Face>(si));
		if(selVols)
			sel.select(sh.begin<Volume>(si), sh.end<Volume>(si));
	}
	else{
		Grid& grid = obj->grid();
	//	subset -1 has to be selected. Those are not directly accessible.
		if(selVrts){
			for(VertexIterator iter = grid.vertices_begin();
				iter != grid.vertices_end(); ++iter)
			{
				if(sh.get_subset_index(*iter) == -1)
					sel.select(*iter);
			}
		}
		if(selEdges){
			for(EdgeIterator iter = grid.edges_begin();
				iter != grid.edges_end(); ++iter)
			{
				if(sh.get_subset_index(*iter) == -1)
					sel.select(*iter);
			}
		}
		if(selFaces){
			for(FaceIterator iter = grid.faces_begin();
				iter != grid.faces_end(); ++iter)
			{
				if(sh.get_subset_index(*iter) == -1)
					sel.select(*iter);
			}
		}
		if(selVols){
			for(VolumeIterator iter = grid.volumes_begin();
				iter != grid.volumes_end(); ++iter)
			{
				if(sh.get_subset_index(*iter) == -1)
					sel.select(*iter);
			}
		}
	}
}


number SelectObstacleSurface(Mesh* obj){
	SelectGivenSubset(obj,2,false,true,false,false);
	return 0;
}


size_t GetInfoFromObstacleSurface(Mesh* obj){
	SelectObstacleSurface(obj);
	Selector& sel = obj->selector();
	return sel.num<Edge>();
	//return sel.contains_edges();
}

number GetNumberOfEdgesOnObstacleSurface(Mesh* obj){
	Selector& sel = obj->selector();
	return sel.num<Edge>();
}

number MeasureObstacleSubsetLength(Mesh* obj){
	SelectObstacleSurface(obj);
	return CalculateVolume(obj->selector().begin<Edge>(),
						   obj->selector().end<Edge>(),
						   obj->position_accessor());
}

number MeasureAverageEdgeLengthInObstacleSurface(Mesh* obj){

	ConstEdgeIterator eit = obj->selector().begin<Edge>();
	ConstEdgeIterator eit_end = obj->selector().end<Edge>();
	number avg_length = 0.;
	for (; eit != eit_end; ++eit) {
		avg_length += EdgeLength(*eit, obj->position_accessor());
	}

	return avg_length / GetNumberOfEdgesOnObstacleSurface(obj);
	
}

number FindLongestEdgeInObstacleSurface(Mesh* obj){

	ConstEdgeIterator eit = obj->selector().begin<Edge>();
	ConstEdgeIterator eit_end = obj->selector().end<Edge>();
	number longestLength = EdgeLengthSq(*eit, obj->position_accessor());

	++eit;
	for(; eit != eit_end; ++eit){

		number curLen = EdgeLengthSq(*eit, obj->position_accessor());
		if(curLen > longestLength){
			longestLength = curLen;
		}
	}

	return longestLength;

}

number FindShortestEdgeInObstacleSurface(Mesh* obj){

	ConstEdgeIterator eit = obj->selector().begin<Edge>();
	ConstEdgeIterator eit_end = obj->selector().end<Edge>();
	number shortesttLength = EdgeLengthSq(*eit, obj->position_accessor());

	++eit;
	for(; eit != eit_end; ++eit){

		number curLen = EdgeLengthSq(*eit, obj->position_accessor());
		if(curLen < shortesttLength){
			shortesttLength = curLen;
		}
	}

	return shortesttLength;

}

}//	end of namespace
}//	end of namespace

