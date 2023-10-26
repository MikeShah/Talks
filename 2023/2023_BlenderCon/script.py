# Note:
# We do have a way to compute the bounding box
# bpy.context.selected_objects[0].bound_box[0][0]
import bpy

import time

start_time = time.time()

print("Starting Script")

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

# =========== Bounding Box Script ===========
# Select the active object
active_obj = bpy.context.active_object

active_object_verts = active_obj.data.vertices

# Store the vertices x, y, and z values
xValues = []
yValues = []
zValues = []

# Only compute bounding box based on
# the vertices if they are selected
for v in active_object_verts:  
   # if v.select == True:
    xValues.append(v.co[0])   
    yValues.append(v.co[1])  
    zValues.append(v.co[2]) 
    
# Iterate through the values we have stored
# and grab the bounds
minx =  min(xValues)
maxx =  max(xValues)
miny =  min(yValues)
maxy =  max(yValues)
minz =  min(zValues)
maxz =  max(zValues)

print("==== Bounds ====")
print(minx,maxx)
print(miny,maxy)
print(minz,maxz)
print(" Dimensions ")
print(abs(minx)+abs(maxx))
print(abs(miny)+abs(maxy))
print(abs(minz)+abs(maxz))

bpy.ops.mesh.primitive_cube_add(enter_editmode=False, align='WORLD', location=(0, 0, 0), scale=(1, 1, 1))
cube_temp = bpy.context.active_object

# Now let's acquire some data 
cube_verts = cube_temp.data.vertices
cube_edges = cube_temp.data.edges
cube_faces = cube_temp.data.polygons


cube_temp_verts = []
for v in cube_verts:  
    entry = [v.co[0],v.co[1],v.co[2]] 
    cube_temp_verts.append(entry) 


cube_temp_edges = []
for segment in cube_edges:
    entry = []
    for pair in segment.vertices:
        entry.append(pair)
    cube_temp_edges.append(entry)
    
# Loop through all of our faces
# and figure out the indices
cube_temp_faces = []
for idx,polygon in cube_faces.items():
    entry = []
    for vertInPolygon in polygon.vertices:
        entry.append(vertInPolygon)
    cube_temp_faces.append(entry)    

# Create the bounding box with some vertex positions setup correctly
bounding_verts = cube_temp_verts.copy()

# Can print off the cube verts
# in order to see the pattern
# print(cube_temp_verts)

# Can otherwise think like a truth table
bounding_verts[0] = [minx,miny,minz]
bounding_verts[1] = [minx,miny,maxz]
bounding_verts[2] = [minx,maxy,minz]
bounding_verts[3] = [minx,maxy,maxz]
bounding_verts[4] = [maxx,miny,minz]
bounding_verts[5] = [maxx,miny,maxz]
bounding_verts[6] = [maxx,maxy,minz]
bounding_verts[7] = [maxx,maxy,maxz]

# New mesh name
bounding_name = "bounding_"+myObject.name
# Create a new 'empty mesh'
bounding_mesh= bpy.data.meshes.new(bounding_name)
# Populate the mesh with geometry data
bounding_mesh.from_pydata(bounding_verts,cube_temp_edges,cube_temp_faces)
# Create the new object with a name and associated mesh
bounding_object = bpy.data.objects.new(bounding_name, bounding_mesh)
# Link in the mesh to a scene so we can actually view it.
bpy.data.collections['Collection'].objects.link(bounding_object)

# Set the bounding box to wireframe by default
bpy.data.objects[bounding_name].display_type = 'WIRE'

# Last step is to apply scale, rotation, and transform to the object
#bounding_object.scale = myObject.scale
#bounding_object.rotation_euler = myObject.rotation_euler
#bounding_object.location = myObject.location

# Another option is to make our target object the parent
# so that the bounding box transforms with it.
bounding_object.parent = myObject

# Unselect every object
for obj in bpy.data.objects:
    bpy.data.objects[obj.name].select_set(False)

# Remove our temporary cube
bpy.data.objects.remove(cube_temp)

print("Made to end in: ",time.time()-start_time)


# Another idea if time
# Creating a bounding box around selected faces or vertices