# PyFlex

All modifications to the original PyFlex are made in the bindings folder.

New additions:
- bindings/scenes/jb_Custm_mesh.h
    - A new scene that allows me to load in simulated particle positions and render
    - The cavity and the suction tool tip are loaded in as shapes that do not interact with particles
- bindgings/examples/test_Custom_mesh.py
    - Python script that runs the above scene
    - Loads in simulated particle data, sets the data in the Flex engine, as well as renders

Changes:
- bindings/PyFlex.cpp
    - line 1567: sets the color of the imported TriMesh (tool tip, cavity)