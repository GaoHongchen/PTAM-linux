#ifndef __Image_Process_H
#define __Image_Process_H

#include <vector>

#include <cvd/image.h>
#include <cvd/byte.h>
#include <cvd/utility.h>
#include <TooN/TooN.h>

using namespace CVD;
using namespace TooN;

class ImageProcess
{
public:
    ImageProcess() {}
    CVD::Image<CVD::byte> GetImageROI(BasicImage<byte> &im, ImageRef irPos, CVD::ImageRef irSize);
    static double ShiTomasiScoreAtPoint(CVD::BasicImage<CVD::byte> &image, int nHalfBoxSize, CVD::ImageRef irCenter);
    inline int SSDAtPoint(CVD::BasicImage<byte> &im, const CVD::ImageRef &ir, CVD::Image<byte> &imTemplate); // Score function
};

class MiniPatch : public ImageProcess
{
public:
    MiniPatch():mirPatchSize(CVD::ImageRef(9,9)){}
    void SampleFromImage(CVD::ImageRef irPos, CVD::BasicImage<CVD::byte> &im);  // Copy pixels out of source image
    bool FindPatch(CVD::ImageRef &irPos,           // Find patch in a new image
                   CVD::BasicImage<CVD::byte> &im,
                   int nRange,
                   std::vector<CVD::ImageRef> &vCorners,
                   std::vector<int> *pvRowLUT = NULL,
                   int nMaxSSD = 9999);

private:
    CVD::ImageRef mirPatchSize;
    CVD::Image<CVD::byte> mimOrigPatch;  // Original pixels
};

#endif