// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// VideoCaptureDevice is the abstract base class for realizing video capture
// device support in Chromium. It provides the interface for OS dependent
// implementations.
// The class is created and functions are invoked on a thread owned by
// VideoCaptureManager. Capturing is done on other threads, depending on the OS
// specific implementation.

#ifndef MEDIA_CAPTURE_VIDEO_VIDEO_CAPTURE_DEVICE_H_
#define MEDIA_CAPTURE_VIDEO_VIDEO_CAPTURE_DEVICE_H_

#include <stddef.h>
#include <stdint.h>

#include <list>
#include <memory>
#include <string>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/single_thread_task_runner.h"
#include "base/time/time.h"
#include "build/build_config.h"
#include "media/base/video_frame.h"
#include "media/capture/capture_export.h"
//#include "media/capture/mojo/image_capture.mojom.h"
#include "media/capture/video/scoped_result_callback.h"
#include "media/capture/video/video_capture_buffer_handle.h"
#include "media/capture/video/video_capture_device_descriptor.h"
#include "media/capture/video_capture_types.h"
#include "ui/gfx/gpu_memory_buffer.h"

namespace tracked_objects {
class Location;
} // namespace tracked_objects

namespace media {

class CAPTURE_EXPORT FrameBufferPool {
public:
    virtual ~FrameBufferPool() { }

    virtual void SetBufferHold(int buffer_id) = 0;
    virtual void ReleaseBufferHold(int buffer_id) = 0;
};

class CAPTURE_EXPORT VideoFrameConsumerFeedbackObserver {
public:
    virtual ~VideoFrameConsumerFeedbackObserver() { }

    // During processing of a video frame, consumers may report back their
    // utilization level to the source device. The device may use this information
    // to adjust the rate of data it pushes out. Values are interpreted as
    // follows:
    // Less than 0.0 is meaningless and should be ignored.  1.0 indicates a
    // maximum sustainable utilization.  Greater than 1.0 indicates the consumer
    // is likely to stall or drop frames if the data volume is not reduced.
    //
    // Example: In a system that encodes and transmits video frames over the
    // network, this value can be used to indicate whether sufficient CPU
    // is available for encoding and/or sufficient bandwidth is available for
    // transmission over the network.  The maximum of the two utilization
    // measurements would be used as feedback.
    //
    // The parameter |frame_feedback_id| must match a |frame_feedback_id|
    // previously sent out by the VideoCaptureDevice we are giving feedback about.
    // It is used to indicate which particular frame the reported utilization
    // corresponds to.
    virtual void OnUtilizationReport(int frame_feedback_id, double utilization) { }

