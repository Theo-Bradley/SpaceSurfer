@tool # Needed so it runs in editor.
extends EditorScenePostImport

var scenePath
var first

# Called right after the scene is imported and gets the root node.
func _post_import(scene):
	scenePath = scene.name
	print("Processing Scene")
	print(scenePath)
	iterate(scene)
	return scene # Remember to return the imported scene

# Recursive function that is called on every node
func iterate(node):
	if node != null:
		node = node as Node3D
		if node.position == Vector3(2.0, 0.0, 1.5): #fix an offset with my asset pack
			node.position = Vector3(0.0, 0.0, 0.0) #if node is offset to the default asset pack offset then zero position
		if node is MeshInstance3D:
			var myShader = load("res://Assets/Shaders and Materials/glTF_import.gdshader") as Shader #load the fixed shader
			var mesh = node.mesh
			for i in range(mesh.get_surface_count()): #iterate over every surface
				var material = mesh.surface_get_material(i) as BaseMaterial3D #get and cast the material
				var newMaterial = ShaderMaterial.new() #create new material
				newMaterial.shader = myShader #use the fixed shader
				newMaterial.set_shader_parameter("albedo", material.albedo_color) #copy over properties
				if scenePath.contains("linear"): #MUST ADD linear IN FILENAME TO DISABLE SRGB LINEARIZATION
					newMaterial.set_shader_parameter("shouldLinearize", false) #toggle sRGB linearization
				else:
					newMaterial.set_shader_parameter("shouldLinearize", true) #toggle sRGB linearization
				mesh.surface_set_material(i, newMaterial) #set
		for child in node.get_children():
			iterate(child) #recurse
