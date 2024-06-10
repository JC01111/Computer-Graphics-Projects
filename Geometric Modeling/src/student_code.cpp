#include "student_code.h"
#include "mutablePriorityQueue.h"

using namespace std;

namespace CGL
{

  /**
   * Evaluates one step of the de Casteljau's algorithm using the given points and
   * the scalar parameter t (class member).
   *
   * @param points A vector of points in 2D
   * @return A vector containing intermediate points or the final interpolated vector
   */
  std::vector<Vector2D> BezierCurve::evaluateStep(std::vector<Vector2D> const &points)
  { 
    // TODO Part 1.
      std::vector<Vector2D> inter_pts;
      for (size_t i = 0; i < points.size()-1; i++) {
          inter_pts.push_back(points[i]*(1-t) + points[1+i]*t);
      }
    return inter_pts;
  }

  /**
   * Evaluates one step of the de Casteljau's algorithm using the given points and
   * the scalar parameter t (function parameter).
   *
   * @param points    A vector of points in 3D
   * @param t         Scalar interpolation parameter
   * @return A vector containing intermediate points or the final interpolated vector
   */
  std::vector<Vector3D> BezierPatch::evaluateStep(std::vector<Vector3D> const &points, double t) const
  {
    // TODO Part 2.
      std::vector<Vector3D> inter_pts;
      for (size_t i = 0; i < points.size()-1; i++) {
          Vector3D interpolated_pt = points[i] * (1-t) + points[i+1] * t;
          inter_pts.push_back(interpolated_pt);
      }
    return inter_pts;
  }

  /**
   * Fully evaluates de Casteljau's algorithm for a vector of points at scalar parameter t
   *
   * @param points    A vector of points in 3D
   * @param t         Scalar interpolation parameter
   * @return Final interpolated vector
   */
  Vector3D BezierPatch::evaluate1D(std::vector<Vector3D> const &points, double t) const
  {
    // TODO Part 2.
      std::vector<Vector3D> curr_pts = points;
      // Repeat through all the lerps
      while (curr_pts.size() > 1) {
          curr_pts = evaluateStep(curr_pts, t);
      }
      return curr_pts[0];  // Final interpolated vector
  }

  /**
   * Evaluates the Bezier patch at parameter (u, v)
   *
   * @param u         Scalar interpolation parameter
   * @param v         Scalar interpolation parameter (along the other axis)
   * @return Final interpolated vector
   */
  Vector3D BezierPatch::evaluate(double u, double v) const 
  {  
    // TODO Part 2.
      std::vector<Vector3D> inter_pts;
      for (size_t i = 0; i < controlPoints.size(); i++) {
          inter_pts.push_back(evaluate1D(controlPoints[i], u));
      }
      return evaluate1D(inter_pts, v);
  }

  Vector3D Vertex::normal( void ) const
  {
    // TODO Part 3.
    // Returns an approximate unit normal at this vertex, computed by
    // taking the area-weighted average of the normals of neighboring
    // triangles, then normalizing.
     Vector3D sumNormal(0, 0, 0);  // Sum of area weighted normals
     HalfedgeCIter h = halfedge();
     HalfedgeCIter h2 = h;
      
     // Check if the initial halfedge is not null and not a boundary
     do {
       if (!h->face()->isBoundary()) {
           Vector3D edge1 = h->next()->vertex()->position - h->vertex()->position;
           Vector3D edge2 = h->next()->next()->vertex()->position - h->next()->vertex()->position;
           // Calculate the area-weighted normal for the face
           Vector3D normal = cross(edge1, edge2);
           sumNormal += normal;
           // Move to the next halfedge around the vertex
           h = h->twin()->next();
        }
     }
     while (h != h2);
     // Normalize the sum of the area-weighted normals
     return sumNormal.unit();
  }

  EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
  {
    // TODO Part 4.
    // This method should flip the given edge and return an iterator to the flipped edge.
      if (!e0->isBoundary()) {
            // Halfedges around the edge to be flipped
            HalfedgeIter h0 = e0->halfedge();
            HalfedgeIter h1 = h0->next();
            HalfedgeIter h2 = h1->next();
            HalfedgeIter h3 = h0->twin();
            HalfedgeIter h4 = h3->next();
            HalfedgeIter h5 = h4->next();
            HalfedgeIter h6 = h1->twin();
            HalfedgeIter h7 = h2->twin();
            HalfedgeIter h8 = h4->twin();
            HalfedgeIter h9 = h5->twin();

            // Vertices at the ends of the edge to be flipped
            VertexIter v0 = h0->vertex();
            VertexIter v1 = h3->vertex();
            VertexIter v2 = h2->vertex();
            VertexIter v3 = h5->vertex();
          
            // Edges associated with the halfedges in the faces adjacent to the original edge
            EdgeIter e1 = h1->edge();
            EdgeIter e2 = h2->edge();
            EdgeIter e3 = h4->edge();
            EdgeIter e4 = h5->edge();
          
            // Faces on either side of the edge
            FaceIter f1 = h0->face();
            FaceIter f2 = h3->face();

            // Reassign neighbors
            h0->setNeighbors(h1,h3,v2,e0,f1);
            h1->setNeighbors(h2,h9,v3,e4,f1);
            h2->setNeighbors(h0,h6,v1,e1,f1);
            h3->setNeighbors(h4,h0,v3,e0,f2);
            h4->setNeighbors(h5,h7,v2,e2,f2);
            h5->setNeighbors(h3,h8,v0,e3,f2);

            // Update the outer halfedges
            h6->setNeighbors(h6->next(),h2,v2,e1,h6->face());
            h7->setNeighbors(h7->next(),h4,v0,e2,h7->face());
            h8->setNeighbors(h8->next(),h5,v3,e3,h8->face());
            h9->setNeighbors(h9->next(),h1,v1,e4,h9->face());

            // Update vertices and edges to make sure poiting to the right halfedge
            v0->halfedge() = h5;
            v1->halfedge() = h2;
            v2->halfedge() = h4;
            v3->halfedge() = h1;
            e0->halfedge() = h0;
            e1->halfedge() = h2;
            e2->halfedge() = h4;
            e3->halfedge() = h5;
            e4->halfedge() = h1;

            // Faces
            f1->halfedge() = h0;
            f2->halfedge() = h3;
      }
      return e0;
  }

  VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
  {
    // TODO Part 5.
    // This method should split the given edge and return an iterator to the newly inserted vertex.
    // The halfedge of this vertex should point along the edge that was split, rather than the new edges.
      if (!e0->isBoundary()) {
           // Around the original edge
           HalfedgeIter h0 = e0->halfedge();
           HalfedgeIter h1 = h0->next();
           HalfedgeIter h2 = h1->next();
           HalfedgeIter h3 = h0->twin();
           HalfedgeIter h4 = h3->next();
           HalfedgeIter h5 = h4->next();
           // Twining the haledges that connect to surrounding vertices and face towards outside
           HalfedgeIter h6 = h1->twin();
           HalfedgeIter h7 = h2->twin();
           HalfedgeIter h8 = h4->twin();
           HalfedgeIter h9 = h5->twin();

           // At the end of the original edge.
           VertexIter v0 = h0->vertex();
           VertexIter v1 = h3->vertex();
           // At the opposite original edge in adjacent faces
           VertexIter v2 = h2->vertex();
           VertexIter v3 = h5->vertex();

           // Associated with halfedges in faces adjacent to the original edge
           EdgeIter e1 = h1->edge();
           EdgeIter e2 = h2->edge();
           EdgeIter e3 = h4->edge();
           EdgeIter e4 = h5->edge();

           // Adjacent to the original edge
           FaceIter f1 = h0->face();
           FaceIter f2 = h3->face();

           // New halfedges, edges, faces to split
           HalfedgeIter h10 = newHalfedge();
           HalfedgeIter h11 = newHalfedge();
           HalfedgeIter h12 = newHalfedge();
           HalfedgeIter h13 = newHalfedge();
           HalfedgeIter h14 = newHalfedge();
           HalfedgeIter h15 = newHalfedge();
           VertexIter v = newVertex();
           EdgeIter e5 = newEdge();
           EdgeIter e6 = newEdge();
           EdgeIter e7 = newEdge();
           FaceIter f3 = newFace();
           FaceIter f4 = newFace();


           // Updating
           h0->setNeighbors(h1,h3,v,e0,f1);
           h1->setNeighbors(h2,h6,v1,e1,f1);
           h2->setNeighbors(h0,h11,v2,e5,f1);
           h3->setNeighbors(h4,h0,v1,e0,f2);
           h4->setNeighbors(h5,h15,v,e7,f2);
           h5->setNeighbors(h3,h9,v3,e4,f2);
           h6->setNeighbors(h6->next(),h1,v2,e1,h6->face());
           h7->setNeighbors(h7->next(),h12,v0,e2,h7->face());
           h8->setNeighbors(h8->next(),h14,v3,e3,h8->face());
           h9->setNeighbors(h9->next(),h5,v1,e4,h9->face());
           h10->setNeighbors(h11,h13,v0,e6,f3);
           h11->setNeighbors(h12,h2,v,e5,f3);
           h12->setNeighbors(h10,h7,v2,e2,f3);
           h13->setNeighbors(h14,h10,v,e6,f4);
           h14->setNeighbors(h15,h8,v0,e3,f4);
           h15->setNeighbors(h13,h4,v3,e7,f4);

           // Vertices
           // New vertex to be at the midpoint of the original edge
           v->position = 0.5 * (v0->position + v1->position);
           // Mark new vertex isNew
           v->isNew = 1;
     
           v0->halfedge() = h10;
           v1->halfedge() = h1;
           v2->halfedge() = h12;
           v3->halfedge() = h5;
           v->halfedge() = h0;
           
           // Edges
           e0->halfedge() = h0;
           e1->halfedge() = h1;
           e2->halfedge() = h12;
           e3->halfedge() = h14;
           e4->halfedge() = h5;
           e5->halfedge() = h2;
           e6->halfedge() = h10;
           e7->halfedge() = h4;
           
           // True if edges touching the new vertex
           e0->isNew = 0;
           e6->isNew = 0;
           e5->isNew = 1;
           e7->isNew = 1;

           // Faces
           f1->halfedge() = h0;
           f2->halfedge() = h3;
           f3->halfedge() = h10;
           f4->halfedge() = h13;
           

           return v;
      }
      return VertexIter();
  }


