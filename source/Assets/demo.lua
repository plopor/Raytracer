-- A simple scene with some miscellaneous geometry.

matGLOSSYREFRACT = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 1.55, 0, 1)
matGLOSSYREFLECT = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0, 1, 1)
matREFRACT = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 1.55, 0, 0)
matREFLECT = gr.material({1.0, 0.0, 0.0}, {0.5, 0.4, 0.8}, 25, 0, 0.7, 0)
matBUMP = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0, 0, 0)
matTEXTURE = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0, 0, 0)
matBUMP2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0, 0, 0)

scene_root = gr.node('root')

s1 = gr.nh_sphere('s1', {-40, 0, -400}, 100, 1, 1)
scene_root:add_child(s1)
s1:set_material(matBUMP)

s2 = gr.nh_sphere('s2', {200, 50, -100}, 150, 1, 0)
scene_root:add_child(s2)
s2:set_material(matTEXTURE)

s3 = gr.nh_sphere('s3', {0, -1200, -500}, 1000, 0, 0)
scene_root:add_child(s3)
s3:set_material(matREFLECT)

s4 = gr.nh_sphere('s4', {-150, -85, 150}, 30, 0, 0)
scene_root:add_child(s4)
s4:set_material(matGLOSSYREFRACT)

s5 = gr.nh_sphere('s5', {0, 100, -250}, 25, 0, 0)
scene_root:add_child(s5)
s5:set_material(matGLOSSYREFLECT)

s6 = gr.nh_sphere('s6', {-180, 80, -110}, 110, 0, 0)
scene_root:add_child(s6)
s6:set_material(matREFRACT)

s7 = gr.nh_sphere('s7', {-520, 300, -800}, 350, 0, 1)
scene_root:add_child(s7)
s7:set_material(matBUMP2)

s8 = gr.nh_sphere('s8', {820, 1300, -500}, 1000, 0, 0)
scene_root:add_child(s8)
s8:set_material(matGLOSSYREFLECT)

white_light = gr.light({-100.0, 250.0, 550.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
purple_light = gr.light({400.0, 100.0, 400.0}, {0.9, 0.9, 0.4}, {1, 0, 0})

gr.render(scene_root, 'demo.png', 1024, 1024,
	  {0, 0, 800}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.1, 0.1, 0.1}, {white_light, purple_light})
