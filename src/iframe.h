#pragma once

#include <stdexcept>
#include <vector>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

#include "global.h"

// technically I'm implementing IFrame for now...
class IFrame
{
public:
    // todo movie filename
    IFrame(std::vector<char> data);
    std::vector<uint8_t> *getFramebuffer();

private:
    std::vector<uint8_t> framebuffer;

    // TODO: this only makes sense on little endian machines, on big endian use 0RGB
    const AVPixelFormat targetPixelFormat = AV_PIX_FMT_BGR0;

    void decode(AVCodecContext *ctx, AVFrame *frame, AVPacket *pkt);

    /**
     * @brief converts AVFrame from one pixel format to another
     *
     */
    AVFrame *convertFrame(AVFrame *frame, AVPixelFormat dstFormat);
    AVFrame *allocateFrame(int width, int height, AVPixelFormat pixelFormat);
};
