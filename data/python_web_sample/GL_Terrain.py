import os

import PyPeridyno as dyno


def filePath(str):
    script_dir = os.getcwd()
    relative_path = "../../../../data/" + str
    file_path = os.path.join(script_dir, relative_path)
    if os.path.isfile(file_path):
        print(file_path)
        return file_path
    else:
        print(f"File not found: {file_path}")
        return -1


scene = dyno.SceneGraph()

land = dyno.LandScape3f()
land.var_file_name().set_value(dyno.FilePath(filePath("landscape/Landscape_1_Map_1024x1024.png")))
land.var_location().set_value(dyno.Vector3f([0, 100, 0]))
land.var_scale().set_value(dyno.Vector3f([1, 64, 1]))

scene.add_node(land)