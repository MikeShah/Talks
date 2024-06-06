
bl_info = {
    "name": "Compute Bounding Box BCon",
    "blender": (3, 00, 0),
    "category": "Object",
}

# Note: ^ This dictionary (bl_info) must be at the top of our file
#       (Usually with one space above) 

import bpy  # Blender Python API
import time # Used for time keeping


class ObjectComputeBoundingBox(bpy.types.Operator):
    """Simple example showing you how to compute bounding box""" # Use this as a tooltip for menu items and buttons.
    bl_idname = "object.computebunding_box"             # Unique identifier for buttons and menu items to reference.
    bl_label = "Compute Bounding Box BCon"                       # Display name in the interface.
    bl_options = {'REGISTER', 'UNDO'}  # Enable undo for the operator.

    def execute(self, context):        # execute() is called when running the operator.

        # =========== Bounding Box Script ===========
        start_time = time.time()
        print("Starting Bounding Box Script")

        # Select the active object
        active_obj = bpy.context.active_object

        # Grab the active vertices form our object
        active_object_verts = active_obj.data.vertices

        # Store the vertices x, y, and z values
        xValues = []
        yValues = []
        zValues = []

        # Only compute bounding box based on
        # the vertices if they are selected
        # Note: Currently I am not making use of this, as we need
        #       to make sure we toggle edit mode off first.
        for v in active_object_verts:  
            if v.select == True: # Nothing done with this quite yet
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

        # Print out our results
        # Useful to compare dimensions with what Blender3D has
        # built-in so we can see if we're correct.
        print("==== Bounds ====")
        print(minx,maxx)
        print(miny,maxy)
        print(minz,maxz)
        print("==== Dimensions ====")
        print(abs(minx)+abs(maxx))
        print(abs(miny)+abs(maxy))
        print(abs(minz)+abs(maxz))

        # Add a temporary cube, for which we will grab its
        # vertices, edges, and faces in order to make our bounding box.
        bpy.ops.mesh.primitive_cube_add(enter_editmode=False, align='WORLD', location=(0, 0, 0), scale=(1, 1, 1))
        cube_temp = bpy.context.active_object

        # Now let's acquire the temporary cubes data
        cube_verts = cube_temp.data.vertices
        cube_edges = cube_temp.data.edges
        cube_faces = cube_temp.data.polygons

        # The purpose of these next statements is to
        # copy and 'flatten' out the data into uor own
        # lists. Then we will creata mesh from each of these
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
        bounding_name = "bounding_"+active_obj.name
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
        bounding_object.parent = active_obj

        # Unselect every object
        for obj in bpy.data.objects:
            bpy.data.objects[obj.name].select_set(False)

        # Remove our temporary cube
        bpy.data.objects.remove(cube_temp)

        print("Made to end in: ",time.time()-start_time)

        return {'FINISHED'}            # Lets Blender know the operator finished successfully.

def menu_func(self, context):
    self.layout.operator(ObjectComputeBoundingBox.bl_idname)

def register():
    bpy.utils.register_class(ObjectComputeBoundingBox)
    bpy.types.VIEW3D_MT_object.append(menu_func)  # Adds the new operator to an existing menu.

def unregister():
    bpy.utils.unregister_class(ObjectComputeBoundingBox)


# This allows you to run the script directly from Blender's Text editor
# to test the add-on without having to install it.
if __name__ == "__main__":
    register()
