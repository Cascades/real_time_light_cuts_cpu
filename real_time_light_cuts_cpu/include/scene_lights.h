#pragma once
#include <stdexcept>
#include <vector>
#include <array>

#include "colors.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace ml
{
    template<size_t max_lights>
    class SceneLights
    {
    private:
        struct Light
        {
            glm::vec4 position;
            glm::vec4 color;
        };

        std::array<Light, max_lights> lights;
        std::array<glm::mat4, max_lights> light_model_matrices;
        std::array<glm::vec4, max_lights> light_colors;

        uint32_t num_lights = 70;
        float lights_height = 3.0f;

    	// calculates a regular grid of lights
        void calculate_light_positions()
        {
            for (uint32_t light_index = 0; light_index < num_lights; ++light_index)
            {
            	// position calculation
                float x_pos = -1000.0f + ((light_index % 10) * (2000.0f / static_cast<float>(std::min(num_lights, 10u))));
                float y_pos = lights_height;
                float max_rows = static_cast<float>((num_lights / 10)) - 1.0f;
                float curr_row = static_cast<float>((light_index / 10));
                float z_pos = -((70.0f * max_rows) / 2.0f) + (curr_row * 70.0f) - 37.0f;

            	// root bounding box calculation
                x_bounds[1] = glm::max(x_pos, x_bounds[1]);
                x_bounds[0] = glm::min(x_pos, x_bounds[0]);
                y_bounds[1] = glm::max(y_pos, y_bounds[1]);
                y_bounds[0] = glm::min(y_pos, y_bounds[0]);
                z_bounds[1] = glm::max(z_pos, z_bounds[1]);
                z_bounds[0] = glm::min(z_pos, z_bounds[0]);

            	// populate data blocks
                lights[light_index].position = glm::vec4(x_pos, y_pos, z_pos, 1.0);
                lights[light_index].color = glm::vec4(ml::utils::hsv_to_rgb(glm::vec3(light_index * (1.0f / num_lights), 1.0, 1.0)), 1.0);
                light_colors[light_index] = glm::vec4(ml::utils::hsv_to_rgb(glm::vec3(light_index * (1.0f / num_lights), 1.0, 1.0)), 1.0);
                light_model_matrices[light_index] = glm::mat4(1.0f);
                light_model_matrices[light_index] = glm::translate(light_model_matrices[light_index], glm::vec3(x_pos, y_pos, z_pos));
            }
        }

    public:
    	// root bounding box
        glm::vec2 x_bounds = glm::vec2(0.0f);
        glm::vec2 y_bounds = glm::vec2(0.0f);
        glm::vec2 z_bounds = glm::vec2(0.0f);
    	
        SceneLights() :
            lights(),
            light_model_matrices(),
            light_colors()
        {};

    	// usually more ot this function (generate gpu buffers)
        void initialise()
        {
            calculate_light_positions();
        }

    	// total size of array
        constexpr size_t size() const noexcept
        {
            return lights.size();
        }

    	// get total size of array in bytes
        constexpr size_t size_bytes() const noexcept
        {
            return size() * sizeof(Light);
        }

    	// get light data
        constexpr Light const* data() const noexcept
        {
            return lights.data();
        }

    	// get number of current lights
        uint32_t const& get_num_lights() const noexcept
        {
            return num_lights;
        }

    	// set number of current lights
        void set_num_lights(uint32_t const& new_num_lights)
        {
            if (new_num_lights > max_lights)
            {
                throw std::runtime_error("num_lights > max_lights");
            }
            num_lights = new_num_lights;
        }

    	// get the maximum possible lights
        constexpr size_t get_max_lights() const noexcept
        {
            return max_lights;
        }

    	// sets heights of lights along y axis
        void set_light_heights(float const& new_light_heights)
        {
            lights_height = new_light_heights;
        }

        friend class UI;
    };
}
