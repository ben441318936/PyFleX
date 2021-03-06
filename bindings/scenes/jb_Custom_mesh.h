class jb_Custom_mesh: public Scene
{
public:

	jb_Custom_mesh(const char* name) : Scene(name) {}

	char* make_path(char* full_path, std::string path) {
		strcpy(full_path, getenv("PYFLEXROOT"));
		strcat(full_path, path.c_str());
		return full_path;
	}

	float rand_float(float LO, float HI) {
        return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(HI-LO)));
    }

    void swap(float* a, float* b) {
	    float tmp = *a;
	    *a = *b;
	    *b = tmp;
	}

	/*  Scene params
	params[0] -> radius
	params[1] -> max number of particles
	params[2,3,4] -> lower limit of scene box
	params[5,6,7] -> upper limit of scene box
	params[8,9,10,11] -> fluid color
	params[12] -> draw options, 0 = particles, 1 = fluid render
	*/
	void Initialize(py::array_t<float> scene_params, int thread_idx = 0)
	{

		auto buf = scene_params.request();
    	auto ptr = (float *) buf.ptr;

		float radius = ptr[0];
		// float radius = 0.3;

		float scale = ptr[1];

		// deforming bunny
		float s = radius*0.5f;
		float m = 0.25f;
		int group = 1;

		char bunny_path[100];
		char box_path[100];
		char sphere_path[100];
		char custom_box_path[100];
		char tip_path[100];

		make_path(bunny_path, "/data/bunny.ply");
		make_path(box_path, "/data/box.ply");
		make_path(sphere_path, "/data/sphere.ply");
		// make_path(custom_box_path, "/data/heart2assem.obj");
		// make_path(custom_box_path, "/data/custom_heart2_2.obj");
		make_path(tip_path, "/data/tip.obj");
		make_path(custom_box_path, "/data/center_obs_shallow.obj");
		// make_path(custom_box_path, "/data/cavity2.obj");

        srand(time(NULL) + thread_idx);
        float x = rand_float(0.45, 1.0);
        float z = rand_float(0.05, 0.15);

        // void CreateParticleShape(const Mesh* srcMesh, Vec3 lower, Vec3 scale, float rotation, float spacing, Vec3 velocity, float invMass, bool rigid, float rigidStiffness, int phase, bool skin, float jitter=0.005f, Vec3 skinOffset=0.0f, float skinExpand=0.0f, Vec4 color=Vec4(0.0f), float springStiffness=0.0f)

        // CreateParticleShape(GetFilePathByPlatform(box_path).c_str(), Vec3(x, -0.0155f, z), 0.2f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), false, 0.0f);
		//CreateParticleShape(GetFilePathByPlatform(box_path).c_str(), Vec3(x_1, -0.0155f, z_1), 0.2f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), false, 0.0f);
		//CreateParticleShape(GetFilePathByPlatform(bunny_path).c_str(), Vec3(3.0f, 0.0f, 0.0f), 0.5f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), true, 0.0f);
		//CreateParticleShape(GetFilePathByPlatform(bunny_path).c_str(), Vec3(2.0f, 0.0f, 1.0f), 0.5f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), true, 0.0f);
		//CreateParticleShape(GetFilePathByPlatform(box_path).c_str(), Vec3(2.0f, 0.0f, 0.0f), 0.45f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), true, 0.0f);

		// CreateParticleShape(GetFilePathByPlatform(sphere_path).c_str(), Vec3(0.0f, 0.0f, 0.0f), 0.1f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), true, 0.0f);
		// CreateParticleShape(GetFilePathByPlatform(tip_path).c_str(), Vec3(0.0f, 0.0f, 0.0f), 0.3f, 0.0f, s, Vec3(0.0f, 0.0f, 0.0f), m, true, 1.0f, NvFlexMakePhase(group++, 0), true, 0.0f);
		
		Mesh* mesh1 = ImportMesh(custom_box_path);
		NvFlexTriangleMeshId mesh1_id = CreateTriangleMesh(mesh1);
		AddTriangleMesh(mesh1_id, Vec3(0.0f, 0.0f, 0.0f), Quat(), Vec3(1/scale, 1/scale, 1/scale));

		Mesh* mesh2 = ImportMesh(tip_path);
		NvFlexTriangleMeshId mesh2_id = CreateTriangleMesh(mesh2);
		AddTriangleMesh(mesh2_id, Vec3(0.1f, 0.15f, 0.6f), Quat(), Vec3(10, 10, 10));
		
		g_numSolidParticles = g_buffers->positions.size();		

		float restDistance = radius*0.55f;

		int max_particles = int(ptr[2]);
		// int max_particles = 100;

		// void CreateParticleGrid(Vec3 lower, int dimx, int dimy, int dimz, float radius, Vec3 velocity, float invMass, bool rigid, float rigidStiffness, int phase, float jitter=0.005f)
		// CreateParticleGridWithLimit(Vec3(0.0f, 0.0f, 0.0f), max_particles, 2, 2, restDistance, Vec3(0.0f), 1.0f, false, 0.0f, NvFlexMakePhase(0, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid), 0.005f, max_particles);

		CreateParticleZero(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f, NvFlexMakePhase(0, eNvFlexPhaseSelfCollide | eNvFlexPhaseFluid), 0.005f, max_particles);


		g_sceneLower = Vec3(ptr[3]/scale, ptr[4]/scale, ptr[5]/scale);
		g_sceneUpper = Vec3(ptr[6]/scale, ptr[7]/scale, ptr[8]/scale);
		// g_sceneLower = Vec3(0.0f, 0.0f, 0.0f);
		// g_sceneUpper = Vec3(1.0f, 1.0f, 1.0f);

		g_numSubsteps = 2;

		g_params.radius = radius;
		g_params.dynamicFriction = 0.01f; 
		g_params.viscosity = 2.0f;
		g_params.numIterations = 4;
		g_params.vorticityConfinement = 40.0f;
		g_params.fluidRestDistance = restDistance;
		g_params.solidPressure = 0.f;
		g_params.relaxationFactor = 0.0f;
		g_params.cohesion = 0.02f;
		g_params.collisionDistance = 0.01f;		

		g_maxDiffuseParticles = 0;
		g_diffuseScale = 0.5f;

		g_fluidColor = Vec4(ptr[9], ptr[10], ptr[11], ptr[12]);
		// g_fluidColor = Vec4(0.113f, 0.425f, 0.55f, 1.f);


		Emitter e1;
		e1.mDir = Vec3(1.0f, 0.0f, 0.0f);
		e1.mRight = Vec3(0.0f, 0.0f, -1.0f);
		e1.mPos = Vec3(radius, 1.f, 0.65f);
		e1.mSpeed = (restDistance/g_dt)*2.0f; // 2 particle layers per-frame
		e1.mEnabled = true;

		g_emitters.push_back(e1);

	    // g_numExtraParticles = 48*1024;

		g_lightDistance = 1.8f;

		g_params.numPlanes = 5;

		g_waveFloorTilt = 0.0f;
		g_waveFrequency = 1.5f;
		g_waveAmplitude = 2.0f;
		
		g_warmup = false;

		// draw options		
		g_drawPoints = true;
		g_drawMesh = true;

		switch (int(ptr[13]))
		{
			case 0:
				g_drawEllipsoids = false;
				break;
			case 1:
				g_drawEllipsoids = true;
				break;
			default:
				g_drawEllipsoids = true;
		}
		// g_drawEllipsoids = true;

		g_drawDiffuse = true;
	}

	void CenterCamera()
	{
		// g_camPos = Vec3((g_sceneLower.x + g_sceneUpper.x)*1.3f, g_sceneUpper.y*1.2f, (g_sceneLower.z + g_sceneUpper.z)*0.5f);
		// g_camAngle = Vec3(DegToRad(90.0f), -DegToRad(50.0f), 0.0f);

		g_camPos = Vec3((g_sceneLower.x + g_sceneUpper.x)*1.4f, g_sceneUpper.y*1.2f, (g_sceneLower.z + g_sceneUpper.z)*0.5f);
		g_camAngle = Vec3(DegToRad(90.0f), -DegToRad(45.0f), 0.0f);

		// g_camPos = Vec3((g_sceneLower.x + g_sceneUpper.x)*0.75f, g_sceneUpper.y*1.2f, (g_sceneLower.z + g_sceneUpper.z)*0.5f);
		// g_camAngle = Vec3(DegToRad(90.0f), -DegToRad(90.0f), 0.0f);


	}
};