  void MeshResampler::upsample( HalfedgeMesh& mesh )
  {
    // TODO Part 6.
    // This routine should increase the number of triangles in the mesh using Loop subdivision.
    // One possible solution is to break up the method as listed below.

    // 1. Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,
    // and store them in Vertex::newPosition. At this point, we also want to mark each vertex as being
    // a vertex of the original mesh.
      
      // Set original edges to false first
      for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); ++e) {
          e->isNew = false;
      }
      
      for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
          float n = v->degree();
          float u;
          if (n == 3) {
              u = 3.0f / 16.0f;
          } else {
              u = 3.0f / (8.0f * n);
          }
          // Adding neighbors vertices position
          Vector3D sum_neighbors_pos;
          HalfedgeIter h = v->halfedge();
          do {
              sum_neighbors_pos += h->twin()->vertex()->position;
              h = h->twin()->next();
          } while (h != v->halfedge());
          // Update new Position
          v->newPosition = (1.0f - n * u) * v->position + u * sum_neighbors_pos;
          v->isNew = false;
      }
      
      // Compute the new positions for edge midpoits
      for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); ++e) {
          Vector3D A = e->halfedge()->vertex()->position;
          Vector3D B = e->halfedge()->twin()->vertex()->position;
          Vector3D C = e->halfedge()->next()->next()->vertex()->position;
          Vector3D D = e->halfedge()->twin()->next()->next()->vertex()->position;
          e->newPosition = (3.0f / 8.0f) * (A + B) + (1.0f / 8.0f) * (C + D);
      }
      
    // 2. Compute the updated vertex positions associated with edges, and store it in Edge::newPosition.
    // 3. Split every edge in the mesh, in any order. For future reference, we're also going to store some
    // information about which subdivide edges come from splitting an edge in the original mesh, and which edges
    // are new, by setting the flat Edge::isNew. Note that in this loop, we only want to iterate over edges of
    // the original mesh---otherwise, we'll end up splitting edges that we just split (and the loop will never end!)
      
      // Only split edges of the original mesh
      std::vector<EdgeIter> originalEdges;
      for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); ++e) {
          if (!e->isNew) {
              originalEdges.push_back(e);
          }
      }
      for (EdgeIter e: originalEdges) {
          VertexIter newVertex = mesh.splitEdge(e);
          newVertex->newPosition = e->newPosition;
          newVertex->isNew = true;
      }
    
    // 4. Flip any new edge that connects an old and new vertex.
      for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); ++e) {
          if (e->isNew) {
              // Check if edge can be flipped
              if (!e->halfedge()->isBoundary() && !e->halfedge()->twin()->isBoundary()) {
                  if (e->halfedge()->vertex()->isNew != e->halfedge()->twin()->vertex()->isNew) {
                      mesh.flipEdge(e);
                  }
              }
          }
      }
      
    // 5. Copy the new vertex positions into final Vertex::position.
      for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
          v->position = v->newPosition;
      }
  }
}
