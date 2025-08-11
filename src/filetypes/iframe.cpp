#include "iframe.h"

namespace filetypes
{
    IFrame::IFrame(std::vector<char> data)
    {
        auto pkt = av_packet_alloc();
        if (!pkt)
        {
            throw std::runtime_error{"could not alloc packet"};
        }

        auto codec = avcodec_find_decoder(AV_CODEC_ID_MPEG2VIDEO);
        if (!codec)
        {
            throw std::runtime_error{"could not load video codec"};
        }

        auto parser = av_parser_init(codec->id);
        if (!parser)
        {
            throw std::runtime_error{"parser not found"};
        }

        auto c = avcodec_alloc_context3(codec);
        if (!c)
        {
            throw std::runtime_error{"could not allocate video codec context"};
        }

        if (avcodec_open2(c, codec, NULL) < 0)
        {
            throw std::runtime_error{"could not open codec"};
        }

        auto frame = av_frame_alloc();
        if (!frame)
        {
            throw std::runtime_error{"could not allocate video frame\n"};
        }

        std::vector<uint8_t> buffer{data.begin(), data.end()};

        // decode
        auto ret = av_parser_parse2(
            parser,
            c,
            &pkt->data,
            &pkt->size,
            buffer.data(),
            data.size(),
            AV_NOPTS_VALUE,
            AV_NOPTS_VALUE,
            0);
        if (ret < 0)
        {
            throw std::runtime_error{"could not parse av data"};
        }

        if (pkt->size)
            decode(c, frame, pkt);

        /* flush the decoder */
        decode(c, frame, nullptr);

        av_parser_close(parser);
        avcodec_free_context(&c);
        av_frame_free(&frame);
        av_packet_free(&pkt);
    }

    std::vector<uint8_t> *IFrame::getFramebuffer()
    {
        return &framebuffer;
    }

    void IFrame::decode(AVCodecContext *ctx, AVFrame *frame, AVPacket *pkt)
    {
        auto ret = avcodec_send_packet(ctx, pkt);
        if (ret < 0)
        {
            throw std::runtime_error{"could not sent packet to decode"};
        }

        while (ret >= 0)
        {
            ret = avcodec_receive_frame(ctx, frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            {
                return;
            }
            else if (ret < 0)
            {
                throw std::runtime_error{"couldn't decode frame"};
            }
            // frame is ready
            frame = convertFrame(frame, targetPixelFormat);
            framebuffer.assign(frame->data[0], &frame->data[0][frame->height * frame->linesize[0]]);
        }
    }

    AVFrame *IFrame::convertFrame(AVFrame *frame, AVPixelFormat dstFormat)
    {
        if (frame->format == dstFormat)
        {
            return frame;
        }

        auto dst = allocateFrame(frame->width, frame->height, dstFormat);
        // TODO: yuv to RGB is accelerated, but yuv -> ARGB/0RGB is not, check if this will impact us
        auto conversion = sws_getContext(
            frame->width,
            frame->height,
            static_cast<AVPixelFormat>(frame->format),
            frame->width,
            frame->height,
            dstFormat,
            SWS_FAST_BILINEAR,
            nullptr,
            nullptr,
            nullptr);
        sws_scale(conversion, frame->data, frame->linesize, 0, frame->height, dst->data, dst->linesize);
        sws_freeContext(conversion);
        return dst;
    }

    AVFrame *IFrame::allocateFrame(int width, int height, AVPixelFormat pixelFormat)
    {
        auto frame = av_frame_alloc();
        if (frame == nullptr)
        {
            throw std::runtime_error{"cannot allocate av frame"};
        }
        if (av_image_alloc(frame->data, frame->linesize, width, height, pixelFormat, 1) < 0)
        {
            throw std::runtime_error{"cannot allocate av image"};
        }
        frame->width = width;
        frame->height = height;
        frame->format = pixelFormat;

        return frame;
    }
}
