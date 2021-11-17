/*
   IGraph library.
   Copyright (C) 2021  The igraph development team <igraph@igraph.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "igraph_constructors.h"

#include "igraph_interface.h"


/**
 * \function igraph_generalized_petersen
 * \brief Generate the Generalized Petersen graph.
 * 
 * The generalized Petersen graph is a graph consisting of an inner 
 * cycle(s) graph and an outer cycle graph, each with \c n vertices. The
 * outer cycle graph is defined by vertex \c i connecting to vertex \c i+i .
 * The inner cycle(s) graph is defined by vertex \c j connecting to vertex \c j+k .
 * In the case that \c gcd(k,n) is not 1, the inner graph will have \c gcd(k,n) cycles.
 * 
 * </para><para>
 * The generalized Petersen graph will have \c 3n edges and \c 2n vertices.
 * 
 * </para><para>
 * Generalized Petersen graphs have some interesting properties, please see 
 * another source, e.g. Wikipedia for details.
 * 
 * \param graph Pointer to an uninitialized graph object, the result will
 * be stored here.
 * \param n Integer, \c n is the number of vertices in the inner and outer 
 * cycle graphs.
 * \param k Integer, \c k is the shift for the inner cycle graph.
 * \return Error code.
 * 
 * \sa \ref igraph_famous() for the original Petersen graph.
 * 
 * Time complexity: O(|V|), the number of vertices in the graph.
 */
igraph_error_t igraph_generalized_petersen(igraph_t *graph, igraph_integer_t n, igraph_integer_t k) {
    /* This is a generalized Petersen graph constructor */
    igraph_vector_int_t edges;
    igraph_integer_t no_of_nodes = 2*n;
    igraph_integer_t i;

    if (n < 3) {
        IGRAPH_ERROR("n must be at least 3.", IGRAPH_EINVAL);
    }

    if (! (k > 0 && 2*k < n)) {
        IGRAPH_ERROR("k must be positive and less than n/2.", IGRAPH_EINVAL);
    }

    IGRAPH_VECTOR_INT_INIT_FINALLY(&edges, 0);
    IGRAPH_CHECK(igraph_vector_int_reserve(&edges, 3*n));

    for (i = 0; i < n; i++) {
        igraph_vector_int_push_back(&edges, i);
        igraph_vector_int_push_back(&edges, (i + 1) % n);
        igraph_vector_int_push_back(&edges, i);
        igraph_vector_int_push_back(&edges, i + n);
        igraph_vector_int_push_back(&edges, i + n);
        igraph_vector_int_push_back(&edges, ((i + k) % n) + n);
    }

    IGRAPH_CHECK(igraph_create(graph, &edges, no_of_nodes, IGRAPH_UNDIRECTED));
    
    igraph_vector_int_destroy(&edges);
    IGRAPH_FINALLY_CLEAN(1);

    return IGRAPH_SUCCESS;
}
