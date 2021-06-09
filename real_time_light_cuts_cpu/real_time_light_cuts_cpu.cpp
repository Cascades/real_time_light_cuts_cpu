#include <chrono>
#include <iostream>
#include <memory>

#include "LightCut.h"
#include "PBT.h"
#include "UBO.h"
#include "scene_lights.h"

int main()
{
	auto const max_lights = 50;
	auto const num_lights = 6;
	
	// scene ligths object
	std::unique_ptr<ml::SceneLights<max_lights>> lights = std::make_unique<ml::SceneLights<max_lights>>();
	lights->set_num_lights(num_lights);
	lights->set_light_heights(3.0f);
	lights->initialise();

	// pbt object
	std::unique_ptr<PBT<float, float, max_lights>> perfect_balanced_tree = std::make_unique<PBT<float, float, max_lights>>(*lights);
	// check time without cache misses
	perfect_balanced_tree->regenerate(*lights);
	perfect_balanced_tree->print();

	// lightcuts object
	LightCut<float, float, max_lights> lc = LightCut<float, float, max_lights>();

	// output vector
	std::vector<size_t> cuts;

	// misc scene data
	UBO ubo{ glm::vec3(1.0f), glm::vec3(0.2f), glm::vec3(0.85f), glm::vec3(0.0f), glm::vec3(0.2f) };


	
	// generate cuts
	const auto t1 = std::chrono::high_resolution_clock::now();
	for (uint32_t offset = 0; offset < 120000; offset += 30)
	{
		lc.generate_cut(*perfect_balanced_tree, 10, glm::vec3(static_cast<float>((50 * offset) % 70), 200.0f, 10.0f), ubo, cuts);
	}
	const auto t2 = std::chrono::high_resolution_clock::now();

	const std::chrono::duration<double, std::milli> ms_double = t2 - t1;
	std::cout << ms_double.count() << "ms for " << 120000.0f / 34.2347f << " iterations" << std::endl;
	
	return 0;
}
