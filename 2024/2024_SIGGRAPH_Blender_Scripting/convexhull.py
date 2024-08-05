import bpy
import bmesh

myObject = bpy.context.active_object
print(myObject.name)

#from pyhull.convex_hull import ConvexHull
from scipy.spatial import ConvexHull

# Copy over vertex data 
copy_verts = []
for v in myObject.data.vertices:
    copy_verts.append([v.co[0],v.co[1],v.co[2]])
    
# Generate the convex hull with quick-hull
hull_points = ConvexHull(copy_verts)

# Print out 
print(hull_points.points)
print("hull points",len(hull_points.points))
print(hull_points.points[0])
print(copy_verts[0])

# Print out the convex hull indices and build
# the vertex coordinates out
count=0
hull_vertices = []
for simplex in hull_points.simplices:
    print(count,':',simplex)
    count=count+1
    
    point1 = copy_verts[simplex[0]]
    point2 = copy_verts[simplex[1]]
    point3 = copy_verts[simplex[2]]
    
    # Append the individual points
    hull_vertices.append(point1)
    hull_vertices.append(point2)
    hull_vertices.append(point3)
    
for h in hull_vertices:
    print(h)
    bpy.ops.mesh.primitive_ico_sphere_add(radius=1, enter_editmode=False, align='WORLD', location=(h[0], h[1], h[2]), scale=(.1, .1, .1))

print("hull_vertices count:",len(hull_vertices))
