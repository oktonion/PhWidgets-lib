#include "Image.h"

#include <photon/PxImage.h>

#include "service/stdex/stdex.h"

#include <ios>

using namespace PhWidgets;
using namespace PhWidgets::Drawing;

Image::Image(const PhImage_t &image):
    Size(image.size),
    Width(Size.w),
    Height(Size.h),
    _image(nullptr)
{ 
    PhImage_t tmp = image;
    _image = PiDuplicateImage(&tmp, Pi_SHMEM);
}

struct Image::ImageInfo
{
    PhImage_t *image;
};

Image::Image(const ImageInfo &image_info):
    Size(image_info.image->size),
    Width(Size.w),
    Height(Size.h),
    _image(image_info.image)
{ }

Image::Image(const Image &other):
    Size(other.Size),
    Width(other.Width),
    Height(other.Height),
    _image(other._image)
{ }

Image Image::FromFile(std::string filename)
{
    ImageInfo image_info;

    image_info.image = PxLoadImage(filename.c_str(), NULL);

    if(NULL == image_info.image)
        throw(std::ios_base::failure(std::string("PhWidgets::Image: cannot load the file")));

    image_info.image->flags |= Ph_RELEASE_IMAGE_ALL;

    return Image(image_info);
}


Image::operator PhImage_t () const
{
    return (*PiDuplicateImage(_image, Pi_SHMEM));
}