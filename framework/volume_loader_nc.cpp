#include "Volume_loader_nc.hpp"
#include <netcdf>
#include <stdexcept>

using namespace netCDF;

// Helper function to get the variable representing the volume data
NcVar Volume_loader_nc::get_volume_variable(const std::string& file_path) const {
    NcFile dataFile(file_path, NcFile::read);

    // Assuming the volume data is stored in a variable named "volume"
    // Modify this according to your NetCDF structure
    NcVar volumeVar = dataFile.getVar("volume");
    if (volumeVar.isNull()) {
        throw std::runtime_error("Volume data not found in the NetCDF file.");
    }
    return volumeVar;
}

glm::ivec3 Volume_loader_nc::get_dimensions(const std::string& file_path) const {
    NcVar volumeVar = get_volume_variable(file_path);

    auto dims = volumeVar.getDims();
    if (dims.size() != 3) {
        throw std::runtime_error("Volume data is expected to be 3D.");
    }

    return glm::ivec3(static_cast<int>(dims[0].getSize()),
        static_cast<int>(dims[1].getSize()),
        static_cast<int>(dims[2].getSize()));
}

unsigned Volume_loader_nc::get_channel_count(const std::string& file_path) const {
    // For simplicity, assuming one channel
    return 1;
}

unsigned Volume_loader_nc::get_bit_per_channel(const std::string& file_path) const {
    NcVar volumeVar = get_volume_variable(file_path);

    // Assuming the data type is short, float, or double
    auto type = volumeVar.getType();
    if (type == ncShort) {
        return 16;
    }
    else if (type == ncFloat) {
        return 32;
    }
    else if (type == ncDouble) {
        return 64;
    }
    else {
        throw std::runtime_error("Unsupported data type in the NetCDF file.");
    }
}

volume_data_type Volume_loader_nc::load_volume(const std::string& file_path) {
    NcVar volumeVar = get_volume_variable(file_path);
    glm::ivec3 dimensions = get_dimensions(file_path);

    volume_data_type data(dimensions.x * dimensions.y * dimensions.z);

    // Read the data
    volumeVar.getVar(data.data());

    return data;
}