#ifndef VOLUME_LOADER_NC_HPP
#define VOLUME_LOADER_NC_HPP

#include "data_types_fwd.hpp"

#include <netcdf>
#include <array>
#include <string>
#include <glm/vec3.hpp>

class Volume_loader_nc
{
public:
	Volume_loader_nc() {}

	volume_data_type load_volume(const std::string& file_path);

	glm::ivec3 get_dimensions(const std::string& file_path) const;
	unsigned get_channel_count(const std::string& file_path) const;
	unsigned get_bit_per_channel(const std::string& file_path) const;

private:
	netCDF::NcVar get_volume_variable(const std::string& file_path) const;
};

#endif // VOLUME_LOADER_NC_HPP