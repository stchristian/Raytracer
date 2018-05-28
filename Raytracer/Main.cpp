#include "RayTrace.h"
#include "Jittered.h"
#include "Regular.h"
#include "Pinhole.h"

#include <string>

int main()
{
	{
		World world;
		world.build();
		Image img;
		double roll_time = 0;
		for (int i = 0; i < 1000; i++)
		{
			//world.render_scene(img);
			//std::string filename = std::to_string(i) + std::string(".bmp");
			////std::cout << filename << std::endl;
			//if ( !img.save_to_bitmap( filename.c_str() ) )
			//	std::cout << "Couldn't save to bmp " << std::endl;
			world.get_camera()->set_roll_angle(0.1);
		}

		std::cout << "Time elapsed with rolling: " << roll_time << " us" << std::endl;
		std::cout << "Average Time elapsed with rolling: " << roll_time / 1000.0 << " us" << std::endl;
	}



	std::cin.get();
}