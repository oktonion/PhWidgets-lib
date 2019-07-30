#include "Image.h"

#include <photon/PxImage.h>

#include "service/stdex/stdex.h"

#include <ios>

using namespace PhWidgets;
using namespace PhWidgets::Drawing;

namespace
{
    static const PhImage_t dummy_image;
}

Image::Image(const PhImage_t &image):
    _image(nullptr)
{ 
    if(&image != &dummy_image)
    {
        PhImage_t tmp = image;
        _image = PiDuplicateImage(&tmp, Pi_SHMEM);
    }
}

Image::Image(const Image &other):
    _image(other._image)
{ }

Image Image::FromFile(std::string filename)
{
    Image result(dummy_image);

    result._image = PxLoadImage(filename.c_str(), NULL);

    if(NULL == result._image)
        throw(std::ios_base::failure(std::string("PhWidgets::Image: cannot load the file")));

    result._image->flags |= Ph_RELEASE_IMAGE_ALL;

    return result;
}


Image::operator PhImage_t () const
{
    return (*PiDuplicateImage(_image, Pi_SHMEM));
}