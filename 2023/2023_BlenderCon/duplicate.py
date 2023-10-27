# Another example script for duplicating an objects geometry
import bpy

print("Starting Duplicate Box Script")
# Select the active object
myObject = bpy.context.active_object

# Let's print out the name of the object
print(myObject.name)

# Now let's acquire some data 
verts = myObject.data.vertices
edges = myObject.data.edges
faces = myObject.data.polygons

# Note
#bpy.context.selected_objects[0].scale

copy_verts = []
for v in verts:
    print(v.co[0],",",v.co[1],"",v.co[2]) 
    entry = [v.co[0],v.co[1],v.co[2]] 
    copy_verts.append(entry)
    
print("verts",copy_verts)    

copy_edges = []
for segment in edges:
    entry = []
    for pair in segment.vertices:
        #print(pair)
        entry.append(pair)
    copy_edges.append(entry)

print("edges:",copy_edges)
    
# Loop through all of our faces
# and figure out the indices
copy_faces = []
for idx,polygon in faces.items():
    #print(polygon.vertices)
    entry = []
    for vertInPolygon in polygon.vertices:
        #print("vertex:",vertInPolygon)
        entry.append(vertInPolygon)
    copy_faces.append(entry)    
    
print("faces",copy_faces)    

# New mesh name
duplicate_name = "duplicate"+myObject.name
# Create a new 'empty mesh'
duplicate_mesh= bpy.data.meshes.new(duplicate_name)
# Populate the mesh with geometry data
duplicate_mesh.from_pydata(copy_verts,copy_edges,copy_faces)
# Create the new object with a name and associated mesh
duplicate_object = bpy.data.objects.new(duplicate_name, duplicate_mesh)
# Link in the mesh to a scene so we can actually view it.
bpy.data.collections['Collection'].objects.link(duplicate_object)
