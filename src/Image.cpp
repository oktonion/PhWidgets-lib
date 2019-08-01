#include "Image.h"

#include <photon/PxImage.h>

#include "service/stdex/stdex.h"

#include <ios>
#include <map>

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

namespace
{
    stdex::mutex error_messages_mtx;
    std::map<stdex::thread::id, std::string> error_messages;

    stdex::mutex warning_messages_mtx;
    std::map<stdex::thread::id, std::string> warning_messages;

    static void *warning( char *msg )
    {
        stdex::unique_lock<stdex::mutex> lock(warning_messages_mtx);
        warning_messages[stdex::this_thread::get_id()] = msg;

        return NULL;
    }

    static void *error( char *msg )
    {
        stdex::unique_lock<stdex::mutex> lock(error_messages_mtx);
        error_messages[stdex::this_thread::get_id()] = msg;
        
        return NULL;
    }

    static void *progress( int percent )
    {
        return NULL;
    }
}


Image Image::FromFile(std::string filename)
{
    ImageInfo image_info;

    PxMethods_t methods;

    std::memset( &methods, 0, sizeof( PxMethods_t ) );
    methods.flags = PX_LOAD;

    methods.px_warning  = warning;
    methods.px_error    = error;
    methods.px_progress = progress;

    image_info.image = PxLoadImage(filename.c_str(), &methods);

    if(NULL == image_info.image)
    {
        std::string msg;
        {
            stdex::unique_lock<stdex::mutex> lock(error_messages_mtx);
            msg = error_messages[stdex::this_thread::get_id()];
        }

        if(msg.length() == 0)
        {
            msg = stdex::generic_category().message(errno);
        }

        throw(std::ios_base::failure(std::string("PhWidgets::Image: ") + msg));
    }

    image_info.image->flags |= Ph_RELEASE_IMAGE_ALL;

    return Image(image_info);
}


Image::operator PhImage_t () const
{
    return (*PiDuplicateImage(_image, Pi_SHMEM));
}