    /*static*/ const double kNoUtilizationRecorded = -1.0;
};

class CAPTURE_EXPORT VideoCaptureDevice
    : public VideoFrameConsumerFeedbackObserver {
public:
    // Interface defining the methods that clients of VideoCapture must have. It
    // is actually two-in-one: clients may implement OnIncomingCapturedData() or
    // ReserveOutputBuffer() + OnIncomingCapturedVideoFrame(), or all of them.
    // All clients must implement OnError().
    class CAPTURE_EXPORT Client {
    public:
        // Move-only type representing access to a buffer handle as well as
        // read-write permission to its contents.
        class CAPTURE_EXPORT Buffer {
        public:
            // Destructor-only interface for encapsulating scoped access permission to
            // a Buffer.
            class CAPTURE_EXPORT ScopedAccessPermission {
            public:
                virtual ~ScopedAccessPermission() { }
            };

            class CAPTURE_EXPORT HandleProvider {
            public:
                virtual ~HandleProvider() { }
                //virtual mojo::ScopedSharedBufferHandle GetHandleForInterProcessTransit() = 0;
                virtual base::SharedMemoryHandle GetNonOwnedSharedMemoryHandleForLegacyIPC() = 0;
                virtual std::unique_ptr<VideoCaptureBufferHandle>
                GetHandleForInProcessAccess() = 0;
            };

            Buffer();
            Buffer(int buffer_id,
                int frame_feedback_id,
                std::unique_ptr<HandleProvider> handle_provider,
                std::unique_ptr<ScopedAccessPermission> access_permission);
            ~Buffer();
            Buffer(Buffer&& other);
            Buffer& operator=(Buffer&& other);

            bool is_valid() const { return handle_provider_ != nullptr; }
            int id() const { return id_; }
            int frame_feedback_id() const { return frame_feedback_id_; }
            HandleProvider* handle_provider() const { return handle_provider_.get(); }

        private:
            std::unique_ptr<HandleProvider> handle_provider_;
            std::unique_ptr<ScopedAccessPermission> access_permission_;
            int id_;
            int frame_feedback_id_;

            DISALLOW_COPY_AND_ASSIGN(Buffer);
        };

        virtual ~Client() { }

        // Captured a new video frame, data for which is pointed to by |data|.
        //
        // The format of the frame is described by |frame_format|, and is assumed to
        // be tightly packed. This method will try to reserve an output buffer and
        // copy from |data| into the output buffer. If no output buffer is
        // available, the frame will be silently dropped. |reference_time| is
        // system clock time when we detect the capture happens, it is used for
        // Audio/Video sync, not an exact presentation time for playout, because it
        // could contain noise. |timestamp| measures the ideal time span between the
        // first frame in the stream and the current frame; however, the time source
        // is determined by the platform's device driver and is often not the system
        // clock, or even has a drift with respect to system clock.
        // |frame_feedback_id| is an identifier that allows clients to refer back to
        // this particular frame when reporting consumer feedback via
        // OnConsumerReportingUtilization(). This identifier is needed because
        // frames are consumed asynchronously and multiple frames can be "in flight"
        // at the same time.
        virtual void OnIncomingCapturedData(const uint8_t* data,
            int length,
            const VideoCaptureFormat& frame_format,
            int clockwise_rotation,
            base::TimeTicks reference_time,
            base::TimeDelta timestamp,
            int frame_feedback_id = 0)
            = 0;

        // Reserve an output buffer into which contents can be captured directly.
        // The returned Buffer will always be allocated with a memory size suitable
        // for holding a packed video frame with pixels of |format| format, of
        // |dimensions| frame dimensions. It is permissible for |dimensions| to be
        // zero; in which case the returned Buffer does not guarantee memory
        // backing, but functions as a reservation for external input for the
        // purposes of buffer throttling.
        //
        // The buffer stays reserved for use by the caller as long as it
        // holds on to the contained |buffer_read_write_permission|.
        virtual Buffer ReserveOutputBuffer(const gfx::Size& dimensions,
            VideoPixelFormat format,
            VideoPixelStorage storage,
            int frame_feedback_id)
            = 0;

        // Provides VCD::Client with a populated Buffer containing the content of
        // the next video frame. The |buffer| must originate from an earlier call to
        // ReserveOutputBuffer().
        // See OnIncomingCapturedData for details of |reference_time| and
        // |timestamp|.
        virtual void OnIncomingCapturedBuffer(Buffer buffer,
            const VideoCaptureFormat& format,
            base::TimeTicks reference_time,
            base::TimeDelta timestamp)
            = 0;

        // Extended version of OnIncomingCapturedBuffer() allowing clients to
        // pass a custom |visible_rect| and |additional_metadata|.
        virtual void OnIncomingCapturedBufferExt(
            Buffer buffer,
            const VideoCaptureFormat& format,
            base::TimeTicks reference_time,
            base::TimeDelta timestamp,
            gfx::Rect visible_rect,
            const VideoFrameMetadata& additional_metadata)
            = 0;

        // Attempts to reserve the same Buffer provided in the last call to one of
        // the OnIncomingCapturedBufferXXX() methods. This will fail if the content
        // of the Buffer has not been preserved, or if the |dimensions|, |format|,
        // or |storage| disagree with how it was reserved via ReserveOutputBuffer().
        // When this operation fails, nullptr will be returned.
        virtual Buffer ResurrectLastOutputBuffer(const gfx::Size& dimensions,
            VideoPixelFormat format,
            VideoPixelStorage storage,
            int new_frame_feedback_id)
            = 0;

        // An error has occurred that cannot be handled and VideoCaptureDevice must
        // be StopAndDeAllocate()-ed. |reason| is a text description of the error.
        virtual void OnError(const tracked_objects::Location& from_here,
            const std::string& reason)
            = 0;

        // VideoCaptureDevice requests the |message| to be logged.
        virtual void OnLog(const std::string& message) { }

        // Returns the current buffer pool utilization, in the range 0.0 (no buffers
        // are in use by producers or consumers) to 1.0 (all buffers are in use).
        virtual double GetBufferPoolUtilization() const = 0;
    };

    ~VideoCaptureDevice() override;

    // Prepares the video capturer for use. StopAndDeAllocate() must be called
    // before the object is deleted.
    virtual void AllocateAndStart(const VideoCaptureParams& params,
        std::unique_ptr<Client> client)
        = 0;

    // In cases where the video capturer self-pauses (e.g., a screen capturer
    // where the screen's content has not changed in a while), consumers may call
    // this to request a "refresh frame" be delivered to the Client.  This is used
    // in a number of circumstances, such as:
    //
    //   1. An additional consumer of video frames is starting up and requires a
    //      first frame (as opposed to not receiving a frame for an indeterminate
    //      amount of time).
    //   2. A few repeats of the same frame would allow a lossy video encoder to
    //      improve the video quality of unchanging content.
    //
    // The default implementation is a no-op. VideoCaptureDevice implementations
    // are not required to honor this request, especially if they do not
    // self-pause and/or if honoring the request would cause them to exceed their
    // configured maximum frame rate. Any VideoCaptureDevice that does self-pause,
    // however, should provide an implementation of this method that makes
    // reasonable attempts to honor these requests.
    //
    // Note: This should only be called after AllocateAndStart() and before
    // StopAndDeAllocate(). Otherwise, its behavior is undefined.
    virtual void RequestRefreshFrame() { }

    // Optionally suspends frame delivery. The VideoCaptureDevice may or may not
    // honor this request. Thus, the caller cannot assume frame delivery will
    // actually stop. Even if frame delivery is suspended, this might not take
    // effect immediately.
    //
    // The purpose of this is to quickly place the device into a state where it's
    // resource utilization is minimized while there are no frame consumers; and
    // then quickly resume once a frame consumer is present.
    //
    // Note: This should only be called after AllocateAndStart() and before
    // StopAndDeAllocate(). Otherwise, its behavior is undefined.
    virtual void MaybeSuspend() { }

    // Resumes frame delivery, if it was suspended. If frame delivery was not
    // suspended, this is a no-op, and frame delivery will continue.
    //
    // Note: This should only be called after AllocateAndStart() and before
    // StopAndDeAllocate(). Otherwise, its behavior is undefined.
    virtual void Resume() { }

    // Deallocates the video capturer, possibly asynchronously.
    //
    // This call requires the device to do the following things, eventually: put
    // hardware into a state where other applications could use it, free the
    // memory associated with capture, and delete the |client| pointer passed into
    // AllocateAndStart.
    //
    // If deallocation is done asynchronously, then the device implementation must
    // ensure that a subsequent AllocateAndStart() operation targeting the same ID
    // would be sequenced through the same task runner, so that deallocation
    // happens first.
    virtual void StopAndDeAllocate() = 0;

//     // Retrieve the photo capabilities of the device (e.g. zoom levels etc).
//     using GetPhotoCapabilitiesCallback = ScopedResultCallback<base::Callback<void(mojom::PhotoCapabilitiesPtr)>>;
//     virtual void GetPhotoCapabilities(GetPhotoCapabilitiesCallback callback);
// 
//     using SetPhotoOptionsCallback = ScopedResultCallback<base::Callback<void(bool)>>;
//     virtual void SetPhotoOptions(mojom::PhotoSettingsPtr settings, SetPhotoOptionsCallback callback);
// 
//     // Asynchronously takes a photo, possibly reconfiguring the capture objects
//     // and/or interrupting the capture flow. Runs |callback| on the thread
//     // where TakePhoto() is called, if the photo was successfully taken.
//     using TakePhotoCallback = ScopedResultCallback<base::Callback<void(mojom::BlobPtr blob)>>;
//     virtual void TakePhoto(TakePhotoCallback callback);

    // Gets the power line frequency, either from the params if specified by the
    // user or from the current system time zone.
    PowerLineFrequency GetPowerLineFrequency(
        const VideoCaptureParams& params) const;

private:
    // Gets the power line frequency from the current system time zone if this is
    // defined, otherwise returns 0.
    PowerLineFrequency GetPowerLineFrequencyForLocation() const;
};

} // namespace media

#endif // MEDIA_CAPTURE_VIDEO_VIDEO_CAPTURE_DEVICE_H_
